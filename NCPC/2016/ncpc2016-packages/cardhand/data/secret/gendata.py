
import numpy as np
suit = "hcsd"
rank = "23456789TJQKA"
np.random.seed(42)

for j in range(1,15):
	n = min(5*j, 52)
	f = open("{:0>2}.random{}.in".format(j+10,n), "w")
	f.write(str(n) + "\n")
	order = np.random.permutation(range(0,52))
	for i in range(0,n):
		f.write(rank[order[i]%13] + suit[order[i]/13] + " \n"[i==n-1])
	f.close()