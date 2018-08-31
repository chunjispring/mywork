#!/bin/sh

#测试sftp

CURR_PID=$$
sftp ftp_haps@10.14.57.228 <<EOF >$CURR_PID
cd /wls/sftp/ftp_haps/puttemp
ls -al
EOF

rm -f mm

for i in `cat $CURR_PID | grep "^-" | awk '{print $9}'`
do
    if [ $i != "sftp>" ];
    then
        echo $i >> mm
    fi
#    echo $i
done

if [ -f mm ];
then
    for i in `cat mm`
    do
        ssh ftp_haps@10.14.57.228 /sbin/fuser /wls/sftp/ftp_haps/puttemp/$i >/dev/null
        if [ $? -eq 0 ];
        then
            exit 4
        fi
        echo $i"    Stutus:"$?

    done
fi


