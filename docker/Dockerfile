FROM ubuntu:18.04

RUN sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
RUN apt-get clean
RUN apt-get update
RUN apt-get install -y vim
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y texlive texlive-science latex-cjk-chinese texlive-full
RUN apt-get install -y python3

CMD ["/bin/bash"]
