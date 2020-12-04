FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

# Install prerequisites
RUN apt update && \
    apt install -y git build-essential texinfo curl wget \
    openjdk-8-jdk-headless libpng-dev \
    autoconf automake libtool libboost-dev && \
    apt clean

# Grab repo and make everything
RUN git clone https://github.com/andwn/marsdev && \
    cd marsdev && \
    make m68k-toolchain-newlib LANGS=c,c++ && \
    make m68k-gdb && \
    make sh-toolchain-newlib LANGS=c,c++ && \
    make -C gdb ARCH=sh && \
    make z80-tools && \
    make sgdk && \
    make sik-tools && \
    make flamewing-tools && \
    cd && rm -rf marsdev
