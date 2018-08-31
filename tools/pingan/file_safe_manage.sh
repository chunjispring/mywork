#!/bin/sh

＃加密测试

JAVA_HOME=$WCJHOME/tmp_test/java_encrypt/jdk/jrockit-jdk1.4.2_15 

#DO NOT CHANGE the lines below.
CONFIG_HOME=$WCJHOME/myetc
BIN_HOME=$WCJHOME/tmp_test/java_encrypt/javabin
CBA_CFG_FILE=$CONFIG_HOME/secure.properties
LOG4F_CFG_FILE=$CONFIG_HOME/log4j.properties

#CLASSPATH=.:$JAVA_HOME/lib/tools.jar:$CONFIG_HOME:$CFTS_HOME/cfts.jar
#CLASSPATH=.:$JAVA_HOME/lib/tools.jar:$CONFIG_HOME:$HOME/lib
CLASSPATH=.:$JAVA_HOME/lib/tools.jar:$BIN_HOME
for jar_name in `ls $WCJHOME/tmp_test/java_encrypt/javalib/*.jar`
do
    CLASSPATH=$CLASSPATH:$jar_name
done
echo $CLASSPATH


if [ $# !=  4 ]
then
    echo "parameter invalid!";
    echo "Usage: $0 Type[0:encode;1:decode] fileName srcFilePath desFilePath"
    exit -1;
fi
OPTYPE=$1

if [ $OPTYPE == 0 ]
then
	echo "encrypt and genmac file"
	#FILENAME=`basename ${ORGFILE}`
	#FILEPATH=`dirname ${ORGFILE}`
	FILENAME=$2
	SRCPATH=$3
	DESPATH=$4
	LEN=`expr length $FILENAME`
	ENCFILE=$(($RANDOM%9+1))_${FILENAME}
	echo $ENCFILE

	$JAVA_HOME/bin/java -cp $CLASSPATH com.paic.docsecure.TriDesEncryptor 1 $SRCPATH/$FILENAME $DESPATH/$ENCFILE $CBA_CFG_FILE $LOG4F_CFG_FILE
	$JAVA_HOME/bin/java -cp $CLASSPATH com.paic.docsecure.SignOper $DESPATH/$ENCFILE $LOG4F_CFG_FILE

elif [ $OPTYPE == 1 ]
then
	echo "decrypt and chkmac file"
	ORGFILE=$2
	#FILENAME=`basename ${ORGFILE}`
        #FILEPATH=`dirname ${ORGFILE}`
	FILENAME=$2
        SRCPATH=$3
        DESPATH=$4
	LEN=`expr length $FILENAME`
	ENCFILE=`expr substr $FILENAME 10 ${LEN}`
	LEN=`expr length $ENCFILE`
	DECFILE=`expr substr $ENCFILE 3 ${LEN}`
	echo $DECFILE

	$JAVA_HOME/bin/java -cp $CLASSPATH com.paic.docsecure.VeriSignOper $SRCPATH/$FILENAME $LOG4F_CFG_FILE
	$JAVA_HOME/bin/java -cp $CLASSPATH com.paic.docsecure.TriDesDecryptor 1 $SRCPATH/$ENCFILE $DESPATH/$DECFILE $CBA_CFG_FILE $LOG4F_CFG_FILE
else
	echo "para type error!please check!"
	exit -1;
fi
