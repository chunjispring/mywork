#!/usr/bin/python
#-*- coding:utf-8 -*-

import cPickle as p
import sys
import os

#中文测试

class MemberInfo:
    savefile='addressbook.data'
    
    def __init__(self):
        self.AddBooK={}
        if os.path.exists(self.savefile) and os.stat(self.savefile).st_size!=0:
            fi=file(self.savefile)
            self.AddBooK=p.load(fi)
            fi.close()
        else:
            pass
    
    def Add(self,name,Phone):
        self.name=name
        self.Phone=Phone
        
        if self.AddBooK.has_key(self.name):
            print 'warning:record exists!'
        else:
            self.AddBooK[self.name]=self.Phone
            print 'Add [%s] success' %self.name
    
    def Delete(self,name):
        self.name=name
        if self.AddBooK.has_key(self.name):
            del self.AddBooK[self.name]
            print 'Delete [%s] success' %self.name
        else:
            print 'no user[%s] information' %self.name
        
    def Update(self,name,newphone):
        self.name=name
        self.Phone=newphone
        if self.AddBooK.has_key(self.name):
            self.AddBooK[self.name]=self.Phone
            print 'Update [%s] success' %self.name
        else:
            print 'no user[%s] information' %self.name
        
    def Select(self,name):
        self.name=name
        if self.AddBooK.has_key(self.name):
            print 'Select success. name: %s  phoneno: %s' %(self.name,self.AddBooK[self.name])
        else:
            print 'no user[%s] information' %self.name
    
    def ShowInfo(self):
        for name,phone in self.AddBooK.items():
            print 'Contact %s at %s' %(name,phone)
            
    def SaveData(self):
        #Save the data
        f=file(self.savefile,'w')
        p.dump(t.AddBooK,f)
        f.close()
    def ClearData(self):
        cf=file(self.savefile,'w')
        cf.close()
    
# Script starts from here
t=MemberInfo()

if len(sys.argv)<2:
    print 'No action specified.'
    sys.exit()

if sys.argv[1].startswith('--'):
    option=sys.argv[1][2:]
    # fetch sys.argv[1] but without the first two characters
    if option=='version':
        print 'Version 1.0'
    elif option=='info':
        t.ShowInfo()
    elif option=='help':
        print '''\
This program create an addressbook, and it can add/update/delete the data in it.
Options include:
  --version : Prints the version number
  --help    : Display this help
  --info    : Show all data in the addressbook
  -A        : Add contactors     "-A name phone"
  -D        : Delete contactors  "-D name"
  -U        : Update contactors  "-U name phone"
  -S        : Select contactors  "-S name"'''
    else:
        print 'Unknown option.'
    sys.exit()
elif sys.argv[1].startswith('-A'):
    t.Add(sys.argv[2],sys.argv[3])
    t.SaveData()
elif sys.argv[1].startswith('-D'):
    t.Delete(sys.argv[2])
    t.SaveData()
elif sys.argv[1].startswith('-U'):
    t.Update(sys.argv[2],sys.argv[3])
    t.SaveData()
elif sys.argv[1].startswith('-S'):
    t.Select(sys.argv[2])
elif sys.argv[1].startswith('-C'):
    t.ClearData()
else:
    print 'Unknown option.'

