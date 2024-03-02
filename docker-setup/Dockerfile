# Use Ubuntu as the base image
FROM ubuntu:latest

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Update and install necessary packages
RUN apt-get update && apt-get install -y \
    tmux \
    htop \
    g++ \
    python3 \
    neovim \
    evince \
    gnome-terminal \
    x11-apps \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Add Microsoft's GPG key and the VSCode repository
RUN apt-get update && apt-get install -y wget
RUN wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > /etc/apt/trusted.gpg.d/microsoft.gpg \
    && echo "deb [arch=amd64,arm64,armhf] http://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list

# Install VSCode
RUN apt-get update && apt-get install -y code

# More packages
RUN apt-get update && apt-get install -y dbus-x11 x11-xkb-utils

# Create a user 'coder' and add to sudo group
RUN useradd -m coder -s /bin/bash && \
    echo "coder ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/coder && \
    chmod 0440 /etc/sudoers.d/coder

# Switch to user 'coder'
USER coder
WORKDIR /home/coder

# Set the display environment variable for X11 forwarding
ENV DISPLAY host.docker.internal:0

# Volume setup for persisting data
VOLUME /home/coder

COPY latest.pdf /home/coder/latest.pdf

# Start bash for interaction
CMD ["/bin/bash"]
