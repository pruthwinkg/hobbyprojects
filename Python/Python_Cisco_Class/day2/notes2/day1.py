Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 26 2016, 12:10:39) 
[GCC 4.2.1 (Apple Inc. build 5666) (dot 3)] on darwin
Type "copyright", "credits" or "license()" for more information.
>>> 

>>> 

>>> # Welcome to Python for Engineers -- Part II
>>> # The class website is at:   http://bit.ly/python-sj149
>>> # Python 2.7.12 install instructions: http://bit.ly/py-install
>>> 

>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> __name__
'__main__'
>>> __doc__
' Fancy, expensive math package for wealthy people\n    who have forgotten all algebra since the 7th grade.\n'
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> __doc__ is None
True
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> help(area)
Help on function area in module __main__:

area(radius)
    Compute the area of circle

>>> area(10)
314.15700000000004
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
>>> help(area)
Help on function area in module __main__:

area(radius)
    Compute the area of circle
    
    >>> area(10)
    314.15700000000004

>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
**********************************************************************
File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 13, in __main__.area
Failed example:
    area(10)
Expected:
    314.15700000000004
Got:
    2495.4377523627604
**********************************************************************
1 items had failures:
   1 of   1 in __main__.area
***Test Failed*** 1 failures.
TestResults(failed=1, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
**********************************************************************
File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 13, in __main__.area
Failed example:
    area(10)
Expected:
    314.15700000000004
Got:
    395.5002305930203
**********************************************************************
1 items had failures:
   1 of   1 in __main__.area
***Test Failed*** 1 failures.
TestResults(failed=1, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> 30 + 40
70
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> area_triangle(10, 15)
75
>>> area_triangle(3, 5)
7
>>> 5 / 2
2
>>> # (int / int) -> int
>>> 45 / 7
6
>>> from __future__ import division
>>> 5 / 2
2.5
>>> 5 // 2
2
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=1)
>>> area_triangle(3, 5)
7.5
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=2)
>>> help(area_triangle)
Help on function area_triangle in module __main__:

area_triangle(base, height)
    Return the area of a triangle
    
    >>> area_triangle(3, 5)
    7.5

>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=2)
>>> area_triangle(-10, 20)
-100.0
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=2)
>>> area_triangle(-10, 20)

Traceback (most recent call last):
  File "<pyshell#24>", line 1, in <module>
    area_triangle(-10, 20)
  File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 29, in area_triangle
    raise RuntimeError('Imaginary numbers not applicable in Kronecker spaces')
RuntimeError: Imaginary numbers not applicable in Kronecker spaces
>>> 
>>> # Abort, Retry or Fail?
>>> 
>>> 
>>> # sin(x)       sine(x)
>>> # cos(x)       cosine(x)
>>> 
>>> 
>>> 2 ^ 5
7
>>> 2 ** 5
32
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=2)
>>> quadratic(a=12, b=23, c=10)
(-0.6666666666666666, -1.25)
>>> 
>>> x1, x2 = quadratic(a=12, b=23, c=10)
>>> x1
-0.6666666666666666
>>> x2
-1.25
>>> 12*x1**2 + 23*x1 + c

Traceback (most recent call last):
  File "<pyshell#40>", line 1, in <module>
    12*x1**2 + 23*x1 + c
NameError: name 'c' is not defined
>>> 
>>> 
>>> x1, x2 = quadratic(a=12, b=23, c=10)
>>> x1
-0.6666666666666666
>>> x2
-1.25
>>> 12*x1**2 + 23*x1 + 10
0.0
>>> 12*x2**2 + 23*x2 + 10
0.0
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=7)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
**********************************************************************
File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 47, in __main__.quadratic
Failed example:
    x2
Expected:
    -1.25
Got:
    -0.25
**********************************************************************
File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 51, in __main__.quadratic
Failed example:
    12*x2**2 + 23*x2 + 10
Expected:
    0.0
Got:
    5.0
**********************************************************************
1 items had failures:
   2 of   5 in __main__.quadratic
***Test Failed*** 2 failures.
TestResults(failed=2, attempted=7)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=7)
>>> 3 + 4j
(3+4j)
>>> 
>>> 
>>> # Run tracing with:
>>> # $ python -m trace --count algebra.py
>>> # output goes to algebra.cover
>>> import algebra
>>> help(algebra)
Help on module algebra:

NAME
    algebra

FILE
    /Users/raymond/Dropbox/Public/sj149/algebra.py

DESCRIPTION
    Fancy, expensive math package for wealthy people
    who have forgotten all algebra since the 7th grade.

FUNCTIONS
    area(radius)
        Compute the area of circle
        
        >>> area(10)
        314.15700000000004
    
    area_triangle(base, height)
        Return the area of a triangle
        
        >>> area_triangle(3, 5)
        7.5
    
    quadratic(a, b, c)
        Return the two roots of the quadratic equation:
        
            ax^2 + bx + c = 0
        
        written in Python as:
        
            a*x**2 + b*x + c == 0
        
        For example:
        
            >>> x1, x2 = quadratic(a=12, b=23, c=10)
            >>> x1
            -0.6666666666666666
            >>> x2
            -1.25
            >>> 12*x1**2 + 23*x1 + 10
            0.0
            >>> 12*x2**2 + 23*x2 + 10
            0.0

DATA
    division = _Feature((2, 2, 0, 'alpha', 2), (3, 0, 0, 'alpha', 0), 8192...
    pi = 3.14157


>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=7)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/algebra.py ==========
TestResults(failed=0, attempted=7)
>>> >>> x1
-0.6666666666666666
>>> x2
-1.25
>>> 12*x1**2 + 23*x1 + 10
0.0
>>> 12*x2**2 + 23*x2 + 10
0.0
SyntaxError: invalid syntax
>>> 
>>> dir(object)
['__class__', '__delattr__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__']
>>> # print s                  ->   s.__str__()
>>> # >>> s                    ->   s.__repr__()
>>> 
>>> s = 'cat'
>>> print s
cat
>>> s
'cat'
>>> s.__str__()
'cat'
>>> s.__repr__()
"'cat'"
>>> 
>>> 
>>> s = 'cat
SyntaxError: EOL while scanning string literal
>>> s = 'cat'
>>> s[0]
'c'
>>> s.__getitem__(0)
'c'
>>> dir(str)
['__add__', '__class__', '__contains__', '__delattr__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getnewargs__', '__getslice__', '__gt__', '__hash__', '__init__', '__le__', '__len__', '__lt__', '__mod__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '_formatter_field_name_split', '_formatter_parser', 'capitalize', 'center', 'count', 'decode', 'encode', 'endswith', 'expandtabs', 'find', 'format', 'index', 'isalnum', 'isalpha', 'isdigit', 'islower', 'isspace', 'istitle', 'isupper', 'join', 'ljust', 'lower', 'lstrip', 'partition', 'replace', 'rfind', 'rindex', 'rjust', 'rpartition', 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith', 'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']
>>> 
>>> len(s)
3
>>> s.__len__()
3
>>> # iterable
>>> for c in s:
	print c.upper()

	
C
A
T
>>> it = iter(s)
>>> type(s)
<type 'str'>
>>> type(it)
<type 'iterator'>
>>> next(it)
'c'
>>> next(it)
'a'
>>> next(it)
't'
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#87>", line 1, in <module>
    next(it)
StopIteration
>>> 
>>> dir(str)
['__add__', '__class__', '__contains__', '__delattr__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getnewargs__', '__getslice__', '__gt__', '__hash__', '__init__', '__le__', '__len__', '__lt__', '__mod__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '_formatter_field_name_split', '_formatter_parser', 'capitalize', 'center', 'count', 'decode', 'encode', 'endswith', 'expandtabs', 'find', 'format', 'index', 'isalnum', 'isalpha', 'isdigit', 'islower', 'isspace', 'istitle', 'isupper', 'join', 'ljust', 'lower', 'lstrip', 'partition', 'replace', 'rfind', 'rindex', 'rjust', 'rpartition', 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith', 'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']
>>> for c in s:
	print c.upper()

	
C
A
T
>>> c = s.__getitem__(0); print c.upper()
C
>>> c = s.__getitem__(1); print c.upper()
A
>>> c = s.__getitem__(2); print c.upper()
T
>>> c = s.__getitem__(3); print c.upper()

Traceback (most recent call last):
  File "<pyshell#95>", line 1, in <module>
    c = s.__getitem__(3); print c.upper()
IndexError: string index out of range
>>> 
>>> 
>>> dir(list)
['__add__', '__class__', '__contains__', '__delattr__', '__delitem__', '__delslice__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getslice__', '__gt__', '__hash__', '__iadd__', '__imul__', '__init__', '__iter__', '__le__', '__len__', '__lt__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__reversed__', '__rmul__', '__setattr__', '__setitem__', '__setslice__', '__sizeof__', '__str__', '__subclasshook__', 'append', 'count', 'extend', 'index', 'insert', 'pop', 'remove', 'reverse', 'sort']
>>> 
>>> s = [10, 20, 30]
>>> for x in s:
	print x ** 2

	
100
400
900
>>> it = iter(s)
>>> type(s)
<type 'list'>
>>> type(it)
<type 'listiterator'>
>>> x = next(it); print x ** 2
100
>>> x = next(it); print x ** 2
400
>>> x = next(it); print x ** 2
900
>>> x = next(it); print x ** 2

Traceback (most recent call last):
  File "<pyshell#110>", line 1, in <module>
    x = next(it); print x ** 2
StopIteration
>>> s.__iter__()
<listiterator object at 0x103ba5cd0>
>>> 
>>> 
>>> 
>>> 
>>> 'hello'.upper()
'HELLO'
>>> 2 + 5 - 1
6
>>> t = 2 + 5
>>> t - 1
6
>>> 'hello' . upper ()
'HELLO'
>>> bm = 'hello' . upper
>>> bm()
'HELLO'
>>> 
>>> def square(x):
	return x ** 2

>>> square(11)
121
>>> square.__call__(11)
121
>>> square.__class__
<type 'function'>
>>> square.__name__
'square'
>>> square.__doc__ is None
True
>>> square.__code__.co_code
'|\x00\x00d\x01\x00\x13S'
>>> ord('A')
65
>>> ord(' ')
32
>>> map(ord, square.__code__.co_code)
[124, 0, 0, 100, 1, 0, 19, 83]
>>> from dis import dis
>>> dis(square)
  2           0 LOAD_FAST                0 (x)
              3 LOAD_CONST               1 (2)
              6 BINARY_POWER        
              7 RETURN_VALUE        
>>> square.__call__(11)
121
>>> square(11)
121
>>> 
>>> f = square
>>> type(f)
<type 'function'>
>>> id(f)
4357513896
>>> id(square)
4357513896
>>> # Assignments never make copies
>>> 
>>> f(11)
121
>>> help(f)
Help on function square in module __main__:

square(x)

>>> f.__name__
'square'
>>> square.__name__
'square'
>>> square.__name__ = 'pointycircle'
>>> f.__name__
'pointycircle'
>>> help(f)
Help on function pointycircle in module __main__:

pointycircle(x)

>>> f.__doc__ = 'A circle smushed until its corners become pointy'
>>> help(square)
Help on function pointycircle in module __main__:

pointycircle(x)
    A circle smushed until its corners become pointy

>>> 
>>> bm = 'hello'.upper
>>> bm()
'HELLO'
>>> bm.__call__()
'HELLO'
>>> 
>>> object.__getattribute__('hello', 'upper')
<built-in method upper of str object at 0x103949a50>
>>> bm
<built-in method upper of str object at 0x103949a50>
>>> 
>>> 
>>> dir(object)
['__class__', '__delattr__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__']
>>> class Circle:
	pass

>>> Circle()
<__main__.Circle instance at 0x103baa290>
>>> class Circle(object):
	pass

>>> Circle()
<__main__.Circle object at 0x103bbcfd0>
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle(10)
<__main__.Circle object at 0x103962d90>
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> c = Circle(radius=10)
>>> vars(c)
{'rad': 10}
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> c = Circle(radius=10)
{'self': <__main__.Circle object at 0x10424dd90>, 'radius': 10}
>>> {'rad': 10}
{'rad': 10}
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
>>> __name__
'__main__'
>>> __doc__
"Show-off the ciruitous code from the user's point of view"
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous(tm)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
>>> print u'\N{snowman}'
☃
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> c = Circle(10)
>>> d = Circle(20)
>>> 
>>> c.__dict__
{'version': 0.1, 'radius': 10}
>>> vars(c)
{'version': 0.1, 'radius': 10}
>>> vars(d)
{'version': 0.1, 'radius': 20}
>>> 
>>> Circle.version

Traceback (most recent call last):
  File "<pyshell#188>", line 1, in <module>
    Circle.version
AttributeError: type object 'Circle' has no attribute 'version'
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.version
0.1
>>> c = Circle(10)
>>> d = Circle(20)
>>> vars(c)
{'radius': 10}
>>> vars(d)
{'radius': 20}
>>> c.version
0.1
>>> vars(Circle)
dict_proxy({'__module__': '__main__', 'area': <function area at 0x1006ff050>, 'version': 0.1, '__dict__': <attribute '__dict__' of 'Circle' objects>, '__weakref__': <attribute '__weakref__' of 'Circle' objects>, '__doc__': 'An advanced circle analytics toolkit for support circle analysis', '__init__': <function __init__ at 0x1006ff500>})
>>> 
>>> 
>>> dir(c)
['__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'area', 'radius', 'version']
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
>>> 
>>> # Kronecker:  God created the integers, all the rest is the work of man.
>>> 11 + 22 == 33
True
>>> type(1.1)
<type 'float'>
>>> 1.1 + 2.2 == 3.3
False
>>> s = 1.1 + 2.2
>>> t = 3.3
>>> 
>>> s
3.3000000000000003
>>> t
3.3
>>> 
>>> s == t
False
>>> 
>>> abs(s - t) < 0.00000001
True
>>> 
>>> 
>>> Circle.version + 0.7 <= 0.8
True
>>> from pprint import pprint
>>> pprint(sorted([
	'raymond',
	'rachel',
	'matthew',
]), width=20)
['matthew',
 'rachel',
 'raymond']
>>> pprint(sorted([
	(7, 1, 4),
	(5, 0, 2),
]), width=20)
[(5, 0, 2),
 (7, 1, 4)]
>>> pprint(sorted([
	(7, 1, 4),
	(5, 0, 2),
	(10, 0, 0),
	(5, -2, 88888),
]), width=20)
[(5, -2, 88888),
 (5, 0, 2),
 (7, 1, 4),
 (10, 0, 0)]
>>> pprint(sorted([
	(7, 1, 4),
	(5, 0, 2),
	(10, 0, 0),
	(5, -2, 88888),
	(10, 0, -5),
]), width=20)
[(5, -2, 88888),
 (5, 0, 2),
 (7, 1, 4),
 (10, 0, -5),
 (10, 0, 0)]
>>> pprint(sorted([
]), width=20)
[]
>>> pprint(sorted([
	(50, 'teach python'),
	(0, 'wake up'),
	(70, 'send bill'),
	(30, 'feed matthew'),
	(40, 'say goodbye to rachel'),
	(80, 'answer email')
	(90, 'go to bed'),
	(85, 'surf the net'),
]), width=40)

Traceback (most recent call last):
  File "<pyshell#226>", line 8, in <module>
    (90, 'go to bed'),
TypeError: 'tuple' object is not callable
>>> pprint(sorted([
	(50, 'teach python'),
	(0, 'wake up'),
	(70, 'send bill'),
	(30, 'feed matthew'),
	(40, 'say goodbye to rachel'),
	(80, 'answer email'),
	(90, 'go to bed'),
	(85, 'surf the net'),
]), width=40)
[(0, 'wake up'),
 (30, 'feed matthew'),
 (40, 'say goodbye to rachel'),
 (50, 'teach python'),
 (70, 'send bill'),
 (80, 'answer email'),
 (85, 'surf the net'),
 (90, 'go to bed')]
>>> 
>>> 0.1.1
SyntaxError: invalid syntax
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.version <= '0.2'
True
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
>>> 
>>> 
>>> 
>>> 
>>> target = '2.7.6'
>>> actual = '2.7.9'
>>> actual >= target
True
>>> actual = '2.7.12'
>>> actual >= target
False
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> target = (2, 7, 6)
>>> actual = (2, 6, 9)
>>> actual >= target
False
>>> actual = (2, 7, 9)
>>> actual >= target
True
>>> actual = (2, 7, 12)
>>> actual >= target
True
>>> 
>>> 
>>> 
>>> 
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version (0, 1, 1)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/client_code.py", line 6, in <module>
    print 'Circle version %s' % Circle.version
TypeError: not all arguments converted during string formatting
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version (0, 1, 1)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/client_code.py", line 6, in <module>
    print 'Circle version %d.%d' % Circle.version
TypeError: not all arguments converted during string formatting
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
>>> 
>>> 
>>> p = 170, 0.4, 0.6
>>> type(p)
<type 'tuple'>
>>> len(p)
3
>>> a, b, c = p
>>> a
170
>>> p[:2]
(170, 0.4)
>>> p[2]
0.6
>>> 
>>> 


>>> 



>>> # Problem:  The tuple is not self-documenting
>>> p = 170, 0.4, 0.6
>>> if p[1] >= 0.5:
	print 'Whew, that is bright!'

	
>>> if p[2] >= 0.5:
	print 'Whew, that is light!'

	
Whew, that is light!
>>> # Problem:  The tuple is not self-documenting
>>> # Problem:  Code with indexed access tends to reveal little or nothing about the context
>>> 
>>> from collections import namedtuple
>>> # a named tuple is a factory function for creating new tuple subclasses
>>> # a named tuple is a factory function for creating new tuple subclasses with named fields
>>> Color = namedtuple('Color', ['hue', 'saturation', 'luminosity'])
>>> issubclass(Color, tuple)
True
>>> p = Color(170, 0.4, 0.6)
>>> isinstance(p, Color)
True
>>> isinstance(p, tuple)
True
>>> len(p)
3
>>> p[0]
170
>>> p[:2]
(170, 0.4)
>>> a, b, c = p
>>> # __repr__
>>> p
Color(hue=170, saturation=0.4, luminosity=0.6)
>>> p.saturation
0.4
>>> # __getattribute__
>>> 
>>> if p.saturation >= 0.5:
	print 'Whew, that is bright!'

	
>>> if p.luminosity >= 0.5:
	print 'Whew, that is light!'

	
Whew, that is light!
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.version
(0, 1, 1)
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.version
Version(major=0, minor=1, micro=1)
>>> Circle.version > (0, 0, 1)
True
>>> Circle.version.major
0
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
>>> 
>>> 
>>> 
>>> 
>>> # http://bit.ly/python-sj149
>>> 
>>> 
>>> import time
>>> tuple(time.localtime())
(2016, 9, 26, 15, 47, 8, 0, 270, 1)
>>> # Problem:  The tuple is not self-documenting
>>> time.localtime()[3] - time.localtime()[-1]
14
>>> # Problem:  Code with indexed access tends to reveal little or nothing about the context
>>> 
>>> time.localtime()
time.struct_time(tm_year=2016, tm_mon=9, tm_mday=26, tm_hour=15, tm_min=48, tm_sec=57, tm_wday=0, tm_yday=270, tm_isdst=1)
>>> time.localtime().tm_hour - time.localtime().tm_isdst
14
>>> 
>>> 
>>> 270.0 / 365
0.7397260273972602
>>> 
>>> 
>>> 
>>> import sys
>>> sys.version
'2.7.12 (v2.7.12:d33e0cf91556, Jun 26 2016, 12:10:39) \n[GCC 4.2.1 (Apple Inc. build 5666) (dot 3)]'
>>> sys.version[:6] > '2.7.6'
False
>>> 
>>> 
>>> tuple(sys.version_info)
(2, 7, 12, 'final', 0)
>>> sys.version_info
sys.version_info(major=2, minor=7, micro=12, releaselevel='final', serial=0)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.1
>>> 
>>> from random import *
>>> random()
0.7165887758558559
>>> seed(8675309)
>>> random()
0.40224696110279223
>>> 
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.1
preliminary study using 10 random circles
seeded using Jenny's number: 8575309
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.1
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
>>> from random import *
>>> random()                       # 0.0 <= x < 1.0
0.5051415848866703
>>> random() * 52                  # 0.0 <= x < 52.0
6.185255120019846
>>> int(32.1)
32
>>> # There are many ways to convert a float an integer
>>> 
>>> int(12.3)
12
>>> int(-12.3)
-12
>>> # Odd function:  f(-x) == -f(x)       symmetric about the origin
>>> # Floating point concept:    signed integer plus a signed fractional part
>>> # int / frac
>>> 
>>> x = 12.3
>>> x - int(x)
0.3000000000000007
>>> x = -12.3
>>> x - int(x)
-0.3000000000000007
>>> -12 + -0.3000000000000007
-12.3
>>> 
>>> 
>>> 
>>> round(12.3)
12.0
>>> round(12.3, 0)
12.0
>>> # round() -> float that is closest to 12.3
>>> round(-12.3)
-12.0
>>> # round() is an  odd function that returns the float nearest the input
>>> 
>>> round(12.5)
13.0
>>> round(13.5)
14.0
>>> round(-12.5)
-13.0
>>> round(-13.5)
-14.0
>>> # round() is an  odd function that returns the float nearest the input (with half away from zero)
>>> # int() is a odd function that returns in int by chopping-off the signed fractional component
>>> 
>>> from math import *
>>> floor(3.14)
3.0
>>> floor(-3.14)
-4.0
>>> ceil(3.14)
4.0
>>> ceil(-3.14)
-3.0
>>> floor(3.0)
3.0
>>> ceil(3.0)
3.0
>>> # ceil/floor are assymmetric the orig, differ by 1 for non-integral inputs, the same for integral
>>> # and that output a float solely determined by up or down direction
>>> 
>>> # In Python 3, int/round/ceil/floor all return integers
>>> # The rounding mode for round() is now:  round-half-even or banker's rounding
>>> int(random() * 52)               # 0 <= x < 52
18
>>> # chunking
>>> # 7 +/- 2
>>> 
>>> 
>>> range(10)
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> len(range(10))
10
>>> range(2, 10)
[2, 3, 4, 5, 6, 7, 8, 9]
>>> len(range(2, 10)) == 10 - 2
True
>>> range(2, 10, 3)
[2, 5, 8]
>>> # START STOP STEP
>>> 
>>> randrange(52)
16
>>> range(52)
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51]
>>> 
>>> range(1000, 2000, 100)
[1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900]
>>> randrange(1000, 2000, 100)
1800
>>> randrange(1000, 2000, 100)
1400
>>> 
>>> 
>>> 
>>> int(random() * 52)
21
>>> randrange(52)
26
>>> outcomes = ['win', 'lose', 'draw']
>>> len(outcomes)
3
>>> int(random() * len(outcomes))
2
>>> outcomes[int(random() * len(outcomes))]            # Choose an outcome randomly
'draw'
>>> outcomes[randrange(len(outcomes))]                 # Choose an outcome randomly
'draw'
>>> choice(outcomes)
'win'
>>> 
>>> results = [choice(outcomes) for i in range(100)]
>>> len(results)
100
>>> results.count('win')
40
>>> results.count('lose')
35
>>> results.count('draw')
25
>>> help(list.count)
Help on method_descriptor:

count(...)
    L.count(value) -> integer -- return number of occurrences of value

>>> # seed randrange random choice
>>> # int round ceil floor
>>> # list.count
>>> # chucking
>>> # designing APIs in parallel
>>> 
>>> 
>>> # Bag with 3 marbles:  white black grey
>>> sample(outcomes, 2)
['draw', 'lose']
>>> sample(outcomes, 2)
['lose', 'win']
>>> # ^---- Sampling without replacement
>>> 
>>> 
>>> outcomes
['win', 'lose', 'draw']
>>> shuffle(outcomes)
>>> outcomes
['draw', 'lose', 'win']
>>> 
>>> 
>>> # sample(outcomes, 1)[0]         sample(outcomes, k)         sample(outcomes, len(outcomes))
>>> # choice(outcomes)                                           shuffle()
>>> # shuffle(); outcomes[0]         shuffle(); outcomes[:k]     shuffle()
>>> 
>>> 
>>> shuffle(outcomes, 6)

Traceback (most recent call last):
  File "<pyshell#437>", line 1, in <module>
    shuffle(outcomes, 6)
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/random.py", line 290, in shuffle
    j = _int(random() * (i+1))
TypeError: 'int' object is not callable
>>> sample(outcomes, 6)

Traceback (most recent call last):
  File "<pyshell#438>", line 1, in <module>
    sample(outcomes, 6)
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/random.py", line 323, in sample
    raise ValueError("sample larger than population")
ValueError: sample larger than population
>>> 
>>> 
>>> outcomes = ['red', 'green', 'green']
>>> shuffle(outcomes)
>>> outcomes
['red', 'green', 'green']
>>> shuffle(outcomes)
>>> outcomes
['green', 'green', 'red']
>>> sample(outcomes, 2)
['green', 'green']
>>> 
>>> range(52)
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51]
>>> xrange(52)
xrange(52)
>>> xrange(52)[3]
3
>>> xrange(1000, 2000, 100)[3]
1300
>>> 
>>> sorted(sample(xrange(1, 57), 6))
[7, 25, 27, 40, 49, 52]
>>> seed('raymond'); sorted(sample(xrange(1, 57), 6))
[11, 12, 16, 22, 23, 42]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.1
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[[...], [...], [...], [...], [...], [...], [...], [...], [...], [...]]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.1
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.1
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[<circuitous.Circle object at 0x104171710>, <circuitous.Circle object at 0x104171090>, <circuitous.Circle object at 0x104171150>, <circuitous.Circle object at 0x104171750>, <circuitous.Circle object at 0x1041717d0>, <circuitous.Circle object at 0x104171810>, <circuitous.Circle object at 0x104171850>, <circuitous.Circle object at 0x1041718d0>, <circuitous.Circle object at 0x104171890>, <circuitous.Circle object at 0x104171950>]
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle(10)
Circle(10.000000)
>>> type(Circle(10).radius)
<type 'int'>
>>> type(Circle(10.00000).radius)
<type 'float'>
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle(10)
Circle(10)
>>> Circle(10.0)
Circle(10.0)
>>> Circle(math.pi)
Circle(3.14159265359)
>>> math.pi
3.141592653589793
>>> 
>>> 
>>> c = Circle(3.14159265359)
>>> c.radius == math.pi
False
>>> str(math.pi)
'3.14159265359'
>>> repr(math.pi)
'3.141592653589793'
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[Circle(0.7563225821847216), Circle(0.8314177952568056), Circle(0.34587373581808056), Circle(0.05808283365766054), Circle(0.22532318620974512), Circle(0.4024635488620961), Circle(0.5844105030134041), Circle(0.33287599331583473), Circle(0.5680224120780014), Circle(0.6895764771896405)]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[Circle(0.40224696110279223), Circle(0.5102471779215914), Circle(0.6637431122665531), Circle(0.8607166923395507), Circle(0.28094269977126785), Circle(0.6413941220751519), Circle(0.6472135534646176), Circle(0.22715569766295207), Circle(0.711696999899619), Circle(0.09115426983797148)]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[Circle(0.40224696110279223),
 Circle(0.5102471779215914),
 Circle(0.6637431122665531),
 Circle(0.8607166923395507),
 Circle(0.28094269977126785),
 Circle(0.6413941220751519),
 Circle(0.6472135534646176),
 Circle(0.22715569766295207),
 Circle(0.711696999899619),
 Circle(0.09115426983797148)]
>>> print(Circle(10))
Circle(10)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[Circle(0.40224696110279223),
 Circle(0.5102471779215914),
 Circle(0.6637431122665531),
 Circle(0.8607166923395507),
 Circle(0.28094269977126785),
 Circle(0.6413941220751519),
 Circle(0.6472135534646176),
 Circle(0.22715569766295207),
 Circle(0.711696999899619),
 Circle(0.09115426983797148)]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[Circle(0.40224696110279223),
 Circle(0.5102471779215914),
 Circle(0.6637431122665531),
 Circle(0.8607166923395507),
 Circle(0.28094269977126785),
 Circle(0.6413941220751519),
 Circle(0.6472135534646176),
 Circle(0.22715569766295207),
 Circle(0.711696999899619),
 Circle(0.09115426983797148)]
[<Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>,
 <Recursion on list with id=4363936832>]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
[Circle(0.40224696110279223),
 Circle(0.5102471779215914),
 Circle(0.6637431122665531),
 Circle(0.8607166923395507),
 Circle(0.28094269977126785),
 Circle(0.6413941220751519),
 Circle(0.6472135534646176),
 Circle(0.22715569766295207),
 Circle(0.711696999899619),
 Circle(0.09115426983797148)]
[0.5083179151495382,
 0.8179205041298087,
 1.384044097288627,
 2.327396215536275,
 0.24796213997951547,
 1.2924085543325607,
 1.3159672444054562,
 0.16210527294445717,
 1.591256324893598,
 0.02610381037583005]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
>>> sum([10, 5, 20])
35
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
>>> average_area
0.9673482079035665
>>> s = [10, 20, 60]
>>> sum(s) / len(s)
30
>>> s = [10, 20, 61]
>>> sum(s) / len(s)
30
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 0.967348207904

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
[Circle(0.1), Circle(0.2), Circle(0.7)]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
[Circle(0.1), Circle(0.2), Circle(0.7)]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
[Circle(0.1), Circle(0.2), Circle(0.7)]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
[Circle(0.1), Circle(0.2), Circle(0.7)]
>>> map(ord, 'Raymond')
[82, 97, 121, 109, 111, 110, 100]
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #0
Circle #0
Circle #0
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
Circle #2
Circle #3
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #0
Circle #1
Circle #2
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
Circle #2
Circle #3
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.2
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.2
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of
Circle #2
A circle with a cut radius of 0.2
has a perimeter of
Circle #3
A circle with a cut radius of 0.7
has a perimeter of
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

A tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

>>> t
Circle(30)
>>> Tire.__dict__
dict_proxy({'perimeter': <function perimeter at 0x104b6b6e0>, '__module__': '__main__', '__doc__': 'Circular tires with a perimeter corrected for the rubber on the tire'})
>>> Tire.__bases__
(<class 'circuitous.Circle'>,)
>>> Tire.__name__
'Tire'
>>> 
>>> 
>>> t.__dict__
{'radius': 30}
>>> t.__class__
<class '__main__.Tire'>
>>> 
>>> t.__class__.__name__
'Tire'
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

A tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

>>> c
Circle(10)
>>> t
Tire(30)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

A tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

A tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

A tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.3
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.3
preliminary study using 10 random circles
seeded using Jenny's number: 8675309
The average area is 1.0

Spec sheet for the template: [0.1, 0.2, 0.7]
Circle #1
A circle with a cut radius of 0.1
has a perimeter of 0.628318530718
has a cold area of 0.0314159265359
and a warm area of 0.0380132711084

Circle #2
A circle with a cut radius of 0.2
has a perimeter of 1.25663706144
has a cold area of 0.125663706144
and a warm area of 0.152053084434

Circle #3
A circle with a cut radius of 0.7
has a perimeter of 4.39822971503
has a cold area of 1.53938040026
and a warm area of 1.86265028431

A tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 235.5

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 282.6

>>> 
>>> 
