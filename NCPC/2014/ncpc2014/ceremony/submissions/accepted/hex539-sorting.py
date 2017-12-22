#!/usr/bin/env python3

#
# Author
#   Robin Lee (hex539)
#
# Algorithm
#   sort the heights so that they are in descending order.
#   say the first x are cut vertically and the rest are
#   cut horizontally - the cost will be x + h[x].
#
#   we try every possible cut-point, not forgetting x=n which
#   can be handled by appending a fake 0-height building to the
#   array.
#
import sys

h = map(int, (sys.stdin.readlines()[1] + " 0").split())

print(min(                        # take the minimum of
          map(sum,                # an (idx+hgt) array
              enumerate(          # made from (idx, hgt) pairs
               reversed(          # in height-descending
                 sorted(h))))))   # sorted order

