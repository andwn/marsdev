FROM ubuntu:jammy as build

ARG DEBIAN_FRONTEND=noninteractive

# Install prerequisites
RUN apt update && \
    apt install -y git build-essential texinfo wget \
    openjdk-17-jdk-headless libpng-dev \
    && apt clean

ENV MARSDEV=/marsdev/mars
ENV GENDEV=$MARSDEV
ENV PATH=$PATH:$JAVA_HOME/bin
ENV HOME=/marsdev
ENV LOG=$HOME/build.log

RUN mkdir -p $HOME
RUN mkdir -p `dirname $LOG`
RUN mkdir -p $MARSDEV

WORKDIR /work

COPY ./ marsdev/

WORKDIR /work/marsdev

#RUN make MARS_BUILD_DIR=$MARSDEV m68k-toolchain clean
RUN make MARS_BUILD_DIR=$MARSDEV m68k-toolchain-newlib clean

#RUN make MARS_BUILD_DIR=$MARSDEV sh-toolchain clean
RUN make MARS_BUILD_DIR=$MARSDEV sh-toolchain-newlib clean

RUN make MARS_BUILD_DIR=$MARSDEV sgdk

RUN make MARS_BUILD_DIR=$MARSDEV x68k-tools
RUN make MARS_BUILD_DIR=$MARSDEV sik-tools

WORKDIR /

RUN rm -rf /work /root/mars

RUN echo '#!/bin/bash\njava -Duser.dir="`pwd`" -jar $MARSDEV/bin/rescomp.jar ${@:-1}' > $MARSDEV/bin/rescomp && chmod +x $MARSDEV/bin/rescomp 

RUN chmod ugo+r -R $HOME
RUN chmod ugo+r -R $MARSDEV
RUN chmod ugo+x -R $MARSDEV/bin

CMD make
