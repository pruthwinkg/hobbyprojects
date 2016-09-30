'''
Key Lesson:  Writing code using globals variables and "print", testing each line as you go
             is incredibly productive and a joyful style of programming.  Accordingly, it
             is a very common thing to do.  Usually, once it is working, we move the code
             into functions with good names, good docstrings, and fast local variables.



'''
from dis import dis
from StringIO import StringIO
from contextlib import closing
import sys
import os


class Ignore(object):
    
    def __init__(self, exctype):
        self.exctype = exctype       

    def __enter__(self):
        return self

    def __exit__(self, exctype, excinst, exctb):
        if exctype == self.exctype:
            return True

class RedirectStdout(object):
    
    def __init__(self, target):
        self.target = target

    def __enter__(self):
        self.oldstdout = sys.stdout
        sys.stdout = self.target
        return self.target
       
    def __exit__(self, exctype, excinst, exctb):
        sys.stdout = self.oldstdout


########################################################################################################

def show_family(lastname, first_names):
    'Display the family members in a nice tabular form'
    print 'The {0} Family'.format(lastname.title())
    print '=' * (11 + len(lastname))
    for name in first_names:
        print '* {name}'.format(name=name.title())
    print

with RedirectStdout(sys.stderr):
    show_family('starks', ['eddard', 'catelyn', 'robb', 'sansa', 'arya', 'bram', 'rickon', 'jon snow'])

help(show_family)

with open('family.dis', 'w') as f:
    with RedirectStdout(f):
        dis(show_family)

with closing(StringIO()) as f:
    with RedirectStdout(f):
        show_family('simpsons', ['homer', 'marge', 'bart', 'lisa', 'maggie'])
    print f.getvalue().upper()

print 'Done'


########################################################################
##
##def show_family(lastname, first_names):
##    'Display the family members in a nice tabular form'
##    print 'The {0} Family'.format(lastname.title())
##    print '=' * (11 + len(lastname))
##    for name in first_names:
##        print '* {name}'.format(name=name.title())
##    print
##
##oldstdout = sys.stdout
##sys.stdout = sys.stderr
##try:
##    show_family('starks', ['eddard', 'catelyn', 'robb', 'sansa', 'arya', 'bram', 'rickon', 'jon snow'])
##finally:    
##    sys.stdout = oldstdout
##
##help(show_family)
##
##f = open('family.dis', 'w')
##try:
##    oldstdout = sys.stdout
##    sys.stdout = f
##    try:
##        dis(show_family)
##    finally:
##        sys.stdout = oldstdout
##finally:
##    f.close()
##
##f = open('tmp.txt', 'w')
##try:
##    oldstdout = sys.stdout
##    sys.stdout = f
##    try:
##        show_family('simpsons', ['homer', 'marge', 'bart', 'lisa', 'maggie'])
##    finally:
##        sys.stdout = oldstdout
##finally:
##    f.close()
##
##f = open('tmp.txt')
##try:
##    s = f.read()
##finally:
##    f.close()
##
##try:
##    os.remove('tmp.txt')
##except OSError:
##    pass
##
##print s.upper()
##
##print 'Done'



