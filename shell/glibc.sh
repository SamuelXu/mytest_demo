#!/bin/sh
#Date:   Feb, 2015

lang=$LANG
export LANG=zh_CN.UTF-8

distro=""
arch=`getconf LONG_BIT`
libcversion=`ldd --version | head -n 1 | awk '{print $NF}'`
libcmain=`echo -n $libcversion | awk -F. '{print $1}'`
libcver=`echo -n $libcversion | awk -F. '{print $2}'`
install_dir=/usr/local/install/

[ -w / ] || {
    echo "Run this script with root priviliges!"
    export LANG=$lang
    exit 1
}

error()
{
    echo $2
    echo "error code:$1"
    export LANG=$lang
    exit 1
}

check_distro()
{
    if [ -f /etc/centos-release ]; then
        distro="CentOS";
    elif [ -f /etc/debian_version ];  then 
        distro="debian";
    elif [ -f /etc/SuSE-release ]; then
        distro="SuSe";
    elif [ -f /etc/fedora-release ]; then
        distro="fedora";
    elif [ -f /etc/redhat-release ]; then
        distro="redhat";
    elif [ ! `lsb_release -d | grep -i "ubuntu" > /dev/null` ]; then
        distro="ubuntu";
    else 
        distro="linux";
    fi
}

check_env()
{
    CURL=`which curl 2>/dev/null`
    if [ $? -ne 0 ];then
        error -1 "curl is not found, please install curl!"
    fi
    UNZIP=`which unzip 2>/dev/null`
    if [ $? -ne 0 ];then
        error -1 "unzip is not found, please install unzip!"
    fi
}

stopservice() {
    pid=`ps -ef |grep 'service'|grep -v ""|awk -F' ' '{print $2}'  2>/dev/null`
    if [ ! -z $pid ] ; then 
        kill $pid
    fi
}

check_env

if [ $libcmain -lt 2 ];then
    error 2 "glibc old version";
elif [ $libcmain -eq 2 -a $libcver -lt 5 ];then
    error 2 "glibc old version";
elif [ $libcver -gt 5 -a $libcver -lt 14 -a $arch -eq 64 ]; then
    url="www.example.com/linux-generic-x86_64-GLIBC_2.5";
elif [ $libcver -gt 14 -a $arch -eq 64 ]; then
    url="www.example.com/linux-generic-x86_64-GLIBC_2.14";
elif [ $libcver -gt 5 -a $libcver -lt 14 -a $arch -eq 32 ]; then
    url="www.example.com/linux-generic-i686-GLIBC_2.5";
else
    url="www.example.com/linux-generic-i686-GLIBC_2.14";
fi

export LANG=$lang
exit 0

