## 放到 /etc/profile.d 目录下，是作为环境变量生效的

TMOUT=3600
HISTSIZE=100000
HISTFILESIZE=100000
PROMPT_COMMAND='{ date "+[ %Y%m%d %H:%M:%S `whoami` ] `history 1 | { read x cmd; echo "$cmd      from ip:$SSH_CLIENT   $SSH_TTY"; }`"; } >> $HOME/.history_detail'

export TMOUT HISTSIZE HISTFILESIZE PROMPT_COMMAND
readonly TMOUT HISTSIZE HISTFILESIZE
