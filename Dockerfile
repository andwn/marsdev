FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

# Install prerequisites
RUN apt update && \
    apt install -y git build-essential texinfo curl wget \
    openjdk-8-jdk-headless libpng-dev \
    autoconf automake libtool libboost-dev && \
    apt clean

ENV MARSDEV=/marsdev/mars
ENV PATH=$PATH:$JAVA_HOME/bin
ENV HOME=/marsdev

WORKDIR /work

RUN git clone https://github.com/andwn/marsdev

WORKDIR /work/marsdev

RUN make m68k-toolchain-newlib LANGS=c,c++ MARSDEV=$MARSDEV
RUN make m68k-gdb MARSDEV=$MARSDEV
RUN make sh-toolchain-newlib LANGS=c,c++ MARSDEV=$MARSDEV
RUN make -C gdb ARCH=sh MARSDEV=$MARSDEV
RUN make z80-tools MARSDEV=$MARSDEV
RUN make sgdk MARSDEV=$MARSDEV
RUN make sik-tools MARSDEV=$MARSDEV
RUN make flamewing-tools MARSDEV=$MARSDEV

RUN rm -rf /work
RUN chmod ugo+r -R $MARSDEV
RUN chmod ugo+x -R $MARSDEV/bin

CMD make
