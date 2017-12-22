#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Solution by lukasP (Lukáš Poláček)

from sys import stdin
s = stdin.readline().strip()
print(sum([1 if "PER"[i % 3] != s[i] else 0 for i in range(len(s))]))
