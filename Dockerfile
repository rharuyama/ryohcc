FROM ubuntu:latest
RUN apt-get update -y
RUN apt-get install make clang lldb -y