import math

def add_logging(orig_func):
    def logging_func(x):
        print 'The {0}() function was called with {1!r}'.format(orig_func.__name__, x)
        answer = orig_func(x)
        print 'The answer is {!r}'.format(answer)
        return answer
    return logging_func

math.cos = add_logging(math.cos)      # Monkey patching
math.tan = add_logging(math.tan)      # Monkey patching
math.sin = add_logging(math.sin)      # Monkey patching





    
