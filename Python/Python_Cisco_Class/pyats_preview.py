
def run_cool(inst, x):
    cls = inst.__class__
    print '\nRunning the cool functions in %s with %d' % (cls.__name__, x)
    for func in cls.__dict__.values():
        if getattr(func, 'cool', False):
            print func.__name__, func(inst, x)

def run_happy(inst, x):
    cls = inst.__class__
    print '\nRunning the happy functions in %s with %d' % (cls.__name__, x)
    for func in cls.__dict__.values():
        if getattr(func, 'happy', False):
            print func.__name__, func(inst, x)

def happy(func):
    func.happy = True
    return func

def cool(func):
    func.cool = True
    return func

######################################

class MathTools(object):

    @cool
    @happy                       # square = cool(happy(square))
    def square(self, x):
        return x ** 2

    @happy
    def cube(self, x):
        return x ** 3

    @cool
    def collatz(self, x):
        return 3*x+1 if x % 2 else x // 2

class PhysicsTools(object):

    @happy
    def string_theory(self, x):
        return 'Sorry, %s is untestable' % x

if __name__ == '__main__':

    m = MathTools()
    p = PhysicsTools()
    run_cool(m, 5)
    run_happy(m, 100)
    run_happy(p, 50)
    run_cool(m, 10)
