'''

Identity functions have the output exactly same thoer input.

Pure functions give the same answer for the same inputs every time,
and they have no side-effects on the environment.

Higher order functions use other funcs as input or output data.

Decorators are higher functions that take exactly one function as an input and return one as an output.

Functions are objects like anything else:
    Attributes:  __class__, __name__, __doc__, __code__
    Method:      __call__

'''

from functools import wraps

def add_logging(orig_func):

    @wraps(orig_func)               # This copies the __name__ and __doc__ from orig_func
    def logging_func(*args):        # variable number of arguments
        print 'The {0}() function was called with {1!r}'.format(orig_func.__name__, args)
        answer = orig_func(*args)
        print 'The answer is {!r}'.format(answer)
        return answer
    
   
    return logging_func

def cache(orig_func):
    answers = {}

    @wraps(orig_func)
    def inner(*args):
        'Compute a value times itself'
        if args in answers:
            return answers[args]
        answer = orig_func(*args)
        answers[args] = answer
        return answer

    return inner

#####################################################

if __name__ == '__main__':

    import math
    from pprint import pprint
    import time

    @cache                                      
    @add_logging                                # square = add_logging(sqaure)
    def square(x):
        'Compute a value times itself'
        return x * x

    @cache
    @add_logging
    def cube(x):
        'Compute a value times itself thrice'
        return x ** 3

    @cache
    @add_logging
    def collatz(x):
        return 3*x+1 if x%2==1 else x//2

    @add_logging
    @cache
    def big_func(x):
        'Simulate slow labor intensive function'
        print 'Doing hard work'
        time.sleep(1)
        return x + 1


    def makepow(base):
        def somepow(exp):
            return pow(base, exp)
        return somepow

    twopow, threepow, fourpow, fivepow, sixpow, sevenpow, eightpow, ninepow, thenpow = map(makepow, range(2,11))

