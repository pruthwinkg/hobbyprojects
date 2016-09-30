from pprint import pprint
import hashlib
import time
import random

## Security code ##############################################

userpass = {}                # Often, this is a persistent dictionary stored on disk

def digest(username, password):
    salt = 'the average life expectancy of a stark, lannister, or targaryen is pretty short'
    salt = repr((username, salt))
    return hashlib.pbkdf2_hmac('sha512', password, salt, 100000)

def verify_strong(password):
    if (len(password) >= 6 and
        any(map(str.isdigit, password)) and
        any(map(str.isupper, password)) and
        any(map(str.islower, password))):
        return
    raise ValueError('Weak password %r:  Must be 6 letters with upper and lowercase and a digit' % password)

def new_account(username, password):
    verify_strong(password)
    hashpass = digest(username, password)
    userpass[username] = hashpass

def secure_compare(a, b):
    'Resist timing attacks with a constant time string compare'
    return sum([p == q for p, q in zip(a, b)]) == len(a)

def verify(username, password):
    hashpass = digest(username, password)
    time.sleep(random.expovariate(25.0))
    return secure_compare(userpass[username], hashpass)

## Attacker Code ##################################
##
##rainbow_table = {}           # hashvalue -> password
##
##with open('notes2/common_passwords.txt') as f:
##    for line in f:
##        password = line.split(',')[0]
##        hashpass = digest(password)
##        rainbow_table[hashpass] = password

## User Sessions ##############################################

new_account('laura', 'cuBs1986')
new_account('glenn', '1marylanD')
new_account('alan', 'Vietnam90')
new_account('don', '7Superman')
new_account('joanne', '1braD007')
new_account('raymond', 'Cisco2016')
new_account('siva', '1Asdfasdf')
new_account('kyle', 'passw0rD')
new_account('vishal', '8bleeP')
new_account('thomas', '7Superman')

print verify('laura', 'cuBs1986')
print verify('raymond', 'sysco')

pprint(userpass)

##for username, hashpass in userpass.items():
##    if hashpass in rainbow_table:
##        print username, '-->', rainbow_table[hashpass]

## Reverse the hashpass table ################################################
# Model 1: Many          The key is the one and a list of values as the many

passuser = {}
for username, hashpass in userpass.items():
    if hashpass not in passuser:
        passuser[hashpass] = [username]
    else:
        passuser[hashpass].append(username)
pprint(passuser)

##############################################################################

from itertools import product

prefixes = [''] + map(str, range(10))
suffixes = [''] + map(str, range(1000) + range(1900, 2050))

start = time.time()
with open('day2/notes2/common_passwords.txt') as f:
    for line in f:
        p = line.split(',')[0]
        case_variants = set([p, p.upper(), p.title(), p.title().swapcase(), p[:-1] + p[-1].upper(),
                            (p[:-1] + p[-1].upper()).swapcase(), p.replace('o', '0'),
                             p.replace('o', '0').title(), p.replace('o', '0')[:-1] + p[-1].upper(),
                            (p.replace('o', '0')[:-1] + p[-1].upper()).swapcase()])
        for t in product(prefixes, case_variants, suffixes):
            password = ''.join(t)
            hashpass = digest('don', password)
            if hashpass in passuser:
                print password, '-->', passuser[hashpass]
                print time.time() - start

