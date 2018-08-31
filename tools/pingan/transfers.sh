#!/bin/sh
cd $HOME
. ./.bash_profile


export LD_LIBRARY_PATH=/home/haps/tmp/wangcj/mylib
### when cyber-ark is down, you can use $WCJHOME/myetc/key.txt to get three keys 
### 1. make sure key.txt locat in $WCJHOME/myetc, and there's three keys in it
### 2. change "$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE" to "$ORDERDIR/encrypt 1 $i $KEYFILE"

KEYFILE=$WCJHOME/myetc/key.txt
CBA_CFG_FILE=$WCJHOME/myetc/cyberark.cfg
ORDERDIR=$WCJHOME/mybin

#FOR UAT
#nas_WCJHOME="$WCJHOME"
#FOR PRD
nas_WCJHOME="/home/haps/tmp/wangcj"

FILEDIR=$nas_WCJHOME/mydata/recvmydata/entity/
DST_FILEDIR=$nas_WCJHOME/mydata/sendmydata/entity
ERR_FILEDIR=$nas_WCJHOME/mydata/error
ORIGFILEDIR=$nas_WCJHOME/get
SENDFLAG=1

while true
do
	cd $FILEDIR
	for i in `ls`
	do
		TEMP1=`wc -c $i | awk '{print $1}'`
		echo $TEMP1
		sleep 10
		TEMP2=`wc -c $i | awk '{print $1}'`
		echo $TEMP2
		if [ $TEMP1 -eq $TEMP2  ]; then
			echo $i
                        ## when cyber-ark down, open below
			$ORDERDIR/encrypt 1 $i $KEYFILE
                        ##$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE
			if [ $? -eq 0 ]; then
				echo "文件'$i'加密成功!"
				ORIGINNAME=`echo ?_$i`	
				$ORDERDIR/mac $ORIGINNAME
				if [ $? -eq 0 ]; then
					echo "文件'$ORIGINNAME'加mac成功!"
					mv *-$ORIGINNAME $DST_FILEDIR
				else
					echo "文件'$ORIGINNAME'加mac失败!"
					mv $ORIGINNAME $ERR_FILEDIR
				fi
			else
				echo "文件'$i'加密失败!"
				mv $i $ERR_FILEDIR
			fi
		else
			sleep 20
		fi
	done
done
