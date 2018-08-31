#!/usr/bin/usr python
# -*- coding:utf-8 -*-

import logging
import os
logging.basicConfig(filename=os.path.join(os.getcwd(),'log.txt'),\
        level=logging.WARN,filemode='w',format='%(asctime)s - %(name)s - %(levelname)s: %(message)s')
logging.debug('this is a debug message')
logging.info('this is a info message')
logging.warning('this is a debug message')
logging.error('this is a error message')

#创建一个logger
ll = logging.getLogger('mylogger')
ll.setLevel(logging.DEBUG)
#创建一个handler，用于写入日志文件
fh=logging.FileHandler('mylogger.log')
fh.setLevel(logging.DEBUG)
#在创建一个handler，用于输出到控制台
ch=logging.StreamHandler()
ch.setLevel(logging.DEBUG)
#定义handler的输出格式
formater=logging.Formatter('%(asctime)s - %(name)s - %(levelname)s: %(message)s')
fh.setFormatter(formater)
ch.setFormatter(formater)
#给logger添加handler
ll.addHandler(fh)
ll.addHandler(ch)
#记录一条日志
ll.info("mmm")
ll.log(logging.ERROR,'error')

#4个主要的组件
#logger    日志类，应用程序往往通过调用它提供的api来记录日志
#handler   对日志信息处理，可以将日志发送（保存）到不同的目标域中
#filter    对日志信息进行过滤
#formatter 日志的格式化

#6个日志级别
#CRITICAL   50
#ERROR      40 
#WARNING    30
#INFO       20
#DEBUG      10
#NOTSET     0

#可以给日志对象或Handler设置日志级别，低于该级别的日志消息会被忽略

##常用logging模块中的函数
#为日志模块配置基本信息  logging.basicConfig([**kwaggs])  filename  filemode  format  datefmt  level  stream
#创建Logger对象          logging.getLogger([name])
#获取/设置日志类型       logging.setLoggerClass(klass)  logging.getLoggerClass()
#获取日志级别对应的名称  logging.getLevelName(lvl)
#print(logging.getLevelName(30))
#print(logging.getLevelName(logging.ERROR))
#不再使用日志系统        logging.shutdown()

##实用handler：
#StreamHandler       输出到控制台
#FileHandler         输出到文件
#BaseRotatingHandler 可以按时间写入到不同的日志中。比如将日志按天写入不同的日期结尾的文件
#SocketHandler       用TCP网络连接写log
#DatagramHandler     用UDP网络连接写log
#SMTPHandler         把log写成email邮寄出去


##Logger对象 通过调用logging.getLogger(name)来创建。方法属性如下：
#设置日志级别                Logger.setLevel(lvl)
#记录DEBUG级别的日志信息     Logger.debug(msg[,*agrs[,**kwargs]])
#记录INFO级别的日志信息      Logger.info(msg[,*agrs[,**kwargs]])
#记录WARNING级别的日志信息   Logger.warnning(msg[,*agrs[,**kwargs]])
#记录ERROR级别的日志信息     Logger.error(msg[,*agrs[,**kwargs]])
#记录CRITICAL级别的日志信息  Logger.decritialbug(msg[,*agrs[,**kwargs]])
#记录日志，参数lvl日志级别   Logger.log(lvl,msg[,*args[,**kwargs]])
#以ERROR级别记录异常跟踪消息 Logger.exception(msg[,*args])
#添加/移除日志消息过滤器     Logger.addFillter(filt)   Logger.removeFilter(filt)
#添加/移除日志消息处理器     Logger.addHandler(hdlr)   Logger.removeHandler(hdlr)
#创建LogRecord对象           Logger.makeRecord(name,lvl,fn,lno,msg,args,exc_info[,func,extra])






