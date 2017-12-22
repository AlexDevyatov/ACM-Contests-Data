#include <algorithm>
#include <iostream>
#include <complex>
#include <vector>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Knapsack by integer convolution
 *
 * Complexity
 *   O((N^2)logN)
 */

typedef long double flack;
typedef complex<flack> flex;
typedef vector<bool> vb;

#define MAXN 1024
void fft(flex *v,int const n,int const s=1){
  static flex tmp[MAXN];
  if (n<=1) return;
  fft(v+0,n/2,s<<1);
  fft(v+s,n/2,s<<1);
  for (int i=0,j=0,k=n>>1,l=0; i<n; i+=2,j++,k++)
    tmp[j]=v[(i+0)*s],
    tmp[k]=v[(i+1)*s];
  for (int i=n>>1,j=n; --j,i--;)
    v[i*s]=tmp[i]+exp(flex(0,-i*2*M_PI/n))*tmp[j],
    v[j*s]=tmp[i]-exp(flex(0,-i*2*M_PI/n))*tmp[j];
}

void convolve(vb &a, vb &b){
  static flex u[MAXN], v[MAXN];
  copy(a.begin(),a.end(),u);
  copy(b.begin(),b.end(),v);
  fft(u,MAXN);
  fft(v,MAXN);
  for (int i=MAXN; i--;) u[i]=conj(u[i]*v[i]);
  fft(u,MAXN);
  for (int i=MAXN; i--;) a[i]=u[i].real()/MAXN >= 0.5L;
}

int x[MAXN],depth[MAXN],sink[MAXN],min_size[MAXN],max_size[MAXN];

void dfs(int a){
    int b=x[sink[a]=a];
    static bool active[MAXN];
    if (active[a]=true, active[b]) min_size[a]=1+(depth[a]-depth[b]);
    else {if (!depth[b]) depth[b]=depth[a]+1, dfs(b); sink[a]=sink[b];}
    active[a]=!++max_size[sink[a]];
}

int main(){
    // read in participants, make connectivity clusters using depth-first search
    int n,m; cin>>n>>m;
    for (int i=0; i<n; i++) cin>>x[i], --x[i];
    for (int i=n; i--;) if (not depth[i]) depth[i]=1, dfs(i);

    // find legal subset sizes with repeated convolution of possible sizes
    vb can(MAXN); can[0]=true; vb aux=can;
    for (int i=0; i<n; i++){
        if (sink[i]==i and max_size[i]){
            for (int j=1; j<=n; j++) aux[j]=(min_size[i]<=j and j<=max_size[i]);
            convolve(can,aux);
        }
    }

    int res=m;
    while (not can[res]) --res;
    cout<<res<<endl;
}
