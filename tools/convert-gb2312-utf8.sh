#!/usr/bin/env bash

# file -i 命令能够查看文件当前的编码
# for i in `ls *.sh` ;do convert-gb2312-utf8.sh $i;done
# for i in `find . -name "*.h" -type f` ;do convert-gb2312-utf8.sh $i;done

if [ $# -ne 1 ]
then
    echo "Usage:`basename $0` inputfilename";
    exit 1;
fi

if [ "`file -i $1 |awk -F';' '{print $2}'`" = " charset=utf-8" ]
then
    echo "$1 已经是utf-8编码了，忽略...";
    exit 2;
else
    echo "Now convert $1 ...";
fi

#if [ "`file -i $1 |awk -F';' '{print $2}'|awk -F'=' '{print $2}'`" = "gb2312" ]
#then
    iconv -f gb2312 -t utf-8  $1 -o $1_utf8;
#fi

exit 0;
