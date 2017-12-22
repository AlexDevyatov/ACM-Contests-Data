#!/usr/bin/env python3

#
# Author
#   Robin Lee (hex539)
#
import sys

h = map(int, (sys.stdin.readlines()[1] + " 0").split())
print(min(map(sum,enumerate(h))))

