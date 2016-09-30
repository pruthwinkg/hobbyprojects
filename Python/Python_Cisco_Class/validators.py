'''Collection of reusable data validation utilities

Common validators:
* validate_percentage
* validate_one_of('stock', 'bond', 'option', 'currency')
* validate_str(minsize=5, maxsize=8, predicate=str.upper)
* validate_email
* validate_macaddr

'''


def validate_percentage(value):
    if not isinstance(value, (bool, int, float)):
        raise TypeError('Expected int or float')
    if value < 0 or value > 100:
        raise ValueError('Expected 0 to 100')

def validate_macaddr(s):
    if not len(s) == 14:
        raise ValueError('Expected 14 characters including dots')
    if s[4] != '.' or s[9] != '.':
        raise ValueError('Missing Dots')
    s = s[:4] + s[5:9] + s[10:]
    if not set(s) <= 'ABCDEFabcdef0123456789':
        raise ValueError('Invalid characters')
