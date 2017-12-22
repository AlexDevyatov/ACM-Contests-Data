#!/usr/bin/env pypy
# generates fully connected NEURAL NETWORK! WUBBALUBBA DUB DUB!
from random import randint as rnd
import sys


# okay, use this as:
#
# generator.py 16 15
#
# to get a 16 layered deep network (DAG)
#
#
# generator.py 16 15 5
#
# to get a cycle of length 5

INF = 500

height = int(sys.argv[1]) - 2
width = int(sys.argv[2])

shortcut = None
if len(sys.argv) > 3:
    shortcut = int(sys.argv[3])
    if shortcut > height:
        exit('shortcut = %d > %d = height' % (shortcut, height))

top = 'imthetop'
bot = 'imthebot'

layers = []
layers.append([top])
vertex_names = [top] # this exists because I don't gidd to ''.join(''.join())
def rnd_name():
    return ''.join([chr(rnd(97,97+25)) for i in range(8)])

for i in range(height):
    this_layer = []
    for j in range(width):
        name = rnd_name()
        this_layer.append(name)
        vertex_names.append(name)
    layers.append(this_layer)

layers.append([bot])
vertex_names.append(bot)
n = height * width + 2 # add top + bot

if n > INF:
    exit('n = %d > %d' % (n, INF))

print(n)
print(' '.join(vertex_names))
for i in range(height+1): # height is really height+2
    for j in range(len(layers[i])):
        name = layers[i][j]
        print('%s %d' % (name, 1)) # all imports on 1 line
        imps = ', '.join(layers[i+1])
        print('import %s' % imps)

if shortcut is None:
    print('%s 0' % bot)
else:
    # add an arc from bot to some guy in level n-shortcut
    print('%s 1' % bot)
    backarc = (height - shortcut) + 2
    print('import %s' % layers[backarc][0])
