#!/bin/sh

# 开始工作

rm -f .error .log

while true 
do
    #beiyu
    smsboomer 13501851042 >>.log 2>>.error
    
    #huang
    #smsboomer 13761690609 >>.log 2>>.error
    
    #wang
    #smsboomer 15801725122 >>.log 2>>.error
    
    #zhao
    #smsboomer 13817609951 >>.log 2>>.error
    
    num=`grep SUCCESS .error |wc -l`
    echo `date +%m%d-%H:%M:%S`"<=======>" $num

    sleep 44
done

exit 

