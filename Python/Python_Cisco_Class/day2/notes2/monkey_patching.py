''' Monkey patching is making variable assignments into some other namespace.

    Legitimate use cases for monkey patching:

        * Fixing erroneous contants
        * Improve error messages
        * Add debugging information
        * Expand the range of inputs

    Illegitimate:

        * If you ever monkey patch your own code, you're living in a state of sin
          and deserve whatever maintenance problems ensue.

'''

import math
import algebra

algebra.pi = math.pi

orig_area_triangle = algebra.area_triangle                # Step 1:  Save reference to original

def better_area_triangle(base, height):                   # Step 2:  Write a wrapper function
    'Wrapper to improve error handling'
    try:
        return orig_area_triangle(base, height)
    except RuntimeError:
        raise ValueError('Negative base or height not supported, use positive inputs instead')

algebra.area_triangle = better_area_triangle              # Step 3:  Monkey patch

orig_sqrt = math.sqrt                                     # Step 1:  Save reference to original

def better_sqrt(x):                                       # Step 2:  Write a wrapper function
    'Wraps math.sqrt to add support for negative inputs'
    if x >= 0.0:
        return orig_sqrt(x)
    return orig_sqrt(-x) * 1j

math.sqrt = better_sqrt                                   # Step 3:  Monkey patch

#############################################################################

if __name__ == '__main__':

    print u'My sources tell me that \N{greek small letter pi} =', algebra.pi
    print 'and that the area of a circle of radius ten is:', algebra.area(10)
    print 'The area of the 1st triangle is', algebra.area_triangle(base=25, height=10)
    try:
        print 'The area of the 2nd triangle is', algebra.area_triangle(base=-5, height=20)
    except ValueError:
        print '... oops, I did it again!'
    print u'The solutions to 12x\N{superscript two} + 23x + 10 = 0 are:'
    print algebra.quadratic(a=12, b=23, c=10)
    print u'The solutions to 12x\N{superscript two} + 8x + 10 = 0 are:'
    print algebra.quadratic(a=12, b=8, c=10)
