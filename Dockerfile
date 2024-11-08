FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    git \
    cmake \
    ninja-build \
    gdb \
    clang-format \
    && rm -rf /var/lib/apt/lists/*

VOLUME /libetk

WORKDIR /libetk

CMD ["/bin/bash"]