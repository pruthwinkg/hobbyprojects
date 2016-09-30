''' Iterator Protocol == Universal Pattern of Object Oriented Design

ITERABLE == Anything that can be looped over == Anything that can be used with a for-loop in Python.
  |-> __iter__() that is responsible for return an ITERATOR.

ITERATOR == An object with state that controls the looping
  |-> __iter__() that returns "self".  Iterators are self-iterable. 
  |-> next() that
   \+   Fetches and returns a value
    \+  Updates the state
     \+ Signal when it is done by raising StopIteration

Convenience functions:
    iter(obj)  ->  obj.__iter__()
    next(obj)  ->  obj.next()

Looping pattern:

    it = iter(iterable)
    while True:
        try:
            value = next(it)
        except StopIteration:
            break
        do_some_thing(value)

'''


############################################################################################
# Anything that is sizeable with len(), indexable with s[0], s[1], ... and raise IndexError,
# is called a SEQUENCE.   All sequences are iterable.

class Squares1:
    'Produce consecutive squares'
    
    def __init__(self, stop):
        self.stop = stop

    def __len__(self):
        return self.stop

    def __getitem__(self, index):
        if index >= self.stop:
            raise IndexError
        return index ** 2

s = Squares1(10)
print list(s)
print tuple(s)
print sum(s)
it = iter(s)
print next(it)
print next(it)
print next(it)
print list(it)      # Lists a partially consumed iterator

############################################################################
# Iterables have an __iter__ method that returns an iterator.
# Iterators have an __iter__ method and next() method.

class Squares2:

    def __init__(self, stop):
        self.stop = stop

    def __iter__(self):
        return Squares2Iterator(self.stop)

class Squares2Iterator:

    def __init__(self, stop):
        self.i = 0
        self.stop = stop    

    def __iter__(self):
        return self

    def next(self):
        value = self.i
        if value >= self.stop:
            raise StopIteration
        self.i += 1
        return value ** 2


s = Squares2(5)
print list(s)
print tuple(s)
print sum(s)
it = iter(s)
print next(it)
print next(it)
print next(it)
print list(it)      # Lists a partially consumed iterator


############################################################################
# Generator is a kind of iterator that runs resumable code

def squares3(stop):
    i = 0
    while i < stop:
        yield i ** 2
        i += 1

s = squares3(10)
print list(s)

s = squares3(10)
print tuple(s)

s = squares3(10)
print sum(s)

s = squares3(10)
it = iter(s)
print next(it)
print next(it)
print next(it)
print list(it)      # Lists a partially consumed iterator

############################################################################
# Two argument form of iter(func, sentinel) -> iterator

from random import randrange
from functools import partial


def roll():
    return randrange(1, 7) + randrange(1, 7)


game = []
while True:
    r = roll()
    if r == 7:
        break
    game.append(r)
print sum(game)

print sum(iter(roll, 7))    # Add up the result of roll() until we get a seven


f = open('day2/notes2/mpl_demo.py')
blocks = []
while True:
    block = f.read(10)
    if block == '':
        break    
    blocks.append(block)
print ''.join(blocks)

f = open('day2/notes2/mpl_demo.py')
print ''.join(iter(partial(f.read, 10), ''))

## Small interpreter ##

while True:
    expr = raw_input('? ')
    if expr == 'quit':
        break
    print repr(eval(expr))

for expr in iter(partial(raw_input, '? '), 'quit'):
    print repr(eval(expr))












































