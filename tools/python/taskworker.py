#!/usr/bin/env python

import sys,time,Queue
from multiprocessing.managers import BaseManager

#中文测试

class QueueManager1(BaseManager):
    pass
    
QueueManager1.register('get_task_queue')
QueueManager1.register('get_result_queue')

server_addr = '127.0.0.1'
print('Connect to server {}...'.format(server_addr))

m = QueueManager1(address=(server_addr,5000), authkey='abc')

m.connect()

task1 = m.get_task_queue()
result1 = m.get_result_queue()

for i in range(10):
    try:
        n = task1.get(timeout=1)
        print('run task {}*{}...'.format(n,n))
        r = '{}*{}={}'.format(n,n,n*n)
        time.sleep(1)
        result1.put(r)
        
    except Queue.Empty:
        print('task queue is empty.')
        
print('worker exit.')

