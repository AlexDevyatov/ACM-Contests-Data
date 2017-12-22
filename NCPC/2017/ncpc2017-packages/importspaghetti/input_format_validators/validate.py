#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
filename = "[a-z]{1,8}"
oneint = re.compile(integer + "\n")
header_line = re.compile(filename + " " + integer + "\n")
import_line = re.compile("import (" + filename + ", )*" + filename + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 500

line = stdin.readline()
assert line[-1] == '\n'
names = line[:-1].split(' ')
assert len(names) == n
assert len(set(names)) == n
for x in names:
    assert re.match(filename, x)

for i in range(n):
    line = stdin.readline()
    assert header_line.match(line)
    (name, k) = line.split()

    assert name == names[i]

    k = int(k)
    assert 0 <= k <= n
    imports = set()
    for _ in range(k):
        line = stdin.readline()
        assert import_line.match(line)
        for imp in line.split()[1:]:
            if imp[-1] == ',':
                imp = imp[:-1]
            assert imp in names, "importing %s which is not a named module" % imp
            assert imp not in imports
            imports.add(imp)

assert len(stdin.readline()) == 0
sys.exit(42)
