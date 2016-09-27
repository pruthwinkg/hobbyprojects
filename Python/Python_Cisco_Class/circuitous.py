''' Circuitous(tm)                         # Give the project a name
An advanced circle analytic solution       # Elevator pitch -- what problem is being solved and how
'''

# Waterfall:  Requirements -> Design -> Coding -> Testing -> Documentation
# Agile:      Do a little req->des->cod->test->doc and repeat frequently <-- learning process
# Lean startup:  Create an MVP, ship it, get feedback, and alter course accordingly
# Generalization / Specialization is a poor model for object oriented programming because of penguins, dophins, and bats
# Inheritance: This is a tool whose sole purpose is code reuse.
# In new-style classes, we inherit from object() which gives us a new __getattribute__
# New-style classes have a much more interesting and powerful dot operator than old-style classes
# We typically don't put docstrings on dunder methods because
# 1) user's rarely see them and 2) the meaning of the dunder methods is well-known
# When copying from one namespace to another we usually keep the variable name the same
# the main exception is when the target namespace has its own jargon or ontology.
# With magic constants, we factor them out to give them a name for improved intelligiblity
# and express "a single source of truth"
# The purpose of modules is to 1) organize code and 2) to support code reuse,
# and 3) provide a single source of truth across an application.
# MVP:  Minimum viable product
# When creating an MVP, aim for the customer's biggest headache or for the crux of the problem
# YAGNI,RN:  You ain't gonna need it, right now.
# "Code is your enemy"
# Dogfooding
# "self" doesn't mean you.  It means "you or one of your children"
# D.R.Y.  Do not repeat yourself.

# Dunder methods:
#   print s                  ->   s.__str__()
#   >>> s                    ->   s.__repr__()
#   s[0]                     ->   s.__getitem__(0)
#   len(s)                   ->   s.__len__()
#   for c in s:              ->   s.__iter__() until StopIteration
#                            ->   s.__getitem__(0)  until IndexError
#   s(a, b)                  ->   s.__call__(a, b)
#   s.m                      ->   s.__getattribute__('m')
#   s + t                    ->   s.__add__(t)

import math
from collections import namedtuple

Version = namedtuple('Version', ['major', 'minor', 'micro'])   # Create a tuple with named fields

class Circle(object):
    'An advanced circle analytics toolkit for support circle analysis'

    version = Version(0, 2, 1)          # Class variables store data that is SHARED by all instances and the class itself

    def __init__(self, radius):
        self.radius = radius            # Instance variables store data that is UNIQUE to each instance

    def area(self):
        'Perform quadrature on a planar shape of uniform revolution'
        return math.pi * self.radius ** 2.0

    def perimeter(self):
        'Compute the perimater'
        return 2.0 * math.pi * self.radius 

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.radius)


    def angle_to_grade(angle):  # Use case is attaching regular functions to classes
        'Convert an inclinometer reading in degrees to a percent grade'
        return math.tan(math.radians(angle)) * 100.00

    angle_to_grade = staticmethod(angle_to_grade)   # Reprogram the dot to not add "self" as a first argument









