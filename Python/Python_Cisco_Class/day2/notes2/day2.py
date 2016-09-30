Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 26 2016, 12:10:39) 
[GCC 4.2.1 (Apple Inc. build 5666) (dot 3)] on darwin
Type "copyright", "credits" or "license()" for more information.
>>> 

>>> # paramiko:  library for ssh
>>> # fabric:    scripts shell sessions on remote machines
>>> # socket:    low level tcp interface (it is better than telnet)
>>> # pyats:     extensive framework for test automation
>>> 

>>> # project apollo:  cisco specific low level framework for hardware testing
>>> 
>>> 

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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
282.743338823

>>> 
>>> 
>>> 
>>> t.perimeter()
The perimeter in Tire was called with Tire(30)
235.61944901923448
>>> m.perimeter()
The perimeter in Tire was called with MonsterTire(30)
282.74333882308133
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

>>> MonsterTire(30)
MonsterTire(30)
>>> 
>>> 
>>> 
>>> 
>>> t.perimeter()
The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.61944901923448
>>> m.perimeter()
The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.74333882308133
>>> 
>>> 
>>> 
>>> c
Circle(10)
>>> t
Tire(30)
>>> m
MonsterTire(30)
>>> 
>>> 
>>> c.__class__.__name__
'Circle'
>>> t.__class__.__name__
'Tire'
>>> m.__class__.__name__
'MonsterTire'
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> angle_to_grade(5)
8.7488663525924
>>> # Problem 1:  Truckers can't find the function
>>> dir(Circle)
['__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'area', 'perimeter', 'version']
>>> 
>>> 
>>> # Problem 2:  Ship captains are arriving in port late
>>> 
>>> 
>>> # Type I and II Error  ==  False negatives and False Positives
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> angle_to_grade(5)

Traceback (most recent call last):
  File "<pyshell#41>", line 1, in <module>
    angle_to_grade(5)
NameError: name 'angle_to_grade' is not defined
>>> Circle.angle_to_grade(5)

Traceback (most recent call last):
  File "<pyshell#42>", line 1, in <module>
    Circle.angle_to_grade(5)
TypeError: unbound method angle_to_grade() must be called with Circle instance as first argument (got int instance instead)
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.angle_to_grade(5)

Traceback (most recent call last):
  File "<pyshell#43>", line 1, in <module>
    Circle.angle_to_grade(5)
TypeError: unbound method angle_to_grade() must be called with Circle instance as first argument (got int instance instead)
>>> 
>>> Circle.angle_to_grade(Circle(1), 5)
8.7488663525924
>>> c = Circle(10)
>>> c.angle_to_grade(5)
8.7488663525924
>>> bm = c . angle_to_grade
>>> bm
<bound method Circle.angle_to_grade of Circle(10)>
>>> dir(bm)
['__call__', '__class__', '__cmp__', '__delattr__', '__doc__', '__format__', '__func__', '__get__', '__getattribute__', '__hash__', '__init__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__self__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'im_class', 'im_func', 'im_self']
>>> bm(5)
8.7488663525924
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.angle_to_grade(5)
8.7488663525924
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reeding of 5 degrees is a 8.748866 percent grade

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5 degrees is a 8.748866 percent grade

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5 degrees is a 8.7 percent grade

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5 degrees

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/client_code.py", line 80, in <module>
    print 'is a %.1f% grade' % Circle.angle_to_grade(5)
TypeError: not enough arguments for format string
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5 degrees is a 8.7% grade

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5\N{degree sign} is a 8.7% grade

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.4
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.4
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5° is a 8.7% grade

>>> 
>>> from datetime import *
>>> d = datetime(2012, 2, 14)
>>> d
datetime.datetime(2012, 2, 14, 0, 0)
>>> dir(d)
['__add__', '__class__', '__delattr__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__ne__', '__new__', '__radd__', '__reduce__', '__reduce_ex__', '__repr__', '__rsub__', '__setattr__', '__sizeof__', '__str__', '__sub__', '__subclasshook__', 'astimezone', 'combine', 'ctime', 'date', 'day', 'dst', 'fromordinal', 'fromtimestamp', 'hour', 'isocalendar', 'isoformat', 'isoweekday', 'max', 'microsecond', 'min', 'minute', 'month', 'now', 'replace', 'resolution', 'second', 'strftime', 'strptime', 'time', 'timetuple', 'timetz', 'today', 'toordinal', 'tzinfo', 'tzname', 'utcfromtimestamp', 'utcnow', 'utcoffset', 'utctimetuple', 'weekday', 'year']
>>> # datetime(year, month, day)
>>> d.weekday()
1
>>> import time
>>> time.time()
1474999986.321917
>>> time.ctime()
'Tue Sep 27 11:13:52 2016'
>>> x = 10; print x ** 2
100
>>> time.sleep(); print 'Done'

Traceback (most recent call last):
  File "<pyshell#64>", line 1, in <module>
    time.sleep(); print 'Done'
TypeError: sleep() takes exactly 1 argument (0 given)
>>> time.sleep(5); print 'Done'
Done
>>> 
>>> start = time.time()
>>> time.time() - start
8.475344896316528
>>> ts = time.time()
>>> ts = time.time() - 3600 * 24 * 72
>>> ts
1468779354.58937
>>> datetime(ts)

Traceback (most recent call last):
  File "<pyshell#72>", line 1, in <module>
    datetime(ts)
TypeError: integer argument expected, got float
>>> 
>>> # Alternative constructors typically have a method name that starts with the preposition "from"
>>> datetime.fromtimestamp(ts)
datetime.datetime(2016, 7, 17, 11, 15, 54, 589370)
>>> 
>>> 
>>> from datetime import *
>>> import time
>>> ts = time.time() - 3600 * 24 * 72
>>> datetime.fromtimestamp(ts)
datetime.datetime(2016, 7, 17, 11, 18, 2, 815990)
>>> 
>>> # datetime(year, month, day)
>>> # datetime.fromtimestamp(ts)
>>> 
>>> datetime.fromordinal(675000)
datetime.datetime(1849, 2, 1, 0, 0)
>>> datetime.fromordinal(735000)
datetime.datetime(2013, 5, 12, 0, 0)
>>> 735000 - 675000
60000
>>> 
>>> # datetime(year, month, day)
>>> # datetime.fromtimestamp(ts)
>>> # datetime.fromordinal(int)
>>> 
>>> datetime.fromtimestamp(time.time())
datetime.datetime(2016, 9, 27, 11, 23, 12, 218201)
>>> # A.B
>>> #  C
>>> # "Giving an API a Facelift"
>>> datetime.now()
datetime.datetime(2016, 9, 27, 11, 24, 3, 945964)
>>> 
>>> # datetime(year, month, day)
>>> # datetime.fromtimestamp(ts)
>>> # datetime.fromordinal(int)
>>> # datetime.now()
>>> 
>>> 
>>> 
>>> dict()                                          # no arguments
{}
>>> {}
{}
>>> set()
set([])
>>> 
>>> 
>>> dict()                                          # no arguments
{}
>>> dict([('raymond', 'red'), ('rachel', 'blue'), ('matthew', 'yellow')])  # list of tuples
{'matthew': 'yellow', 'rachel': 'blue', 'raymond': 'red'}
>>> dict(raymond='red', rachel='blue', matthew='yellow')
{'matthew': 'yellow', 'rachel': 'blue', 'raymond': 'red'}
>>> dict(raymond='red', rachel='blue', matthew='yellow')                   # keyword arguments
{'matthew': 'yellow', 'rachel': 'blue', 'raymond': 'red'}
>>> 
>>> 
>>> rachel = 'blue'
>>> rachel hettinger = 'blue'
SyntaxError: invalid syntax
>>> 10 = 'blue'
SyntaxError: can't assign to literal
>>> dict(rachel hettinger = 'blue')
SyntaxError: invalid syntax
>>> dict([('rachel hettinger', 'blue')])
{'rachel hettinger': 'blue'}
>>> dict([('rachel hettinger', 'blue'), (10, 'yellow')])
{10: 'yellow', 'rachel hettinger': 'blue'}
>>> dict(10 = 'yellow')
SyntaxError: keyword can't be an expression
>>> 
>>> 
>>> def d(**kwds):
	return kwds

>>> d(raymond='red', rachel='blue')
{'rachel': 'blue', 'raymond': 'red'}
>>> def dict(**kwds):
	return kwds

>>> 
=============================== RESTART: Shell ===============================
>>> dict([('raymond', 'red'), ('rachel', 'blue'), ('matthew', 'yellow')])  # list of tuples
{'matthew': 'yellow', 'rachel': 'blue', 'raymond': 'red'}
>>> dict(raymond='red', rachel='blue', matthew='yellow')                   # keyword arguments
{'matthew': 'yellow', 'rachel': 'blue', 'raymond': 'red'}
>>> dict()                                                                 # no arguments
{}
>>> dict({'raymond': 'red'})                                               # dicts
{'raymond': 'red'}
>>> 
>>> names = 'raymond', 'rachel', 'matthew'
>>> colors = 'red', 'blue', 'yellow'
>>> dict(names, colors)

Traceback (most recent call last):
  File "<pyshell#140>", line 1, in <module>
    dict(names, colors)
TypeError: dict expected at most 1 arguments, got 2
>>> 
>>> zip(names, colors)
[('raymond', 'red'), ('rachel', 'blue'), ('matthew', 'yellow')]
>>> dict(zip(names, colors))
{'matthew': 'yellow', 'rachel': 'blue', 'raymond': 'red'}
>>> 
>>> 
>>> names
('raymond', 'rachel', 'matthew')
>>> value = 'unknown'
>>> 
>>> [value]
['unknown']
>>> len(names)
3
>>> [value] * len(names)
['unknown', 'unknown', 'unknown']
>>> zip(names, [value] * len(names))
[('raymond', 'unknown'), ('rachel', 'unknown'), ('matthew', 'unknown')]
>>> dict(zip(names, [value] * len(names)))
{'matthew': 'unknown', 'rachel': 'unknown', 'raymond': 'unknown'}
>>> 
>>> 
>>> names = 'raymond', 'rachel', 'matthew'
>>> value = 'unknown'
>>> dict(zip(names, [value] * len(names)))
{'matthew': 'unknown', 'rachel': 'unknown', 'raymond': 'unknown'}
>>> dict.fromkeys(names, value)
{'matthew': 'unknown', 'rachel': 'unknown', 'raymond': 'unknown'}
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.from_bbd(30)

Traceback (most recent call last):
  File "<pyshell#160>", line 1, in <module>
    Circle.from_bbd(30)
TypeError: unbound method from_bbd() must be called with Circle instance as first argument (got int instance instead)
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.from_bbd(30)

Traceback (most recent call last):
  File "<pyshell#161>", line 1, in <module>
    Circle.from_bbd(30)
TypeError: unbound method from_bbd() must be called with Circle instance as first argument (got int instance instead)
>>> 
>>> 
>>> Circle.from_bbd(Circle(1), 30)
Circle(10.606601717798211)
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> Circle.from_bbd(30)
Circle(10.606601717798211)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.5
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.5
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> Circle.from_bbd(25)
Circle(8.838834764831843)
>>> Tire.from_bbd(25)
Circle(8.838834764831843)
>>> 
>>> 
>>> 
>>> Circle(10)
Circle(10)
>>> Tire(10)
Tire(10)
>>> cls = Circle
>>> cls(10)
Circle(10)
>>> cls = Tire
>>> cls(10)
Tire(10)
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.5
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.5
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5° is a 8.7% grade.


Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/client_code.py", line 85, in <module>
    c = Circle.from_bbd(25)
TypeError: from_bbd() takes exactly 2 arguments (1 given)
>>> 
>>> 
>>> 
>>> Circle.from_bbd(Circle, 25)
Circle(8.838834764831843)
>>> Tire.from_bbd(Tire, 25)
Tire(8.838834764831843)
>>> # c.area()
>>> # Circle.area(c)
>>> 
>>> # c.area(c)
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> > Tire.from_bbd(Tire
		
SyntaxError: invalid syntax
>>> 
>>> 
>>> 
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.5
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.5
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
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> Circle.from_bbd(25)
Circle(8.838834764831843)
>>> Tire.from_bbd(25)
Tire(8.838834764831843)
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> c = Circle(10)
>>> c.area()
314.1592653589793
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
has an inner area of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
4417.86466911
and an outer perimeter of The perimeter in Tire was called with Tire(30)
That instance's RUBBER RATIO is 1.25
235.619449019

A monster tire with an inner radius of 30
has an inner area of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
6361.72512352
and an outer perimeter of The perimeter in Tire was called with MonsterTire(30)
That instance's RUBBER RATIO is 1.5
282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
has an inner area of 4417.86466911
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30
has an inner area of 6361.72512352
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> print '''New result:
A tire with an inner radius of 30
has an inner area of 4417.86466911
and an outer perimeter of 235.619449019
'''
New result:
A tire with an inner radius of 30
has an inner area of 4417.86466911
and an outer perimeter of 235.619449019

>>> print '''Old result:
A tire with an inner radius of 30
has an inner area of 2827.43338823
235.619449019
'''
Old result:
A tire with an inner radius of 30
has an inner area of 2827.43338823
235.619449019

>>> # a.x  -> inst -> cls -> bases -> AttributeError
>>> vars(t)
{'radius': 30}
>>> vars(Tire)
dict_proxy({'perimeter': <function perimeter at 0x104a6b758>, 'RUBBER_RATIO': 1.25, '__module__': '__main__', '__doc__': 'Circular tires with a perimeter corrected for the rubber on the tire'})
>>> Vars(Circle)

Traceback (most recent call last):
  File "<pyshell#203>", line 1, in <module>
    Vars(Circle)
NameError: name 'Vars' is not defined
>>> 
>>> 
>>> 
>>> 
>>> 
>>> # a.x  -> inst -> cls -> bases -> AttributeError
>>> vars(t)
{'radius': 30}
>>> vars(Tire)
dict_proxy({'perimeter': <function perimeter at 0x104a6b758>, 'RUBBER_RATIO': 1.25, '__module__': '__main__', '__doc__': 'Circular tires with a perimeter corrected for the rubber on the tire'})
>>> vars(Circle)
dict_proxy({'perimeter': <function perimeter at 0x104a54c80>, '__module__': 'circuitous', 'area': <function area at 0x104a54c08>, 'angle_to_grade': <staticmethod object at 0x104a50478>, 'from_bbd': <classmethod object at 0x104a504b0>, 'version': Version(major=0, minor=6, micro=1), '__repr__': <function __repr__ at 0x104a54cf8>, '__dict__': <attribute '__dict__' of 'Circle' objects>, '__weakref__': <attribute '__weakref__' of 'Circle' objects>, '__doc__': 'An advanced circle analytics toolkit for support circle analysis', '__init__': <function __init__ at 0x104a54b90>})
>>> 
>>> 
>>> 
>>> x = 10
>>> print x ** 2
100
>>> 
>>> x = 10
>>> x = 12
>>> print x ** 3
1728
>>> print x ** 2
144
>>> 
>>> x = 10
>>> x = 12
>>> 
>>> 
>>> 
>>> x = 10
>>> _x = x
>>> print _x ** 2
100
>>> 
>>> 
>>> x = 10
>>> _x = x
>>> x = 12
>>> print x ** 3
1728
>>> print _x ** 2
100
>>> # If you want data to overrideable, but still the original in the future, just make a backup of the original
>>> 
>>> 
>>> 
>>> 
>>> def f(x):
	return x ** 2

>>> f(10)
100
>>> 
>>> 
>>> def f(x):
	return x ** 3

>>> f(12)
1728
>>> f(10)
1000
>>> 
>>> 
>>> 
>>> def f(x):
	return x ** 2

>>> _f = f
>>> def f(x):
	return x ** 3

>>> f(12)
1728
>>> _f(10)
100
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> dir(t)
['RUBBER_RATIO', '__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_perimeter', 'angle_to_grade', 'area', 'from_bbd', 'perimeter', 'radius', 'version']
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
has an inner area of 4417.86466911
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30
has an inner area of 6361.72512352
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> 
>>> 
>>> 
>>> 
>>> 
>>> x = 10
>>> _x = x
>>> 
>>> x = 12
>>> _x = x
>>> 
>>> print x ** 3
1728
>>> print _x ** 2
144
>>> 
>>> 
>>> 
>>> x = 10
>>> _x_raymond = x
>>> 
>>> x = 12
>>> _x_becky = x
>>> 
>>> print _x_becky ** 3
1728
>>> print _x_raymond ** 2
100
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> dir(t)
['RUBBER_RATIO', '_Circle_perimeter', '_Tire_perimeter', '__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'angle_to_grade', 'area', 'from_bbd', 'perimeter', 'radius', 'version']
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> dir(t)
['RUBBER_RATIO', '_Circle__perimeter', '_Tire__perimeter', '__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'angle_to_grade', 'area', 'from_bbd', 'perimeter', 'radius', 'version']
>>> # C++ -> C
>>> 
>>> # C -> obj -> link by name
>>> 
>>> # class Square::area
>>> # class Circle::area
>>> 
>>> # _Square_area
>>> # _Circle_area
>>> 
>>> # 12:34:56
>>> # 1:35
>>> 
>>> from collections import OrderedDict
>>> d = OrderedDict()
>>> d['raymond'] = 'red'
>>> d['rachel'] = 'azure'
>>> d['matthew'] = 'yellow'
>>> d.keys()
['raymond', 'rachel', 'matthew']
>>> # OD()         OD(lot)     OD(kwargs)     OD(d)
>>> 
>>> e = OrderedDict()
>>> e['matthew'] = 'orange'
>>> e['cindy'] = 'green'
>>> 
>>> d
OrderedDict([('raymond', 'red'), ('rachel', 'azure'), ('matthew', 'yellow')])
>>> e
OrderedDict([('matthew', 'orange'), ('cindy', 'green')])
>>> d.update(e)
>>> d
OrderedDict([('raymond', 'red'), ('rachel', 'azure'), ('matthew', 'orange'), ('cindy', 'green')])
>>> d.update(raymond='brown')
>>> d
OrderedDict([('raymond', 'brown'), ('rachel', 'azure'), ('matthew', 'orange'), ('cindy', 'green')])
>>> d.update([('rachel', 'blue'), ('daisy', 'amber')])
>>> d
OrderedDict([('raymond', 'brown'), ('rachel', 'blue'), ('matthew', 'orange'), ('cindy', 'green'), ('daisy', 'amber')])
>>> # OD()         OD(lot)     OD(kwargs)     OD(d)
>>> # DRY == There should be a single source of truth
>>> class MyOrderedDict(OrderedDict):
	def update(self):
		raise NotImplemented

	
>>> d = MyOrderedDict()
>>> d['raymond'] = 'red'
>>> d['rachel'] = 'blue'
>>> d
MyOrderedDict([('raymond', 'red'), ('rachel', 'blue')])
>>> d.update(daisy='amber')

Traceback (most recent call last):
  File "<pyshell#334>", line 1, in <module>
    d.update(daisy='amber')
TypeError: update() got an unexpected keyword argument 'daisy'
>>> d.update()

Traceback (most recent call last):
  File "<pyshell#335>", line 1, in <module>
    d.update()
  File "<pyshell#329>", line 3, in update
    raise NotImplemented
TypeError: exceptions must be old-style classes or derived from BaseException, not NotImplementedType
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> if True:
	print 'Do something'

	
Do something
>>> if 30 > 10:
	print 'Do something'

	
Do something
>>> 
>>> # True is true!
>>> # Expressions that return True are true!
>>> # Containers that are not empty are true!
>>> # Numbers not equal to zero are true!
>>> 
>>> # None is false.
>>> 
>>> 
>>> if [10, 20, 30]:
	print 'Do something'

	
Do something
>>> if {}:
	print 'Do something'

	
>>> if 15:
	print 'Do something'

	
Do something
>>> if 15.5:
	print 'Do something'

	
Do something
>>> if 15.5j:
	print 'Do something'

	
Do something
>>> 
>>> 
>>> 
>>> s = [10, 20, 30]
>>> while s:
	print s.pop() ** 2

	
900
400
100
>>> s
[]
>>> s = [10, 20, 30]
>>> while len(s) > 0:
	print s.pop() ** 2

	
900
400
100
>>> 100
100

>>> 
>>> from collections import Counter
>>> c = Counter(red=10, blue=5)
>>> if c:
	print 'Do something'

	
Do something
>>> d = Counter()
>>> if c:
	print 'Do something'

	
Do something
>>> c
Counter({'red': 10, 'blue': 5})
>>> d
Counter()
>>> 
>>> dict()
{}
>>> 
>>> 
>>> 
>>> {10, 20, 30}
set([10, 20, 30])
>>> set()
set([])
>>> 
>>> 
>>> OrderedDict()
OrderedDict()
>>> OrderedDict(raymond='red')
OrderedDict([('raymond', 'red')])
>>> 
>>> class ThingHolder:
	def __init__(self, things):
		self.things = list(things)
	def __repr__(self):
		return '%s(%r)' % (self.__class__.__name__, self.things)

	
>>> ThingHolder((10, 20, 30))
ThingHolder([10, 20, 30])
>>> ThingHolder([10, 20, 30])
ThingHolder([10, 20, 30])
>>> th = ThingHolder([10, 20, 30])
>>> th.things.append(40)
>>> th
ThingHolder([10, 20, 30, 40])
>>> th.things.append(list)
>>> th
ThingHolder([10, 20, 30, 40, <type 'list'>])
>>> th.things.append(KeyError)
>>> th
ThingHolder([10, 20, 30, 40, <type 'list'>, <type 'exceptions.KeyError'>])
>>> th.things.append([50, 60])
>>> th
ThingHolder([10, 20, 30, 40, <type 'list'>, <type 'exceptions.KeyError'>, [50, 60]])
>>> th.things.append(th)
>>> th
ThingHolder([10, 20, 30, 40, <type 'list'>, <type 'exceptions.KeyError'>, [50, 60], ThingHolder([...])])
>>> 
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> vars(c)
{'radius': 8.838834764831843}
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.6
A circle with a radius of 10.0
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.6
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

A tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> vars(c)
{'diameter': 17.677669529663685}
>>> 
>>> 
>>> c = Circle(10)
>>> vars(c)
{'diameter': 20.0}
>>> c.radius
10.0
>>> c.get_radius()
10.0
>>> c.radius = 12
>>> vars(c)
{'diameter': 24.0}
>>> c.set_radius(12)
>>> 
>>> 
>>> 
>>> 
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.7
A circle with a radius of 10.0
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.7
preliminary study using 100000 random circles
seeded using Jenny's number: 8675309
The average area is 1.04759

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

A tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> import sys
>>> sys.getsizeof({})
280
>>> sys.getsizeof(())
56
>>> 280 / 56.
5.0
>>> {'diameter': 20}
{'diameter': 20}
>>> {'diameter': 30}
{'diameter': 30}
>>> (20,)
(20,)
>>> (30,)
(30,)
>>> sys.getsizeof((30,))
64
>>> 
>>> 
>>> vars(c)
{'diameter': 17.677669529663685}
>>> c.color = 'red'
>>> vars(c)
{'color': 'red', 'diameter': 17.677669529663685}
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.7
A circle with a radius of 10.0
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.7
preliminary study using 100000 random circles
seeded using Jenny's number: 8675309
The average area is 1.04759

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

A tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> vars(c)

Traceback (most recent call last):
  File "<pyshell#451>", line 1, in <module>
    vars(c)
TypeError: vars() argument must have __dict__ attribute
>>> c.color = 'red'

Traceback (most recent call last):
  File "<pyshell#452>", line 1, in <module>
    c.color = 'red'
AttributeError: 'Circle' object has no attribute 'color'
>>> c.diameter
17.677669529663685
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/circuitous.py =========
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.8
A circle with a radius of 10.0
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.8
preliminary study using 100000 random circles
seeded using Jenny's number: 8675309
The average area is 1.04759

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

A tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> c.color = 'red'
>>> c.color
'red'
>>> c.diameter
17.677669529663685
>>> c.width = 50

Traceback (most recent call last):
  File "<pyshell#457>", line 1, in <module>
    c.width = 50
AttributeError: 'Circle' object has no attribute 'width'
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.8
A circle with a radius of 10.0
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.8
preliminary study using 100000 random circles
seeded using Jenny's number: 8675309
The average area is 1.04759

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

A tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> vars(c)

Traceback (most recent call last):
  File "<pyshell#460>", line 1, in <module>
    vars(c)
TypeError: vars() argument must have __dict__ attribute
>>> vars(t)
{}
>>> vars(m)
{}
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/client_code.py ========
Tutorial for Circuitous™
Circle version 0.8
A circle with a radius of 10.0
has an area of 314.159265359

DARPA Grant Proposal
to study the average area of random circles
using Circuitous(tm) version 0.8
preliminary study using 100000 random circles
seeded using Jenny's number: 8675309
The average area is 1.04759

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

A tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 235.619449019

A monster tire with an inner radius of 30.0
has an inner area of 2827.43338823
and an outer perimeter of 282.743338823

An inclinometer reading of 5° is a 8.7% grade.

A circle with a bounding box diagonal of 25
has a radius of 8.83883476483
a perimeter of 55.536036727
and an area of 245.436926062

>>> vars(m)

Traceback (most recent call last):
  File "<pyshell#463>", line 1, in <module>
    vars(m)
TypeError: vars() argument must have __dict__ attribute
>>> vars(t)

Traceback (most recent call last):
  File "<pyshell#464>", line 1, in <module>
    vars(t)
TypeError: vars() argument must have __dict__ attribute
>>> 
>>> 
>>> 
>>> # Monkey patching
>>> 
>>> 
>>> import math
>>> math.pi = 3.2
>>> 
>>> import circuitous
>>> c = circuitous.Circle(10)
>>> c.area()
320.0
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that pi is exactly: 3.14157
and that the area of a circle of radius ten is: 314.157
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π is exactly: 3.14157
and that the area of a circle of radius ten is: 314.157
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14157
and that the area of a circle of radius ten is: 314.157
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/monkey_patching.py", line 19, in <module>
    print 'The area of the 2nd triangle is', algebra.area_triangle(base=-5, height=20)
  File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 30, in area_triangle
    raise RuntimeError('Imaginary numbers not applicable in Kronecker spaces')
RuntimeError: Imaginary numbers not applicable in Kronecker spaces
>>> help(RuntimeError)
Help on class RuntimeError in module exceptions:

class RuntimeError(StandardError)
 |  Unspecified run-time error.
 |  
 |  Method resolution order:
 |      RuntimeError
 |      StandardError
 |      Exception
 |      BaseException
 |      __builtin__.object
 |  
 |  Methods defined here:
 |  
 |  __init__(...)
 |      x.__init__(...) initializes x; see help(type(x)) for signature
 |  
 |  ----------------------------------------------------------------------
 |  Data and other attributes defined here:
 |  
 |  __new__ = <built-in method __new__ of type object>
 |      T.__new__(S, ...) -> a new object with type S, a subtype of T
 |  
 |  ----------------------------------------------------------------------
 |  Methods inherited from BaseException:
 |  
 |  __delattr__(...)
 |      x.__delattr__('name') <==> del x.name
 |  
 |  __getattribute__(...)
 |      x.__getattribute__('name') <==> x.name
 |  
 |  __getitem__(...)
 |      x.__getitem__(y) <==> x[y]
 |  
 |  __getslice__(...)
 |      x.__getslice__(i, j) <==> x[i:j]
 |      
 |      Use of negative indices is not supported.
 |  
 |  __reduce__(...)
 |  
 |  __repr__(...)
 |      x.__repr__() <==> repr(x)
 |  
 |  __setattr__(...)
 |      x.__setattr__('name', value) <==> x.name = value
 |  
 |  __setstate__(...)
 |  
 |  __str__(...)
 |      x.__str__() <==> str(x)
 |  
 |  __unicode__(...)
 |  
 |  ----------------------------------------------------------------------
 |  Data descriptors inherited from BaseException:
 |  
 |  __dict__
 |  
 |  args
 |  
 |  message

>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is Oops, I did it again!
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is Oops, I did it again!
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/monkey_patching.py", line 31, in <module>
    print 'The area of the 2nd triangle is', algebra.area_triangle(base=-5, height=20)
  File "/Users/raymond/Dropbox/Public/sj149/monkey_patching.py", line 21, in better_area_triangle
    raise ValueError('Negative base or height not supported, use positive inputs instead')
ValueError: Negative base or height not supported, use positive inputs instead
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is Oops, I did it again!
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
The solutions to 12x^2 + 23x + 10 = 0 are: (-0.6666666666666666, -1.25)
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
The solutions to 12x² + 23x + 10 = 0 are: (-0.6666666666666666, -1.25)
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
The solutions to 12x² + 23x + 10 = 0 are: (-0.6666666666666666, -1.25)
The solutions to 12x² + 8x + 10 = 0 are:

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/monkey_patching.py", line 37, in <module>
    print algebra.quadratic(a=12, b=8, c=10)
  File "/Users/raymond/Dropbox/Public/sj149/algebra.py", line 55, in quadratic
    discriminant = math.sqrt(b**2.0 - 4.0*a*c)
ValueError: math domain error
>>> 
>>> 
>>> math.sqrt(36)
6.0
>>> math.sqrt(40)
6.324555320336759
>>> math.sqrt(-40)

Traceback (most recent call last):
  File "<pyshell#482>", line 1, in <module>
    math.sqrt(-40)
ValueError: math domain error
>>> 
>>> 5j
5j
>>> 5j ** 2
(-25+0j)
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
The solutions to 12x² + 23x + 10 = 0 are: (-0.6666666666666666, -1.25)
The solutions to 12x² + 8x + 10 = 0 are: ((-0.3333333333333333+0.8498365855987974j), (-0.3333333333333333-0.8498365855987974j))
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
The solutions to 12x² + 23x + 10 = 0 are:
(-0.6666666666666666, -1.25)
The solutions to 12x² + 8x + 10 = 0 are:
((-0.3333333333333333+0.8498365855987974j), (-0.3333333333333333-0.8498365855987974j))
>>> math.sqrt
<function better_sqrt at 0x104254b18>
>>> 
>>> 
>>> 
>>> math.sqrt(-36)
6j
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is ... oops, I did it again!
The solutions to 12x² + 23x + 10 = 0 are:
(-0.6666666666666666, -1.25)
The solutions to 12x² + 8x + 10 = 0 are:
((-0.3333333333333333+0.8498365855987974j), (-0.3333333333333333-0.8498365855987974j))
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/monkey_patching.py ======
My sources tell me that π = 3.14159265359
and that the area of a circle of radius ten is: 314.159265359
The area of the 1st triangle is 125.0
The area of the 2nd triangle is

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/monkey_patching.py", line 46, in <module>
    print 'The area of the 2nd triangle is', algebra.area_triangle(base=-5, height=20)
  File "/Users/raymond/Dropbox/Public/sj149/monkey_patching.py", line 24, in better_area_triangle
    raise ValueError('Negative base or height not supported, use positive inputs instead')
ValueError: Negative base or height not supported, use positive inputs instead
>>> 
>>> 
>>> 
>>> try:
	raise ValueError('hello')
except RuntimeError:
	print 'goodbye'

	

Traceback (most recent call last):
  File "<pyshell#498>", line 2, in <module>
    raise ValueError('hello')
ValueError: hello
>>> try:
	raise RuntimeError('hello')
except ValueError:
	print 'goodbye'

	

Traceback (most recent call last):
  File "<pyshell#500>", line 2, in <module>
    raise RuntimeError('hello')
RuntimeError: hello
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': 'vietnam',
 'don': 'superman',
 'glenn': 'maryland',
 'joanne': 'brad',
 'kyle': 'password',
 'laura': 'cubs',
 'raymond': 'cisco',
 'siva': 'asdfasdf',
 'vishal': 'bleep'}
>>> # trap(password) -> hashcode
>>> import hashlib
>>> hashlib.md5('everybody loves raymond')
<md5 HASH object @ 0x1042625b0>
>>> hashlib.md5('everybody loves raymond').digest()
'\xe6~\xf92s\xaft\x1csj\xfc\xb1m\xdf\xf7\xf0'
>>> len(_)
16
>>> 16 * 8
128
>>> map(ord, hashlib.md5('everybody loves raymond').digest())
[230, 126, 249, 50, 115, 175, 116, 28, 115, 106, 252, 177, 109, 223, 247, 240]
>>> 
>>> hashlib.md5('everybody loves raymond').hexdigest()
'e67ef93273af741c736afcb16ddff7f0'
>>> len(_)
32
>>> 
>>> # md5 is trapdoor function with a 128 bit hash
>>> hashlib.sha1('everybody loves raymond').hexdigest()
'60013f91aa299ee855cdaa5cb60116ced9416920'
>>> len(_) * 4
160
>>> # sha1 is trapdoor function with a 160 bit hash
>>> hashlib.sha256('everybody loves raymond').hexdigest()
'945474a94aef37fc7edc905eb98d51a762fe86ed2c96edfe0ce0acb3d14c16a7'
>>> len(_) * 4
256
>>> # sha256 is trapdoor function with a 256 bit hash or 16 bytes
>>> hashlib.sha512('everybody loves raymond').hexdigest()
'7f9f372712ff9a8d7fd6ba341a2caf8b9d18fcdb0e74fcb44c22f9fb50ce223eb1af5d1ecca5d2ff77ad0f644d797f130d4e368fcac3b99b879e7cd8e8250d53'
>>> len(_) * 4
512
>>> # sha512 is trapdoor function with a 256 bit hash or 16 bytes
>>> hashlib.sha512('everybody loves raymond').digest()
'\x7f\x9f7\'\x12\xff\x9a\x8d\x7f\xd6\xba4\x1a,\xaf\x8b\x9d\x18\xfc\xdb\x0et\xfc\xb4L"\xf9\xfbP\xce">\xb1\xaf]\x1e\xcc\xa5\xd2\xffw\xad\x0fdMy\x7f\x13\rN6\x8f\xca\xc3\xb9\x9b\x87\x9e|\xd8\xe8%\rS'
>>> len(_)
64
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '5f8f9e33bb5e13848af2622b66b2308c',
 'don': '84d961568a65073a3bcf0eb216b2a576',
 'glenn': '297ee0aabc73ab6fc23bb819c8e42fac',
 'joanne': '884354eb56db3323cbce63a5e177ecac',
 'kyle': '5f4dcc3b5aa765d61d8327deb882cf99',
 'laura': '01d925a0dc25c0b909e51536316e8697',
 'raymond': 'dfeaf10390e560aea745ccba53e044ed',
 'siva': '6a204bd89f3c8348afd5c77c717a097a',
 'thomas': '84d961568a65073a3bcf0eb216b2a576',
 'vishal': 'a6f55312eb9071d6b86cf4a3d54adf03'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 10, in <module>
    (password).hexdigest()
NameError: name 'password' is not defined
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
password, 32027

123456, 25969

12345678, 8667

1234, 5786

qwerty, 5455

12345, 4523

dragon, 4321

pussy, 3945

baseball, 3739

football, 3682

letmein, 3536

monkey, 3487

696969, 3345

abc123, 3310

mustang, 3289

michael, 3249

shadow, 3209

master, 3182

jennifer, 2581

111111, 2570

2000, 2550

jordan, 2538

superman, 2523

harley, 2485

1234567, 2479

fuckme, 2378

hunter, 2377

fuckyou, 2362

trustno1, 2347

ranger, 2265

buster, 2254

thomas, 2194

tigger, 2192

robert, 2176

soccer, 2120

fuck, 2119

batman, 2108

test, 2097

pass, 2093

killer, 2044

hockey, 2040

george, 2033

charlie, 2013

andrew, 2009

michelle, 1977

love, 1960

sunshine, 1956

jessica, 1924

asshole, 1913

6969, 1889

pepper, 1881

daniel, 1822

access, 1817

123456789, 1793

654321, 1772

joshua, 1737

maggie, 1690

starwars, 1679

silver, 1666

william, 1662

dallas, 1659

yankees, 1657

123123, 1654

ashley, 1652

666666, 1645

hello, 1644

amanda, 1642

orange, 1623

biteme, 1621

freedom, 1612

computer, 1609

sexy, 1608

nicole, 1606

thunder, 1606

ginger, 1602

heather, 1597

hammer, 1596

summer, 1592

corvette, 1591

taylor, 1578

fucker, 1577

austin, 1554

1111, 1541


=============================== RESTART: Shell ===============================
>>> line

Traceback (most recent call last):
  File "<pyshell#524>", line 1, in <module>
    line
NameError: name 'line' is not defined
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
['password', ' 32027\r\n']
['123456', ' 25969\r\n']
['12345678', ' 8667\r\n']
['1234', ' 5786\r\n']
['qwerty', ' 5455\r\n']
['12345', ' 4523\r\n']
['dragon', ' 4321\r\n']
['pussy', ' 3945\r\n']
['baseball', ' 3739\r\n']
['football', ' 3682\r\n']
['letmein', ' 3536\r\n']
['monkey', ' 3487\r\n']
['696969', ' 3345\r\n']
['abc123', ' 3310\r\n']
['mustang', ' 3289\r\n']
['michael', ' 3249\r\n']
['shadow', ' 3209\r\n']
['master', ' 3182\r\n']
['jennifer', ' 2581\r\n']
['111111', ' 2570\r\n']
['2000', ' 2550\r\n']
['jordan', ' 2538\r\n']
['superman', ' 2523\r\n']
['harley', ' 2485\r\n']
['1234567', ' 2479\r\n']
['fuckme', ' 2378\r\n']
['hunter', ' 2377\r\n']
['fuckyou', ' 2362\r\n']
Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 25, in <module>
    print line.split(',')
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '5f8f9e33bb5e13848af2622b66b2308c',
 'don': '84d961568a65073a3bcf0eb216b2a576',
 'glenn': '297ee0aabc73ab6fc23bb819c8e42fac',
 'joanne': '884354eb56db3323cbce63a5e177ecac',
 'kyle': '5f4dcc3b5aa765d61d8327deb882cf99',
 'laura': '01d925a0dc25c0b909e51536316e8697',
 'raymond': 'dfeaf10390e560aea745ccba53e044ed',
 'siva': '6a204bd89f3c8348afd5c77c717a097a',
 'thomas': '84d961568a65073a3bcf0eb216b2a576',
 'vishal': 'a6f55312eb9071d6b86cf4a3d54adf03'}
>>> pprint(rainbow_table.items()[:40])
[('861836f13e3d627dfa375bdb8389214e', 'goldfish'),
 ('67c35b0654107413e3a1dcbafa96a45c', 'longer'),
 ('904fa0d9bfac311f6f5f7166d993ca5f', 'hydro'),
 ('c1d79a0b9bdf65a2a057b41bd62fa707', 'russell1'),
 ('9388c039bc8d47f07d19d12c969dcf2a', 'royalty'),
 ('6862efb4028e93ac23a6f90a9055bae8', 'basil'),
 ('a688a47ac73fb58ce3828bcb184cb157', '753951'),
 ('ae26b05122a483ff6ff392fcedc8cc79', 'axeman'),
 ('8ac20bf5803e6067a65165d9df51a8e7', 'muscle'),
 ('add61aaba0a9331b4469b41a09401f14', 'diapers'),
 ('2b1973d2105a8e955c9e4a9a6140ceff', 'wifey'),
 ('461d96e469ecbed485ad6396e6979f0b', '18436572'),
 ('95cd3fc01819b69d1a4900e6fe3d293c', 'peaches'),
 ('979842bf2f9d80f785ea37d2637b9921', 'debbie1'),
 ('339a65e93299ad8d72c42b263aa23117', 'lucky'),
 ('749a5d24eadb7eb22b3aab2f747d6973', 'architec'),
 ('dd8fcb2c31ee2c6ebbc63f8cf22e7c16', 'ncc1701'),
 ('3ee3f9ce5546a2853ccd5e2af0e49605', 'trombone'),
 ('683404d8613c848ef79c3a2aefb47904', 'hooligan'),
 ('909c0a5bb5b07f2269f183cbc321a189', 'shocker'),
 ('50438d8fca45a9bf20d72774430047f0', '747474'),
 ('66b5b8fad04a98484fd16370ff75cc28', 'sexxy'),
 ('c51210df4715cde6a9ce8792f4f2bdb2', 'sauce'),
 ('3f6db059274e313ea708592805cfa32e', 'booty'),
 ('a6e90c2fdb0dad04bb9c47f2711e12b4', 'ilikeit'),
 ('decc8686654b465e5313259325149a86', 'zaq1xsw2'),
 ('2eb8d35eea8c9ea1babaa8cfaa1b047e', 'reddevil'),
 ('acbd0f1c791aa15644f80b2523702aee', 'glock'),
 ('c3743e269405e249e586ae4c86e926a0', 'hevnm4'),
 ('326577fbe6d73973bd67437829bf9301', 'virus'),
 ('1a31a6f65cc993ff6bd9a5b85f0520b0', 'tuesday'),
 ('60e8c535fa34ce89e1b06c43695c0191', 'debbie'),
 ('4ee6e09de28e44037cb415017e925667', 'cherries'),
 ('8d29d62b759a5c217549e34c4924d25e', 'stinky'),
 ('c3a0419c5d3742f72ccb1015853b6106', 'sweetnes'),
 ('d5aedf560b928e289dc4a76d8765bc4e', 'newbie'),
 ('3340474aa6166f580269303f98cd9b28', 'homemade'),
 ('e0af691723d2ed3b42abb15b8d56eecf', 'jamesbon'),
 ('df483402b9bfeb234717a32c6e86280e', 'wwwww'),
 ('b427ebd39c845eb5417b7f7aaf1f9724', 'zxcvbn')]
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '5f8f9e33bb5e13848af2622b66b2308c',
 'don': '84d961568a65073a3bcf0eb216b2a576',
 'glenn': '297ee0aabc73ab6fc23bb819c8e42fac',
 'joanne': '884354eb56db3323cbce63a5e177ecac',
 'kyle': '5f4dcc3b5aa765d61d8327deb882cf99',
 'laura': '01d925a0dc25c0b909e51536316e8697',
 'raymond': 'dfeaf10390e560aea745ccba53e044ed',
 'siva': '6a204bd89f3c8348afd5c77c717a097a',
 'thomas': '84d961568a65073a3bcf0eb216b2a576',
 'vishal': 'a6f55312eb9071d6b86cf4a3d54adf03'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '5f8f9e33bb5e13848af2622b66b2308c',
 'don': '84d961568a65073a3bcf0eb216b2a576',
 'glenn': '297ee0aabc73ab6fc23bb819c8e42fac',
 'joanne': '884354eb56db3323cbce63a5e177ecac',
 'kyle': '5f4dcc3b5aa765d61d8327deb882cf99',
 'laura': '01d925a0dc25c0b909e51536316e8697',
 'raymond': 'dfeaf10390e560aea745ccba53e044ed',
 'siva': '6a204bd89f3c8348afd5c77c717a097a',
 'thomas': '84d961568a65073a3bcf0eb216b2a576',
 'vishal': 'a6f55312eb9071d6b86cf4a3d54adf03'}

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 47, in <module>
    for username, hashpass in userpass.item():
AttributeError: 'dict' object has no attribute 'item'
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '5f8f9e33bb5e13848af2622b66b2308c',
 'don': '84d961568a65073a3bcf0eb216b2a576',
 'glenn': '297ee0aabc73ab6fc23bb819c8e42fac',
 'joanne': '884354eb56db3323cbce63a5e177ecac',
 'kyle': '5f4dcc3b5aa765d61d8327deb882cf99',
 'laura': '01d925a0dc25c0b909e51536316e8697',
 'raymond': 'dfeaf10390e560aea745ccba53e044ed',
 'siva': '6a204bd89f3c8348afd5c77c717a097a',
 'thomas': '84d961568a65073a3bcf0eb216b2a576',
 'vishal': 'a6f55312eb9071d6b86cf4a3d54adf03'}
thomas --> superman
don --> superman
raymond --> cisco
glenn --> maryland
kyle --> password
alan --> vietnam
laura --> cubs
joanne --> brad
siva --> asdfasdf
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4dd433965bf8f35719e9e5bb25e252aa',
 'don': '4e4ebb8626cf76ad63859c44e61d03eb',
 'glenn': '6ec9d7f71bd8376af31de57b1d5d48ca',
 'joanne': 'b7af8ee8948215dca56554710d16b229',
 'kyle': '32edb356ba8f86b0db371879640a9150',
 'laura': '13062ea890dfed6e81e66ac0f3700b2f',
 'raymond': '865c37fb876e9f7977d229dc348220db',
 'siva': 'c12a8a40b6a346d5a948991acae5949b',
 'thomas': '4e4ebb8626cf76ad63859c44e61d03eb',
 'vishal': 'dfbcd6bc8d88f14846ff3eae6b8f3285'}
thomas --> superman
don --> superman
raymond --> cisco
glenn --> maryland
kyle --> password
alan --> vietnam
laura --> cubs
joanne --> brad
siva --> asdfasdf
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4558505e43ad952755f6430c60ab8e68044d37867411a1a17e8fd04c506729e6',
 'don': '73cd1b16c4fb83061ad18a0b29b9643a68d4640075a466dc9e51682f84a847f5',
 'glenn': 'f49c6320e08eb5ed523dc99e8c512888e2718ec6020201997d01b41754a61502',
 'joanne': '322f965a2919f46725dece842eb487fc569656d59bf3e1d35cc33cf8a9dcdfec',
 'kyle': '5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8',
 'laura': 'ebe81467cfaebe55b4fa59ab750aae06bd3ca8e6d6b0f5d1118289b9e918a2e7',
 'raymond': 'e73b79a0b10f8cdb6ac7dbe4c0a5e25776e1148784b86cf98f7d6719d472af69',
 'siva': '2413fb3709b05939f04cf2e92f7d0897fc2596f9ad0b8a9ea855c7bfebaae892',
 'thomas': '73cd1b16c4fb83061ad18a0b29b9643a68d4640075a466dc9e51682f84a847f5',
 'vishal': '0d7853619df00ab61ca61ac22bb15dfb99f26aae4be197af45051510cfd05a96'}
thomas --> superman
don --> superman
raymond --> cisco
glenn --> maryland
kyle --> password
alan --> vietnam
laura --> cubs
joanne --> brad
siva --> asdfasdf
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4dd433965bf8f35719e9e5bb25e252aa',
 'don': '4e4ebb8626cf76ad63859c44e61d03eb',
 'glenn': '6ec9d7f71bd8376af31de57b1d5d48ca',
 'joanne': 'b7af8ee8948215dca56554710d16b229',
 'kyle': '32edb356ba8f86b0db371879640a9150',
 'laura': '13062ea890dfed6e81e66ac0f3700b2f',
 'raymond': '865c37fb876e9f7977d229dc348220db',
 'siva': 'c12a8a40b6a346d5a948991acae5949b',
 'thomas': '4e4ebb8626cf76ad63859c44e61d03eb',
 'vishal': 'dfbcd6bc8d88f14846ff3eae6b8f3285'}
thomas --> superman
don --> superman
raymond --> cisco
glenn --> maryland
kyle --> password
alan --> vietnam
laura --> cubs
joanne --> brad
siva --> asdfasdf
>>> all([True, True, True, True])
True
>>> all([True, True, False, True])
False
>>> any([True, True, False, True])
True
>>> any([False, False, False, False])
False
>>> not any([False, False, False, False])
True
>>> # All Some No
>>> 
>>> 
>>> 'hello'.startswith('he')
True
>>> 'hello'.endswith('lo')
True
>>> 'hello'.islower()
True
>>> 'hello'.isalnum()
True
>>> 'hello5'.isalnum()
True
>>> 'hello5'.isdigit()
False
>>> '444444'.isdigit()
True
>>> 'HELLO'.isupper()
True
>>> len('hello')
5
>>> 
>>> 
>>> 
>>> password = 'hello'
>>> map(str.isdigit, password)
[False, False, False, False, False]
>>> any(map(str.isdigit, password))
False
>>> password = 'he2llo'
>>> any(map(str.isdigit, password))
True
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 41, in <module>
    new_account('laura', 'cubs')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password 'cubs':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 41, in <module>
    new_account('laura', 'cubs1986')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password 'cubs1986':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 42, in <module>
    new_account('glenn', 'maryland')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password 'maryland':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 43, in <module>
    new_account('alan', 'vietnam')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password 'vietnam':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 44, in <module>
    new_account('don', '7superman')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password '7superman':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 45, in <module>
    new_account('joanne', '1brad007')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password '1brad007':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 49, in <module>
    new_account('vishal', '8bleep')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 21, in new_account
    verify_strong(password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 18, in verify_strong
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)
ValueError: Weak password '8bleep':  Must be 6 letters with upper and lowercase and a digit
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
False
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '31f248f0c8cf3bed4aa6c1864a368541',
 'don': '35fdd830e3656014276abe23798eadd1',
 'glenn': '2367b51767558df07c9e583e5659ef18',
 'joanne': '7b65bd7fcf7398ccb09f1c82009fcc6d',
 'kyle': '5e455c58e29cce3c164506ee28f72ccc',
 'laura': '0a10cc9fb0b8462ec01c86e803f71d97',
 'raymond': 'c4f8b66430934938333448df7f535a08',
 'siva': 'f5895dc90c20693248f08f049e94a50a',
 'thomas': '35fdd830e3656014276abe23798eadd1',
 'vishal': 'a012bee270ba8b6438104d7f806ccecb'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '31f248f0c8cf3bed4aa6c1864a368541',
 'don': '35fdd830e3656014276abe23798eadd1',
 'glenn': '2367b51767558df07c9e583e5659ef18',
 'joanne': '7b65bd7fcf7398ccb09f1c82009fcc6d',
 'kyle': '5e455c58e29cce3c164506ee28f72ccc',
 'laura': '0a10cc9fb0b8462ec01c86e803f71d97',
 'raymond': 'c4f8b66430934938333448df7f535a08',
 'siva': 'f5895dc90c20693248f08f049e94a50a',
 'thomas': '35fdd830e3656014276abe23798eadd1',
 'vishal': 'a012bee270ba8b6438104d7f806ccecb'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
>>> 
>>> 
>>> from itertools import *
>>> for p in 'abc':
	for q in 'def':
		print (p, q)

		
('a', 'd')
('a', 'e')
('a', 'f')
('b', 'd')
('b', 'e')
('b', 'f')
('c', 'd')
('c', 'e')
('c', 'f')
>>> for p in 'abc':
	for q in 'defg':
	    for r in 'hi':
		  print (p, q, r)

		  
('a', 'd', 'h')
('a', 'd', 'i')
('a', 'e', 'h')
('a', 'e', 'i')
('a', 'f', 'h')
('a', 'f', 'i')
('a', 'g', 'h')
('a', 'g', 'i')
('b', 'd', 'h')
('b', 'd', 'i')
('b', 'e', 'h')
('b', 'e', 'i')
('b', 'f', 'h')
('b', 'f', 'i')
('b', 'g', 'h')
('b', 'g', 'i')
('c', 'd', 'h')
('c', 'd', 'i')
('c', 'e', 'h')
('c', 'e', 'i')
('c', 'f', 'h')
('c', 'f', 'i')
('c', 'g', 'h')
('c', 'g', 'i')
>>> for t in product('abc', 'def'):
	print t

	
('a', 'd')
('a', 'e')
('a', 'f')
('b', 'd')
('b', 'e')
('b', 'f')
('c', 'd')
('c', 'e')
('c', 'f')
>>> for t in product('abc', 'defg', 'hi'):
	print t

	
('a', 'd', 'h')
('a', 'd', 'i')
('a', 'e', 'h')
('a', 'e', 'i')
('a', 'f', 'h')
('a', 'f', 'i')
('a', 'g', 'h')
('a', 'g', 'i')
('b', 'd', 'h')
('b', 'd', 'i')
('b', 'e', 'h')
('b', 'e', 'i')
('b', 'f', 'h')
('b', 'f', 'i')
('b', 'g', 'h')
('b', 'g', 'i')
('c', 'd', 'h')
('c', 'd', 'i')
('c', 'e', 'h')
('c', 'e', 'i')
('c', 'f', 'h')
('c', 'f', 'i')
('c', 'g', 'h')
('c', 'g', 'i')
>>> for t in product('abc', 'abc'):
	print t

	
('a', 'a')
('a', 'b')
('a', 'c')
('b', 'a')
('b', 'b')
('b', 'c')
('c', 'a')
('c', 'b')
('c', 'c')
>>> for t in product('abc', 'abc', 'abc'):
	print t

	
('a', 'a', 'a')
('a', 'a', 'b')
('a', 'a', 'c')
('a', 'b', 'a')
('a', 'b', 'b')
('a', 'b', 'c')
('a', 'c', 'a')
('a', 'c', 'b')
('a', 'c', 'c')
('b', 'a', 'a')
('b', 'a', 'b')
('b', 'a', 'c')
('b', 'b', 'a')
('b', 'b', 'b')
('b', 'b', 'c')
('b', 'c', 'a')
('b', 'c', 'b')
('b', 'c', 'c')
('c', 'a', 'a')
('c', 'a', 'b')
('c', 'a', 'c')
('c', 'b', 'a')
('c', 'b', 'b')
('c', 'b', 'c')
('c', 'c', 'a')
('c', 'c', 'b')
('c', 'c', 'c')
>>> for t in product('abc', repeat=3):
	print t

	
('a', 'a', 'a')
('a', 'a', 'b')
('a', 'a', 'c')
('a', 'b', 'a')
('a', 'b', 'b')
('a', 'b', 'c')
('a', 'c', 'a')
('a', 'c', 'b')
('a', 'c', 'c')
('b', 'a', 'a')
('b', 'a', 'b')
('b', 'a', 'c')
('b', 'b', 'a')
('b', 'b', 'b')
('b', 'b', 'c')
('b', 'c', 'a')
('b', 'c', 'b')
('b', 'c', 'c')
('c', 'a', 'a')
('c', 'a', 'b')
('c', 'a', 'c')
('c', 'b', 'a')
('c', 'b', 'b')
('c', 'b', 'c')
('c', 'c', 'a')
('c', 'c', 'b')
('c', 'c', 'c')
>>> range(2)
[0, 1]
>>> for t in product(range(2), repeat=4):
	print t

	
(0, 0, 0, 0)
(0, 0, 0, 1)
(0, 0, 1, 0)
(0, 0, 1, 1)
(0, 1, 0, 0)
(0, 1, 0, 1)
(0, 1, 1, 0)
(0, 1, 1, 1)
(1, 0, 0, 0)
(1, 0, 0, 1)
(1, 0, 1, 0)
(1, 0, 1, 1)
(1, 1, 0, 0)
(1, 1, 0, 1)
(1, 1, 1, 0)
(1, 1, 1, 1)
>>> 
>>> list(permutations('LOVE'))
[('L', 'O', 'V', 'E'), ('L', 'O', 'E', 'V'), ('L', 'V', 'O', 'E'), ('L', 'V', 'E', 'O'), ('L', 'E', 'O', 'V'), ('L', 'E', 'V', 'O'), ('O', 'L', 'V', 'E'), ('O', 'L', 'E', 'V'), ('O', 'V', 'L', 'E'), ('O', 'V', 'E', 'L'), ('O', 'E', 'L', 'V'), ('O', 'E', 'V', 'L'), ('V', 'L', 'O', 'E'), ('V', 'L', 'E', 'O'), ('V', 'O', 'L', 'E'), ('V', 'O', 'E', 'L'), ('V', 'E', 'L', 'O'), ('V', 'E', 'O', 'L'), ('E', 'L', 'O', 'V'), ('E', 'L', 'V', 'O'), ('E', 'O', 'L', 'V'), ('E', 'O', 'V', 'L'), ('E', 'V', 'L', 'O'), ('E', 'V', 'O', 'L')]
>>> pprint(list(permutations('LOVE')))
[('L', 'O', 'V', 'E'),
 ('L', 'O', 'E', 'V'),
 ('L', 'V', 'O', 'E'),
 ('L', 'V', 'E', 'O'),
 ('L', 'E', 'O', 'V'),
 ('L', 'E', 'V', 'O'),
 ('O', 'L', 'V', 'E'),
 ('O', 'L', 'E', 'V'),
 ('O', 'V', 'L', 'E'),
 ('O', 'V', 'E', 'L'),
 ('O', 'E', 'L', 'V'),
 ('O', 'E', 'V', 'L'),
 ('V', 'L', 'O', 'E'),
 ('V', 'L', 'E', 'O'),
 ('V', 'O', 'L', 'E'),
 ('V', 'O', 'E', 'L'),
 ('V', 'E', 'L', 'O'),
 ('V', 'E', 'O', 'L'),
 ('E', 'L', 'O', 'V'),
 ('E', 'L', 'V', 'O'),
 ('E', 'O', 'L', 'V'),
 ('E', 'O', 'V', 'L'),
 ('E', 'V', 'L', 'O'),
 ('E', 'V', 'O', 'L')]
>>> pprint(list(permutations('LOVE', 2)))
[('L', 'O'),
 ('L', 'V'),
 (
'L', 'E'),
 ('O', 'L'),
 ('O', 'V'),
 ('O', 'E'),
 ('V', 'L'),
 ('V', 'O'),
 ('V', 'E'),
 ('E', 'L'),
 ('E', 'O'),
 ('E', 'V')]
>>> pprint(list(combinations('LOVE', 2)))
[('L', 'O'), ('L', 'V'), ('L', 'E'), ('O', 'V'), ('O', 'E'), ('V', 'E')]
>>> # product(userstatus, action)
>>> 
>>> 
>>> p = 'password'
>>> p.replace('o', '0')
'passw0rd'
>>> p.upper()
'PASSWORD'
>>> p.title()
'Password'
>>> p.title().swapcase()
'pASSWORD'
>>> password[:-1]
'voltro'
>>> p[:-1]
'passwor'
>>> p[:-1] + p[-1].upper()
'passworD'
>>> (p[:-1] + p[-1].upper()).swapcase()
'PASSWORd'
>>> 
>>> range(10)
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> map(str, range(10))
['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
>>> map(str, range(10)) + ['']
['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '']
>>> map(str, range(100)) + ['']
['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31', '32', '33', '34', '35', '36', '37', '38', '39', '40', '41', '42', '43', '44', '45', '46', '47', '48', '49', '50', '51', '52', '53', '54', '55', '56', '57', '58', '59', '60', '61', '62', '63', '64', '65', '66', '67', '68', '69', '70', '71', '72', '73', '74', '75', '76', '77', '78', '79', '80', '81', '82', '83', '84', '85', '86', '87', '88', '89', '90', '91', '92', '93', '94', '95', '96', '97', '98', '99', '']
>>> 
>>> 
>>> 
>>> prefixes = map(str, range(10))
>>> case_variants = [p, p.upper(), p.title(), p.title().swapcase(), p[:-1] + p[-1].upper(),
		    (p[:-1] + p[-1].upper()).swapcase(), p.replace('o', '0'),
		 p.replace('o', '0').title(), p.replace('o', '0')[:-1] + p[-1].upper()]
>>> case_variants = [p, p.upper(), p.title(), p.title().swapcase(), p[:-1] + p[-1].upper(),
		    (p[:-1] + p[-1].upper()).swapcase(), p.replace('o', '0'),
		 p.replace('o', '0').title(), p.replace('o', '0')[:-1] + p[-1].upper(),
		 (p.replace('o', '0')[:-1] + p[-1].upper()).swapcase()]
>>> case_variants
['password', 'PASSWORD', 'Password', 'pASSWORD', 'passworD', 'PASSWORd', 'passw0rd', 'Passw0Rd', 'passw0rD', 'PASSW0Rd']
>>> suffixes = map(str, range(100)) + ['']
>>> suffixes = map(str, range(1000)) + ['']
>>> 
>>> len(prefixes)
10
>>> len(case_variants)
10
>>> len(suffixes)
1001
>>> 1001 + 10 + 10
1021
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
password
PASSWORD
Password
pASSWORD
passworD
PASSWORd
passw0rd
Passw0Rd
passw0rD
PASSW0Rd
123456
123456
123456
123456
123456
123456
123456
123456
123456
123456
12345678
12345678
12345678
12345678
12345678
12345678
12345678
12345678
12345678
12345678
1234
1234
1234
1234
1234
1234
1234
1234
1234
1234
qwerty
QWERTY
Qwerty
qWERTY
qwertY
QWERTy
qwerty
Qwerty
qwertY
QWERTy
12345
12345
12345
12345
12345
12345
12345
12345
12345
12345
dragon
DRAGON
Dragon
dRAGON
dragoN
DRAGOn
drag0n
Drag0N
drag0N
DRAG0n
pussy
PUSSY
Pussy
pUSSY
pussY
PUSSy
pussy
Pussy
pussY
PUSSy
baseball
BASEBALL
Baseball
bASEBALL
basebalL
BASEBALl
baseball
Baseball


Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 85, in <module>
    print password
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
('0', 'password')
('0', 'PASSWORD')
('0', 'Password')
('0', 'pASSWORD')
('0', 'passworD')
('0', 'PASSWORd')
('0', 'passw0rd')
('0', 'Passw0Rd')
('0', 'passw0rD')
('0', 'PASSW0Rd')
('1', 'password')
('1', 'PASSWORD')
('1', 'Password')
('1', 'pASSWORD')
('1', 'passworD')
('1', 'PASSWORd')
('1', 'passw0rd')
('1', 'Passw0Rd')
('1', 'passw0rD')
('1', 'PASSW0Rd')
('2', 'password')
('2', 'PASSWORD')
('2', 'Password')
('2', 'pASSWORD')
('2', 'passworD')
('2', 'PASSWORd')
('2', 'passw0rd')
('2', 'Passw0Rd')
('2', 'passw0rD')
('2', 'PASSW0Rd')
('3', 'password')
('3', 'PASSWORD')
('3', 'Password')
('3', 'pASSWORD')
('3', 'passworD')
('3', 'PASSWORd')
('3', 'passw0rd')
('3', 'Passw0Rd')
('3', 'passw0rD')
('3', 'PASSW0Rd')
('4', 'password')
('4', 'PASSWORD')
('4', 'Password')
('4', 'pASSWORD')
('4', 'passworD')
('4', 'PASSWORd')
('4', 'passw0rd')
('4', 'Passw0Rd')
('4', 'passw0rD')
('4', 'PASSW0Rd')
('5', 'password')
('5', 'PASSWORD')
('5', 'Password')
('5', 'pASSWORD')
('5', 'passworD')
('5', 'PASSWORd')
('5', 'passw0rd')
('5', 'Passw0Rd')
('5', 'passw0rD')
('5', 'PASSW0Rd')
('6', 'password')
('6', 'PASSWORD')
('6', 'Password')
('6', 'pASSWORD')
('6', 'passworD')
('6', 'PASSWORd')
('6', 'passw0rd')
('6', 'Passw0Rd')
('6', 'passw0rD')
('6', 'PASSW0Rd')
('7', 'password')
('7', 'PASSWORD')
('7', 'Password')
('7', 'pASSWORD')
('7', 'passworD')
('7', 'PASSWORd')
('7', 'passw0rd')
('7', 'Passw0Rd')
('7', 'passw0rD')
('7', 'PASSW0Rd')
('8', 'password')
('8', 'PASSWORD')
('8', 'Password')
('8', 'pASSWORD')
('8', 'passworD')
('8', 'PASSWORd')
('8', 'passw0rd')
('8', 'Passw0Rd')
('8', 'passw0rD')
('8', 'PASSW0Rd')
('9', 'password')
('9', 'PASSWORD')
('9', 'Password')
('9', 'pASSWORD')
('9', 'passworD')
('9', 'PASSWORd')
('9', 'passw0rd')
('9', 'Passw0Rd')
('9', 'passw0rD')
('9', 'PASSW0Rd')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('0', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('1', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('2', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('3', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('4', '123456')
('5', '123456')
('5', '123456')
('5', '123456')
('5', '123456')
('5', '123456')
('5', '123456')


Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 87, in <module>
    print password
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
0password
0PASSWORD
0Password
0pASSWORD
0passworD
0PASSWORd
0passw0rd
0Passw0Rd
0passw0rD
0PASSW0Rd
1password
1PASSWORD
1Password
1pASSWORD
1passworD
1PASSWORd
1passw0rd
1Passw0Rd
1passw0rD
1PASSW0Rd
2password
2PASSWORD
2Password
2pASSWORD
2passworD
2PASSWORd
2passw0rd
2Passw0Rd
2passw0rD
2PASSW0Rd
3password
3PASSWORD
3Password
3pASSWORD
3passworD
3PASSWORd
3passw0rd
3Passw0Rd
3passw0rD
3PASSW0Rd
4password
4PASSWORD
4Password
4pASSWORD
4passworD
4PASSWORd
4passw0rd
4Passw0Rd
Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 87, in <module>
    print ''.join(password)
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
0password0
0password1
0password2
0password3
0password4
0password5
0password6
0password7
0password8
0password9
0password10
0password11
0password12
0password13
0password14
0password15
0password16
0password17
0password18
0password19
0password20
0password21
0password22
0password23
0password24
0password25
0password26
0password27
0password28
0password29
0password30
0password31
0password32
0password33
0password34
0password35
0password36
0password37
0password38
0password39
0password40
0password41
0password42
0password43
0password44
0password45
0password46
0password47
0password48
0password49
0password50
0password51
0password52
0password53
0password54
0password55
0password56
0password57
0password58


Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 88, in <module>
    print password
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
>>> 
>>> range(1900, 2050)
[1900, 1901, 1902, 1903, 1904, 1905, 1906, 1907, 1908, 1909, 1910, 1911, 1912, 1913, 1914, 1915, 1916, 1917, 1918, 1919, 1920, 1921, 1922, 1923, 1924, 1925, 1926, 1927, 1928, 1929, 1930, 1931, 1932, 1933, 1934, 1935, 1936, 1937, 1938, 1939, 1940, 1941, 1942, 1943, 1944, 1945, 1946, 1947, 1948, 1949, 1950, 1951, 1952, 1953, 1954, 1955, 1956, 1957, 1958, 1959, 1960, 1961, 1962, 1963, 1964, 1965, 1966, 1967, 1968, 1969, 1970, 1971, 1972, 1973, 1974, 1975, 1976, 1977, 1978, 1979, 1980, 1981, 1982, 1983, 1984, 1985, 1986, 1987, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039, 2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2048, 2049]
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
password 32edb356ba8f86b0db371879640a9150
password0 c538258eced7d9c6846f076593b51a69
password1 9844341da73adcf2d198c5edc3e7d131
password2 238d585dbf83264363c5125efb5e1989
password3 6b5325b1fe667d9020593bc586277bbe
password4 46aa88c976708238e50f1f84f170fd77
password5 b2bcda723c42135773edd9be1259eb61
password6 3a0d274153e9af4d340f9c83d043401e
password7 fd45a7d3e030627005ce4722d72e408c
password8 73581033b419cbc5be2d4e80fab50e78
password9 d290d35b88763282bda1ff7dacacd1e6
password10 b85a66ab86935659e70362c7e7c0404b
password11 5b89a77f0b61fc6c85cfabcbd61aad9e
password12 34593588413386dd91877a3fa056bda6
password13 6d386472fa3b4ebaf6b66299c4e5c8c3
password14 8d4b8a6c5d9e3169a222dfa0df1f9fbb
password15 fa6c749b247b695514547723436e38ae
password16 bdd2f2bff8f2565727951500b458eeed
password17 b0cfdcb78fca1c1e947f8cdc41240e88
password18 ba52a2bf7807b29aef7dd124ef50520b
password19 f6333bf8eed8c8148013f0ef2ef9818c
password20 067ce0dbab85c3e65646c632607140df
password21 6adb832afb09306821e88dff19210fd3
password22 3d7ec118af85857bf0345b026a29decc
password23 1b0eacc1e1d3dea508439c1482fff4e8
password24 f0a4db6786fa6db66bb0f89cfd6fee22


Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 89, in <module>
    print password, hashpass
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
passw0rD --> ['kyle']
7Superman --> ['thomas', 'don']
7Superman --> ['thomas', 'don']

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 87, in <module>
    password = ''.join(t)
KeyboardInterrupt
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
passw0rD --> ['kyle']
7Superman --> ['thomas', 'don']
1Asdfasdf --> ['siva']
passw0rD --> ['kyle']
1marylanD --> ['glenn']
Vietnam90 --> ['alan']

=============================== RESTART: Shell ===============================
>>> 
>>> 
>>> 
