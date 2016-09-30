Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 26 2016, 12:10:39) 
[GCC 4.2.1 (Apple Inc. build 5666) (dot 3)] on darwin
Type "copyright", "credits" or "license()" for more information.
>>> 

>>> n = 10
>>> for x in range(n):
	print x ** 2

	
0
1
4
9
16
25
36
49
64
81
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The hettinger Family
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
===========
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
* raymond
* rachel
* matthew
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
* raymond
* rachel
* matthew
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
* Raymond
* Rachel
* Matthew
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
* Raymond
* Rachel
* Matthew

>>> type(name)
<type 'str'>
>>> name.upper()
'MATTHEW'
>>> dir(str)
['__add__', '__class__', '__contains__', '__delattr__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getnewargs__', '__getslice__', '__gt__', '__hash__', '__init__', '__le__', '__len__', '__lt__', '__mod__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '_formatter_field_name_split', '_formatter_parser', 'capitalize', 'center', 'count', 'decode', 'encode', 'endswith', 'expandtabs', 'find', 'format', 'index', 'isalnum', 'isalpha', 'isdigit', 'islower', 'isspace', 'istitle', 'isupper', 'join', 'ljust', 'lower', 'lstrip', 'partition', 'replace', 'rfind', 'rindex', 'rjust', 'rpartition', 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith', 'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
* Raymond
* Rachel
* Matthew

>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Hettinger Family
====================
* Raymond
* Rachel
* Matthew

>>> '''hello'''
'hello'
>>> 'don\'t'
"don't"
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

>>> 
>>> 
>>> import sys
>>> sys.stdout
<idlelib.PyShell.PseudoOutputFile object at 0x103962c90>
>>> sys.stderr
<idlelib.PyShell.PseudoOutputFile object at 0x103962cd0>
>>> sys.stdin
<idlelib.PyShell.PseudoInputFile object at 0x103962c50>
>>> 
>>> print 'hello'
hello
>>> sys.stdout.write('hello'.__str__()); sys.stdout.write('\n')
hello
>>> 
>>> print >> sys.stderr, 'hello'
hello
>>> sys.stderr.write('hello'.__str__()); sys.stderr.write('\n')
hello
>>> 
>>> 
>>> print >> sys.stderr, 30 + 40
70
>>> sys.stderr.write((30).__add__(40).__str__()); sys.stderr.write('\n')
70
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

>>> 
>>> show_family.__name__
'show_family'
>>> show_family.__doc__
'Display the family members in a nice tabular form'
>>> show_family.__code__.co_code
'd\x01\x00j\x00\x00|\x00\x00j\x01\x00\x83\x00\x00\x83\x01\x00GHd\x02\x00d\x03\x00t\x02\x00|\x00\x00\x83\x01\x00\x17\x14GHx%\x00|\x01\x00D]\x1d\x00}\x02\x00d\x04\x00j\x00\x00d\x05\x00|\x02\x00j\x01\x00\x83\x00\x00\x83\x00\x01GHq.\x00WHd\x06\x00S'
>>> map(ord, show_family.__code__.co_code)
[100, 1, 0, 106, 0, 0, 124, 0, 0, 106, 1, 0, 131, 0, 0, 131, 1, 0, 71, 72, 100, 2, 0, 100, 3, 0, 116, 2, 0, 124, 0, 0, 131, 1, 0, 23, 20, 71, 72, 120, 37, 0, 124, 1, 0, 68, 93, 29, 0, 125, 2, 0, 100, 4, 0, 106, 0, 0, 100, 5, 0, 124, 2, 0, 106, 1, 0, 131, 0, 0, 131, 0, 1, 71, 72, 113, 46, 0, 87, 72, 100, 6, 0, 83]
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

 14           0 LOAD_CONST               1 ('The {0} Family')
              3 LOAD_ATTR                0 (format)
              6 LOAD_FAST                0 (lastname)
              9 LOAD_ATTR                1 (title)
             12 CALL_FUNCTION            0
             15 CALL_FUNCTION            1
             18 PRINT_ITEM          
             19 PRINT_NEWLINE       

 15          20 LOAD_CONST               2 ('=')
             23 LOAD_CONST               3 (11)
             26 LOAD_GLOBAL              2 (len)
             29 LOAD_FAST                0 (lastname)
             32 CALL_FUNCTION            1
             35 BINARY_ADD          
             36 BINARY_MULTIPLY     
             37 PRINT_ITEM          
             38 PRINT_NEWLINE       

 16          39 SETUP_LOOP              37 (to 79)
             42 LOAD_FAST                1 (first_names)
             45 GET_ITER            
        >>   46 FOR_ITER                29 (to 78)
             49 STORE_FAST               2 (name)

 17          52 LOAD_CONST               4 ('* {name}')
             55 LOAD_ATTR                0 (format)
             58 LOAD_CONST               5 ('name')
             61 LOAD_FAST                2 (name)
             64 LOAD_ATTR                1 (title)
             67 CALL_FUNCTION            0
             70 CALL_FUNCTION          256
             73 PRINT_ITEM          
             74 PRINT_NEWLINE       
             75 JUMP_ABSOLUTE           46
        >>   78 POP_BLOCK           

 18     >>   79 PRINT_NEWLINE       
             80 LOAD_CONST               6 (None)
             83 RETURN_VALUE        
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

 14           0 LOAD_CONST               1 ('The {0} Family')
              3 LOAD_ATTR                0 (format)
              6 LOAD_FAST                0 (lastname)
              9 LOAD_ATTR                1 (title)
             12 CALL_FUNCTION            0
             15 CALL_FUNCTION            1
             18 PRINT_ITEM          
             19 PRINT_NEWLINE       

 15          20 LOAD_CONST               2 ('=')
             23 LOAD_CONST               3 (11)
             26 LOAD_GLOBAL              2 (len)
             29 LOAD_FAST                0 (lastname)
             32 CALL_FUNCTION            1
             35 BINARY_ADD          
        
=============================== RESTART: Shell ===============================
>>> help.__name__

Traceback (most recent call last):
  File "<pyshell#31>", line 1, in <module>
    help.__name__
AttributeError: '_Helper' object has no attribute '__name__'
>>> lambda x: x**2
<function <lambda> at 0x1043761b8>
>>> (lambda x: x**2).__name__
'<lambda>'
>>> type(hex)
<type 'builtin_function_or_method'>
>>> hex.__name__
'hex'
>>> 
>>> 
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

 14           0 LOAD_CONST               1 ('The {0} Family')
              3 LOAD_ATTR                0 (format)
              6 LOAD_FAST                0 (lastname)
              9 LOAD_ATTR                1 (title)
             12 CALL_FUNCTION            0
             15 CALL_FUNCTION            1
             18 PRINT_ITEM          
             19 PRINT_NEWLINE       

 15          20 LOAD_CONST               2 ('=')
             23 LOAD_CONST               3 (11)
             26 LOAD_GLOBAL              2 (len)
             29 LOAD_FAST                0 (lastname)
             32 CALL_FUNCTION            1
             35 BINARY_ADD          
             36 BINARY_MULTIPLY     
             37 PRINT_ITEM          
             38 PRINT_NEWLINE       

 16          39 SETUP_LOOP              37 (to 79)
             42 LOAD_FAST                1 (first_names)
             45 GET_ITER            
        >>   46 FOR_ITER                29 (to 78)
             49 STORE_FAST               2 (name)

 17          52 LOAD_CONST               4 ('* {name}')
             55 LOAD_ATTR                0 (format)
             58 LOAD_CONST               5 ('name')
             61 LOAD_FAST                2 (name)
             64 LOAD_ATTR                1 (title)
             67 CALL_FUNCTION            0
             70 CALL_FUNCTION          256
             73 PRINT_ITEM          
             74 PRINT_NEWLINE       
             75 JUMP_ABSOLUTE           46
        >>   78 POP_BLOCK           

 18     >>   79 PRINT_NEWLINE       
             80 LOAD_CONST               6 (None)
             83 RETURN_VALUE        
Done
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

 14           0 LOAD_CONST               1 ('The {0} Family')
              3 LOAD_ATTR                0 (format)
              6 LOAD_FAST                0 (lastname)
              9 LOAD_ATTR                1 (title)
             12 CALL_FUNCTION            0
             15 CALL_FUNCTION            1
             18 PRINT_ITEM          
             19 PRINT_NEWLINE       

 15          20 LOAD_CONST               2 ('=')
             23 LOAD_CONST               3 (11)
             26 LOAD_GLOBAL              2 (len)
             29 LOAD_FAST                0 (lastname)
             32 CALL_FUNCTION            1
             35 BINARY_ADD          
             36 BINARY_MULTIPLY     
             37 PRINT_ITEM          
             38 PRINT_NEWLINE       

 16          39 SETUP_LOOP              37 (to 79)
             42 LOAD_FAST                1 (first_names)
             45 GET_ITER            
        >>   46 FOR_ITER                29 (to 78)
             49 STORE_FAST               2 (name)

 17          52 LOAD_CONST               4 ('* {name}')
             55 LOAD_ATTR                0 (format)
             58 LOAD_CONST               5 ('name')
             61 LOAD_FAST                2 (name)
             64 LOAD_ATTR                1 (title)
             67 CALL_FUNCTION            0
             70 CALL_FUNCTION          256
             73 PRINT_ITEM          
             74 PRINT_NEWLINE       
             75 JUMP_ABSOLUTE           46
        >>   78 POP_BLOCK           

 18     >>   79 PRINT_NEWLINE       
             80 LOAD_CONST               6 (None)
             83 RETURN_VALUE        
Done
>>> name = 'Raymond'
>>> name.title()
'Raymond'
>>> name = 42
>>> name.title()

Traceback (most recent call last):
  File "<pyshell#41>", line 1, in <module>
    name.title()
AttributeError: 'int' object has no attribute 'title'
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/redirect.py", line 23, in <module>
    show_family(42, ['eddard', 'catelyn', 'robb', 'sansa', 'arya', 'bram', 'rickon', 'jon snow'])
  File "/Users/raymond/Dropbox/Public/sj149/redirect.py", line 14, in show_family
    print 'The {0} Family'.format(lastname.title())
AttributeError: 'int' object has no attribute 'title'
>>> print 'hello'
hello
>>> list = [10, 20, 30]
>>> 
>>> 
>>> list('abc')

Traceback (most recent call last):
  File "<pyshell#46>", line 1, in <module>
    list('abc')
TypeError: 'list' object is not callable
>>> [10, 20, 30]('abc')

Traceback (most recent call last):
  File "<pyshell#47>", line 1, in <module>
    [10, 20, 30]('abc')
TypeError: 'list' object is not callable
>>> 
>>> del list
>>> list('abc')
['a', 'b', 'c']
>>> list = [10, 20, 30]
>>> list
[10, 20, 30]
>>> list('abc')

Traceback (most recent call last):
  File "<pyshell#53>", line 1, in <module>
    list('abc')
TypeError: 'list' object is not callable
>>> del list
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

Done
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> os.remove('xyz.txt')

Traceback (most recent call last):
  File "<pyshell#55>", line 1, in <module>
    os.remove('xyz.txt')
NameError: name 'os' is not defined
>>> import os
>>> os.remove('xyz.txt')

Traceback (most recent call last):
  File "<pyshell#57>", line 1, in <module>
    os.remove('xyz.txt')
OSError: [Errno 2] No such file or directory: 'xyz.txt'
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> 
>>> 2 ** 200 - 1
1606938044258990275541962092341162602522202993782792835301375L
>>> dir(f)
['__class__', '__delattr__', '__doc__', '__enter__', '__exit__', '__format__', '__getattribute__', '__hash__', '__init__', '__iter__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'close', 'closed', 'encoding', 'errors', 'fileno', 'flush', 'isatty', 'mode', 'name', 'newlines', 'next', 'read', 'readinto', 'readline', 'readlines', 'seek', 'softspace', 'tell', 'truncate', 'write', 'writelines', 'xreadlines']
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> 
>>> 
>>> e = KeyError('roger')
>>> isinstance(e, KeyError)
True
>>> e.__class__
<type 'exceptions.KeyError'>
>>> e.args
('roger',)
>>> e = KeyError('roger', 'david')
>>> e.args
('roger', 'david')
>>> raise e

Traceback (most recent call last):
  File "<pyshell#69>", line 1, in <module>
    raise e
KeyError: ('roger', 'david')
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> # We want a class that is file-like:
>>> #     f.write  f.read  f.seek  f.close
>>> 
>>> # We want it to store a string
>>> #     f.getvalue()
>>> 
>>> 
>>> from StringIO import StringIO
>>> f = StringIO()
>>> dir(f)
['__doc__', '__init__', '__iter__', '__module__', 'buf', 'buflist', 'close', 'closed', 'flush', 'getvalue', 'isatty', 'len', 'next', 'pos', 'read', 'readline', 'readlines', 'seek', 'softspace', 'tell', 'truncate', 'write', 'writelines']
>>> 
>>> f.write('Line one\n')
>>> f.write('Line two\n')
>>> f.getvalue()
'Line one\nLine two\n'
>>> f.close()
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> dir(f)
['__doc__', '__init__', '__iter__', '__module__', 'buflist', 'close', 'closed', 'flush', 'getvalue', 'isatty', 'len', 'next', 'read', 'readline', 'readlines', 'seek', 'softspace', 'tell', 'truncate', 'write', 'writelines']
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/redirect.py ==========
The Starks Family
=================
* Eddard
* Catelyn
* Robb
* Sansa
* Arya
* Bram
* Rickon
* Jon Snow

Help on function show_family in module __main__:

show_family(lastname, first_names)
    Display the family members in a nice tabular form

THE SIMPSONS FAMILY
===================
* HOMER
* MARGE
* BART
* LISA
* MAGGIE


Done
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> square(10)
100
>>> cube(10)
1000
>>> collatz(10)
5
>>> collatz(5)
16
>>> big_func(10)
Doing hard work
11
>>> help(square)
Help on function square in module __main__:

square(x)
    Compute a value times itself

>>> help(cube)
Help on function cube in module __main__:

cube(x)
    Compute a value times itself thrice

>>> help(collatz)
Help on function collatz in module __main__:

collatz(x)

>>> help(big_func)
Help on function big_func in module __main__:

big_func(x)
    Simulate slow labor intensive function

>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
=============================== RESTART: Shell ===============================
>>> x = 10
>>> globals()['x']
10
>>> globals()['x'] = 11
>>> x
11
>>> 
>>> 
>>> sorted(globals().keys())
['__builtins__', '__doc__', '__name__', '__package__', 'x']
>>> dir()
['__builtins__', '__doc__', '__name__', '__package__', 'x']
>>> 
>>> 
>>> 
>>> import collections
>>> sorted(collections.__dict__.keys())
['Callable', 'Container', 'Counter', 'Hashable', 'ItemsView', 'Iterable', 'Iterator', 'KeysView', 'Mapping', 'MappingView', 'MutableMapping', 'MutableSequence', 'MutableSet', 'OrderedDict', 'Sequence', 'Set', 'Sized', 'ValuesView', '__all__', '__builtins__', '__doc__', '__file__', '__name__', '__package__', '_abcoll', '_chain', '_class_template', '_eq', '_field_template', '_get_ident', '_heapq', '_imap', '_iskeyword', '_itemgetter', '_repeat', '_repr_template', '_starmap', '_sys', 'defaultdict', 'deque', 'namedtuple']
>>> dir(collections)
['Callable', 'Container', 'Counter', 'Hashable', 'ItemsView', 'Iterable', 'Iterator', 'KeysView', 'Mapping', 'MappingView', 'MutableMapping', 'MutableSequence', 'MutableSet', 'OrderedDict', 'Sequence', 'Set', 'Sized', 'ValuesView', '__all__', '__builtins__', '__doc__', '__file__', '__name__', '__package__', '_abcoll', '_chain', '_class_template', '_eq', '_field_template', '_get_ident', '_heapq', '_imap', '_iskeyword', '_itemgetter', '_repeat', '_repr_template', '_starmap', '_sys', 'defaultdict', 'deque', 'namedtuple']
>>> 
>>> type(collections)
<type 'module'>
>>> dir()
['__builtins__', '__doc__', '__name__', '__package__', 'collections', 'x']
>>> 
>>> def f(x):
	pass

>>> type(f)
<type 'function'>
>>> dir()
['__builtins__', '__doc__', '__name__', '__package__', 'collections', 'f', 'x']
>>> class Router:
	pass

>>> # Classes make objects.   Classes are objects.  Therefore, there are classes that make classes.
>>> #                                                 ^-- Metaclasses
>>> type(Router)
<type 'classobj'>
>>> Router.__class__

Traceback (most recent call last):
  File "<pyshell#133>", line 1, in <module>
    Router.__class__
AttributeError: class Router has no attribute '__class__'
>>> type(Router)
<type 'classobj'>
>>> 
>>> 
>>> 
>>> 
>>> # Four assigning words:      =      import      def       class
>>> 
>>> def f(a, b, c):
	print a, b, c

	
>>> a = 100
>>> f(1, 2, 3)
1 2 3
>>> a
100
>>> globals()['a']
100
>>> def f(a, b, c):
	print locals()
	print a, b, c

	
>>> f(1, 2, 3)
{'a': 1, 'c': 3, 'b': 2}
1 2 3
>>> globals()['a']
100
>>> 
>>> 
>>> def f(a, b, c):
	d = a + b + c
	print locals()
	print a, b, c

	
>>> d = 200
>>> f(1, 2, 3)
{'a': 1, 'c': 3, 'b': 2, 'd': 6}
1 2 3
>>> d
200
>>> 
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> 
>>> d = 300
>>> print locals()['d']
300
>>> print globals()['d']
300
>>> 
>>> # At the module level, globals() and locals() are the same dictionary
>>> 
>>> 
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> # At the module level, globals() and locals() are the same dictionary
>>> 
>>> locals() == globals()
True
>>> 
>>> 
>>> # Four assigning words:      =      import      def       class
>>> 
>>> 
>>> 
>>> # Four assigning words:      =      import      def       class
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> # At the module level, globals() and locals() are the same dictionary
>>> 
>>> def f(a, b, c):
	d = a + b + c
	import random
	class Switch:
		pass
	def g(z):
		pass
	print locals()

	
>>> f(1, 2, 3)
{'a': 1, 'c': 3, 'b': 2, 'd': 6, 'g': <function g at 0x104b662a8>, 'random': <module 'random' from '/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/random.pyc'>, 'Switch': <class __main__.Switch at 0x104b4adb8>}
>>> 
>>> 
>>> # Four assigning words:      =      import      def       class
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> # At the module level, globals() and locals() are the same dictionary
>>> 
>>> a = 100
>>> def f(a, b, c):
	return a, b, c, d

>>> d = 200
>>> f(1, 2, 3)
(1, 2, 3, 200)
>>> def f(a, b, c):
	return a, b, c, d, len('hello')

>>> f(1, 2, 3)
(1, 2, 3, 200, 5)
>>> dir()
['Router', '__builtins__', '__doc__', '__name__', '__package__', 'a', 'collections', 'd', 'f', 'x']
>>> __builtins__.len('hello')
5
>>> def len(obj):
	return 42

>>> dir()
['Router', '__builtins__', '__doc__', '__name__', '__package__', 'a', 'collections', 'd', 'f', 'len', 'x']
>>> len('xyz')
42
>>> __builtins__.len('xyz')
3
>>> f(1, 2, 3)
(1, 2, 3, 200, 42)
>>> del len
>>> f(1, 2, 3)
(1, 2, 3, 200, 5)
>>> # Four assigning words:      =      import      def       class
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> # At the module level, globals() and locals() are the same dictionary
>>> # Rule of lookups:     locals() -> globals() -> __builtins__ -> NameError
>>> 
>>> 
>>> xyz

Traceback (most recent call last):
  File "<pyshell#225>", line 1, in <module>
    xyz
NameError: name 'xyz' is not defined
>>> 
>>> 
>>> 
>>> def f(x):
	def g(y):
		return x, y, z
	print 'The answer is', g(20)

	
>>> z = 10
>>> x = 0
>>> 
>>> f(5)
The answer is (5, 20, 10)
>>> # Four assigning words:      =      import      def       class
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> # At the module level, globals() and locals() are the same dictionary
>>> # Rule of lookups:     locals() -> nested_scope -> globals() -> __builtins__ -> NameError
>>> 
>>> 
>>> 
>>> def f(x):
	def g(y):
		return x, y, z
	return g

>>> h = f(5)
>>> h.__name__
'g'
>>> g(20)

Traceback (most recent call last):
  File "<pyshell#256>", line 1, in <module>
    g(20)
NameError: name 'g' is not defined
>>> h(20)
(5, 20, 10)
>>> # Functions know:  __class__  __name__  __doc__  __code__  __closure__
>>> h.__closure__
(<cell at 0x104b62c20: int object at 0x10030c098>,)
>>> h.__closure__[0]
<cell at 0x104b62c20: int object at 0x10030c098>
>>> h.__closure__[0].cell_contents
5
>>> 
>>> 
>>> def f(x):
	def g(y):
		return x, y, z
	return g

>>> 
>>> 
>>> 
>>> 
>>> 
>>> def f(x):
	def g(y):
		'This is the inner function'
		return x, y, z
	return g

>>> h = g(5)

Traceback (most recent call last):
  File "<pyshell#273>", line 1, in <module>
    h = g(5)
NameError: name 'g' is not defined
>>> 
>>> 
>>> 
>>> 
>>> 

>>> 


>>> def f(x):
	def g(y):
		'This is the inner function'
		return x, y, z
	return g

>>> h = f(5)
>>> i = f(6)
>>> j = f(7)
>>> 
>>> 
>>> h(20)
(5, 20, 10)
>>> i(20)
(6, 20, 10)
>>> j(20)
(7, 20, 10)
>>> 
>>> [func.__class__ for func in [h, i, j]]
[<type 'function'>, <type 'function'>, <type 'function'>]
>>> [func.__name__ for func in [h, i, j]]
['g', 'g', 'g']
>>> [func.__doc__ for func in [h, i, j]]
['This is the inner function', 'This is the inner function', 'This is the inner function']
>>> [func.__code__.co_code for func in [h, i, j]]
['\x88\x00\x00|\x00\x00t\x00\x00f\x03\x00S', '\x88\x00\x00|\x00\x00t\x00\x00f\x03\x00S', '\x88\x00\x00|\x00\x00t\x00\x00f\x03\x00S']
>>> [func.__closure__[0].cell_contents for func in [h, i, j]]
[5, 6, 7]
>>> 
>>> # Four assigning words:      =      import      def       class
>>> # Rule of assignments:  All assignments go into locals unless explicitly declared as global
>>> # At the module level, globals() and locals() are the same dictionary
>>> # Rule of lookups:     locals() -> nested_scope/closure -> globals() -> __builtins__ -> NameError
>>> # What is the purpose of a def-in-a-def?
>>> #   The outer functions is used to make many other functions
>>> #   that have the same __class__, __name__, __doc__, __code__.co_code
>>> #   but differ in the __closure__ which is the nested namespace when the inner function was made
>>> 
>>> 
>>> 
>>> 
>>> 
>>> s = [10, 20, 30]
>>> a, b, c = s
>>> 
>>> 
>>> map(ord, range(10))

Traceback (most recent call last):
  File "<pyshell#314>", line 1, in <module>
    map(ord, range(10))
TypeError: ord() expected string of length 1, but int found
>>> map(square, range(10))

Traceback (most recent call last):
  File "<pyshell#315>", line 1, in <module>
    map(square, range(10))
NameError: name 'square' is not defined
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> map(square, range(10))
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
>>> map(ord, 'Raymond')
[82, 97, 121, 109, 111, 110, 100]
>>> 
>>> 
>>> 
>>> 
>>> a = pow(2, 2)
>>> a
4
>>> b = pow(2, 3)
>>> 
>>> a = pow(2, 2)
>>> b = pow(2, 3)
>>> def twopow(exp):
	return pow(2, exp)

>>> a = twopow(2)
>>> b = twopow(3)
>>> 
>>> 
>>> map(twopow, range(2, 10))
[4, 8, 16, 32, 64, 128, 256, 512]
>>> 
>>> 
>>> def twopow(exp):
	return pow(2, exp)

>>> a, b, c, d, e, f, g, h = map(twopow, range(2, 10))
>>> def threepow(exp):
	return pow(3, exp)

>>> twopow(5)
32
>>> threepow(5)
243
>>> def fourpow(exp):
	return pow(4, exp)

>>> def makepow(base):
	def somepow(exp):
		return pow(base, exp)
	return somepow

>>> twopow = makepow(2)
>>> threepow = makepow(3)
>>> 
>>> twopow(5)
32
>>> threepow(5)
243
>>> [func.__class__ for func in [twopow, threepow]]
[<type 'function'>, <type 'function'>]
>>> [func.__name__ for func in [twopow, threepow]]
['somepow', 'somepow']
>>> [func.__doc__ for func in [twopow, threepow]]
[None, None]
>>> [func.__code__.co_code for func in [twopow, threepow]]
['t\x00\x00\x88\x00\x00|\x00\x00\x83\x02\x00S', 't\x00\x00\x88\x00\x00|\x00\x00\x83\x02\x00S']
>>> [func.__closure__[0].cell_value for func in [twopow, threepow]]

Traceback (most recent call last):
  File "<pyshell#360>", line 1, in <module>
    [func.__closure__[0].cell_value for func in [twopow, threepow]]
AttributeError: 'cell' object has no attribute 'cell_value'
>>> [func.__closure__[0].cellvalue for func in [twopow, threepow]]

Traceback (most recent call last):
  File "<pyshell#361>", line 1, in <module>
    [func.__closure__[0].cellvalue for func in [twopow, threepow]]
AttributeError: 'cell' object has no attribute 'cellvalue'
>>> dir(func.__closure__[0])
['__class__', '__cmp__', '__delattr__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'cell_contents']
>>> [func.__closure__[0].cell_contents for func in [twopow, threepow]]
[2, 3]
>>> 
>>> 
>>> def makepow(base):
	def somepow(exp):
		return pow(base, exp)
	return somepow

>>> twopow, threepow, fourpow, fivepow, sixpow, sevenpow, eightpow, ninepow, tenpow = map(makepow,range(2, 11))
>>> sixpow(3)
216
>>> sevenpow(3)
343
>>> 
>>> 
>>> 
>>> 
>>> 
>>> x = 10
>>> import math
>>> y = math.cos(x)
>>> 
>>> orig_cos = math.cos
>>> def logging_cos(x):
	'Wrap math.cos() to add input and output printing'
	print 'The cos() function was called with {!r}'.format(x)
	answer = orig_cos(x)
	print 'The answer is {!r}'.format(answer)
	return answer

>>> logging_cos(5)
The cos() function was called with 5
The answer is 0.2836621854632263
0.2836621854632263
>>> math.cos = logging_cos
>>> 
>>> x = 10
>>> y = math.cos(x)
The cos() function was called with 10
The answer is -0.8390715290764524
>>> 
>>> y = math.sin(x)
>>> 
>>> orig_sin = math.sin
>>> def logging_sin(x):
	'Wrap math.sin() to add input and output printing'
	print 'The sin() function was called with {!r}'.format(x)
	answer = orig_sin(x)
	print 'The answer is {!r}'.format(answer)
	return answer

>>> math.sin = logging_sin
>>> y = math.sin(x)
The sin() function was called with 10
The answer is -0.5440211108893699
>>> y = math.cos(x)
The cos() function was called with 10
The answer is -0.8390715290764524
>>> import math
>>> dir(math)
['__doc__', '__file__', '__name__', '__package__', 'acos', 'acosh', 'asin', 'asinh', 'atan', 'atan2', 'atanh', 'ceil', 'copysign', 'cos', 'cosh', 'degrees', 'e', 'erf', 'erfc', 'exp', 'expm1', 'fabs', 'factorial', 'floor', 'fmod', 'frexp', 'fsum', 'gamma', 'hypot', 'isinf', 'isnan', 'ldexp', 'lgamma', 'log', 'log10', 'log1p', 'modf', 'pi', 'pow', 'radians', 'sin', 'sinh', 'sqrt', 'tan', 'tanh', 'trunc']
>>> 
>>> def add_logging(orig_func):
	def logging_func(x):
		print 'The {0} () function was called with {1!r}'.format(orig_func.__name__, x)
		answer = orig_func(x)
		print 'The answer is {!r}'.format(answer)
		return answer
	return logging_func

>>> math.tan = add_logging(math.tan)
>>> math.exp = add_logging(math.exp)
>>> 
>>> y = math.cos(x)
The cos() function was called with 10
The answer is -0.8390715290764524
>>> y = math.sin(x)
The sin() function was called with 10
The answer is -0.5440211108893699
>>> y = math.tax(x)

Traceback (most recent call last):
  File "<pyshell#416>", line 1, in <module>
    y = math.tax(x)
AttributeError: 'module' object has no attribute 'tax'
>>> y = math.tan(x)
The tan () function was called with 10
The answer is 0.6483608274590867
>>> y = math.exp(x)
The exp () function was called with 10
The answer is 22026.465794806718
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> x = 10
>>> y = square(x)
The square () function was called with 10
The answer is 100
>>> y = cube(x)
The cube () function was called with 10
The answer is 1000
>>> y = collatz(x)
The collatz () function was called with 10
The answer is 5
>>> y = big_func(x)
The big_func () function was called with 10
Doing hard work
The answer is 11
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> x = 10
>>> y = square(x)
The square () function was called with 10
The answer is 100
>>> y = cube(x)
The cube () function was called with 10
The answer is 1000
>>> y = collatz(x)
The collatz () function was called with 10
The answer is 5
>>> y = big_func(x)
The big_func () function was called with 10
Doing hard work
The answer is 11
>>> 
>>> 
>>> 
>>> 
>>> y = big_func(10)
The big_func () function was called with 10
Doing hard work
The answer is 11
>>> y = big_func(20)
The big_func () function was called with 20
Doing hard work
The answer is 21
>>> y = big_func(10)
The big_func () function was called with 10
Doing hard work
The answer is 11
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> big_func(10)
Doing hard work
11
>>> big_func(20)
Doing hard work
21
>>> bf_answers
{10: 11, 20: 21}
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> big_func(10)
Doing hard work
11
>>> big_func(20)
Doing hard work
21
>>> big_func(10)
11
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> big_func(10)
Doing hard work
11
>>> big_func(20)
Doing hard work
21
>>> big_func(10)
11
>>> square(10)
100
>>> square(20)
400
>>> square(10)
100
>>> bf_answers
{10: 11, 20: 21}
>>> sq_answers
{10: 100, 20: 400}
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> big_func(10)
The big_func () function was called with 10
Doing hard work
The answer is 11
11
>>> big_func(20)
The big_func () function was called with 20
Doing hard work
The answer is 21
21
>>> big_func(10)
11
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> big_func(10)
The inner () function was called with 10
Doing hard work
The answer is 11
11
>>> big_func(10)
The inner () function was called with 10
The answer is 11
11
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> 
>>> 
>>> 
>>> c = 'a'
>>> n = ord(c)
>>> 
>>> ord = add_logging(ord)
>>> n = ord(c)
The ord () function was called with 'a'
The answer is 97
>>> 
>>> 
>>> pow(2, 5)
32
>>> pow(5, 2)
25
>>> pow(2, 5)
32
>>> pow(5, 2)
25
>>> pow = cache(pow)
>>> pow(2, 5)

Traceback (most recent call last):
  File "<pyshell#470>", line 1, in <module>
    pow(2, 5)
TypeError: inner() takes exactly 1 argument (2 given)
>>> 
>>> 
>>> 
>>> def f(a, b, *args):
	print a
	print b
	print args

	
>>> f(10, 20, 30, 40, 50)
10
20
(30, 40, 50)
>>> 
>>> 
>>> t = (2, 5)
>>> pow(t[0], t[1])

Traceback (most recent call last):
  File "<pyshell#483>", line 1, in <module>
    pow(t[0], t[1])
TypeError: inner() takes exactly 1 argument (2 given)
>>> del pow
>>> pow(t[0], t[1])
32
>>> pow(*t)
32
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> big_func(10)
The big_func () function was called with 10
Doing hard work
The answer is 11
11
>>> big_func(10)
11
>>> pow = cache(pow)
>>> pow(2, 5)
32
>>> pow(5, 2)
25
>>> pow(2, 5)
32
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> x = 10
>>> y = square(10)
The square () function was called with (10,)
The answer is 100
>>> 
>>> pow = add_logging(pow)
>>> x = 2
>>> y = 5
>>> z = pow(x, y)
The pow () function was called with (2, 5)
The answer is 32
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> square.__name__
'inner'
>>> square.__doc__
'Compute a value times itself'
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> square.__name__
'inner'
>>> square.__doc__
>>> square.__doc__ is None
True
>>> help(square)
Help on function inner in module __main__:

inner(*args)

>>> from dis import dis
>>> dis(square)
 39           0 LOAD_FAST                0 (args)
              3 LOAD_DEREF               0 (answers)
              6 COMPARE_OP               6 (in)
              9 POP_JUMP_IF_FALSE       20

 40          12 LOAD_DEREF               0 (answers)
             15 LOAD_FAST                0 (args)
             18 BINARY_SUBSCR       
             19 RETURN_VALUE        

 41     >>   20 LOAD_DEREF               1 (orig_func)
             23 LOAD_FAST                0 (args)
             26 CALL_FUNCTION_VAR        0
             29 STORE_FAST               1 (answer)

 42          32 LOAD_FAST                1 (answer)
             35 LOAD_DEREF               0 (answers)
             38 LOAD_FAST                0 (args)
             41 STORE_SUBSCR        

 43          42 LOAD_FAST                1 (answer)
             45 RETURN_VALUE        
>>> 
>>> 
>>> 
>>> help(square)
Help on function inner in module __main__:

inner(*args)

>>> help(collatz)
Help on function inner in module __main__:

inner(*args)

>>> help(big_func)
Help on function inner in module __main__:

inner(*args)

>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> 
>>> 
>>> square.__name__
'logging_func'
>>> square.__doc__
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> help(square)
Help on function square in module __main__:

square(*args)
    square

>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> help(square)
Help on function square in module __main__:

square(*args)
    Compute a value times itself

>>> help(cube)
Help on function cube in module __main__:

cube(*args)
    Compute a value times itself thrice

>>> help(big_func)
Help on function big_func in module __main__:

big_func(*args)
    Simulate slow labor intensive function

>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/decorator_school.py ======
>>> help(square)
Help on function square in module __main__:

square(*args)
    Compute a value times itself

>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/fibo.py ============
>>> for i in range(12):
	print i, fibo(i)

	
0 0
1 1
2 1
3 2
4 3
5 5
6 8
7 13
8 21
9 34
10 55
11 89
>>> 
>>> 
>>> a = 5
>>> b = 8
>>> t = (b, a+b)
>>> t
(8, 13)
>>> a, b = t
>>> 
>>> 
>>> a = t[0]
>>> b = t[1]
>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/fibo.py ============
>>> for i in range(12):
	print i, fibo(i)

	
0 0
1 1
2 1
3 2
4 3
5 5
6 8
7 13
8 21
9 34
10 55
11 89
>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/fibo.py ============
280571172992510140037611932413038677189525
>>> 
>>> 
>>> 
>>> # Micro-webframeworks:  Connect applications to webservers
>>> #          chess()  <---  /funstuff/games.php
>>> #         function  <---  path or route or url
>>> 
>>> # Itty   Bottle Flask ...
>>> 
>>> 
>>> # Suggestion:  Read the source for bottle.py
>>> 
>>> 
>>> # copy notes2/bottle.py .
>>> import bottle
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:05:11] "GET / HTTP/1.1" 404 720
127.0.0.1 - - [29/Sep/2016 16:05:11] "GET /favicon.ico HTTP/1.1" 404 742
127.0.0.1 - - [29/Sep/2016 16:05:29] "GET / HTTP/1.1" 404 720

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:08:12] "GET / HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:09:09] "GET / HTTP/1.1" 200 6

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:09:54] "GET / HTTP/1.1" 200 17
127.0.0.1 - - [29/Sep/2016 16:11:32] "GET / HTTP/1.1" 200 17
127.0.0.1 - - [29/Sep/2016 16:11:48] "GET / HTTP/1.1" 200 17

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:17:06] "GET / HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:17:17] "GET / HTTP/1.1" 200 17

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:19:26] "GET / HTTP/1.1" 200 6
>>> import time
>>> time.time()
1475191316.812406
>>> time.ctime()
'Thu Sep 29 16:22:03 2016'
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:23:06] "GET / HTTP/1.1" 200 17
127.0.0.1 - - [29/Sep/2016 16:23:11] "GET /now HTTP/1.1" 200 24
127.0.0.1 - - [29/Sep/2016 16:23:17] "GET /now HTTP/1.1" 200 24
127.0.0.1 - - [29/Sep/2016 16:23:19] "GET /now HTTP/1.1" 200 24
127.0.0.1 - - [29/Sep/2016 16:23:22] "GET /now HTTP/1.1" 200 24
127.0.0.1 - - [29/Sep/2016 16:23:24] "GET /now HTTP/1.1" 200 24

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:24:46] "GET /now HTTP/1.1" 200 24
127.0.0.1 - - [29/Sep/2016 16:24:51] "GET / HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:24:58] "GET /now HTTP/1.1" 200 24
127.0.0.1 - - [29/Sep/2016 16:25:12] "GET / HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:25:18] "GET / HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:25:20] "GET / HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:25:22] "GET /now HTTP/1.1" 200 24
>>> word = 'hello'
>>> word.upper()
'HELLO'
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:27:15] "GET /upper/superman HTTP/1.1" 200 8
127.0.0.1 - - [29/Sep/2016 16:27:26] "GET /batman HTTP/1.1" 404 732
127.0.0.1 - - [29/Sep/2016 16:27:36] "GET /upper/batman HTTP/1.1" 200 6
127.0.0.1 - - [29/Sep/2016 16:27:42] "GET /upper/superman HTTP/1.1" 200 8
>>> 
>>> 
>>> query = dict(radius='10')
>>> float(query['radius'])
10.0
>>> query = dict(radis='10')
>>> float(query['radius'])

Traceback (most recent call last):
  File "<pyshell#571>", line 1, in <module>
    float(query['radius'])
KeyError: 'radius'
>>> float(query.get('radius', '0.0'))
0.0
>>> query = dict(radius='10')
>>> float(query.get('radius', '0.0'))
10.0
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:35:44] "GET /area/circle?radius=10 HTTP/1.1" 200 7
127.0.0.1 - - [29/Sep/2016 16:35:51] "GET /area/circle?radius=12 HTTP/1.1" 200 9
127.0.0.1 - - [29/Sep/2016 16:35:56] "GET /area/circle?radius=10 HTTP/1.1" 200 7
127.0.0.1 - - [29/Sep/2016 16:36:16] "GET /upper/superman HTTP/1.1" 200 8
127.0.0.1 - - [29/Sep/2016 16:36:19] "GET /area/circle?radius=10 HTTP/1.1" 200 7
127.0.0.1 - - [29/Sep/2016 16:37:00] "GET /area/circle?radius=10 HTTP/1.1" 200 7

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:38:16] "GET /area/circle?radius=10 HTTP/1.1" 200 71
127.0.0.1 - - [29/Sep/2016 16:39:14] "GET /area/circle?radius=10 HTTP/1.1" 200 71
127.0.0.1 - - [29/Sep/2016 16:48:35] "GET /area/circle?rads=15 HTTP/1.1" 200 55
127.0.0.1 - - [29/Sep/2016 16:49:09] "GET /area/circle?rads=15 HTTP/1.1" 200 55
Traceback (most recent call last):
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/bottle.py", line 862, in _handle
    return route.call(**args)
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/bottle.py", line 1732, in wrapper
    rv = callback(*a, **ka)
  File "/Users/raymond/Dropbox/Public/sj149/rest_api_server.py", line 26, in circle_area_service
    radius = float(request.query.get('radius', '0.0'))
ValueError: could not convert string to float: xyz
127.0.0.1 - - [29/Sep/2016 16:49:19] "GET /area/circle?radius=xyz HTTP/1.1" 500 763

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:52:52] "GET /area/circle?radius=xyz HTTP/1.1" 200 48
127.0.0.1 - - [29/Sep/2016 16:53:16] "GET /area/circle?radius=xyz HTTP/1.1" 200 48
127.0.0.1 - - [29/Sep/2016 16:56:58] "GET /area/circle?radius=10 HTTP/1.1" 200 71

====== RESTART: /Users/raymond/Dropbox/Public/sj149/rest_api_server.py ======
Bottle v0.12.9 server starting up (using WSGIRefServer())...
Listening on http://localhost:8080/
Hit Ctrl-C to quit.

127.0.0.1 - - [29/Sep/2016 16:57:56] "GET /area/circle?radius=10 HTTP/1.1" 200 70
127.0.0.1 - - [29/Sep/2016 16:59:09] "GET /area/circle?radius=10 HTTP/1.1" 200 70
127.0.0.1 - - [29/Sep/2016 16:59:14] "GET /area/circle?radius=10 HTTP/1.1" 200 70
>>> 
