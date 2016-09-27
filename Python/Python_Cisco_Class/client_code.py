"Show-off the ciruitous code from the user's point of view"

from __future__ import division
from circuitous import Circle
import math

print u'Tutorial for Circuitous\N{trade mark sign}'
print 'Circle version %d.%d' % Circle.version[:2]
c = Circle(10)
print 'A circle with a radius of', c.radius
print 'has an area of', c.area()
print

## Academic Friends ######################################

from random import seed, random
from pprint import pprint

n = 10
jenny = 8675309
print 'DARPA Grant Proposal'
print 'to study the average area of random circles'
print 'using Circuitous(tm) version %d.%d' % Circle.version[:2]
print 'preliminary study using %d random circles' % n
print "seeded using Jenny's number: %d" % jenny
seed(jenny)
circles = [Circle(random()) for i in xrange(n)]
areas = [circle.area() for circle in circles]
average_area = sum(areas) / n
print 'The average area is %.1f' % average_area


## Rubber sheet company ###########################################

cut_template = [0.1, 0.2, 0.7]
print 'Spec sheet for template:', cut_template
circles = map(Circle, cut_template)

for i, circle in enumerate(circles):
    print 'Circle #%d' %i
    print 'A circle with a cut radius of', circle.radius
    print 'has a perimater of', circle.perimeter()
    print 'has a cold area of', circle.area()
    circle.radius *= 1.1
    print 'and a warm area of', circle.area()
    print

## National Tire Chain ############################################

class Tire(Circle):
    'Circular tires with a perimeter corrected for the rubber o the tire'
    RUBBER_RATIO = 1.25    

    def perimeter(self):
        return Circle.perimeter(self) * self.RUBBER_RATIO           # Extending
        #return 2.0 * math.pi * self.radius * self.RUBBER_RATIO      # Overriding

class MonsterTire(Tire):

    RUBBER_RATIO = 1.50

t = Tire(30)
print 'A tire with an inner raius of', t.radius
print 'has an area of', t.area()
print 'and has an outer perimeter of ', t.perimeter()
print

t = MonsterTire(30)
print 'A tire with an inner raius of', t.radius
print 'has an area of', t.area()
print 'and has an outer perimeter of ', t.perimeter()
print


## National Trucking Company ##############################################

print u'An inclinometer reading of 5\N{degree sign}',
print 'is a %f%% grade' % Circle.angle_to_grade(5)
print

