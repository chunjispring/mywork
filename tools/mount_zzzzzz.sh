#/bin/bash

#挂载远端共享目录

sudo mount -t cifs //172.17.237.21/UATProject/zzzzzz $HOME/mnt/ -o username=cjwang,password=23qwe!@#,rw,uid=0,gid=0,dir_mode=0777,file_mode=0777

exit
