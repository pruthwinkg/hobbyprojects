
def run_cool(funcs, x):
    print 'Running the cool functions with', x
    for func in funcs:
        if getattr(func, 'cool', False):
            print func.__name__, func(x)

def run_happy(funcs, x):
    print 'Running the happy functions with', x
    for func in funcs:
        if getattr(func, 'happy', False):
            print func.__name__, func(x)

def happy(func):
    func.happy = True
    return func

def cool(func):
    func.cool = True
    return func

######################################

@cool
@happy                       # square = cool(happy(square))
def square(x):
    return x ** 2

@happy
def cube(x):
    return x ** 3

@cool
def collatz(x):
    return 3*x+1 if x % 2 else x // 2

if __name__ == '__main__':

    funcs = [square, cube, collatz, cube]
    run_cool(funcs, 5)
    run_happy(funcs, 100)
    run_cool(funcs, 10)
