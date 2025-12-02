#!/bin/bash

CP_PREFIXES=("smarthome-cp-")

CP_DOCKER_COMPOSE_FILE="./docker-compose.yml"

# Specify the services for which you want to remove images
CP_SERVICES=("web_app" "configuration" "telemetry" "infra" "authentication")


VIRTUAL_DP_DOCKER_COMPOSE_FILE="./virtual_dataplane/docker-compose.yml"
VIRTUAL_DP_PREFIXES=("smarthome-dpsim-")
VIRTUAL_DP_SERVICES=("light" "web_app" "test_controlplane")

function run_wipe_clean() {

    local DOCKER_COMPOSE_FILE="$1"
    local PREFIXES="$2"
    local SERVICES=("${@:3}")

    docker-compose -f $DOCKER_COMPOSE_FILE down

    # Remove dangling images (<none>)
    DOCKER_IMAGES=$(docker images --filter "dangling=true" -q --no-trunc)
    for DOCKER_IMAGE in $DOCKER_IMAGES; do
        docker rmi "$DOCKER_IMAGE"
        echo "Dangling image $DOCKER_IMAGE removed"
    done  

    for PREFIX in "${PREFIXES[@]}"; do
        for SERVICE in "${SERVICES[@]}"; do
            # Construct the full service name with the prefix
            FULL_SERVICE_NAME="${PREFIX}${SERVICE}"

            # Get the image IDs for the specified service
            IMAGE_IDS=$(docker images --format "{{.ID}}" $FULL_SERVICE_NAME)

            # Print the IMAGE_IDS
            echo "Image IDs for $FULL_SERVICE_NAME:"
            for IMAGE_ID in $IMAGE_IDS; do
                echo "$IMAGE_ID"
            done


            #Remove containers with the '-debug' suffix
            DEBUG_CONTAINERS=$(docker ps -a --format "{{.Names}}" | grep "${FULL_SERVICE_NAME}-debug")
            for DEBUG_CONTAINER in $DEBUG_CONTAINERS; do
                docker rm -f "$DEBUG_CONTAINER"
                echo "Container $DEBUG_CONTAINER removed"
            done

            # Remove the images
            for IMAGE_ID in $IMAGE_IDS; do
                docker rmi $IMAGE_ID
                echo "Image $IMAGE_ID for $FULL_SERVICE_NAME removed"
            done
        done
    done
}

function run_start_force_build() {
    local DOCKER_COMPOSE_FILE="$1"

    if [ -z "$2" ]; then
        echo "Starting all required containers"
        docker-compose -f $DOCKER_COMPOSE_FILE up -d --build --force-recreate
    else
        echo "Starting the specified service: $2"
        docker-compose -f $DOCKER_COMPOSE_FILE up -d --build --force-recreate "$2"
    fi
}

function run_restart_containers() {
    if [ -z "$1" ]; then
        echo "Restarting all required containers"
        docker-compose restart
    else
        echo "Restarting the specified service: $1"
        docker-compose restart "$1"
    fi
}

function run_start_background() {
	echo "Starting all required containers"
	docker-compose up -d
}

function run_start_shell_debugging() {
    local DOCKER_COMPOSE_FILE="$1"
    local container_name="$2"

    if [[ -z "$container_name" ]]; then
        echo "Usage: $0 -sh <container-name>"
        exit 1
    fi
    custom_container_name="smarthome-cp-$container_name-debug"
    echo "Creating a new container '$container_name' with interactive shell (Debugging only)"
    docker-compose -f $DOCKER_COMPOSE_FILE run --name "$custom_container_name" "$container_name" sh
}


function run_virtual_dataplane() {
    local sub_command="$1"    

    if [[ -z "$sub_command" ]]; then
        echo "Usage: $0 -v <sub_command>"
        exit 1
    fi

    case "$sub_command" in
        "help")
            echo "Usage: ./build.sh -v [help|all|clean|sh|rebuild|custom]"
            ;;
        "all")
            echo "Starting all required containers"
            docker-compose -f "$VIRTUAL_DP_DOCKER_COMPOSE_FILE" up -d
            ;;
        "clean")
            echo "Cleaning all required containers"
            run_wipe_clean "$VIRTUAL_DP_DOCKER_COMPOSE_FILE" "${VIRTUAL_DP_PREFIXES[@]}" "${VIRTUAL_DP_SERVICES[@]}"
            ;;
        "rebuild")    
            shift        
            local service_name="$1"
            if [[ -z "$service_name" ]]; then
                echo "Rebuilding the whole virtual dataplane"
                run_start_force_build "$VIRTUAL_DP_DOCKER_COMPOSE_FILE"
            else
                echo "Rebuilding the virtual dataplane for service $service_name"
                run_start_force_build "$VIRTUAL_DP_DOCKER_COMPOSE_FILE" "$service_name"
            fi
            ;;
        "sh")
            echo "Create a interactive shell container for debugging"
            run_start_shell_debugging "$VIRTUAL_DP_DOCKER_COMPOSE_FILE" "${2}"
        ;;              
        "custom")
            echo "Starting custom containers or performing a custom action"
            # Add your custom logic here
            ;;
        *)
            echo "Invalid subcommand: $sub_command"
            echo "Usage: ./build.sh -v [help|all|clean|rebuild|custom]"
            ;;
    esac
}


option="${1}"
case ${option} in
   -d) run_wipe_clean "$CP_DOCKER_COMPOSE_FILE" "${CP_PREFIXES[@]}" "${CP_SERVICES[@]}"
      ;;

   -f) run_start_force_build "$CP_DOCKER_COMPOSE_FILE" "${2}"
	  ;;

   -r) run_restart_containers "${2}"
	  ;;      

   -s) run_start_background
      ;;

   -v) run_virtual_dataplane "${@:2}"
      ;;

   -sh) run_start_shell_debugging "$CP_DOCKER_COMPOSE_FILE" "${2}"
      ;;

   *)
   printf "`basename ${0}`:usage:
                [-d (Does a full clean of the project)]
                [-s (Start the project)]
                [-f (Force build the containers and start the project)]
                [-r (Restart containers)]
                [-v (Manage virtual dataplane)
                [-sh (Create a interactive shell container for debugging)]\n"
      exit 1 # Command to come out of the program with status 1
      ;;
esac
