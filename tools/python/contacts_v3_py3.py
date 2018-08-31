#!/usr/bin/env python3
#-*- coding:utf-8 -*-

#支持Python3.x

import pickle as cp
import os
import re

_hello = '''|------------------------------------------------------|
| This is a program with the basic funcs of addressbook|
| Author : wangcj                                      |
| Version: 3.0                                         |
| Date   : 1/9/2014                                    |
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

contacts = {}

#中文测试

class Person:
    '''Person is used to store the info of a person.'''
    def __init__(self, name, phone='', email='', address=''):
        self.name = name
        self.phone = phone
        self.email = email
        self.address = address
        
    def __str__(self):
        return "Phone:" + self.phone + "  Email:" + self.email + "  Address:" + self.address
        
class AddressBook:
    '''AddressBook is used to add/delete/update/select 
    the information in the addressbook.data of the person.'''
    
    def Add(self,person):
        '''Add a new person!'''
        if contacts.__contains__(person.name):
            print ('warning:record exists!')
        else:
            contacts[person.name]=person
            print ('Add [{}] success.'.format(person.name))
        
    def Delete(self,name):
        '''Delete a person!''' 
        if contacts.__contains__(name):
            del contacts[name]
            print ('Delete [{}] success.'.format(name))
        else:
            print ('No user[{}] information,delete fail.'.format(name))
        
    def Update(self,name):
        '''Update a person!''' 
        if contacts.__contains__(name):
            if input("Modify Phone? (y/n)") == 'y':
                contacts[name].phone = input("Input Phone:")
            if input("Modify Email? (y/n)") == 'y':
                contacts[name].email = input("Input Email:")
            if input("Modify Address? (y/n)") == 'y':
                contacts[name].address = input("Input Address:")
            print ('Update [{}] success.'.format(name))
        else:
            print ('No user[{}] information.'.format(name))
        
    def Select(self,name):
        '''Find a person!''' 
        if contacts.__contains__(name):
            print ('Select success.Name:{}  {}.'.format(name,contacts[name]))
        else:
            print ('No user[{}] information.'.format(name))
        
    def ShowInfo(self):
        '''Show all the people in addressbook''' 
        print ('Name      Phone        Email               Address')
        for name,contact in contacts.items():
            #调用ljust前先计算中文字符个数(中文会被ljust当做一个字符，是个bug)
            temp = re.findall('[^a-zA-Z0-9.]+', name)
            count=0
            for i in temp:
                count += len(i)
            print ('{}{}{}{}'.format(name.ljust(10-count),contact.phone.ljust(13),contact.email.ljust(20),contact.address))
        
class DataFile:
    def FileExists(self):
        '''Judge if the datafile exists''' 
        if os.path.exists(self.savefile) and os.stat(self.savefile).st_size!=0:
            return True
        else:
            return False
        
    def LoadData(self):
        '''Load data to dict'''
        global contacts
        with open(self.savefile,'rb') as f:
            contacts = cp.load(f)
        
    def SaveData(self):
        '''Save dict to datafile'''
        global contacts
        with open(self.savefile,'wb') as f:
            cp.dump(contacts,f)
        
    def ClearData(self):
        '''clear datafile'''
        global contacts
        contacts={}
        print ('Clear the contacts data success.')
        
# Script starts from here
def main():
    print (_hello)
    runningflag = True
    
    ab = AddressBook()
    
    da=DataFile()
    da.savefile = 'addressbook.data'
    
    print (_menu)
    
    if da.FileExists():
        da.LoadData()
    
    while runningflag: 
        cmd = input('>>>Input a Command: ') 
        if cmd == 'A' or cmd == 'a': 
            print (_help) 
            info = input('Person Info: ')  
            person = Person(*info.split(' ')) 
            ab.Add(person) 
        elif cmd == 'D' or cmd == 'd': 
            name = input('Please input a name: ') 
            ab.Delete(name) 
        elif cmd == 'M' or cmd == 'm': 
            name = input('Please input a name: ') 
            ab.Update(name) 
        elif cmd == 'F' or cmd == 'f': 
            name = input('Please input a name: ') 
            ab.Select(name) 
        elif cmd == 'L' or cmd == 'l': 
            ab.ShowInfo() 
        elif cmd == 'C' or cmd == 'c':
            da.ClearData()
        elif cmd == 'Q' or cmd == 'q': 
            runningflag = False 
        else: 
            print ("Unknown option,please choose one from the commands menu!")
    
    da.SaveData()
    print (_bye)
    
if __name__ == '__main__':
    main()
    

