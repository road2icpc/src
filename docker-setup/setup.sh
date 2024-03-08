#!/bin/bash

cp ../PDF/latest.pdf .

docker build -t eucdocker .

docker volume create coder_home

xhost +local:docker

docker run -it --rm -e DISPLAY=$DISPLAY \
    --privileged \
    -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
    -v /run/dbus:/run/dbus \
    -v coder_home:/home/coder eucdocker
