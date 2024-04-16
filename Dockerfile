FROM debian:bookworm-slim as build_env

ARG DEBIAN_FRONTEND=noninteractive

ENV MARS_BUILD_DIR=/marsdev/build
ENV MARS_INSTALL_DIR=/marsdev/mars
ENV GENDEV=$MARS_INSTALL_DIR
ENV PATH=$PATH:$JAVA_HOME/bin
ENV HOME=/marsdev

# Install prerequisites
RUN apt update && \
    apt install -y git build-essential texinfo wget \
    openjdk-17-jdk-headless libpng-dev && \
    apt clean && \
    mkdir -p $MARS_BUILD_DIR && \
    mkdir -p $MARS_INSTALL_DIR/bin

COPY ./ $MARS_BUILD_DIR
WORKDIR $MARS_BUILD_DIR

FROM build_env as build_m68k_toolchain

RUN make m68k-toolchain-newlib

FROM build_m68k_toolchain as build_sh_toolchain

RUN make sh-toolchain-newlib

FROM build_sh_toolchain as build_sgdk

RUN make sgdk

FROM build_sgdk as build_x68k_tools

RUN make x68k-tools

FROM build_x68k_tools as build_sik_tools

RUN make sik-tools

FROM build_sik_tools as build_install

RUN make install

# Hack to run rescomp
RUN echo '#!/bin/bash\njava -Duser.dir="`pwd`" -jar $MARS_INSTALL_DIR/bin/rescomp.jar ${@:-1}' > $MARS_INSTALL_DIR/bin/rescomp && chmod +x $MARS_INSTALL_DIR/bin/rescomp

FROM build_install as build_final

WORKDIR /

RUN rm -rf /work $MARS_BUILD_DIR && \
    chmod ugo+r -R $HOME && \
    chmod ugo+r -R $MARS_INSTALL_DIR && \
    chmod ugo+rx -R $MARS_INSTALL_DIR/mars.sh && \
    chmod ugo+rx -R $MARS_INSTALL_DIR/bin && \
    chmod ugo+rx -R $MARS_INSTALL_DIR/m68k-elf/bin && \
    chmod ugo+rx -R $MARS_INSTALL_DIR/sh-elf/bin && \
    echo "exec \"\$@\"" >> /marsdev/mars/mars.sh

ENTRYPOINT ["/marsdev/mars/mars.sh"]
CMD make
