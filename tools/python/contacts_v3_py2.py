#!/usr/bin/python
#-*- coding:utf-8 -*-

import cPickle as cp
import os

#中文测试

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

class Person:
    '''Person is used to store the info of a person.'''
    def __init__(self, name, phone='', email='', address=''):
        self.name = name
        self.phone = phone
        self.email = email
        self.address = address
        
    def __str__(self):
        return "Name: " + self.name + " Phone: " + self.phone + " Email: " +\
               self.email + " Address: " + self.address
        
class AddressBook:
    '''AddressBook is used to add/delete/update/select 
    the information in the addressbook.data of the person.'''
    
    def Add(self,person):
        '''Add a new person!'''
        if contacts.has_key(person.name):
            print 'warning:record exists!'
        else:
            contacts[person.name]=person
            print 'Add [%s] success' %person.name
        
    def Delete(self,name):
        '''Delete a person!''' 
        if contacts.has_key(name):
            del contacts[name]
            print 'Delete [%s] success' %name
        else:
            print 'No user[%s] information,delete fail' %name
        
    def Update(self,name):
        '''Update a person!''' 
        if contacts.has_key(name):
            if raw_input("Modify Phone? (y/n)") == 'y':
                contacts[name].phone = raw_input("Input Phone:")
            if raw_input("Modify Email? (y/n)") == 'y':
                contacts[name].email = raw_input("Input Email:")
            if raw_input("Modify Address? (y/n)") == 'y':
                contacts[name].address = raw_input("Input Address:")
            print 'Update [%s] success' %name
        else:
            print 'No user[%s] information' %name
        
    def Select(self,name):
        '''Find a person!''' 
        if contacts.has_key(name):
            print 'Select success.',name, ':', contacts[name]
        else:
            print 'No user[%s] information.' %name
        
    def ShowInfo(self):
        '''Show all the people in addressbook''' 
        print 'Name      Phone        Email               Address'
        for name,contact in contacts.items():
            print '%s%s%s%s' %(contact.name.ljust(10),contact.phone.ljust(13),contact.email.ljust(20),contact.address)
        
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
        f=file(self.savefile)
        contacts = cp.load(f)
        f.close()
        
    def SaveData(self):
        '''Save dict to datafile'''
        global contacts
        f=file(self.savefile,'w')
        cp.dump(contacts,f)
        f.close()
        
    def ClearData(self):
        '''clear datafile'''
        global contacts
        contacts={}
        print 'Clear the contacts data success.'
        
# Script starts from here
def main():
    print _hello
    runningflag = True
    
    ab = AddressBook()
    
    da=DataFile()
    da.savefile = 'addressbook.data'
    
    print _menu
    
    if da.FileExists():
        da.LoadData()
    
    while runningflag: 
        cmd = raw_input('>>>Input a Command: ') 
        if cmd == 'A' or cmd == 'a': 
            print _help 
            info = raw_input('Person Info: ') 
            info = info.split(' ') 
            person = Person(info[0],info[1],info[2],info[3]) 
            ab.Add(person) 
        elif cmd == 'D' or cmd == 'd': 
            name = raw_input('Please input a name: ') 
            ab.Delete(name) 
        elif cmd == 'M' or cmd == 'm': 
            name = raw_input('Please input a name: ') 
            ab.Update(name) 
        elif cmd == 'F' or cmd == 'f': 
            name = raw_input('Please input a name: ') 
            ab.Select(name) 
        elif cmd == 'L' or cmd == 'l': 
            ab.ShowInfo() 
        elif cmd == 'C' or cmd == 'c':
            da.ClearData()
        elif cmd == 'Q' or cmd == 'q': 
            runningflag = False 
        else: 
            print "Unknown option,please choose one from the commands menu!" 
    
    da.SaveData()
    print _bye
    
if __name__ == '__main__':
    contacts = {}
    main()
    

