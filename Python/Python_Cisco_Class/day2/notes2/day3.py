Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 26 2016, 12:10:39) 
[GCC 4.2.1 (Apple Inc. build 5666) (dot 3)] on darwin
Type "copyright", "credits" or "license()" for more information.
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '4bf5b1c6c5404991f3212153d023f5dd',
 'don': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'glenn': 'b6c329e4c1f5ce5759f8cc8312d11c00',
 'joanne': 'a0947f5a710cfa4b66bc62931aa89354',
 'kyle': '8cfb0ac0f1f255c045db0b88902d7932',
 'laura': '6ed26cee5db448c36cffef9b47891baf',
 'raymond': 'c87c33040612632a7a1b0e592aebd956',
 'siva': '8fce1aa343cc97c47cf46e02fa5b0b9a',
 'thomas': 'ac8fb4c5e881ba9b765663fafc0ec858',
 'vishal': '274b76855c4a3752796af3873b2e0d6a'}
{'274b76855c4a3752796af3873b2e0d6a': ['vishal'],
 '4bf5b1c6c5404991f3212153d023f5dd': ['alan'],
 '6ed26cee5db448c36cffef9b47891baf': ['laura'],
 '8cfb0ac0f1f255c045db0b88902d7932': ['kyle'],
 '8fce1aa343cc97c47cf46e02fa5b0b9a': ['siva'],
 'a0947f5a710cfa4b66bc62931aa89354': ['joanne'],
 'ac8fb4c5e881ba9b765663fafc0ec858': ['thomas', 'don'],
 'b6c329e4c1f5ce5759f8cc8312d11c00': ['glenn'],
 'c87c33040612632a7a1b0e592aebd956': ['raymond']}
>>> username = 'raymond'
>>> password = 'superman'
>>> username + password
'raymondsuperman'
>>> username = 'raymonds'
>>> password = 'uperman'
>>> username + password
'raymondsuperman'
>>> username = 'raymond'
>>> password = 'superman'
>>> repr((username, password))
"('raymond', 'superman')"
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 37, in <module>
    hashpass = digest(password)
TypeError: digest() takes exactly 2 arguments (1 given)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': 'eab02067ab95ccd829346a6351acd796',
 'don': '8c7d52ec9a84c1435066e35988ef5da6',
 'glenn': '7a7e7a53ffeb98b0a7f7d45c7d3db73d',
 'joanne': '3faa64dd2b3b6226c7218ba9bf76fa3a',
 'kyle': 'f1834696954f284e4fc18a47e6d11f2d',
 'laura': '3d1c555bd51f93e24dc879f02c0bc331',
 'raymond': 'b3a38c73f6abf8b450a95ef21741dc13',
 'siva': 'c577de6b667bbe647aa65993f90aed66',
 'thomas': '62aeb033af37919c8a750340317e424c',
 'vishal': '5e56944cbf048ed8e12794952a2aa38f'}
{'3d1c555bd51f93e24dc879f02c0bc331': ['laura'],
 '3faa64dd2b3b6226c7218ba9bf76fa3a': ['joanne'],
 '5e56944cbf048ed8e12794952a2aa38f': ['vishal'],
 '62aeb033af37919c8a750340317e424c': ['thomas'],
 '7a7e7a53ffeb98b0a7f7d45c7d3db73d': ['glenn'],
 '8c7d52ec9a84c1435066e35988ef5da6': ['don'],
 'b3a38c73f6abf8b450a95ef21741dc13': ['raymond'],
 'c577de6b667bbe647aa65993f90aed66': ['siva'],
 'eab02067ab95ccd829346a6351acd796': ['alan'],
 'f1834696954f284e4fc18a47e6d11f2d': ['kyle']}
>>> digest('don', '7Superman')
'8c7d52ec9a84c1435066e35988ef5da6'
>>> digest('thomas', '7Superman')
'62aeb033af37919c8a750340317e424c'
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': 'eab02067ab95ccd829346a6351acd796',
 'don': '8c7d52ec9a84c1435066e35988ef5da6',
 'glenn': '7a7e7a53ffeb98b0a7f7d45c7d3db73d',
 'joanne': '3faa64dd2b3b6226c7218ba9bf76fa3a',
 'kyle': 'f1834696954f284e4fc18a47e6d11f2d',
 'laura': '3d1c555bd51f93e24dc879f02c0bc331',
 'raymond': 'b3a38c73f6abf8b450a95ef21741dc13',
 'siva': 'c577de6b667bbe647aa65993f90aed66',
 'thomas': '62aeb033af37919c8a750340317e424c',
 'vishal': '5e56944cbf048ed8e12794952a2aa38f'}
{'3d1c555bd51f93e24dc879f02c0bc331': ['laura'],
 '3faa64dd2b3b6226c7218ba9bf76fa3a': ['joanne'],
 '5e56944cbf048ed8e12794952a2aa38f': ['vishal'],
 '62aeb033af37919c8a750340317e424c': ['thomas'],
 '7a7e7a53ffeb98b0a7f7d45c7d3db73d': ['glenn'],
 '8c7d52ec9a84c1435066e35988ef5da6': ['don'],
 'b3a38c73f6abf8b450a95ef21741dc13': ['raymond'],
 'c577de6b667bbe647aa65993f90aed66': ['siva'],
 'eab02067ab95ccd829346a6351acd796': ['alan'],
 'f1834696954f284e4fc18a47e6d11f2d': ['kyle']}
7Superman --> ['don']

========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': 'eab02067ab95ccd829346a6351acd796',
 'don': '8c7d52ec9a84c1435066e35988ef5da6',
 'glenn': '7a7e7a53ffeb98b0a7f7d45c7d3db73d',
 'joanne': '3faa64dd2b3b6226c7218ba9bf76fa3a',
 'kyle': 'f1834696954f284e4fc18a47e6d11f2d',
 'laura': '3d1c555bd51f93e24dc879f02c0bc331',
 'raymond': 'b3a38c73f6abf8b450a95ef21741dc13',
 'siva': 'c577de6b667bbe647aa65993f90aed66',
 'thomas': '62aeb033af37919c8a750340317e424c',
 'vishal': '5e56944cbf048ed8e12794952a2aa38f'}
{'3d1c555bd51f93e24dc879f02c0bc331': ['laura'],
 '3faa64dd2b3b6226c7218ba9bf76fa3a': ['joanne'],
 '5e56944cbf048ed8e12794952a2aa38f': ['vishal'],
 '62aeb033af37919c8a750340317e424c': ['thomas'],
 '7a7e7a53ffeb98b0a7f7d45c7d3db73d': ['glenn'],
 '8c7d52ec9a84c1435066e35988ef5da6': ['don'],
 'b3a38c73f6abf8b450a95ef21741dc13': ['raymond'],
 'c577de6b667bbe647aa65993f90aed66': ['siva'],
 'eab02067ab95ccd829346a6351acd796': ['alan'],
 'f1834696954f284e4fc18a47e6d11f2d': ['kyle']}

=============================== RESTART: Shell ===============================
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': 'fff1970fdd6029c3b99aa3a0997af203',
 'don': '0f793fb245b017582ce3743ee3761be7',
 'glenn': '30a774bb143e6612ec9e582e998194d3',
 'joanne': 'bf48a4c2d944a94395cb4060487dc8b0',
 'kyle': '2642e13aa18fd21e833b4a47d3c6e558',
 'laura': '07181db1939c7c51c0926689096da5da',
 'raymond': 'e371b0a0124986a7feba9a058f3893e0',
 'siva': 'b785512e210772947547e49e94d91eb7',
 'thomas': '7bd44aa0f7f88de53ac535b97396c913',
 'vishal': '5d05a2c04f1a7b8c729acfd6e49947c9'}
{'07181db1939c7c51c0926689096da5da': ['laura'],
 '0f793fb245b017582ce3743ee3761be7': ['don'],
 '2642e13aa18fd21e833b4a47d3c6e558': ['kyle'],
 '30a774bb143e6612ec9e582e998194d3': ['glenn'],
 '5d05a2c04f1a7b8c729acfd6e49947c9': ['vishal'],
 '7bd44aa0f7f88de53ac535b97396c913': ['thomas'],
 'b785512e210772947547e49e94d91eb7': ['siva'],
 'bf48a4c2d944a94395cb4060487dc8b0': ['joanne'],
 'e371b0a0124986a7feba9a058f3893e0': ['raymond'],
 'fff1970fdd6029c3b99aa3a0997af203': ['alan']}
7Superman --> ['don']
6.62993597984

========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '6d00ab09a5541affec98bb6b184394d1',
 'don': '9972da613e2fe7776142ab649f2bb27c',
 'glenn': '500f2e7f82c00142b27b028596c1c39b',
 'joanne': 'a09c8af5eb06fcc9c5339de3ae5fd5eb',
 'kyle': 'fd2b43d85b69ece2cf034a103e799904',
 'laura': '40229e15c553c68898d357c79a01784c',
 'raymond': '439e8283bc2c69e63b899f940c9e3b11',
 'siva': '89288fee9e6dbf69f1e54cd7e80dd763',
 'thomas': '6775e77950d84bd6147926c1d70f473e',
 'vishal': '9c301cc5e7e38c9cf5da747b9d52d908'}
{'40229e15c553c68898d357c79a01784c': ['laura'],
 '439e8283bc2c69e63b899f940c9e3b11': ['raymond'],
 '500f2e7f82c00142b27b028596c1c39b': ['glenn'],
 '6775e77950d84bd6147926c1d70f473e': ['thomas'],
 '6d00ab09a5541affec98bb6b184394d1': ['alan'],
 '89288fee9e6dbf69f1e54cd7e80dd763': ['siva'],
 '9972da613e2fe7776142ab649f2bb27c': ['don'],
 '9c301cc5e7e38c9cf5da747b9d52d908': ['vishal'],
 'a09c8af5eb06fcc9c5339de3ae5fd5eb': ['joanne'],
 'fd2b43d85b69ece2cf034a103e799904': ['kyle']}
7Superman --> ['don']
11.4127931595

========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '52a10d4f87f25b09c82467b4c951c309',
 'don': 'bdc1c1187358496490071442d99cfa67',
 'glenn': '3a7c1c95014d9d1566a81aeee8c9c8a9',
 'joanne': '39dd2de9e425a6e76e5087868545210a',
 'kyle': 'cd9d18dea354bd8b0c627719a7bca2fd',
 'laura': 'e6b824f6aad40c318d4f8ebf60cb1d05',
 'raymond': 'a40f3528f28a68b5043146004ba71dd8',
 'siva': '823844b344cabfbf123d84b05e18f06c',
 'thomas': '1a13c52cea35966dde7a8f6042ccc720',
 'vishal': 'b6ade6c64ea939fa0651d81571ffd77f'}
{'1a13c52cea35966dde7a8f6042ccc720': ['thomas'],
 '39dd2de9e425a6e76e5087868545210a': ['joanne'],
 '3a7c1c95014d9d1566a81aeee8c9c8a9': ['glenn'],
 '52a10d4f87f25b09c82467b4c951c309': ['alan'],
 '823844b344cabfbf123d84b05e18f06c': ['siva'],
 'a40f3528f28a68b5043146004ba71dd8': ['raymond'],
 'b6ade6c64ea939fa0651d81571ffd77f': ['vishal'],
 'bdc1c1187358496490071442d99cfa67': ['don'],
 'cd9d18dea354bd8b0c627719a7bca2fd': ['kyle'],
 'e6b824f6aad40c318d4f8ebf60cb1d05': ['laura']}

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 94, in <module>
    hashpass = digest('don', password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 14, in digest
    result = hashlib.md5(result + str(i)).hexdigest()
KeyboardInterrupt
>>> 11.4127931595 / 4 * 100000
285319.8289875
>>> 11.4127931595 / 4 * 100000 / 3600
79.25550805208333
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 42, in <module>
    new_account('laura', 'cuBs1986')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 23, in new_account
    hashpass = digest(username, password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 10, in digest
    salt = repr(username, salt)
TypeError: repr() takes exactly one argument (2 given)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 42, in <module>
    new_account('laura', 'cuBs1986')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 23, in new_account
    hashpass = digest(username, password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 11, in digest
    return hashlib.pdbkdf2_hmac('sha512', password, salt)
AttributeError: 'module' object has no attribute 'pdbkdf2_hmac'
>>> dir(hashlib)
['__all__', '__builtins__', '__doc__', '__file__', '__get_builtin_constructor', '__name__', '__package__', '_hashlib', '_trans_36', '_trans_5C', 'algorithms', 'algorithms_available', 'algorithms_guaranteed', 'binascii', 'md5', 'new', 'pbkdf2_hmac', 'sha1', 'sha224', 'sha256', 'sha384', 'sha512', 'struct']
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 42, in <module>
    new_account('laura', 'cuBs1986')
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 23, in new_account
    hashpass = digest(username, password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 11, in digest
    return hashlib.pbkdf2_hmac('sha512', password, salt)
TypeError: pbkdf2_hmac() takes at least 4 arguments (3 given)
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '\xae\x15\xa4\xcf\x0bOk\xc5\xf9fZf\xe2\x1bU\x86xF\x96mRR3\xbfO\xd4\xc29\xa5+\xfab@<;\xce-\x04\xb5\xac\xf0\x1e\xcdhc\xe8\xe9&c\xfbq.9\x8a\xb0\xd7\xb2w5\x11\x00\x82>-',
 'don': '\x86\x05\x8b\x99\x0c\x02\xea\x96G\xe6\xe2\xd0\x1f\xeb\x8e\xd8j0\xf6\xdb\xa1\x0bW*\x95u~\x14\x17\x02+\x15Q\x0e\x94\x0c\x9c\xd6\xec\x9c\xd2w\xa3\xbb~\xb3\xef\xbb,\xb4S\xa3\xd6O\x85\xfe(\xb2o\x15\x88\xf4O1',
 'glenn': "&5M(S\x9c\x9aC\xa8\xebS\xe2\x97\xc8\xb0m\x9f\x9e\xac\x87\x93+\xed;\xa3\xd7T\xfb\xde\tU(cI\x7f'q\xb4\x8a\xba\xe8)\x1f\x0c\x97i\xc4\x8e\xc4_\xad\xb8\x1d(\xcb(\x9d\xd5\xf5\xca\xe4/^\xab",
 'joanne': '\xc8\x08\x06)\xab\xbc\xf9\x16\xfc\x01C\x00\x14(5q\xbe\xca\x8d\xbdi\x90\xd6l\xf5\x10\xae\x1a\xa5\xb1\xd8\xbc/C\x19\xba\xc61\xfd\xf3>\xad\x1aH\x8f\xb70^\xc5>B9Z]Ua-\x89\xfereu\x8f\x9c',
 'kyle': '\xb5\x17\x11}\xc1\xd0\xa5R\xdcK\x16\xf5\xdf\xd5\x93\xbe\xaa\xf1\x19\x0e\x8d\x8d\x18\x93\xd3fI\xc2w\x8ex\xc7\xc0\xf9\xf37K\x1a`\x91-L8<\x8a=\x1f]\xde`5T\x07\xb0a\xbe\xa1\xea\xb2\xb2\xf7\xac\x8cO',
 'laura': '\x05m\x93m\xb1\xa7\x1d\xd6\x80\x95\xb9\xf7 \x88\xe3\xbdx\xaaD\xb1b;?\xe7\xc2\x00E\xaeQVM?\x82m\xdfp\xdc\xe7\xebn\xd8qj\xab\xc0\x0f?\xe5p\x18kz\x95#\xc2t\xc8\x00,\xe0a\xf3.\xe8',
 'raymond': '=\xf3-\xd9\xbf\xe3\x0f\x98*\ry\x87cca\xe6S.Gn\xeb\x9cZ\x1e\x1c@\xa5R\x16\xbf6\xac\r&\x85\xbd\x05\x19a\x7f!\xac\xb2\xa9J\x86\xabbHu\xce\xdd\xb8\xe6\x82\xb4\xc2\xfebWz\xc5\x0b\x86',
 'siva': 'n\xfa\xdd:\r\xc1\x1d\xf6\xbc*\x97\x01\xbc\xe4\x84\xd3>~\x90Vy:|\xf3\x0cB\x125\x84\x91&\x80\xc0\xcaR\xd92\xe9"\x965\xdf\x8a^\xb8y\x07L\xc46*#\xa2\xd5\xe1\x16,\xd1\x89*\xc8|d\x9b',
 'thomas': '\xd2\xa3\xdd#,{Y\xd0\x0b~^\xebH\xadF~3b\xad\xe6\xdd\x96\xac\xf6\xf4\xca\xc3\xb9\x7f\x18o\xa3\x15\xb7d\xe8\xba\x9b\x9f\xd5ur\x89\x84\xe9\xc2\xfan\x8b:4\x0e\xdd\x88\xa9B\x19s\xc7\xa2Rs\xf5\n',
 'vishal': '\x9f\xbdI\xe9\x10\x13\xd97\x9e\xcf\xf2$\xfeZ&\x88S\xf9\xaa\xa6~q\x05(\xa5\xdf\xebp\x05\xcc\x976$\xe3\x98W\xe6\xa0HI\x1a\x7f\x8f<B)\xb1\t\x0f\x99+\x94\x16)\x9dJM\xee\xa8\xd6\xe8\x9b$\r'}
{'\x05m\x93m\xb1\xa7\x1d\xd6\x80\x95\xb9\xf7 \x88\xe3\xbdx\xaaD\xb1b;?\xe7\xc2\x00E\xaeQVM?\x82m\xdfp\xdc\xe7\xebn\xd8qj\xab\xc0\x0f?\xe5p\x18kz\x95#\xc2t\xc8\x00,\xe0a\xf3.\xe8': ['laura'],
 "&5M(S\x9c\x9aC\xa8\xebS\xe2\x97\xc8\xb0m\x9f\x9e\xac\x87\x93+\xed;\xa3\xd7T\xfb\xde\tU(cI\x7f'q\xb4\x8a\xba\xe8)\x1f\x0c\x97i\xc4\x8e\xc4_\xad\xb8\x1d(\xcb(\x9d\xd5\xf5\xca\xe4/^\xab": ['glenn'],
 '=\xf3-\xd9\xbf\xe3\x0f\x98*\ry\x87cca\xe6S.Gn\xeb\x9cZ\x1e\x1c@\xa5R\x16\xbf6\xac\r&\x85\xbd\x05\x19a\x7f!\xac\xb2\xa9J\x86\xabbHu\xce\xdd\xb8\xe6\x82\xb4\xc2\xfebWz\xc5\x0b\x86': ['raymond'],
 'n\xfa\xdd:\r\xc1\x1d\xf6\xbc*\x97\x01\xbc\xe4\x84\xd3>~\x90Vy:|\xf3\x0cB\x125\x84\x91&\x80\xc0\xcaR\xd92\xe9"\x965\xdf\x8a^\xb8y\x07L\xc46*#\xa2\xd5\xe1\x16,\xd1\x89*\xc8|d\x9b': ['siva'],
 '\x86\x05\x8b\x99\x0c\x02\xea\x96G\xe6\xe2\xd0\x1f\xeb\x8e\xd8j0\xf6\xdb\xa1\x0bW*\x95u~\x14\x17\x02+\x15Q\x0e\x94\x0c\x9c\xd6\xec\x9c\xd2w\xa3\xbb~\xb3\xef\xbb,\xb4S\xa3\xd6O\x85\xfe(\xb2o\x15\x88\xf4O1': ['don'],
 '\x9f\xbdI\xe9\x10\x13\xd97\x9e\xcf\xf2$\xfeZ&\x88S\xf9\xaa\xa6~q\x05(\xa5\xdf\xebp\x05\xcc\x976$\xe3\x98W\xe6\xa0HI\x1a\x7f\x8f<B)\xb1\t\x0f\x99+\x94\x16)\x9dJM\xee\xa8\xd6\xe8\x9b$\r': ['vishal'],
 '\xae\x15\xa4\xcf\x0bOk\xc5\xf9fZf\xe2\x1bU\x86xF\x96mRR3\xbfO\xd4\xc29\xa5+\xfab@<;\xce-\x04\xb5\xac\xf0\x1e\xcdhc\xe8\xe9&c\xfbq.9\x8a\xb0\xd7\xb2w5\x11\x00\x82>-': ['alan'],
 '\xb5\x17\x11}\xc1\xd0\xa5R\xdcK\x16\xf5\xdf\xd5\x93\xbe\xaa\xf1\x19\x0e\x8d\x8d\x18\x93\xd3fI\xc2w\x8ex\xc7\xc0\xf9\xf37K\x1a`\x91-L8<\x8a=\x1f]\xde`5T\x07\xb0a\xbe\xa1\xea\xb2\xb2\xf7\xac\x8cO': ['kyle'],
 '\xc8\x08\x06)\xab\xbc\xf9\x16\xfc\x01C\x00\x14(5q\xbe\xca\x8d\xbdi\x90\xd6l\xf5\x10\xae\x1a\xa5\xb1\xd8\xbc/C\x19\xba\xc61\xfd\xf3>\xad\x1aH\x8f\xb70^\xc5>B9Z]Ua-\x89\xfereu\x8f\x9c': ['joanne'],
 '\xd2\xa3\xdd#,{Y\xd0\x0b~^\xebH\xadF~3b\xad\xe6\xdd\x96\xac\xf6\xf4\xca\xc3\xb9\x7f\x18o\xa3\x15\xb7d\xe8\xba\x9b\x9f\xd5ur\x89\x84\xe9\xc2\xfan\x8b:4\x0e\xdd\x88\xa9B\x19s\xc7\xa2Rs\xf5\n': ['thomas']}

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 80, in <module>
    start = time.time()
NameError: name 'time' is not defined
>>> 'cat' == 'dog'
False
>>> 'cat' == 'cog'
False
>>> 'cat' == 'coh'
False
>>> 'cat' == 'coi'
False
>>> 'cat' == 'coj'
False
>>> 100 ** 5
10000000000
>>> 100 * 5
500
>>> 
>>> 
>>> 
>>> a = 'catinthehat'
>>> b = 'catinahathe'
>>> zip(a, b)
[('c', 'c'), ('a', 'a'), ('t', 't'), ('i', 'i'), ('n', 'n'), ('t', 'a'), ('h', 'h'), ('e', 'a'), ('h', 't'), ('a', 'h'), ('t', 'e')]
>>> [p == q for p, q in zip(a, b)]
[True, True, True, True, True, False, True, False, False, False, False]
>>> all([p == q for p, q in zip(a, b)])
False
>>> sum([p == q for p, q in zip(a, b)])
6
>>> sum([p == q for p, q in zip(a, b)]) == len(a)
False
>>> 
========== RESTART: /Users/raymond/Dropbox/Public/sj149/security.py ==========
True
False
{'alan': '\xae\x15\xa4\xcf\x0bOk\xc5\xf9fZf\xe2\x1bU\x86xF\x96mRR3\xbfO\xd4\xc29\xa5+\xfab@<;\xce-\x04\xb5\xac\xf0\x1e\xcdhc\xe8\xe9&c\xfbq.9\x8a\xb0\xd7\xb2w5\x11\x00\x82>-',
 'don': '\x86\x05\x8b\x99\x0c\x02\xea\x96G\xe6\xe2\xd0\x1f\xeb\x8e\xd8j0\xf6\xdb\xa1\x0bW*\x95u~\x14\x17\x02+\x15Q\x0e\x94\x0c\x9c\xd6\xec\x9c\xd2w\xa3\xbb~\xb3\xef\xbb,\xb4S\xa3\xd6O\x85\xfe(\xb2o\x15\x88\xf4O1',
 'glenn': "&5M(S\x9c\x9aC\xa8\xebS\xe2\x97\xc8\xb0m\x9f\x9e\xac\x87\x93+\xed;\xa3\xd7T\xfb\xde\tU(cI\x7f'q\xb4\x8a\xba\xe8)\x1f\x0c\x97i\xc4\x8e\xc4_\xad\xb8\x1d(\xcb(\x9d\xd5\xf5\xca\xe4/^\xab",
 'joanne': '\xc8\x08\x06)\xab\xbc\xf9\x16\xfc\x01C\x00\x14(5q\xbe\xca\x8d\xbdi\x90\xd6l\xf5\x10\xae\x1a\xa5\xb1\xd8\xbc/C\x19\xba\xc61\xfd\xf3>\xad\x1aH\x8f\xb70^\xc5>B9Z]Ua-\x89\xfereu\x8f\x9c',
 'kyle': '\xb5\x17\x11}\xc1\xd0\xa5R\xdcK\x16\xf5\xdf\xd5\x93\xbe\xaa\xf1\x19\x0e\x8d\x8d\x18\x93\xd3fI\xc2w\x8ex\xc7\xc0\xf9\xf37K\x1a`\x91-L8<\x8a=\x1f]\xde`5T\x07\xb0a\xbe\xa1\xea\xb2\xb2\xf7\xac\x8cO',
 'laura': '\x05m\x93m\xb1\xa7\x1d\xd6\x80\x95\xb9\xf7 \x88\xe3\xbdx\xaaD\xb1b;?\xe7\xc2\x00E\xaeQVM?\x82m\xdfp\xdc\xe7\xebn\xd8qj\xab\xc0\x0f?\xe5p\x18kz\x95#\xc2t\xc8\x00,\xe0a\xf3.\xe8',
 'raymond': '=\xf3-\xd9\xbf\xe3\x0f\x98*\ry\x87cca\xe6S.Gn\xeb\x9cZ\x1e\x1c@\xa5R\x16\xbf6\xac\r&\x85\xbd\x05\x19a\x7f!\xac\xb2\xa9J\x86\xabbHu\xce\xdd\xb8\xe6\x82\xb4\xc2\xfebWz\xc5\x0b\x86',
 'siva': 'n\xfa\xdd:\r\xc1\x1d\xf6\xbc*\x97\x01\xbc\xe4\x84\xd3>~\x90Vy:|\xf3\x0cB\x125\x84\x91&\x80\xc0\xcaR\xd92\xe9"\x965\xdf\x8a^\xb8y\x07L\xc46*#\xa2\xd5\xe1\x16,\xd1\x89*\xc8|d\x9b',
 'thomas': '\xd2\xa3\xdd#,{Y\xd0\x0b~^\xebH\xadF~3b\xad\xe6\xdd\x96\xac\xf6\xf4\xca\xc3\xb9\x7f\x18o\xa3\x15\xb7d\xe8\xba\x9b\x9f\xd5ur\x89\x84\xe9\xc2\xfan\x8b:4\x0e\xdd\x88\xa9B\x19s\xc7\xa2Rs\xf5\n',
 'vishal': '\x9f\xbdI\xe9\x10\x13\xd97\x9e\xcf\xf2$\xfeZ&\x88S\xf9\xaa\xa6~q\x05(\xa5\xdf\xebp\x05\xcc\x976$\xe3\x98W\xe6\xa0HI\x1a\x7f\x8f<B)\xb1\t\x0f\x99+\x94\x16)\x9dJM\xee\xa8\xd6\xe8\x9b$\r'}
{'\x05m\x93m\xb1\xa7\x1d\xd6\x80\x95\xb9\xf7 \x88\xe3\xbdx\xaaD\xb1b;?\xe7\xc2\x00E\xaeQVM?\x82m\xdfp\xdc\xe7\xebn\xd8qj\xab\xc0\x0f?\xe5p\x18kz\x95#\xc2t\xc8\x00,\xe0a\xf3.\xe8': ['laura'],
 "&5M(S\x9c\x9aC\xa8\xebS\xe2\x97\xc8\xb0m\x9f\x9e\xac\x87\x93+\xed;\xa3\xd7T\xfb\xde\tU(cI\x7f'q\xb4\x8a\xba\xe8)\x1f\x0c\x97i\xc4\x8e\xc4_\xad\xb8\x1d(\xcb(\x9d\xd5\xf5\xca\xe4/^\xab": ['glenn'],
 '=\xf3-\xd9\xbf\xe3\x0f\x98*\ry\x87cca\xe6S.Gn\xeb\x9cZ\x1e\x1c@\xa5R\x16\xbf6\xac\r&\x85\xbd\x05\x19a\x7f!\xac\xb2\xa9J\x86\xabbHu\xce\xdd\xb8\xe6\x82\xb4\xc2\xfebWz\xc5\x0b\x86': ['raymond'],
 'n\xfa\xdd:\r\xc1\x1d\xf6\xbc*\x97\x01\xbc\xe4\x84\xd3>~\x90Vy:|\xf3\x0cB\x125\x84\x91&\x80\xc0\xcaR\xd92\xe9"\x965\xdf\x8a^\xb8y\x07L\xc46*#\xa2\xd5\xe1\x16,\xd1\x89*\xc8|d\x9b': ['siva'],
 '\x86\x05\x8b\x99\x0c\x02\xea\x96G\xe6\xe2\xd0\x1f\xeb\x8e\xd8j0\xf6\xdb\xa1\x0bW*\x95u~\x14\x17\x02+\x15Q\x0e\x94\x0c\x9c\xd6\xec\x9c\xd2w\xa3\xbb~\xb3\xef\xbb,\xb4S\xa3\xd6O\x85\xfe(\xb2o\x15\x88\xf4O1': ['don'],
 '\x9f\xbdI\xe9\x10\x13\xd97\x9e\xcf\xf2$\xfeZ&\x88S\xf9\xaa\xa6~q\x05(\xa5\xdf\xebp\x05\xcc\x976$\xe3\x98W\xe6\xa0HI\x1a\x7f\x8f<B)\xb1\t\x0f\x99+\x94\x16)\x9dJM\xee\xa8\xd6\xe8\x9b$\r': ['vishal'],
 '\xae\x15\xa4\xcf\x0bOk\xc5\xf9fZf\xe2\x1bU\x86xF\x96mRR3\xbfO\xd4\xc29\xa5+\xfab@<;\xce-\x04\xb5\xac\xf0\x1e\xcdhc\xe8\xe9&c\xfbq.9\x8a\xb0\xd7\xb2w5\x11\x00\x82>-': ['alan'],
 '\xb5\x17\x11}\xc1\xd0\xa5R\xdcK\x16\xf5\xdf\xd5\x93\xbe\xaa\xf1\x19\x0e\x8d\x8d\x18\x93\xd3fI\xc2w\x8ex\xc7\xc0\xf9\xf37K\x1a`\x91-L8<\x8a=\x1f]\xde`5T\x07\xb0a\xbe\xa1\xea\xb2\xb2\xf7\xac\x8cO': ['kyle'],
 '\xc8\x08\x06)\xab\xbc\xf9\x16\xfc\x01C\x00\x14(5q\xbe\xca\x8d\xbdi\x90\xd6l\xf5\x10\xae\x1a\xa5\xb1\xd8\xbc/C\x19\xba\xc61\xfd\xf3>\xad\x1aH\x8f\xb70^\xc5>B9Z]Ua-\x89\xfereu\x8f\x9c': ['joanne'],
 '\xd2\xa3\xdd#,{Y\xd0\x0b~^\xebH\xadF~3b\xad\xe6\xdd\x96\xac\xf6\xf4\xca\xc3\xb9\x7f\x18o\xa3\x15\xb7d\xe8\xba\x9b\x9f\xd5ur\x89\x84\xe9\xc2\xfan\x8b:4\x0e\xdd\x88\xa9B\x19s\xc7\xa2Rs\xf5\n': ['thomas']}

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 97, in <module>
    hashpass = digest('don', password)
  File "/Users/raymond/Dropbox/Public/sj149/security.py", line 13, in digest
    return hashlib.pbkdf2_hmac('sha512', password, salt, 100000)
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/hashlib.py", line 213, in pbkdf2_hmac
    rkey ^= int(binascii.hexlify(prev), 16)
KeyboardInterrupt
>>> 
>>> 
>>> 
>>> 
>>> [random.expovariate(2.0) for i in range(20)]
[0.383212800058289, 0.4165805005632202, 0.46499030014766746, 0.8201090289409808, 0.2933215418269363, 0.07308747761177434, 0.6669402328336995, 0.19184816663702206, 0.6290880382269778, 0.01124598121290786, 0.07332167588658756, 0.7539616581826912, 0.3242215187015236, 0.018211896794359066, 0.6019891546075661, 1.9144671163703073, 0.6483295221342883, 0.6150516679482355, 0.8482203873447652, 0.07418446084487636]
>>> from pprint import pprint
>>> pprint(sorted([random.expovariate(2.0) for i in range(100)]))
[0.0004603153231435356,
 0.0012663554036637084,
 0.002848143039542834,
 0.006536609720175324,
 0.013618818517316115,
 0.01691112685804074,
 0.019035596839927733,
 0.027851964016988036,
 0.03045230489929439,
 0.037388046755708663,
 0.04565122272867735,
 0.046951696874269755,
 0.06859890879991627,
 0.06870140157008336,
 0.08564796519846103,
 0.09294673748773036,
 0.09371027026744208,
 0.09901503608943964,
 0.12187175118023302,
 0.1318990720327899,
 0.13338560179164063,
 0.1444698319471214,
 0.15127884786496765,
 0.15489196127464247,
 0.1561089168396315,
 0.15726133768932782,
 0.1779352436670331,
 0.1784602797059847,
 0.18674201108226327,
 0.1898359143822347,
 0.1900321346673969,
 0.19188795683759824,
 0.192866011004884,
 0.19484318156277036,
 0.20364721681308512,
 0.21423712232399025,
 0.2193790151045368,
 0.23230839551036417,
 0.2458739872582944,
 0.24848991843198995,
 0.24888085690272177,
 0.25799339968607077,
 0.2618390684503006,
 0.26817644096657467,
 0.26929819020005563,
 0.2750609879680318,
 0.2891890283920494,
 0.30044633665522424,
 0.3080186848810076,
 0.3140247858156136,
 0.3251514527521619,
 0.33347185034940485,
 0.3384415116691779,
 0.36213345973457817,
 0.3644703246318074,
 0.3758644338625712,
 0.3832310000014989,
 0.38516337383503446,
 0.3916737875111845,
 0.3937653107235095,
 0.4100768699234494,
 0.4101945930918264,
 0.4651288806905725,
 0.47269520515663876,
 0.4755538559425685,
 0.4918548537078218,
 0.529902036493175,
 0.5465523635721402,
 0.5492012795967203,
 0.5535408218692247,
 0.5559304374724039,
 0.6149305719739082,
 0.6313315246261468,
 0.6332301751738637,
 0.6382910527531936,
 0.6674422764084189,
 0.6857146727811052,
 0.699426263948093,
 0.7102588431502607,
 0.7111660292564519,
 0.7507931871320994,
 0.7819407835228391,
 0.7908724496902049,
 0.7911176261730518,
 0.8174802052291399,
 0.8559999366433662,
 0.8991738917220671,
 0.9075447580040755,
 0.921908478954135,
 0.9535266676504961,
 1.0028730092177782,
 1.0321093756578548,
 1.055999884193323,
 1.1203759174464403,
 1.1455378190650345,
 1.3104916177856614,
 1.418532734710223,
 1.653962462352913,
 1.8557434258283536,
 3.6973598463960085]
>>> pprint(sorted([random.expovariate(5.0) for i in range(100)]))
[0.0005938012953263582,
 0.002434700029498844,
 0.0028395370241022086,
 0.004285783513701293,
 0.006129314896330769,
 0.006646579994091255,
 0.006992051773039009,
 0.010973880750246837,
 0.021463783011776587,
 0.02172640244780799,
 0.02205281938990785,
 0.024554447675133307,
 0.025374176664896924,
 0.026359368218284978,
 0.03608258104253612,
 0.03836981461594691,
 0.040009341434531207,
 0.04091495640213484,
 0.04264249672964238,
 0.04534491566567556,
 0.04681086560499892,
 0.050188030997381027,
 0.0511445096351516,
 0.05386394355748737,
 0.05854356329546584,
 0.059006736046162564,
 0.060488257931686475,
 0.06195663219689405,
 0.06338904044038587,
 0.06436370677668476,
 0.07005870347770383,
 0.07124288067740736,
 0.0722228071939946,
 0.07530547287715841,
 0.0777264764070715,
 0.08461158604447604,
 0.08514692321658832,
 0.08524323634383311,
 0.08627109124718371,
 0.08668021623169433,
 0.08814515710996255,
 0.08834989488146044,
 0.08966200906996494,
 0.09788641128505324,
 0.10256989340310822,
 0.11028893441019047,
 0.1122623978630192,
 0.11689351467478551,
 0.1358360938786372,
 0.14324565106916692,
 0.14340517459017113,
 0.14360252799602685,
 0.1480711717740158,
 0.15618455776448187,
 0.16698349958912984,
 0.16855207899279584,
 0.17020875010095093,
 0.17434461622540046,
 0.1949001445228958,
 0.19900712133491236,
 0.20054885543815598,
 0.20895155626385553,
 0.21138146067201408,
 0.21312025376809585,
 0.22027041959689017,
 0.22037271792316876,
 0.22192394585390723,
 0.22553563135587412,
 0.22769328570421296,
 0.22901778436202253,
 0.23607797899797361,
 0.24606996108374135,
 0.25238674802790634,
 0.25639912889062655,
 0.26261472061739927,
 0.27127578730547974,
 0.2732154895616644,
 0.275107528441744,
 0.2918035927234239,
 0.2983955356296643,
 0.30088632351938105,
 0.31643087911667944,
 0.3168302479049601,
 0.3180412190254967,
 0.33121239213000775,
 0.355431926958613,
 0.35665221733312297,
 0.3719861193222301,
 0.37815879903482247,
 0.40765743309919855,
 0.4207612136574377,
 0.4232481980504182,
 0.44539542333510973,
 0.4457557543789322,
 0.4554784958668539,
 0.5001048750465659,
 0.5894283666332808,
 0.5989574499650523,
 0.6532845175947214,
 0.7871898579301491]
>>> pprint(sorted([random.expovariate(25.0) for i in range(100)]))
[0.00017009627283655376,
 0.001315435769491987,
 0.002237569628303734,
 0.0022385643421616867,
 0.0026448694211142726,
 0.002675566173601245,
 0.003470262767318565,
 0.003999006186528421,
 0.004200702820257419,
 0.0049522781179879545,
 0.0062052811070564175,
 0.006431262013126662,
 0.006466826971335953,
 0.007077760892143105,
 0.007563507138533035,
 0.008056281211086654,
 0.008186594268899564,
 0.008559236060902533,
 0.008758057885632324,
 0.009157406860952264,
 0.009441574337152535,
 0.009476834360156741,
 0.00960409372314406,
 0.010952395739983975,
 0.011372590202574966,
 0.011379784782074263,
 0.011554917965648014,
 0.012171453073806517,
 0.012624568181941319,
 0.013406287480437087,
 0.01424684137781751,
 0.01427406776635808,
 0.01458361644838849,
 0.01549939059656645,
 0.01556738514024149,
 0.016204508344201615,
 0.017359165202101182,
 0.01827713067711945,
 0.01837208375406798,
 0.020603820024174734,
 0.021982824641795434,
 0.023108407600062573,
 0.02371566690677171,
 0.02442379505157434,
 0.024718264632289638,
 0.025513422815369467,
 0.02552158959076405,
 0.027358863285240276,
 0.0276117157778605,
 0.027625258529445463,
 0.027816400050426623,
 0.02834319768461946,
 0.02863482850445419,
 0.029429641250120438,
 0.03072831195039121,
 0.03100800752384864,
 0.0314220200226137,
 0.03168595919419583,
 0.031947815187921245,
 0.03282604605064797,
 0.03428046296648112,
 0.03502067333244852,
 0.039875795344549096,
 0.04262817322074299,
 0.04273365792527126,
 0.043519700107341484,
 0.04537563148673338,
 0.04599403656039771,
 0.05013863980209799,
 0.052872166854845394,
 0.06244022925126429,
 0.06251477909315759,
 0.06289494125225768,
 0.06457770565295852,
 0.0660259562142172,
 0.06889036652613278,
 0.06902308200399482,
 0.07108348314289668,
 0.07167846014803031,
 0.07216308281204041,
 0.0749392711959295,
 0.07978423383987812,
 0.08434572212604324,
 0.08477796721495676,
 0.08882266706640747,
 0.09191823236925702,
 0.09266204384382634,
 0.09642273439535964,
 0.10661418587279213,
 0.10838898596894823,
 0.11470554600563608,
 0.13485574403399705,
 0.13852238222511792,
 0.14716401693073344,
 0.1524818375315323,
 0.15827521597493058,
 0.17203060726394326,
 0.19508236914349758,
 0.2148167577374779,
 0.24980568399962017]
>>> '123'.isdigit()
True
>>> bm = '123'.isdigit
>>> bm()
True
>>> um = str.isdigit
>>> um('123')
True
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> rachel
2 --> matthew
3 -->

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/looping_idioms.py", line 16, in <module>
    print i, '-->', names[i]
IndexError: list index out of range
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
>>> range(len(colors) - 1, -1, -1)
[3, 2, 1, 0]
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
>>> names
['raymond', 'rachel', 'matthew']
>>> colors
['red', 'blue', 'yellow', 'green']
>>> #   <cond>  ?  <posres> :  <negres>;                   Ternary operator or conditional expression
>>> #   grade = (score >= 70) ? "pass" : "fail";
>>> 
>>> #   <posres> if <cond> else <negres>
>>> 
>>> score = 50
>>> 'pass' if score >= 70 else 'fail'
'fail'
>>> score = 85
>>> 'pass' if score >= 70 else 'fail'
'pass'
>>> 
>>> 
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
raymond --> red
rachel --> blue
matthew --> yellow
>>> nn
3
>>> nc
4
>>> n
3
>>> range(n)
[0, 1, 2]
>>> min([30, 5, 10, 20])
5
>>> max([30, 5, 10, 20])
30
>>> sum([30, 5, 10, 20])
65
>>> len([30, 5, 10, 20])
4
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
Blue
Green
Red
Yellow
>>> 
>>> len('hello')
5
>>> map(len, ['hello', 'goodbye'])
[5, 7]
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
Blue
Green
Red
Yellow
RED
BLUE
GREEN
YELLOW
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/looping_idioms.py =======
RAYMOND
RACHEL
MATTHEW
Raymond
Rachel
Matthew
1 --> raymond
2 --> rachel
3 --> matthew
0 --> raymond
1 --> rachel
2 --> matthew
GREEN
YELLOW
BLUE
RED
Green
Yellow
Blue
Red
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
raymond --> red
rachel --> blue
matthew --> yellow
Blue
Green
Red
Yellow
RED
BLUE
GREEN
YELLOW
Austin
Chicago
Dallas
>>> cities
['austin', 'dallas', 'chicago', 'dallas', 'austin', 'chicago']
>>> 
>>> # iterator school
>>> # property
>>> # with statement
>>> # validators
>>> # closures
>>> # decorators
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/iterator_school.py", line 47, in <module>
    s = Squares1(10)
NameError: name 'Squares1' is not defined
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
>>> 
>>> 
>>> s.__class__
<class __main__.Squares1 at 0x10065e328>
>>> vars(s)
{'stop': 10}
>>> len(s)
10
>>> s[0]
0
>>> s[1]
1
>>> s[2]
4
>>> s[3]
9
>>> s[4]
16
>>> s[10]

Traceback (most recent call last):
  File "<pyshell#88>", line 1, in <module>
    s[10]
  File "/Users/raymond/Dropbox/Public/sj149/iterator_school.py", line 44, in __getitem__
    raise IndexError
IndexError
>>> 
>>> 
>>> 
>>> for x in s:
	print x

	
0
1
4
9
16
25
36
49
64
81
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
>>> it
<iterator object at 0x10394dd50>
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
>>> it
<iterator object at 0x10424dd50>
>>> iter(it)
<iterator object at 0x10424dd50>
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> 
>>> 
>>> for c in 'cat':
	print c.upper()

	
C
A
T
>>> it = iter('cat')
>>> it
<iterator object at 0x10424de10>
>>> next(it)
'c'
>>> next(it)
'a'
>>> next(it)
't'
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#108>", line 1, in <module>
    next(it)
StopIteration
>>> dir(str)
['__add__', '__class__', '__contains__', '__delattr__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getnewargs__', '__getslice__', '__gt__', '__hash__', '__init__', '__le__', '__len__', '__lt__', '__mod__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '_formatter_field_name_split', '_formatter_parser', 'capitalize', 'center', 'count', 'decode', 'encode', 'endswith', 'expandtabs', 'find', 'format', 'index', 'isalnum', 'isalpha', 'isdigit', 'islower', 'isspace', 'istitle', 'isupper', 'join', 'ljust', 'lower', 'lstrip', 'partition', 'replace', 'rfind', 'rindex', 'rjust', 'rpartition', 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith', 'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']
>>> 
>>> s = 'cat'
>>> len(s)
3
>>> s[0]
'c'
>>> s[1]
'a'
>>> s[2]
't'
>>> s[3]

Traceback (most recent call last):
  File "<pyshell#116>", line 1, in <module>
    s[3]
IndexError: string index out of range
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> 
>>> 
>>> 
>>> dir(s)
['__doc__', '__init__', '__iter__', '__module__', 'stop']
>>> vars(s)
{'stop': 5}
>>> 
>>> 
>>> it = iter(s)

Traceback (most recent call last):
  File "<pyshell#124>", line 1, in <module>
    it = iter(s)
  File "/Users/raymond/Dropbox/Public/sj149/iterator_school.py", line 67, in __iter__
    return Squares2Iterator(self.stop)
NameError: global name 'Squares2Iterator' is not defined
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> it = iter(s)
>>> it
<__main__.Squares2Iterator instance at 0x1040da950>
>>> vars(it)
{'i': 0, 'stop': 5}
>>> iter(it)
<__main__.Squares2Iterator instance at 0x1040da950>
>>> 
>>> next(it)
0
>>> next(it)
1
>>> next(it)
4
>>> vars(it)
{'i': 3, 'stop': 5}
>>> next(it)
9
>>> next(it)
16
>>> 16
16
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#137>", line 1, in <module>
    next(it)
StopIteration
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16]
(0, 1, 4, 9, 16)
30
0
1
4
[9, 16]
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> squares3(10)
0
1
4
9
16
25
36
49
64
81
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> g = squares3(5)
>>> g
<generator object squares3 at 0x1038262d0>
>>> dir(g)
['__class__', '__delattr__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__iter__', '__name__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'close', 'gi_code', 'gi_frame', 'gi_running', 'next', 'send', 'throw']
>>> iter(g)
<generator object squares3 at 0x1038262d0>
>>> next(g)
0
>>> next(g)
1
>>> next(g)
4
>>> next(g)
9
>>> next(g)
16
>>> next(g)

Traceback (most recent call last):
  File "<pyshell#148>", line 1, in <module>
    next(g)
StopIteration
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
()
0

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/iterator_school.py", line 109, in <module>
    print next(it)
StopIteration
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> 
>>> 
>>> 
>>> 
>>> s = 'abc'
>>> for c in s:
	print c.upper()

	
A
B
C
>>> for c in s:
	print c.upper()

	
A
B
C
>>> 
>>> 
>>> s = 'abc'
>>> it = iter(s)
>>> for c in it:
	print c.upper()

	
A
B
C
>>> for c in it:
	print c.upper()

	

>>> 
>>> 
>>> 
>>> def f():
	yield 10
	yield 20
	yield 30

	
>>> g = f()
>>> g
<generator object f at 0x10394c460>
>>> next(g)
10
>>> next(g)
20
>>> next(g)
30
>>> next(g)

Traceback (most recent call last):
  File "<pyshell#181>", line 1, in <module>
    next(g)
StopIteration
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> 
>>> 
>>> 
>>> len('hello')
5
>>> pow(2, 5)
32
>>> from time import *
>>> time()
1475087574.583921
>>> 
>>> from functools import partial
>>> 
>>> pow(2, 5)
32
>>> 
>>> twopow = partial(pow, 2)
>>> twopow(5)
32
>>> twopow(7)
128
>>> 
>>> thirtytwo = partial(pow, 2, 5)
>>> thirtytwo()
32
>>> 
>>> from random import *
>>> range(10)
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> len(_)
10
>>> range(2, 10)
[2, 3, 4, 5, 6, 7, 8, 9]
>>> len(_)
8
>>> range(2, 10, 3)
[2, 5, 8]
>>> randrange(10)
6
>>> randrange(2, 10)
7
>>> randrange(2, 10, 3)
5
>>> 
>>> 
>>> range(1, 7)
[1, 2, 3, 4, 5, 6]
>>> roll = partial(randrange, 1, 7)
>>> roll()
2
>>> roll()
3
>>> roll()
5
>>> roll()
6
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
>>> roll()
7
>>> roll()
11
>>> roll()
9
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
9
6
5
2
10
9
8
11
3
9
10
8
11
11
12
4
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
56
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
0
20
>>> f = open('notes2/mpl_demo.py')
>>> type(f)
<type 'file'>
>>> f.read(10)
'from mpl_t'
>>> f.read(10)
'oolkits.mp'
>>> f.read(10)
'lot3d impo'
>>> f.read(10)
'rt Axes3D\n'
>>> f.read(10)
'import mat'
>>> f.read(10)
'plotlib.py'
>>> f.read(10)
'plot as pl'
>>> f.read(10)
't\nimport n'
>>> f.read(10)
'umpy as np'
>>> f.read(10)
'\n\nfig = pl'
>>> f.read(10)
't.figure()'
>>> f.read(10)
'\nax = fig.'
>>> f.read(10)
'add_subplo'
>>> f.read(10)
't(111, pro'
>>> f.read(10)
"jection='3"
>>> f.read(10)
"d')\nfor c,"
>>> f.read(10)
' z in zip('
>>> f.read(10)
"['r', 'g',"
>>> for i in range(100):
	print repr(f.read(10))

	
" 'b', 'y']"
', [30, 20,'
' 10, 0]):\n'
'    xs = n'
'p.arange(2'
'0)\n    ys '
'= np.rando'
'm.rand(20)'
'\n\n    # Yo'
'u can prov'
'ide either'
' a single '
'color or a'
'n array. T'
'o demonstr'
'ate this,\n'
'    # the '
'first bar '
'of each se'
't will be '
'colored cy'
'an.\n    cs'
' = [c] * l'
'en(xs)\n   '
" cs[0] = '"
"c'\n    ax."
'bar(xs, ys'
', zs=z, zd'
"ir='y', co"
'lor=cs, al'
'pha=0.8)\n\n'
'ax.set_xla'
"bel('X')\na"
'x.set_ylab'
"el('Y')\nax"
'.set_zlabe'
"l('Z')\n\npl"
't.show()\n'
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''
''


Traceback (most recent call last):
  File "<pyshell#243>", line 2, in <module>
    print repr(f.read(10))
  File "/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/idlelib/PyShell.py", line 1356, in write
    return self.shell.write(s, self.tags)
KeyboardInterrupt
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
50
0
from mpl_t
oolkits.mp
lot3d impo
rt Axes3D

import mat
plotlib.py
plot as pl
t
import n
umpy as np


fig = pl
t.figure()

ax = fig.
add_subplo
t(111, pro
jection='3
d')
for c,
 z in zip(
['r', 'g',
 'b', 'y']
, [30, 20,
 10, 0]):

    xs = n
p.arange(2
0)
    ys 
= np.rando
m.rand(20)


    # Yo
u can prov
ide either
 a single 
color or a
n array. T
o demonstr
ate this,

    # the 
first bar 
of each se
t will be 
colored cy
an.
    cs
 = [c] * l
en(xs)
   
 cs[0] = '
c'
    ax.
bar(xs, ys
, zs=z, zd
ir='y', co
lor=cs, al
pha=0.8)


ax.set_xla
bel('X')
a
x.set_ylab
el('Y')
ax
.set_zlabe
l('Z')

pl
t.show()

>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
60
8
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
0
19
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()


Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/iterator_school.py", line 148, in <module>
    print ''.join(iter(partial(f.read, 10)), '')
TypeError: 'functools.partial' object is not iterable
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
28
60
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

>>> 
>>> 
>>> s = raw_input('? ')
? Hello World
>>> s
'Hello World'
>>> 
>>> s = raw_input('? ')
? 30 + 40
>>> eval(s)
70
>>> s
'30 + 40'
>>> 30 + 40
70
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
49
10
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

? 30 + 40

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/iterator_school.py", line 155, in <module>
    print repr(eval(s))
TypeError: eval() arg 1 must be a string or code object
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
20
8
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

? 30 + 40
70
? 55 - 2 * 15
25
? 'hello' * 5
'hellohellohellohellohello'
? quit
>>> 
====== RESTART: /Users/raymond/Dropbox/Public/sj149/iterator_school.py ======
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
(0, 1, 4, 9, 16, 25, 36, 49, 64, 81)
285
0
1
4
[9, 16, 25, 36, 49, 64, 81]
26
39
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for c, z in zip(['r', 'g', 'b', 'y'], [30, 20, 10, 0]):
    xs = np.arange(20)
    ys = np.random.rand(20)

    # You can provide either a single color or an array. To demonstrate this,
    # the first bar of each set will be colored cyan.
    cs = [c] * len(xs)
    cs[0] = 'c'
    ax.bar(xs, ys, zs=z, zdir='y', color=cs, alpha=0.8)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

? 30 + 40
70
? 55 - 5
50
? quit
? 30  + 40
70
? quit
>>> 
>>> 
>>> 
>>> sorted(iter(partial(raw_input, '? '), 'quit'))
? 55
? 18
? 45
? 25 ** 2
? 55 - 5
? quit
['18', '25 ** 2', '45', '55', '55 - 5']
>>> sorted(map(eval, iter(partial(raw_input, '? '), 'quit')))
? 55
? 18
? 45
? 25 ** 2
? 55 - 5
? quit
[18, 45, 50, 55, 625]
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', 'midpoint': 32, 'low': 30}
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', 'midpoint': 32.5, 'low': 30}
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> p.low = 32
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', 'midpoint': 32.5, 'low': 32}
>>> (32 + 35) / 2.0
33.5
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', 'low': 30}
>>> p.low = 32
>>> p.midpoint()

Traceback (most recent call last):
  File "<pyshell#265>", line 1, in <module>
    p.midpoint()
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 19, in midpoint
    return (low + high) / 2
NameError: global name 'low' is not defined
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> p.low = 32
>>> p.midpoint()
33.5
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> 
>>> 
>>> p.low
30
>>> p.symbol
'CSCO'
>>> p.high
35
>>> p.midpoint()
32.5
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> p.low
30
>>> p.high
35
>>> p.symbol
'CSCO'
>>> p.midpoint
32.5
>>> 
>>> p.low = 32
>>> p.midpoint
33.5
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', 'low': 32}
>>> 
>>> 
>>> p.low = 'hello'
>>> 


>>> 


















>>> 



>>> 












>>> 
>>> p.symbol
'CSCO'
>>> p.xyz

Traceback (most recent call last):
  File "<pyshell#291>", line 1, in <module>
    p.xyz
AttributeError: 'PriceRange' object has no attribute 'xyz'
>>> 
>>> 
>>> p.midpoint

Traceback (most recent call last):
  File "<pyshell#294>", line 1, in <module>
    p.midpoint
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 23, in midpoint
    def midpoint(self):
TypeError: cannot concatenate 'str' and 'int' objects
>>> 
>>> 
>>> 
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> p.low
30
>>> p.high
35
>>> p.symbol
'CSCO'
>>> p.midpoint
32.5
>>> p.low = 32
>>> p.midpoint
33.5
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', '_low': 32}
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> p.low
30
>>> p.high
35
>>> p.symbol
'CSCO'
>>> p.midpoint
32.5
>>> p.low = 32
>>> p.midpoint
33.5
>>> vars(p)
{'high': 35, 'symbol': 'CSCO', '_low': 32}
>>> 
>>> 
>>> p.low = 'hello'

Traceback (most recent call last):
  File "<pyshell#314>", line 1, in <module>
    p.low = 'hello'
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 35, in set_low
    raise TypeError('Expected int or float')
TypeError: Expected int or float
>>> p.low = -5

Traceback (most recent call last):
  File "<pyshell#315>", line 1, in <module>
    p.low = -5
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 37, in set_low
    raise ValueError('Expected 0 to 100')
ValueError: Expected 0 to 100
>>> p.low = 5000

Traceback (most recent call last):
  File "<pyshell#316>", line 1, in <module>
    p.low = 5000
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 37, in set_low
    raise ValueError('Expected 0 to 100')
ValueError: Expected 0 to 100
>>> 
>>> 
>>> p.high = 'goodbye'
>>> 
>>> 
>>> 


>>> 







>>> 


>>> 

















>>> 



>>> 



>>> p.midpoint

Traceback (most recent call last):
  File "<pyshell#328>", line 1, in <module>
    p.midpoint
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 24, in midpoint
TypeError: unsupported operand type(s) for +: 'int' and 'str'
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> p.high = 'goodbye'

Traceback (most recent call last):
  File "<pyshell#329>", line 1, in <module>
    p.high = 'goodbye'
  File "/Users/raymond/Dropbox/Public/sj149/property_demo.py", line 54, in set_high
    raise TypeError('Expected int or float')
TypeError: Expected int or float
>>> 
>>> 
>>> # DRY
>>> #  \--> Factoring
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> 
======= RESTART: /Users/raymond/Dropbox/Public/sj149/property_demo.py =======
>>> vars(p)
{'symbol': 'CSCO', '_high': 35, '_low': 30}
>>> 
>>> import this
The Zen of Python, by Tim Peters

Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!
>>> help(property)
Help on class property in module __builtin__:

class property(object)
 |  property(fget=None, fset=None, fdel=None, doc=None) -> property attribute
 |  
 |  fget is a function to be used for getting an attribute value, and likewise
 |  fset is a function for setting, and fdel a function for del'ing, an
 |  attribute.  Typical use is to define a managed attribute x:
 |  
 |  class C(object):
 |      def getx(self): return self._x
 |      def setx(self, value): self._x = value
 |      def delx(self): del self._x
 |      x = property(getx, setx, delx, "I'm the 'x' property.")
 |  
 |  Decorators make defining new properties or modifying existing ones easy:
 |  
 |  class C(object):
 |      @property
 |      def x(self):
 |          "I am the 'x' property."
 |          return self._x
 |      @x.setter
 |      def x(self, value):
 |          self._x = value
 |      @x.deleter
 |      def x(self):
 |          del self._x
 |  
 |  Methods defined here:
 |  
 |  __delete__(...)
 |      descr.__delete__(obj)
 |  
 |  __get__(...)
 |      descr.__get__(obj[, type]) -> value
 |  
 |  __getattribute__(...)
 |      x.__getattribute__('name') <==> x.name
 |  
 |  __init__(...)
 |      x.__init__(...) initializes x; see help(type(x)) for signature
 |  
 |  __set__(...)
 |      descr.__set__(obj, value)
 |  
 |  deleter(...)
 |      Descriptor to change the deleter on a property.
 |  
 |  getter(...)
 |      Descriptor to change the getter on a property.
 |  
 |  setter(...)
 |      Descriptor to change the setter on a property.
 |  
 |  ----------------------------------------------------------------------
 |  Data descriptors defined here:
 |  
 |  fdel
 |  
 |  fget
 |  
 |  fset
 |  
 |  ----------------------------------------------------------------------
 |  Data and other attributes defined here:
 |  
 |  __new__ = <built-in method __new__ of type object>
 |      T.__new__(S, ...) -> a new object with type S, a subtype of T

>>> 
>>> 
>>> def f():
	yield 'it'
	yield 'is'
	yield 'time'
	yield 'for'
	yield 'lunch'

	
>>> for word in f():
	print word

	
it
is
time
for
lunch
>>> it = f()
>>> next(it)
'it'
>>> next(it)
'is'
>>> next(it)
'time'
>>> next(it)
'for'
>>> next(it)
'lunch'
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#356>", line 1, in <module>
    next(it)
StopIteration
>>> print list(f())
['it', 'is', 'time', 'for', 'lunch']
>>> it = f()
>>> list(it)
['it', 'is', 'time', 'for', 'lunch']
>>> list(it)
[]
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#361>", line 1, in <module>
    next(it)
StopIteration
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> 
>>> # @ notation
>>> 
>>> # @tool
>>> # def f(): pass
>>> 
>>> # def f(): pass
>>> # f = tool(f)
>>> 
>>> 
>>> 
>>> def square(x):
	'Return a value times itself'
	return x ** 2

>>> square.__class__
<type 'function'>
>>> square.__doc__
'Return a value times itself'
>>> square.__name__
'square'
>>> square.__code__.co_code
'|\x00\x00d\x01\x00\x13S'
>>> square.__call__
<method-wrapper '__call__' of function object at 0x1038d8578>
>>> square.__call__(7)
49
>>> 
>>> def double_doc(func):
	'Double the docstring'
	func.__doc__ *= 2
	return func

>>> square = double_doc(square)
>>> help(square)
Help on function square in module __main__:

square(x)
    Return a value times itselfReturn a value times itself

>>> 
>>> @double_doc
def cube(x):
	'Return a value times itself thrice'
	return x ** 3

>>> cube(11)
1331
>>> help(cube)
Help on function cube in module __main__:

cube(x)
    Return a value times itself thriceReturn a value times itself thrice

>>> double_doc(square)
<function square at 0x1038d8578>
>>> 
>>> 
>>> def cube(x):
	'Return a value times itself thrice'
	return x ** 3

>>> type(cube)
<type 'function'>
>>> cube = property(cube)
>>> type(cube)
<type 'property'>
>>> 
>>> 
>>> @property
def cube(x):
	'Return a value times itself thrice'
	return x ** 3

>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
square 25
cube 125
collatz 16
cube 125
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
square 25
cube 125
collatz 16
cube 125
>>> square.cool
True
>>> cube.cool

Traceback (most recent call last):
  File "<pyshell#422>", line 1, in <module>
    cube.cool
AttributeError: 'function' object has no attribute 'cool'
>>> 
>>> 
>>> getattr(square, 'cool', False)
True
>>> getattr(cube, 'cool', False)
False
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
square 25
collatz 16
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
Running the cool functions with 5
square 25
collatz 16
Running the cool functions with 10
square 100
collatz 5
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
Running the cool functions with 5
square 25
collatz 16
Running the happy functions with 100
square 10000
cube 1000000
cube 1000000
Running the cool functions with 10
square 100
collatz 5
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
Running the cool functions with 5
square 25
collatz 16
Running the happy functions with 100
square 10000
cube 1000000
cube 1000000
Running the cool functions with 10
square 100
collatz 5
>>> 
======== RESTART: /Users/raymond/Dropbox/Public/sj149/at_notation.py ========
Running the cool functions with 5
square 25
collatz 16
Running the happy functions with 100
square 10000
cube 1000000
cube 1000000
Running the cool functions with 10
square 100
collatz 5
>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/tmp2.py ============
Running the cool functions with 5

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/tmp2.py", line 41, in <module>
    run_cool(MathTools, 5)
  File "/Users/raymond/Dropbox/Public/sj149/tmp2.py", line 4, in run_cool
    for func in funcs:
NameError: global name 'funcs' is not defined
>>> MathTools.__name__
'MathTools'
>>> MathTools.__bases__
(<type 'object'>,)
>>> MathTools.__dict__
dict_proxy({'__module__': '__main__', 'cube': <function cube at 0x104169aa0>, 'collatz': <function collatz at 0x104169b18>, 'square': <function square at 0x104169a28>, '__dict__': <attribute '__dict__' of 'MathTools' objects>, '__weakref__': <attribute '__weakref__' of 'MathTools' objects>, '__doc__': None})
>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/tmp2.py ============

Running the cool functions in MathTools with 5
collatz

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/tmp2.py", line 41, in <module>
    run_cool(MathTools, 5)
  File "/Users/raymond/Dropbox/Public/sj149/tmp2.py", line 6, in run_cool
    print func.__name__, func(x)
TypeError: collatz() takes exactly 2 arguments (1 given)
>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/tmp2.py ============

Running the cool functions in MathTools with 5
collatz 16
square 25

Running the happy functions in MathTools with 100

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/tmp2.py", line 52, in <module>
    run_happy(m, 100)
  File "/Users/raymond/Dropbox/Public/sj149/tmp2.py", line 12, in run_happy
    for func in funcs:
NameError: global name 'funcs' is not defined
>>> 
============ RESTART: /Users/raymond/Dropbox/Public/sj149/tmp2.py ============

Running the cool functions in MathTools with 5
collatz 16
square 25

Running the happy functions in MathTools with 100
cube 1000000
square 10000

Running the happy functions in PhysicsTools with 50
string_theory Sorry, 50 is untestable

Running the cool functions in MathTools with 10
collatz 5
square 100
>>> 
>>> 
>>> 
>>> 
>>> # Generators are a kind of iterator that runs code
>>> #    iterator protocol -> __iter__ next()
>>> #    runs code until there is yield which returns a value
>>> #    when next() is sent, it resumes from it left off
>>> #    when it is done, it raises StopIteration
>>> 
>>> # Strategy for making generators:
>>> #    write a function using "print"
>>> #    once it prints what you want, convert to "yield"
>>> 
>>> 
>>> range(10)
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> xrange(10)
xrange(10)
>>> it = iter(range(10))
>>> it
<listiterator object at 0x103a4ded0>
>>> it = iter(xrange(10))
>>> it
<rangeiterator object at 0x1006fdbd0>
>>> next(it)
0
>>> next(it)
1
>>> sum(range(1000000))
499999500000
>>> sum(xrange(1000000))
499999500000
>>> 
>>> it = enumerate('abc')
>>> it
<enumerate object at 0x1038262d0>
>>> next(it)
(0, 'a')
>>> next(it)
(1, 'b')
>>> next(it)
(2, 'c')
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#461>", line 1, in <module>
    next(it)
StopIteration
>>> 
>>> 
>>> it = reversed('abc')
>>> dir(it)
['__class__', '__delattr__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__iter__', '__length_hint__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'next']
>>> next(it)
'c'
>>> next(it)
'b'
>>> next(it)
'a'
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#469>", line 1, in <module>
    next(it)
StopIteration
>>> 
>>> 
>>> 
>>> zip('abc', 'def')
[('a', 'd'), ('b', 'e'), ('c', 'f')]
>>> from itertools import izip
>>> it = izip('abc', 'def')
>>> it
<itertools.izip object at 0x1039b2ef0>
>>> dir(it)
['__class__', '__delattr__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__iter__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'next']
>>> next(it)
('a', 'd')
>>> next(it)
('b', 'e')
>>> next(it)
('c', 'f')
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#481>", line 1, in <module>
    next(it)
StopIteration
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
0
1
2
3
4
5
6
7
8
9
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
>>> myxrange(10)
<generator object myxrange at 0x104026140>
>>> g = myxrange(10)
>>> next(g)
0
>>> next(g)
1
>>> next(g)
2
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000
Task 2: Reinvent enumerate()
(1, 'raymond')
(2, 'rachel')
(3, 'matthew')
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000
Task 2: Reinvent enumerate()
>>> it = myenumerate(['raymond', 'rachel', 'matthew'], start=1)

>>> it
<generator object myenumerate at 0x103537460>
>>> next(it)
(1, 'raymond')
>>> next(it)
(2, 'rachel')
>>> next(it)
(3, 'matthew')
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#492>", line 1, in <module>
    next(it)
StopIteration
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000
Task 2: Reinvent enumerate()
{1: 'raymond', 2: 'rachel', 3: 'matthew'}
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000
Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}
>>> 
>>> 
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000

Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}

Task 3: Reinvent reversed()
f
e
d
c
b
a
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000

Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}

Task 3: Reinvent reversed()
fedcba
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000

Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}

Task 3: Reinvent reversed()
fedcba

Task 4:  Reinvent izip()
('a', 'x')
('b', 'y')
('c', 'z')
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000

Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}

Task 3: Reinvent reversed()
fedcba

Task 4:  Reinvent izip()
>>> it = myizip('abcde', 'xyz')
>>> next(it)
('a', 'x')
>>> next(it)
('b', 'y')
>>> next(it)
('c', 'z')
>>> next(it)

Traceback (most recent call last):
  File "<pyshell#499>", line 1, in <module>
    next(it)
StopIteration
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000

Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}

Task 3: Reinvent reversed()
fedcba

Task 4:  Reinvent izip()
[('a', 'x'), ('b', 'y'), ('c', 'z')]
{'a': 'x', 'c': 'z', 'b': 'y'}
>>> 
===== RESTART: /Users/raymond/Dropbox/Public/sj149/generator_practice.py =====
Task 1: Reinvent xrange()
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
499999500000

Task 2: Reinvent enumerate()
{1001: 'raymond', 1002: 'rachel', 1003: 'matthew'}

Task 3: Reinvent reversed()
fedcba

Task 4:  Reinvent izip()
[('a', 'x'), ('b', 'y'), ('c', 'z')]
{'a': 'x', 'c': 'z', 'b': 'y'}
a --> x
b --> y
c --> z
>>> 
>>> 
>>> 
>>> # with-statement
>>> 

>>> 
>>> 
>>> 
>>> 
>>> # pickling   json     compression
>>> 
>>> # live object --(encoding)--> str --(decoder)--> live object
>>> 
>>> hansolo = dict(
	ship = 'milleneum falcon',
	status = 'wanted by jabba the hut',
	friends = ['luke', 'leia', 'chewy'],
	occupation = 'smuggler',
)
>>> 
>>> type(hansolo)
<type 'dict'>
>>> hansolo.keys()
['status', 'ship', 'friends', 'occupation']
>>> len(hansolo)
4
>>> hansolo['ship']
'milleneum falcon'
>>> 
>>> for friend in hansolo['friends']:
	print "Don't worry Han, %s will save you" % friend.title()

	
Don't worry Han, Luke will save you
Don't worry Han, Leia will save you
Don't worry Han, Chewy will save you
>>> 
>>> import pickle
>>> c = pickle.dumps(hansolo)
>>> del hansolo
>>> type(c)
<type 'str'>
>>> len(c)
177
>>> c.keys()

Traceback (most recent call last):
  File "<pyshell#534>", line 1, in <module>
    c.keys()
AttributeError: 'str' object has no attribute 'keys'
>>> hansolo['ship']

Traceback (most recent call last):
  File "<pyshell#535>", line 1, in <module>
    hansolo['ship']
NameError: name 'hansolo' is not defined
>>> 
>>> 
>>> 
>>> hansolo = pickle.loads(c)
>>> type(hansolo)
<type 'dict'>
>>> for friend in hansolo['friends']:
	print "Don't worry Han, %s will save you" % friend.title()

	
Don't worry Han, Luke will save you
Don't worry Han, Leia will save you
Don't worry Han, Chewy will save you
>>> 
>>> 
>>> c = json.dumps(hansolo)

Traceback (most recent call last):
  File "<pyshell#545>", line 1, in <module>
    c = json.dumps(hansolo)
NameError: name 'json' is not defined
>>> import json
>>> c = json.dumps(hansolo)
>>> type(c)
<type 'str'>
>>> del hansolo
>>> hansolo = json.loads(c)
>>> hansolo
{u'status': u'wanted by jabba the hut', u'ship': u'milleneum falcon', u'friends': [u'luke', u'leia', u'chewy'], u'occupation': u'smuggler'}
>>> 
>>> 
>>> # live object --(encoding)--> str --(decoder)--> live object
>>> #             json/xml/yaml/pickle
>>> 
>>> s = '''
            she sells sea shells by the sea shore
            peter piper picked a peck of pickled peppers
            double rubber baby buggy bumpers
            which witch has which witches wristwatch
'''
>>> 
>>> len(s)
206
>>> import zlib
>>> c = zlib.compress(s)
>>> len(c)
113
>>> zlib.decompress(c) == s
True
>>> import bz2
>>> c = bz2.compress(s)
>>> bz2.decompress(c) == s
True
>>> len(c)
140
>>> # zlib is faster and compresses better than bz2 for short strings
>>> 
>>> with open('notes2/hamlet.txt') as f:
	play = f.read()

	
>>> len(play)
202238
>>> len(zlib.compress(c))
151
>>> len(zlib.compress(play))
73748
>>> _ / 202238.
0.3646594606354889
>>> len(bz2.compress(play))
56442
>>> _ / 202238.
0.2790870162877402
>>> # bz2 is more impressive for large strings
>>> 
>>> 
>>> 
>>> # pickle/json         loads/dumps   load/dump
>>> # zlib/bz2            compress      decompress
>>> 
>>> # abracadabra
>>> # 65 66                         128 - ab
>>> # 72                            129 - abr
>>> #
>>> # aaaabbcrrdd 121
>>> # 4a2b1c2r2d
>>> # arithmetic encoder
>>> 
>>> 
>>> # Compressor heads video series on Google
>>> 
>>> 
>>> # 1.5year ss    .5 wk1
>>> # 1.5year ex    .5 xls
>>> # 1 day          1 minutes                 pickle.dump(wb, f)
>>> 
>>> 
>>> 
>>> #   A   ->    B   ->      C                    t
>>> #   A         ->          C                    u
>>> 
>>> # gatherinfo   sorted   do million lookups
>>> # gatherinfo            do million lookups
>>> 
>>> # compute result     compress it        write to disk
>>> #   cpu                 cpu                  i/o
>>> #             3Gb                  1Gb
>>> 
>>> # compute result                t        write to disk
>>> #             3Gb                  3Gb
>>> # compute result                t     ram  (swap)  write
>>> 
>>> 
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
>>> f
<closed file 'notes2/hamlet.txt', mode 'r' at 0x1038b4c00>
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/with_demo.py", line 8, in <module>
    print 32 / 0
ZeroDivisionError: integer division or modulo by zero
>>> f
<open file 'notes2/hamlet.txt', mode 'r' at 0x10418ac00>
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238

Traceback (most recent call last):
  File "/Users/raymond/Dropbox/Public/sj149/with_demo.py", line 9, in <module>
    print 32 / 0
ZeroDivisionError: integer division or modulo by zero
>>> f
<closed file 'notes2/hamlet.txt', mode 'r' at 0x1038b4c00>
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
Starting up
Worker 0 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 1 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 2 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 3 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 4 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 5 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 6 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 7 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 8 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 9 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Done
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
Starting up
Worker 0 is reporting for workWorker 1 is reporting for workWorker 2 is reporting for workWorker 3 is reporting for workWorker 4 is reporting for workWorker 5 is reporting for workWorker 6 is reporting for workWorker 7 is reporting for workWorker 8 is reporting for workWorker 9 is reporting for workThe count is









 This works great!This works great!This works great!This works great!This works great!This works great!This works great!This works great!This works great!This works great!10










I really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingDone










It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!
>>> 










========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
Starting up
Worker 0 is reporting for workWorker 1 is reporting for workWorker 2 is reporting for workWorker 3 is reporting for workWorker 4 is reporting for workWorker 5 is reporting for workWorker 6 is reporting for workWorker 7 is reporting for workWorker 8 is reporting for workWorker 9 is reporting for workThe count is









 This works great!This works great!This works great!This works great!This works great!This works great!This works great!This works great!This works great!This works great!10










I really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingI really trust multi-threadingDone










It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!It is soooooo easy!
>>> 










========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
Starting up
Worker 0 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 1 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 2 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 3 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 4 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 5 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 6 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 7 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 8 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 9 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
The count is 10
Done
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
Starting up
Worker 0 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 1 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 2 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 3 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 4 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 5 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 6 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 7 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 8 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 9 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
The count is 10
Done
Starting up
Worker 0 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 1 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 2 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 3 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 4 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 5 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 6 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 7 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 8 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 9 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
The count is 10
Done
>>> dir(f)
['__class__', '__delattr__', '__doc__', '__enter__', '__exit__', '__format__', '__getattribute__', '__hash__', '__init__', '__iter__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'close', 'closed', 'encoding', 'errors', 'fileno', 'flush', 'isatty', 'mode', 'name', 'newlines', 'next', 'read', 'readinto', 'readline', 'readlines', 'seek', 'softspace', 'tell', 'truncate', 'write', 'writelines', 'xreadlines']
>>> 
>>> 
>>> dir(printer_lock)
['__class__', '__delattr__', '__doc__', '__enter__', '__exit__', '__format__', '__getattribute__', '__hash__', '__init__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'acquire', 'acquire_lock', 'locked', 'locked_lock', 'release', 'release_lock']
>>> 
========= RESTART: /Users/raymond/Dropbox/Public/sj149/with_demo.py =========
202238
202238
Starting up
Worker 0 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 1 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 2 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 3 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 4 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 5 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 6 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 7 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 8 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 9 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
The count is 10
Done
Starting up
Worker 0 is reporting for workThe count is
 This works great!10

I really trust multi-threadingDone

It is soooooo easy!
>>> 
Worker 1 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 2 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 3 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 4 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 5 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 6 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 7 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 8 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
Worker 9 is reporting for work
This works great!
I really trust multi-threading
It is soooooo easy!
It is soooooo easy!
SyntaxError: invalid syntax
>>> 
>>> 
>>> 
>>> # Files are context managers (they are withable)
>>> # Locks are context managers (they are withable)
>>> 
>>> 
