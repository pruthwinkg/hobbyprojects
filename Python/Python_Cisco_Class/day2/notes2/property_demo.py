''' Goal:  Become a black belt with property().

Fundamental action:     Converts attribute access like a.x into method access like a.m()
How does it work?       It reprograms the dot (actually, the __getattribute__ method)
Main cause of failure?  Forgot to inherit from object

Computed fields using properties:
* Save storage space
* Reduce risk of data inconsistency
* Provide a consistent API

Managed attributes:
* Control all read and write access to an attribute
* A primary use case is data validation
* This is a miraculous and powerful technique
  for hunting down hard-to-find data corruption bugs

'''

from __future__ import division
from validators import validate_percentage

class PriceRange(object):

    def __init__(self, symbol, low, high):
        self.symbol = symbol
        self.low = low
        self.high = high

    @property                      # midpoint = property(midpoint)
    def midpoint(self):
        return (self.low + self.high) / 2

    # Managed attributes #####################

    @property
    def low(self):
        return self._low

    @low.setter
    def low(self, low):
        validate_percentage(low)
        self._low = low

    @property
    def high(self):
        return self._high

    @high.setter
    def high(self, high):
        validate_percentage(high)
        self._high = high
    
p = PriceRange('CSCO', 30, 35)





