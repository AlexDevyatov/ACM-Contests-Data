#include <iostream>
 using namespace std;    
// solve (ax+b)x+c=y mod 2^n(if possible)

int pwr[32];
int sol(int,int,int,int); 
bool odd( int a){return (a%2!=0);}
bool even(int a){return (a%2==0);}

int main()                                              
{ const int M30=1073741824;
  pwr[0]=1; for(int k=1;k<32;k++) pwr[k]=2*pwr[k-1];
  
  int nruns; // total and actual nr of runs            
  int a,b,c,x,y,z,n, nsols; // 0 or 1 or >=2 solutions

  cin >> nruns;
  for( int nr=1; nr <= nruns; nr++)
  { 
    cin  >> y >> a >> b >> c >> n; nsols = 1;
    // reduce to (ax+b)x+c=0             
    c = c - y; if (c<0)c=(c+M30)+M30; 
    if (n==1) { if (even(a+b)) {if (even(c)) nsols=2; else nsols =0;}
               else {nsols=1; x=c%2;}}
    else 
    {
      if (even(a)&& even(b)&& even(c))
      {  // strike common factors
         if ((a==0)&&(b==0)&&(c==0)) nsols = 2; else 
         while ((a%2 ==0)&&(b%2 ==0)&&(c%2 ==0)) 
         { nsols=2; a=a/2; b=b/2; c=c/2;     }
      }
      if (even(a)&& even(b)){ nsols = 0;}              
      if (odd(a)&& even(b)) // eqn eqv with (ax+b/2)^2=ac+bb/4
      { z = (b*b/4-a*c)%pwr[n];       
        if (z==0)   nsols = 2; // 0 and 2^(n-1)
        else   
        {  while ((z%4)==0) z=z/4; // z^2=1 has 4 solutions      
           if    ((z%8+7)==0) nsols=2; //odd square = 8v+1
           else   nsols= 0; 
        }
      } 
      if (odd(a)&& odd(b))
         if (even(c)) nsols =2; else nsols=0;
      
      if (even(a)&& odd(b)&&(nsols==1)) x = sol(n,a,b,c);
    }
    if      (nsols == 1) cout << x << endl;
    else if (nsols == 2) cout << "No unique solution" << endl;
    else                 cout << "No unique solution" << endl;   
  }
  
  return 0;
}


int sol(int n, int a, int b, int c)                    
{ int x = 0;
  for ( int k = 1; k <= n; k++)
  { 
    if ( (((a*x+b)*x+c)% pwr[k])!= 0) x = x+pwr[k-1];
  }                                                    
  return x;
} 
