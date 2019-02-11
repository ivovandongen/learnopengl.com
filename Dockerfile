FROM ubuntu:18.04

# --------------------------------------------------------------------------------------------------
# Install common packages

RUN set -eu \
 && apt-get update \
 && apt-get -y install git make locales \
     clang \
     python python-pip \
     ccache cmake \
     libx11-dev xorg-dev

# --------------------------------------------------------------------------------------------------
# Setup environment

RUN locale-gen en_US.UTF-8

ENV LC_ALL="en_US.UTF-8" \
    CC="clang" \
    CXX="clang++"\
    PATH=/usr/lib/ccache:$PATH \
    WORK_DIR=/work

WORKDIR $WORK_DIR
