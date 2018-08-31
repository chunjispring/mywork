#!/bin/sh

#中文测试

ArriveFlag=0

while true
do
  for rpt_file in `ls RD1002 `
  do
    ArriveFlag=1;
  done

  echo $ArriveFlag
  
  if [ $ArriveFlag -eq 1 ]; then
    break;
  fi

  sleep 120
done


