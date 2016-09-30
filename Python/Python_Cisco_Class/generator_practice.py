# Generators are a kind of iterator that runs code
#    iterator protocol -> __iter__ next()
#    runs code until there is yield which returns a value
#    when next() is sent, it resumes from it left off
#    when it is done, it raises StopIteration

# Strategy for making generators:
#    write a function using "print"
#    once it prints what you want, convert to "yield"


print '\nTask 1: Reinvent xrange()'

def myxrange(stop):
    i = 0
    while i < stop:
        yield i
        i += 1

print list(myxrange(10))
print sum(myxrange(1000000))


print '\nTask 2: Reinvent enumerate()'

def myenumerate(iterable, start=0):
    i = start
    for element in iterable:
        yield(i, element)
        i += 1

print dict(myenumerate(['raymond', 'rachel', 'matthew'], start=100))


print '\nTask 3: Reinvent reversed()'


def myreversed(sequence):
    i = len(sequence) - 1
    while(i >= 0):
        yield sequence[i]
        i -= 1

print ''.join(myreversed('abcdef'))

print '\nTask 4:  Reinvent izip()'

def myizip(s1, s2):
    it1 = iter(s1)
    it2 = iter(s2)
    while True:
        try:
            v1 = next(it1)
            v2 = next(it2)
        except StopIteration:
            break
        yield (v1, v2)

print list(myizip('abcde', 'xyz'))
print dict(myizip('abcde', 'xyz'))





