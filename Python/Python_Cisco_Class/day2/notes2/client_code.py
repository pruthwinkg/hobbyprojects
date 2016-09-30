"Show-off the ciruitous code from the user's point of view"

from __future__ import division
from circuitous import Circle

print u'Tutorial for Circuitous\N{trade mark sign}'
print 'Circle version %d.%d' % Circle.version[:2]
c = Circle(10)
print 'A circle with a radius of', c.radius
print 'has an area of', c.area()
print

## Academic Friends ######################################

from random import seed, random
from pprint import pprint

n = 100000
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
print 'The average area is %.5f' % average_area
print

## Rubber Sheet Company ################################################

cut_template = [0.1, 0.2, 0.7]
print 'Spec sheet for the template:', cut_template
circles = map(Circle, cut_template)

for i, circle in enumerate(circles, start=1):
    print 'Circle #%d' % i
    print 'A circle with a cut radius of', circle.radius
    print 'has a perimeter of', circle.perimeter()
    print 'has a cold area of', circle.area()
    circle.radius *= 1.1
    # circle.set_radius(circle.get_radius() * 1.1)
    print 'and a warm area of', circle.area()
    print

## National Tire Chain ################################################

class Tire(Circle):
    'Circular tires with a perimeter corrected for the rubber on the tire'

    __slots__ = []

    RUBBER_RATIO = 1.25

    def perimeter(self):
        return Circle.perimeter(self) * self.RUBBER_RATIO       # Extending
        return 2.0 * 3.14 * self.radius * self.RUBBER_RATIO     # Overriding

    __perimeter = perimeter

class MonsterTire(Tire):

    __slots__ = []

    RUBBER_RATIO = 1.50

t = Tire(30)
print 'A tire with an inner radius of', t.radius
print 'has an inner area of', t.area()
print 'and an outer perimeter of', t.perimeter()
print

m = MonsterTire(30)
print 'A monster tire with an inner radius of', m.radius
print 'has an inner area of', m.area()
print 'and an outer perimeter of', m.perimeter()
print

## National Trucking Company ##############################################

print u'An inclinometer reading of 5\N{degree sign}',
print 'is a %.1f%% grade.' % Circle.angle_to_grade(5)
print

## National Graphics Company ##############################################

c = Circle.from_bbd(25)
print 'A circle with a bounding box diagonal of 25'
print 'has a radius of', c.radius
print 'a perimeter of', c.perimeter()
print 'and an area of', c.area()
print

## US Gov't ###############################################################

# ISO 10666: No circle software shall compute an area directly from
# instance data.  It MUST first call perimeter and infer the data indirectly.

# ISO 10667: No circle software shall store the radius in an instance.
# It MUST store the diameter and ONLY the diameter.

