#!/usr/bin/python
#-*- coding:utf-8 -*-

import cPickle as p
import getopt
import sys
import os

#中文测试

_options = [
    'help',
    'version',
    'usedata',
    'cleardata',
    'printdata',
]
_short_options = 'hVUcp'

_help = '''\
This program create an contacts, and it can add/update/delete the data in it.
Options include:
      --help       : Display this help
      --version    : Prints the version number
      --usedata    : Add/Del/Up/Sel the contacts
      --cleardata  : Clear all data in the contacts
      --printdata  : Show all data in the contacts
      -h           : As --help
      -V           : As --version
      -U           : As --usedata
      -c           : As --cleardata
      -p           : As --printdata'''

_except = """
    [Fatal] {}
    Try '{} --help' for more options."""

savefile = 'addressbook.data'
contacts={}

class MemberInfo:
    def __init__(self,name,email='',tel=''):
        self.name = name
        self.email = email
        self.tel = tel
    
def FileExists():
    if os.path.exists(savefile) and os.stat(savefile).st_size!=0:
        return True
    else:
        return False
    
def Add():
    global contacts
    s = raw_input('Please input name,email,telno to add: ')
    tmp=s.split(' ')
    mem=MemberInfo(tmp[0],tmp[1],tmp[2])
    
    if contacts.has_key(mem.name):
        print 'warning:record exists!'
    else:
        contacts[mem.name]=mem.email+','+mem.tel
        print 'Add [%s] success' %mem.name
    
def Delete():
    global contacts
    s = raw_input('Please input the persons\'name to delete: ')
    
    if contacts.has_key(s):
        del contacts[s]
        print 'Delete [%s] success' %s
    else:
        print 'No user[%s] information,delete fail' %s
    
def Update():
    global contacts
    s = raw_input('Please input the name\'s new email,tel to update: ')
    tmp=s.split(' ')
    mem=MemberInfo(tmp[0],tmp[1],tmp[2])
    
    if contacts.has_key(mem.name):
        contacts[mem.name]=mem.email+','+mem.tel
        print 'Update [%s] success' %mem.name
    else:
        print 'No user[%s] information' %mem.name
    
def Select():
    global contacts
    s = raw_input('Please enter the name which you want to select: ')
    
    if contacts.has_key(s):
        print 'Select success.',s, ':', contacts[s]
    else:
        print 'No user[%s] information.' %s
    
def ShowInfo():
    global contacts
    for name,contact in contacts.items():
        print 'Contact %s at %s' %(name,contact)

def LoadData():
    global contacts
    
    f=file(savefile)
    contacts = p.load(f)
    f.close()
        
def SaveData():
    global contacts
    
    #Save the data
    f=file(savefile,'w')
    p.dump(contacts,f)
    f.close()
        
def ClearData():
    cf=file(savefile,'w')
    cf.close()
    print 'Clear the contacts data success.'
    
# Script starts from here
def main():
    script_name = 'contacts.py'
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], _short_options, _options)
    except getopt.GetoptError as e:
        print _except.format(e, script_name)
        exit(-1)
    
    #print opts
    #print args
    if not opts :
        # Display help.
        print _help
    else:
        if FileExists():
            LoadData()
        
        for opt, arg in opts:
            if opt in ('--help','-h'):
                print _help;
                sys.exit()
            elif opt in ('--version','-V'):
                print 'Version 2.0'
                sys.exit()
            elif opt in ('--cleardata','-c'):
                ClearData()
                sys.exit()
            elif opt in ('--printdata','-p'):
                ShowInfo()
                sys.exit()
            elif opt in ('--usedata','-U'):
                while True:
                    choice = raw_input('1.add\n2.delete\n3.update\n4.select\n5.exit\n')
                    if choice == '1':
                        Add()
                        SaveData()
                    elif choice == '2':
                        Delete()
                        SaveData()
                    elif choice == '3': 
                        Update()
                        SaveData()
                    elif choice == '4':
                        Select()
                    elif choice == '5':
                        sys.exit()
                    else:
                        print "Don't have this option, Please try again!"
            elif len(opt)==0:
                print 'Unknown option.'

if __name__ == '__main__':
    main()
    
    
    
