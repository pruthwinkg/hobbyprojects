import random
import string
import uuid

def generate_random_string(length, chars=string.ascii_letters + string.digits):
    return ''.join(random.choice(chars) for _ in range(length))


def generate_uuid(prefix, length):
    uuid_length = length - len(prefix)
    random_string = ''.join(random.choice(string.hexdigits) for _ in range(uuid_length))
    final_uuid = f"{prefix}{random_string}"
    return final_uuid

def generate_mac_address():
    """Generate a random MAC address."""
    mac = [0x00, 0x16, 0x3e,
           random.randint(0x00, 0x7f),
           random.randint(0x00, 0xff),
           random.randint(0x00, 0xff)]
    return ':'.join(map(lambda x: "%02x" % x, mac))