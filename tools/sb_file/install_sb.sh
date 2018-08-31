#/bin/sh

#安装npm
sudo apt install npm

#升级npm为最新版本
sudo npm install npm@latest -g

#安装用于安装nodejs的模块n
sudo npm install -g n

#通过n模块安装指定版本的nodejs
sudo n latest

#以CLI命令运行
sudo PUPPETEER_SKIP_CHROMIUM_DOWNLOAD=1 npm install smsboomer -g

#sudo chown -R xxx:xxx /usr/local/bin/smsboomer
#sudo chown -R xxx:xxx /usr/local/lib/node_modules
