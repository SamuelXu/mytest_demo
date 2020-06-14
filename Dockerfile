FROM ubuntu:latest

ENV TZ 'Asia/Shanghai'
ADD https://raw.githubusercontent.com/cpplint/cpplint/master/cpplint.py /usr/local/bin/cpplint.py

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list && \
        apt-get -y update && \
        echo $TZ > /etc/timezone && \
        apt-get update && apt-get install -y tzdata && \
        rm /etc/localtime && \
        ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && \
        dpkg-reconfigure -f noninteractive tzdata && \
        apt-get clean && \
        apt-get -y update && \
        apt-get -y install graphviz && \
        apt-get -y install build-essential && \
        apt-get -y install git && \
        apt-get -y install cmake && \
        apt-get -y install vim && \
        apt-get -y install doxygen && \
        apt-get -y install curl && \
        apt-get -y install python3 && \
        ln -s /usr/bin/python3 /usr/bin/python && \
        chmod +x /usr/local/bin/cpplint.py && \
        curl https://bazel.build/bazel-release.pub.gpg | apt-key add - && \
        echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list && \
        apt update && apt-get -y install bazel
CMD /bin/bash
