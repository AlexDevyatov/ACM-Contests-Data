
import sys, math

def run():
    N=long(sys.stdin.readline().strip())
    print(getDivisorCnt(N))

def isQuadrat(N):
    d=math.sqrt(N)
    	
    start = long(math.ceil(d-10))
    end = long(math.ceil(d+10))
    for i in range(start, end):
        if i*i==N:
            return True
    return False

def getDivisorCnt(N):
    res=1;
    for i in range(2, 1000000+1):
        cnt=1
        while N%i==0:
            N/=i
            cnt+=1
        res*=cnt
		
    if(N==1):
        return res;
		
    #//there is still something there, but we know: this one is prime or has two factors
    if(probablyPrime(N)):
        return res*2L
    else: #//is not prime, but we know there are at most two factors
        if(isQuadrat(N)): #//the factors are the same:
            return res*3L
        else:#//factors are different
            return res*4L
	
import random

def decompose(n):
   exponentOfTwo = 0

   while n % 2 == 0:
      n = n/2
      exponentOfTwo += 1

   return exponentOfTwo, n

def isWitness(possibleWitness, p, exponent, remainder):
   possibleWitness = pow(possibleWitness, remainder, p)

   if possibleWitness == 1 or possibleWitness == p - 1:
      return False

   for _ in range(exponent):
      possibleWitness = pow(possibleWitness, 2, p)

      if possibleWitness == p - 1:
         return False

   return True

def probablyPrime(p, accuracy=100):
   if p == 2 or p == 3: return True
   if p < 2: return False

   numTries = 0
   exponent, remainder = decompose(p - 1)

   for _ in range(accuracy):
      possibleWitness = random.randint(2, p - 2)
      if isWitness(possibleWitness, p, exponent, remainder):
         return False

   return True

run()
