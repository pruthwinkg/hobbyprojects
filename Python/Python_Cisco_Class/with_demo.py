'Build a deep understanding of the with statement'

# How to open and close files -- The Old Way   ###############

f = open('day2/notes2/hamlet.txt')
try:
    play = f.read()
    print len(play)
finally:
    f.close()

# How to open and close files -- The New Way  ###############

with open('day2/notes2/hamlet.txt') as f:
    play = f.read()
    print len(play)


#############################################################

import threading

counter_lock = threading.Lock()
printer_lock = threading.Lock()

counter = 0

def worker(i):
    printer_lock.acquire()
    try:
        print 'Worker %d is reporting for work' % i
        print 'This works great!'
        print 'I really trust multi-threading'
        print 'It is sooooo easy'
    finally: 
        printer_lock.release()


def coworker():
    global counter
    counter_lock.acquire()
    try:
        counter += 1
    finally:
        counter_lock.release()

printer_lock.acquire()
try:
    print 'Starting up'
finally:
    printer_lock.release()

for i in range(10):
    threading.Thread(target=worker, args=(i,)).start()
    threading.Thread(target=coworker).start()

printer_lock.acquire()
try:
    print 'The count is', counter
    print 'Done'
finally:
    printer_lock.release()


#############################################################
#   Better multithreaded code using 'with'    
#############################################################

import threading 

counter_lock = threading.Lock()
printer_lock = threading.Lock()

counter = 0

def worker(i):
    with printer_lock:
        print 'Worker %d is reporting for work' % i
        print 'This works great!'
        print 'I really trust multi-threading'
        print 'It is soooooo easy!'

def cworker():
    global counter
    with counter_lock:
        counter += 1

with printer_lock:
    print 'Starting up'
    
for i in range(10):
    threading.Thread(target=worker, args=(i,)).start()
    threading.Thread(target=cworker).start()

with printer_lock:
    print 'The count is', counter    
    print 'Done'
