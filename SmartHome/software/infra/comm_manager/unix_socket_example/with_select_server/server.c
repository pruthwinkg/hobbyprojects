#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>

#define SERVER_PORT  12345
#define SOCKET_FILE_PATH "test.server.socket"

#define TRUE             1
#define FALSE            0

main (int argc, char *argv[])
{
   int    i, len, rc, on = 1;
   int    listen_sd, max_sd, new_sd;
   int    desc_ready, end_server = FALSE;
   int    close_conn;
   char   buffer[80];
   struct sockaddr_un addr;
   struct timeval      timeout;
   fd_set              master_set, working_set;
    int flags = 0;

   /*************************************************************/
   /* Create an AF_INET6 stream socket to receive incoming      */
   /* connections on                                            */
   /*************************************************************/
   listen_sd = socket(AF_UNIX, SOCK_STREAM, 0);
   if (listen_sd < 0)
   {
      perror("socket() failed");
      exit(-1);
   }

   /*************************************************************/
   /* Allow socket descriptor to be reuseable                   */
   /*************************************************************/
   rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on));
   if (rc < 0)
   {
      perror("setsockopt() failed");
      close(listen_sd);
      exit(-1);
   }

   /*************************************************************/
   /* Set socket to be nonblocking. All of the sockets for      */
   /* the incoming connections will also be nonblocking since   */
   /* they will inherit that state from the listening socket.   */
   /*************************************************************/
//   rc = ioctl(listen_sd, FIONBIO, (char *)&on);
    rc = fcntl(listen_sd, F_SETFL, (fcntl(listen_sd, F_GETFL, 0) | O_NONBLOCK));
    if (rc < 0)
   {
      perror("fcntl() failed");
      close(listen_sd);
      exit(-1);
   }

    if(fcntl(listen_sd, F_GETFL) & O_NONBLOCK) {
    // socket is non-blocking
    printf("Sokcet set to non-blocking mode\n");
    } else {
    printf("Sokcet set to blocking mode\n");

    }


   /*************************************************************/
   /* Bind the socket                                           */
   /*************************************************************/
   memset(&addr, 0, sizeof(addr));
   addr.sun_family      = AF_UNIX;
   strcpy(addr.sun_path, SOCKET_FILE_PATH);

    unlink(SOCKET_FILE_PATH);

   rc = bind(listen_sd,
             (struct sockaddr *)&addr, sizeof(addr));
   if (rc < 0)
   {
      perror("bind() failed");
      close(listen_sd);
      exit(-1);
   }



   /*************************************************************/
   /* Set the listen back log                                   */
   /*************************************************************/
   rc = listen(listen_sd, 32);
   if (rc < 0)
   {
      perror("listen() failed");
      close(listen_sd);
      exit(-1);
   }

   /*************************************************************/
   /* Initialize the master fd_set                              */
   /*************************************************************/
   FD_ZERO(&master_set);
   max_sd = listen_sd;
   FD_SET(listen_sd, &master_set);

   /*************************************************************/
   /* Initialize the timeval struct to 3 minutes.  If no        */
   /* activity after 3 minutes this program will end.           */
   /*************************************************************/
   timeout.tv_sec  = 3 * 60;
   timeout.tv_usec = 0;

   /*************************************************************/
   /* Loop waiting for incoming connects or for incoming data   */
   /* on any of the connected sockets.                          */
   /*************************************************************/
   do
   {
    printf("master_set %d, max_sd = %d\n", master_set, max_sd);

      /**********************************************************/
      /* Copy the master fd_set over to the working fd_set.     */
      /**********************************************************/
      memcpy(&working_set, &master_set, sizeof(master_set));

      /**********************************************************/
      /* Call select() and wait 3 minutes for it to complete.   */
      /**********************************************************/
      printf("Waiting on select()...\n");
      rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);

      /**********************************************************/
      /* Check to see if the select call failed.                */
      /**********************************************************/
      if (rc < 0)
      {
         perror("  select() failed");
         break;
      }

      /**********************************************************/
      /* Check to see if the 3 minute time out expired.         */
      /**********************************************************/
      if (rc == 0)
      {
         printf("  select() timed out.  End program.\n");
         break;
      }

      /**********************************************************/
      /* One or more descriptors are readable.  Need to         */
      /* determine which ones they are.                         */
      /**********************************************************/
      desc_ready = rc;
      printf("Entering for loop, desc_ready = %d\n", desc_ready);
      for (i=0; i <= max_sd  &&  desc_ready > 0; ++i)
      {
         /*******************************************************/
         /* Check to see if this descriptor is ready            */
         /*******************************************************/
         if (FD_ISSET(i, &working_set))
         {
            /****************************************************/
            /* A descriptor was found that was readable - one   */
            /* less has to be looked for.  This is being done   */
            /* so that we can stop looking at the working set   */
            /* once we have found all of the descriptors that   */
            /* were ready.                                      */
            /****************************************************/
            desc_ready -= 1;

            /****************************************************/
            /* Check to see if this is the listening socket     */
            /****************************************************/
            if (i == listen_sd)
            {
               printf("  Listening socket is readable\n");
               /*************************************************/
               /* Accept all incoming connections that are      */
               /* queued up on the listening socket before we   */
               /* loop back and call select again.              */
               /*************************************************/
               do
               {
                  /**********************************************/
                  /* Accept each incoming connection.  If       */
                  /* accept fails with EWOULDBLOCK, then we     */
                  /* have accepted all of them.  Any other      */
                  /* failure on accept will cause us to end the */
                  /* server.                                    */
                  /**********************************************/
                  new_sd = accept(listen_sd, NULL, NULL);
                  if (new_sd < 0)
                  {
                     if (errno != EWOULDBLOCK)
                     {
                        perror("  accept() failed");
                        end_server = TRUE;
                     }
                     break;
                  }

                rc = fcntl(new_sd, F_SETFL, (fcntl(new_sd, F_GETFL, 0) | O_NONBLOCK));
               if (rc < 0)
               {
                  perror("fcntl() failed");
                  close(new_sd);
                  exit(-1);
               }


                  /**********************************************/
                  /* Add the new incoming connection to the     */
                  /* master read set                            */
                  /**********************************************/
                  printf("  New incoming connection - %d\n", new_sd);
                  FD_SET(new_sd, &master_set);
                  if (new_sd > max_sd)
                     max_sd = new_sd;

                  /**********************************************/
                  /* Loop back up and accept another incoming   */
                  /* connection                                 */
                  /**********************************************/
               } while (new_sd != -1);
            }

            /****************************************************/
            /* This is not the listening socket, therefore an   */
            /* existing connection must be readable             */
            /****************************************************/
            else
            {
               printf("  Descriptor %d is readable\n", i);
               close_conn = FALSE;
               /*************************************************/
               /* Receive all incoming data on this socket      */
               /* before we loop back and call select again.    */
               /*************************************************/
               do
               {

    if(fcntl(i, F_GETFL) & O_NONBLOCK) {
    // socket is non-blocking
    printf("Sokcet %d set to non-blocking mode\n", i);
    } else {
    printf("Sokcet %d set to blocking mode\n", i);

    }


                  /**********************************************/
                  /* Receive data on this connection until the  */
                  /* recv fails with EWOULDBLOCK.  If any other */
                  /* failure occurs, we will close the          */
                  /* connection.                                */
                  /**********************************************/
                  printf("calling receive.....\n");
                  rc = recv(i, buffer, sizeof(buffer), 0);
                  printf("done with recieve.... rc = %d\n",rc);
                  if (rc < 0)
                  {
                     if (errno != EWOULDBLOCK)
                     {
                        perror("  recv() failed");
                        close_conn = TRUE;
                     }
                     break;
                  }
                    printf("Received data : %s\n", buffer);
                  /**********************************************/
                  /* Check to see if the connection has been    */
                  /* closed by the client                       */
                  /**********************************************/
                  if (rc == 0)
                  {
                     printf("  Connection closed\n");
                     close_conn = TRUE;
                     break;
                  }

                  /**********************************************/
                  /* Data was received                          */
                  /**********************************************/
                  len = rc;
                  printf("  %d bytes received\n", len);

#if 1
                  /**********************************************/
                  /* Echo the data back to the client           */
                  /**********************************************/
                  printf("calling send()....\n");
                  rc = send(i, buffer, len, 0);
                  printf("done with send ... rc = %d\n", rc);
                  if (rc < 0)
                  {
                     perror("  send() failed");
                     close_conn = TRUE;
                     break;
                  }
#endif
               } while (TRUE);

               /*************************************************/
               /* If the close_conn flag was turned on, we need */
               /* to clean up this active connection.  This     */
               /* clean up process includes removing the        */
               /* descriptor from the master set and            */
               /* determining the new maximum descriptor value  */
               /* based on the bits that are still turned on in */
               /* the master set.                               */
               /*************************************************/
               if (close_conn)
               {
                  close(i);
                  FD_CLR(i, &master_set);
                  if (i == max_sd)
                  {
                     while (FD_ISSET(max_sd, &master_set) == FALSE)
                        max_sd -= 1;
                  }
               }
            } /* End of existing connection is readable */
         } /* End of if (FD_ISSET(i, &working_set)) */
      } /* End of loop through selectable descriptors */

   } while (end_server == FALSE);

   /*************************************************************/
   /* Clean up all of the sockets that are open                 */
   /*************************************************************/
   for (i=0; i <= max_sd; ++i)
   {
      if (FD_ISSET(i, &master_set))
         close(i);
   }
}
