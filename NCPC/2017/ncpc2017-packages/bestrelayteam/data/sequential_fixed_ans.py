import random
import string

print(500)

print("BEST 8.01 8.00")
print("SECONDBEST 14.00 14.00")

def rname():
    return ''.join(random.choice(string.ascii_uppercase) for _ in range(20))

for i in range(498):
    print(rname(), "{:.2f} {:.2f}".format(19.99 - 0.005 * i - 0.005, 14.99 + 0.005 * i))
