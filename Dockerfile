FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

# Install prerequisites
RUN apt update && \
    apt install -y git build-essential texinfo curl wget \
    openjdk-8-jdk-headless libpng-dev \
    autoconf automake libtool libboost-dev && \
    apt clean

ENV MARSDEV=/marsdev/mars
ENV GENDEV=$MARSDEV
ENV PATH=$PATH:$JAVA_HOME/bin
ENV HOME=/marsdev
ENV LOG=$HOME/build.log
#ENV MARSDEV_GIT=https://github.com/dleslie/marsdev
ENV MARSDEV_GIT=https://github.com/andwn/marsdev

RUN rm -rf $HOME $MARSDEV $LOG

RUN mkdir -p $HOME
RUN mkdir -p `dirname $LOG`
RUN mkdir -p $MARSDEV

WORKDIR /work

RUN git clone $MARSDEV_GIT
#COPY ./ marsdev/

WORKDIR /work/marsdev
RUN make m68k-toolchain-newlib LANGS=c,c++ MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make m68k-gdb MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make sh-toolchain-newlib LANGS=c,c++ MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make -C gdb ARCH=sh MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make z80-tools MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make sgdk MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make sik-tools MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)
RUN make flamewing-tools MARSDEV=$MARSDEV 2>&1 | (tee -a $LOG)

WORKDIR /

RUN rm -rf /work
RUN rm -rf /root/mars

RUN echo '#!/bin/bash\njava -Duser.dir="`pwd`" -jar $MARSDEV/bin/rescomp.jar ${@:-1}' > $MARSDEV/bin/rescomp && chmod +x $MARSDEV/bin/rescomp 

RUN chmod ugo+r -R $HOME
RUN chmod ugo+r -R $MARSDEV
RUN chmod ugo+x -R $MARSDEV/bin

CMD make
