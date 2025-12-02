/*******************************************************************************
    Description : Event Manager header file

            It provides the various event notification facility.
            The event notification mechanism can be sent between threads/
            process (parent-child) or even between unrelated process

    Notes : Event Manager module will provide the below functionality :   
            - A module/thread can register for any number of events.
            - A module/thread can unicast/multicast/broadcast an event
            - A event can be serviced now/deferred for later

    It will make use of eventfd() and SCOM to handle all the above functionalities.
    It is very rich than the taskhandler libraries event notification mechanism

    Resources : http://pgplus1628.github.io/epoll-eventfd.html
                http://man7.org/linux/man-pages/man2/eventfd.2.html

*******************************************************************************/

#ifndef INCLUDE_EVENT_MANAGER_H__
#define INCLUDE_EVENT_MANAGER_H__




/*******************************************************************************/
/*              Public Functions                                               */
/*******************************************************************************/



#endif /* INCLUDE_EVENT_MANAGER_H__ */
