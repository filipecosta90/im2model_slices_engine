FROM gcc:8

RUN curl https://cmake.org/files/v3.12/cmake-3.12.1-Linux-x86_64.sh -o /tmp/curl-install.sh \
      && chmod u+x /tmp/curl-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/curl-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/curl-install.sh

ENV PATH="/usr/bin/cmake/bin:${PATH}"

COPY . /.

RUN gcc -o myapp main.c
CMD ["./myapp"]
