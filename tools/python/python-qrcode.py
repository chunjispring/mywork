#!/usr/bin/env python
# coding=utf-8

#生成二维码

#sudo apt-get install python-pip
#sudo apt-get install libzbar-dev
#sudo pip install zbar
#sudo apt-get install python-qrtools
#sudo apt-get install python-qrcode

import sys
import qrcode

def usage():
    print sys.argv[0] + ' info pic'

def createQRimages(info, pic):
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
        )
    
    qr.add_data(info)
    qr.make(fit=True)
    img = qr.make_image()
    img.save(pic)

if __name__ == '__main__':
    if len(sys.argv) == 3:
        createQRimages(sys.argv[1], sys.argv[2])
    else:
        usage()

