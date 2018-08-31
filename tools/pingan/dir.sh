#!/bin/sh
FILEDIR=$WKPATH/tools

cd $FILEDIR
for i in `ls`
do
	TEMP1=`wc -c $i | awk '{print $1}'`
	echo $TEMP1
	sleep 1
	TEMP2=`wc -c $i | awk '{print $1}'`
	echo $TEMP2
	if [ $TEMP1 -eq $TEMP2  ]; then
		echo $i
## when cyber-ark down, open below
##$ORDERDIR/encrypt 1 $i $KEYFILE
#$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE
		if [ $? -eq 0 ]; then
			echo "文件'$i'加密成功!"
			ORIGINNAME=`echo ?_$i`
			echo $ORIGINNAME
#$ORDERDIR/mac $ORIGINNAME
			if [ $? -eq 0 ]; then
				echo "文件'$ORIGINNAME'加mac成功!"
#mv *-$ORIGINNAME $DST_FILEDIR
			else
				echo "文件'$ORIGINNAME'加mac失败!"
#mv $ORIGINNAME $ERR_FILEDIR
			fi
		else
			echo "文件'$i'加密失败!"
#mv $i $ERR_FILEDIR
		fi
	else
		sleep 2
	fi
done


