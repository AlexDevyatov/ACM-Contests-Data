from random import *
from sys import argv

seed('ololo')

test = 0
def out(t):
	global test
	test += 1
	print('%d'%test)
	out = open('../tests/%02d'%test, 'w')
	out.write(str(len(t)))
	out.write('\n')
	for i in t:
		out.write(i)
		out.write('\n')
	
def without_pop(n, k):
	oper = ['+', '?']
	result = []
	p = 0
	for i in range(n):
		o = oper[randint(0, 1)]
		if (o == '+' or p == 0):
			result.append('+' + str(randint(1, k)))
			p+=1
		else:
			result.append('?' + str(randint(1, p)))
	
	return result
	
def only_stack(n, k):	
	oper = ['+', '-']
	result = []
	p = 0
	for i in range(n):
		o = oper[randint(0, 1)]
		if (o == '+' or p == 0):
			result.append('+' + str(randint(1, k)))
			p+=1
		else:
			result.append('-')
			p-=1
			
	return result

def tests(n, k):
	oper = ['+', '?', '-']
	result = []
	p = 0
	for i in range(n):
		o = oper[randint(0, 2)]
		if (o == '+' or p == 0):
			result.append('+' + str(randint(1, k)))
			p+=1
		elif o == '?':
			result.append('?' + str(randint(1, p)))
		else:
			result.append('-')
			p-=1
	
	return result

def square(n, k):
	result = []
	for i in range(n):
		result.append('+' + str(randint(1, k)))
	for i in range(n):
		result.append('?' + str(randint(n//2, n))) 
	
	return result

#sample test
out(['+1','+2','+3','?2','-','-','?1'])		
 
#min tests
out(tests(5, 10))
out(without_pop(7, 20))
out(only_stack(8, 30))
out(tests(10, 50))
out(without_pop(50, 1000))

#middle_tests
out(only_stack(100, 1000))
out(tests(150, 3000))
out(only_stack(500, 20000))
out(without_pop(2000, 1000000))
out(tests(5000, 1234567))

#max_tests
out(tests(30000, 500000000))
out(tests(50000, 502003000))
out(square(30000, 1000000))
out(without_pop(70000, 900000000))
out(square(50000, 1000000000))
out(without_pop(100000, 1000000000))
out(only_stack(100000, 1000000000))
out(tests(100000, 1000000000))
