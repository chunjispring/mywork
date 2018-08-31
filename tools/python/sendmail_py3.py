#!/usr/bin/env python
#-*- coding:utf-8 -*-

#python对SMTP的支持有 smtplib 和 email 两个模块
#email 负责构造邮件  smtplib 负责发送邮件

from email import encoders
from email.header import Header
from email.mime.text import MIMEText
from email.utils import parseaddr, formataddr
import smtplib

#格式化邮件地址
#如果邮件地址包含中文，需要通过Header对象进行编码
#不能简单传入 name<addr@example.com>
def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((\
         Header(name, 'utf-8').encode(),\
         addr if isinstance(addr, str) else addr))

#输入Email的地址和口令：
from_addr = 'chunjispring88@163.com'
password = '12345678'

#输入SMTP服务器的地址：
smtp_server = 'smtp.163.com'
smtp_port = 25        #SMTP协议默认端口是25

#输入收件人地址：
to_addr = '824985860@qq.com'

#邮件内容
#mag['To']接受的是字符串而不是list，如果有多个邮件地址，用','分隔即可
msg = MIMEText('hello,send by python...', 'plain', 'utf-8')
#msg = MIMEText('hello,send by python...', 'html', 'utf-8')
msg['From'] = _format_addr('Python爱好者<%s>' %from_addr)
msg['To'] = _format_addr('管理员<%s>' %to_addr)
msg['Subject'] = Header('来自SMTP的问候...', 'utf-8').encode()

#邮件发送
server = smtplib.SMTP(smtp_server, smtp_port)
#server.astarttls()             #创建安全连接 加密传输
server.set_debuglevel(1)
server.login(from_addr, password)
server.sendmail(from_addr, [to_addr], msg.as_string())
server.quit()

