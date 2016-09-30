''' World Famous Fibonacci function

        Fibo definition:
               0 -> 0
               1 -> 1
               n -> F(n-1) + F(n-2),    where n >= 1

        How to trace:

                $ python -m trace --count fibo.py
                55

     Dynamic Programming!
        
'''

from decorator_school import cache

def fibo(n):
    a, b = 0, 1
    for i in xrange(n):
        a, b = b, a+b
    return a

@cache
def fibo(n):
    if n == 0: return 0
    if n == 1: return 1
    return fibo(n-1) + fibo(n-2)
    

print fibo(200)
