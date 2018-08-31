#!/bin/sh
cd $HOME
. ./.bash_profile

### when cyber-ark is down, you can use $HOME/config/keylw.txt to get three keys
### 1. make sure key.txt locat in $HOME/config, and there's three keys in it
### 2. change "$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE" to "$ORDERDIR/encrypt 1 $i $KEYFILE"

#FOR UAT
#nas_home="$HOME"

#FOR PRD
nas_home="/home/haps/tmp/wangcj"

ORDERDIR=$WCJHOME/bin
SRCFILEDIR=$nas_home/mydata/recvmydata/sos/get
DSTFILEDIR=$nas_home/mydata/sendmydata/sos
BAKFILEDIR=$nas_home/mydata/backup/sos
ERRFILEDIR=$nas_home/mydata/error

while true
do
         
	 if [ ! -d $SRCFILEDIR ]
	 then
		echo ${SRCFILEDIR}" don't exist!"
		exit 0;
	 fi

         cd $SRCFILEDIR
         #for i in `ls`
         for i in `ls DSP_SOS_CUSTINFO_NEW*`
         do
                  TEMP1=`wc -c $i | awk '{print $1}'`
                  echo $TEMP1
                  sleep 10
                  TEMP2=`wc -c $i | awk '{print $1}'`
                  echo $TEMP2
                  if [ $TEMP1 -eq $TEMP2  ]; then
                          echo $i
                          #$ORDERDIR/encrypt 0 $i $CBA_CFG_FILE
			  $WCJHOME/mybin/file_safe_manage.sh 0 $i $SRCFILEDIR $DSTFILEDIR
                          if [ $? -eq 0 ]; then
				   echo "文件'$i'加密加mac成功!"
				   mv $i $BAKFILEDIR
                          else
                                   echo "文件'$i'加密加mac失败!"
                                   mv $i $ERRFILEDIR
                          fi
                  else
                          sleep 20
                  fi
         done

	 SOSFILENAME=HAPS_--DSP_M_SOS--_`date +%Y%m%d`.ZIP
         if [ `ls -lA $DSTFILEDIR|grep DSP_SOS_CUSTINFO_NEW|wc -l` -eq 2 ]; then
		cd $DSTFILEDIR
		ls -A|grep DSP_SOS_CUSTINFO_NEW|xargs -i zip $SOSFILENAME {}
		mv $SOSFILENAME $nas_home/put
		mv *DSP_SOS_CUSTINFO_NEW* $BAKFILEDIR
         fi

         sleep 600 
done
