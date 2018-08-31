#!/bin/sh

#中文测试

for((integer = 1; integer <= 10000; integer++))
do  
    #echo "$integer"  
    $WKPATH/bin/c_test.bin/aa $integer
done 

exit 0

