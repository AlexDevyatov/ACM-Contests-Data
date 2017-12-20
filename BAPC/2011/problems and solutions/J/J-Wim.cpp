#include <iostream>                  
using namespace std;

int primes[4000];
int prf[33], expt[33];
void buildprimes( int& k);           // with primes as global
void Visit(int& max, int d, int k, int N); // all factors of N  
void fact( int N, int& k);          // k= # primefactors of N

int main()
{ 
  int nruns;

  int N, k, nrpr, max, p, q, x, y; 
  bool twoes;
  buildprimes( nrpr );

  cin >> nruns;
  for( int nr=0; nr<nruns; nr++)
  {
    cin >> N;

    if (N%4==2) cout << "IMPOSSIBLE" << "\n" ;
    else 
    { if (N%4==0){ twoes=true; N=N/4;} else twoes = false;
      fact( N, k);     // N = prf_1^expt_1...prf_k^expt_k
      // for (int j=1;j<=k;j++)
      // cout << prf[j] << "^" << expt[j] << endl;
      max = 0;
      Visit( max, 1, k, N);
      p = N/max; q = max; if (twoes){ p=2*p; q=2*q;} // p >= q
      x = (p+q)/2; y = (p-q)/2;
      cout << y << " " << x << "\n";
    }
  }

  return 0;
}

void Visit(int& max, int d, int k, int N)
{ int min, q;
  if (k==0){ q = N/d; if (d<q) min=d; else min=q;
                    if (min > max) max = min;    }
  else { for( int j=0; j < expt[k]; j++)
         {  Visit( max, d, k-1, N); d= d*prf[k]; }
         Visit( max, d, k-1, N);
}      }  

void fact( int N, int& k)
{ int cnt=0,i=0;k=0; //i index in primes table, k index in prf
  while ((N>1 )&&( primes[i]*primes[i] <=N ))
   { if (N%primes[i]==0)
     {cnt = 0; 
      while ( N%primes[i] == 0){ N = N/primes[i] ; cnt++;}
      k=k+1; expt[k]=cnt; prf[k]=primes[i];
     } 
     i=i+1;
   }
  if (N!=1){ k=k+1; expt[k]=1; prf[k] = N;} 
}   

void buildprimes( int& k) // k length of primes table
{ int x=3, j; primes[0]=2; primes[1]=3; k=2;
  while (x < 32000) // sqrt MaxInt = 32768
  { x=x+2; j=1; // starting with 3
    while (( primes[j]*primes[j] <= x) && (x%primes[j]!=0)) j=j+1;
    if (x % primes[j] !=0) primes[k++] = x; 
  }
}