#!/usr/bin/env python
# coding=utf-8

#解析二维码文件

#sudo apt-get install python-pip
#sudo apt-get install libzbar-dev
#sudo pip install zbar
#sudo apt-get install python-qrtools
#sudo apt-get install python-qrcode

import sys
import qrtools

def decodeQRimages(path):
    image = qrtools.QR()
    res = image.decode(path)

    if res:
        return image.data

if __name__ == '__main__':
#    path=r"./ppp.jpg"
    path=sys.argv[1]
    print decodeQRimages(path)


