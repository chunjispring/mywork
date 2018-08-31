#!/usr/bin/env python
# -*- coding:utf-8 -*-
#支持Python3.x

import sqlite3      #导入SQLite驱动
import os
import re           #导入正则表达式 处理ljust()的bug问题

_hello = '''|------------------------------------------------------|
| This is a program with the basic funcs of addressbook|
| Author : wangcj                                      |
| Version: 4.0                                         |
| Date   : 12/9/2014                                   |
| Please do as the tips!                               |
|------------------------------------------------------|\n'''

_help = '''Please input the person info as the following format: 
             name phone email address\n'''
    
_menu = ''' Input a command. The commands are shown in the below.
 *****************************************************
 * Command Name               Description            *
 *****************************************************
 * 'A' or 'a'                 Add a person           *
 * 'C' or 'c'                 Clear the datafile     *
 * 'D' or 'd'                 Delete a person        *
 * 'F' or 'f'                 Find a person          *
 * 'L' or 'l'                 List all people        *
 * 'M' or 'm'                 Modify a person        *
 * 'Q' or 'q'                 Exit                   *
 ***************************************************** \n'''

_bye = '''|-----------------------------------------------------|
| Thank you for using this program!                   |
|-----------------------------------------------------|'''

#定义一个end伪关键字，确定code block的缩进范围
__builtins__.end = None

class UserInfo(object):
    '''定义用户信息类'''
    def __init__(self, name, phone="", email="", address=""):
        self.name = name
        self.phone = phone
        self.email = email
        self.address = address

    def __str__(self):
        return "%s,%s,%s,%s" %(self.name, self.phone, self.email, self.address)

class UserTable:
    '''定义用户表操作类'''
    def get_conn(self,path):
        '''连接到SQLite数据库 数据库文件是test.db 如果文件不存在会在当前目录自动创建'''
        try:
            conn = sqlite3.connect(path)
            return conn
        except sqlite3.Error:
            print("连接sqlite3数据库失败")
            return
    end

    def get_cursor(self,conn):
        '''获取数据库的游标对象'''
        return conn.cursor()
    end

    def close_cursor(self,cu):
        '''关闭数据库游标对象'''
        if cu is not None:
            cu.close()
    end

    def close_db(self,conn):
        '''关闭数据库连接对象'''
        if conn is not None:
            conn.close()
    end

    def create_table(self,conn,sql):
        '''创建数据库表'''
        cu = self.get_cursor(conn)
        cu.execute(sql)
        conn.commit()
        self.close_cursor(cu)
    end

    def Add(self,conn,sql,data):
        '''插入数据，从数据库中查询用户名是否存在，如果在就报错，没有就插入表中'''
        if self.SelectRecord(conn,data.name):
            print ('warning:record exists!')
        else:
            cu = self.get_cursor(conn)
            lt = (data.name,data.phone,data.email,data.address)
            cu.execute(sql,lt)
            conn.commit()
            self.close_cursor(cu)
            print ('Add [{}] success.'.format(data.name))
    end

    def Delete(self,conn,sql,name):
        '''删除数据，从数据库中查询用户名是否存在，如果在就删除，没有就报错'''
        if self.SelectRecord(conn,name):
            cu = self.get_cursor(conn)
            d = (name,)
            cu.execute(sql,d)
            conn.commit()
            self.close_cursor(cu)
            print ('Delete [{}] success.'.format(name))
        else:
            print ('No user[{}] information,delete fail.'.format(name))
    end

    def Update(self,conn,name):
        '''更新数据，从数据库中查询用户名是否存在，如果在就更新，没有就报错'''
        update_sql1 = '''UPDATE user SET phone=? WHERE name=?'''
        update_sql2 = '''UPDATE user SET email=? WHERE name=?'''
        update_sql3 = '''UPDATE user SET address=? WHERE name=?'''
        
        if self.SelectRecord(conn,name):
            cu = self.get_cursor(conn)
            lt = ()
            if input("Modify Phone? (y/n)") == 'y':
                phone = input("Input Phone:")
                lt = (phone, name)
                cu.execute(update_sql1, lt)
            if input("Modify Email? (y/n)") == 'y':
                email = input("Input Email:")
                lt = (email, name)
                cu.execute(update_sql2, lt)
            if input("Modify Address? (y/n)") == 'y':
                address = input("Input Address:")
                lt = (address, name)
                cu.execute(update_sql3, lt)
                
            if len(lt) < 2:
                print ('No Modify.')
            else:
                print ('Update [{}] success.'.format(name))
            conn.commit()
            self.close_cursor(cu)
        else:
            print ('No user[{}] information,update fail.'.format(name))
    end

    def Select(self,conn,sql,name):
        '''查询一条数据，从数据库中查询用户名是否存在，如果在就返回信息，没有就报错'''
        if name is not None:
            cu = self.get_cursor(conn)
            d = (name,)
            cu.execute(sql,d)
            r = cu.fetchone()
            
            print ('Select success.{}.'.format(r))
            
            self.close_cursor(cu)
        else:
            print ('No user[{}] information.'.format(name))
    end

    def SelectRecord(self,conn,name):
        '''从数据库中查询用户名是否存在，如果在就返回True，没有False'''
        sel_sql = '''SELECT * FROM user WHERE name= ?'''
        data=(name,)
        cu = self.get_cursor(conn)
        cu.execute(sel_sql,data)
        r = cu.fetchall()
    
        self.close_cursor(cu)
        if len(r) > 0:
            return True
        else:
            return False
    end

    def ShowInfo(self,conn,sql):
        '''查询所有数据，将数据库中所有信息打印到屏幕上'''
        print ('Name         Phone        Email        Address')
        cu = self.get_cursor(conn)
        cu.execute(sql)
        r = cu.fetchall()

        if len(r) > 0:
            for e in range(len(r)):
                for v in r[e]:
                    #调用ljust前先计算中文字符个数(中文会被ljust当做一个字符，是个bug)
                    temp = re.findall('[^a-zA-Z0-9.]+', v)
                    count=0
                    for i in temp:
                        count += len(i)
                    print (v.ljust(12-count),end=" ")
                print()
        self.close_cursor(cu)
    end

    def ClearData(self,conn,sql):
        '''清空数据库'''
        cu = self.get_cursor(conn)
        cu.execute(sql)
        conn.commit()
        self.close_cursor(cu)
        print ('Clear the contacts data success.')
    end
end

# Script starts from here
def main():
    print (_hello)
    runningflag = True
    
    print (_menu)
    
    DB_SQLITE_NAME = 'addressbook.db'
    
    #判断是数据库文件中uesr表是否存在，如果不存在则创建
    create_table_sql = '''CREATE TABLE if not exists user(
                          name varchar(20) NOT NULL,
                          phone varchar(11) DEFAULT NULL,
                          email varchar(20) DEFAULT NULL,
                          address varchar(200) DEFAULT NULL,
                          PRIMARY KEY(name)
                         )'''
    
    insert_sql = '''INSERT INTO user(name,phone,email,address) values(?,?,?,?)'''
    
    delete_sql = '''DELETE FROM user WHERE name=?'''
    
    select_sql = '''SELECT * FROM user WHERE name=?'''
    
    show_sql = '''SELECT * FROM user'''
    
    clear_sql = '''DELETE FROM user'''
    
    user = UserTable()
    conn = user.get_conn(DB_SQLITE_NAME)
    user.create_table(conn,create_table_sql)
    
    while runningflag:
        cmd = input('>>>Input a Command: ') 
        if cmd == 'A' or cmd == 'a': 
            print (_help) 
            info = input('Person Info: ') 
            data = UserInfo(*info.split(' '))
            user.Add(conn, insert_sql, data) 
            
        elif cmd == 'D' or cmd == 'd': 
            name = input('Please input a name: ') 
            user.Delete(conn, delete_sql, name) 
            
        elif cmd == 'M' or cmd == 'm': 
            name = input('Please input a name: ') 
            user.Update(conn, name)
            
        elif cmd == 'F' or cmd == 'f': 
            name = input('Please input a name: ') 
            user.Select(conn, select_sql, name)
            
        elif cmd == 'L' or cmd == 'l': 
            user.ShowInfo(conn, show_sql)
            
        elif cmd == 'C' or cmd == 'c':
            user.ClearData(conn, clear_sql,)
            
        elif cmd == 'Q' or cmd == 'q': 
            runningflag = False
            
        else: 
            print ("Unknown option,please choose one from the commands menu!")
            
    user.close_db(conn)
    print (_bye)
end
    
    
if __name__ == '__main__':
    main()
    

