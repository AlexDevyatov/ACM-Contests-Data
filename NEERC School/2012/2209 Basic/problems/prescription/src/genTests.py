from os import *
from io import *
import random



random.seed(313110);
test =[];
test += ['house_g_0101_first_january_angioplasty']
test += ['khoukse_k_1012_tenth_december_endoscopy']
test += ['abab'];
test += ['aba'];
test += ['abcdefghi'];
test += ['ihgfedcba'];
test += ['jksfdgklafdjkgsdfkl'];
test += ['aaaaaaaaaaaaaaaaaaa'];
test += ['wwwwwwwwwwwwwwwwwwwaw'];
test += ['zzzzzz']
test += ['zza']
test += ['aaz']
test += ['112']
test += ['110']
test += ['_____________']
test += ['o_o']
test += ['_a']
test += ['a_']
test += ['est1947']
test += ['0_0']
test += ['_0']


def printtest(testNo, x):
	if not (path.exists("../tests")):
		mkdir("../tests")
	tst = open("../tests/%d%d" % divmod(testNo, 10), "w")
	tst.write(test[x] + "\n");
	tst.close()

def printrandtest(testNo):
	if not (path.exists("../tests")):
		mkdir("../tests")
	tst = open("../tests/%d%d" % divmod(testNo, 10), "w")
	for j in range(1000000):
		tst.write(random.choice('qwertyuiopasdfghjklzxcvbnm0123456789_'));
	tst.write("\n");
	tst.close()



testNo = 0;

for i in range(21):
	testNo = testNo + 1
	printtest(testNo, i);

for i in range(5):
	testNo = testNo + 1
	printrandtest(testNo);
	

