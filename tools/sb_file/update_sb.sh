#!/usr/bin/env zsh

#更新

export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games  
. ~/.zshrc 

LOGFILE=~/Downloads/update.log

cat >>$LOGFILE <<EOF
`date +%F' '%H:%M:%S`
`smsboomer update` 
========================= 
EOF

exit 
