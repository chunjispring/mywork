#!/bin/sh
cd $HOME
. ./.bash_profile

### when cyber-ark is down, you can use $WCJHOME/myetc/keylw.txt to get three keys
### 1. make sure key.txt locat in $WCJHOME/myetc, and there's three keys in it
### 2. change "$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE" to "$ORDERDIR/encrypt 1 $i $KEYFILE"
export LD_LIBRARY_PATH=/home/haps/tmp/wangcj/mylib
KEYFILE=$WCJHOME/myetc/keypost1.txt
CBA_CFG_FILE=$WCJHOME/myetc/cyberark_post1.cfg

#FOR UAT
#nas_WCJHOME="$WCJHOME"

#FOR PRD
nas_WCJHOME="/home/haps/tmp/wangcj"

ORDERDIR=$WCJHOME/mybin
SRCFILEDIR=$nas_WCJHOME/mydata/recvmydata/post1/get/
DSTFILEDIR=$nas_WCJHOME/mydata/sendmydata/post1/
BAKFILEDIR=$nas_WCJHOME/mydata/backup/post1
ERRFILEDIR=$nas_WCJHOME/mydata/error

while true
do
	#if [ "`ls -A $ORIGFILEDIR/`" != "" ]; then
	#	mv $ORIGFILEDIR/* $FILEDIR
	#else :
	#fi
	
	cd $SRCFILEDIR
	for i in `ls`
	do
		TEMP1=`wc -c $i | awk '{print $1}'`
		echo $TEMP1
		sleep 10
		TEMP2=`wc -c $i | awk '{print $1}'`
		echo $TEMP2
		if [ $TEMP1 -eq $TEMP2  ]; then
			echo $i
			##$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE
			$ORDERDIR/encrypt 1 $i $KEYFILE
			if [ $? -eq 0 ]; then
				echo "文件'$i'加密成功!"
				ORIGINNAME=`echo ?_$i`
				$ORDERDIR/mac $ORIGINNAME
				if [ $? -eq 0 ]; then
					echo "文件'$ORIGINNAME'加mac成功!"
					mv *-$ORIGINNAME $DSTFILEDIR
				else
					echo "文件'$ORIGINNAME'加mac失败!"
					mv $ORIGINNAME $ERRFILEDIR
				fi
			else
				echo "文件'$i'加密失败!"
				mv $i $ERRFILEDIR
			fi
		else
			sleep 20
		fi
	done

done
