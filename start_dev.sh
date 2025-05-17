#!/bin/bash

# Allow local container access to XQuartz (only needed once per session)
xhost + 127.0.0.1

# Docker compose up in background mode
docker-compose up -d

# Wait for the container to be fully up
sleep 1

#Open interactive shell
docker exec -it minirt /bin/bash
