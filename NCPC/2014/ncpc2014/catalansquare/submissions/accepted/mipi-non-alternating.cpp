#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;
typedef vector<int> VI;
typedef long long LL;

#define FOR(x,b,e) for(int x=(b);x<=(e);++x)
#define FORD(x,b,e) for(int x=(b);x>=(e);--x)
#define REP(x,n) for(int x=0;x<(n);++x)
#define VAR(v,n) __typeof(n) v=(n)
#define ALL(c) (c).begin(),(c).end()
#define SIZE(x) (int)(x).size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second

/* ====== BIG INT CLASS FROM WARSAW LIBRARY ====== */
class Natural {
	static const int BASE = 100000000;
	static const int BASEDIGS = 8;
	int ndigs;
	int *digs;

	void init(int n,const int *d) {
		while(n>0 && d[n-1]==0) --n;
		ndigs=n;
		digs=new int[n];
		for(int i=0;i<n;++i) digs[i]=d[i];
	}

	Natural(int n,const int *d) { init(n,d); }
	
	/* przesuwanie (dla dzielenia i pierwiastkowania) */
	Natural operator<<(int sh) const { // sh >= 0
		int n=sh+ndigs;
		int d[n];
		REP(i,sh) d[i]=0;
		REP(i,ndigs) d[i+sh]=digs[i];
		return Natural(n,d);
	}

	public:
	
	/* konstruktory */
	Natural(int x=0) {
		int d[2];
		d[0]=x%BASE;
		d[1]=x/BASE;
		init(2,d);
	}
	
	Natural(const Natural& a) {
		init(a.ndigs,a.digs);
	}

	Natural(const char *s) {
		int n=strlen(s);
		int nd=n/BASEDIGS+1;
		int d[nd];
		REP(i,nd) {
			d[i]=0;
			FORD(j,BASEDIGS-1,0) {
				int poz=i*BASEDIGS+j;
				if(poz<n) d[i]=10*d[i]+s[n-1-poz]-'0';
			}
		}
		init(nd,d);
	}

	/* destruktor */
	~Natural() { delete[] digs; }

	/* przypisanie */
	Natural &operator=(const Natural& a) {
		delete[] digs;
		init(a.ndigs,a.digs);
		return *this;
	}

	/* dodawanie */
	Natural operator+(const Natural& a) const {
		int n=max(ndigs,a.ndigs)+1;
		int d[n];
		REP(i,n) d[i]=0;
		REP(i,n) {
			if(i<ndigs) d[i]+=digs[i];
			if(i<a.ndigs) d[i]+=a.digs[i];
			if(d[i]>=BASE) { d[i]-=BASE; ++d[i+1]; }
		}
		return Natural(n,d);
	}

	Natural &operator+=(const Natural& a) {
		return *this = *this + a;
	}

	/* odejmowanie */
	Natural operator-(const Natural& a) const { // a <= *this
		int d[ndigs];
		REP(i,ndigs) d[i]=digs[i];
		REP(i,ndigs) {
			if (i < a.ndigs) d[i]-=a.digs[i];
			if (d[i] < 0) {
				d[i]+=BASE;
				--d[i+1];
			}
		}
		return Natural(ndigs,d);
	}

	Natural &operator-=(const Natural& a) {
		return *this = *this - a;
	}

	/* mnozenie liczb */
	Natural operator*(const Natural& a) const {
		int n=ndigs+a.ndigs;
		int d[n];
		REP(i,n) d[i]=0;
		REP(i,ndigs) {
			int p=0;
			REP(j,a.ndigs) {
				long long v=(long long)(digs[i])*a.digs[j];
				int v1=v/BASE,v0=v%BASE;
				d[i+j]+=v0+p;
				p=v1+d[i+j]/BASE;
				d[i+j]%=BASE;
			}
			for(int j=i+a.ndigs;p>0;++j) {
				d[j]+=p;
				p=d[j]/BASE;
				d[j]%=BASE;
			}
		}
		return Natural(n,d);
	}

	Natural &operator*=(const Natural&a) {
		return *this = *this * a;
	}

	/* dzielenie liczb */
	Natural operator/(const Natural& a) const {
		int n=max(ndigs-a.ndigs+1,0);
		int d[n];
		Natural prod;
		FORD(i,n-1,0) {
			int l=0, r=BASE-1;
			while(l<r) {
				int m=(l+r+1)/2;
				if (*this<prod+(a*m<<i))
					r=m-1;
				else
					l=m;
			}
			prod+=a*l<<i;
			d[i]=l;
		}
		return Natural(n,d);
	}

	Natural &operator/=(const Natural& a) {
		return *this = *this / a;
	}

	/* modulo */
	Natural operator%(const Natural&a) const {
		return *this - *this/a*a;
	}

	Natural &operator%=(const Natural&a) {
		return *this = *this % a;
	}

	/* pierwiastek */
	Natural sqrt() const {
		int n=(ndigs+1)/2;
		int d[n];
		REP(i,n) d[i]=0;
		Natural sq;
		FORD(i,n-1,0) {
			Natural a(n,d);
			int l=0, r=BASE-1;
			while(l<r) {
				int m=(l+r+1)/2;
				if (*this<sq+(a*2*m<<i)+(Natural(m)*m<<2*i))
					r=m-1;
				else
					l=m;
			}
			sq+=(a*2*l<<i)+(Natural(l)*l<<2*i);
			d[i]=l;
		}
		return Natural(n,d);
	}

	/* mnozenie przez inta */
	Natural operator*(int x) const { // !!! 0 <= x <= BASE
		int n=ndigs+1;
		int d[n];
		long long a=0;
		REP(i,ndigs) {
			a+=digs[i]*(long long)x;
			d[i]=a%BASE;
			a/=BASE;
		}
		d[ndigs]=a;
		return Natural(n,d);
	}

	Natural &operator*=(int x) {
		return *this = *this * x;
	}

	/* dzielenie przez inta */
	Natural operator/(int x) const { // !!! 0 < x
		int d[ndigs];
		long long a=0;
		FORD(i,ndigs-1,0) {
			a=BASE*a+digs[i];
			d[i]=a/x;
			a%=x;
		}
		return Natural(ndigs,d);
	}

	Natural &operator/=(int x) {
		return *this = *this / x;
	}

	/* modulo int */
	int operator%(int x) const { // !!! 0 < x
		long long a=0;
		FORD(i,ndigs-1,0) {
			a=BASE*a+digs[i];
			a%=x;
		}
		return a;
	}

	/* porównania (< potrzebne dla dzielenia i pierwiastka) */
	bool operator<(const Natural& a) const {
		if(ndigs<a.ndigs) return true;
		if(ndigs>a.ndigs) return false;
		FORD(i,ndigs-1,0) {
			if(digs[i]<a.digs[i]) return true;
			if(digs[i]>a.digs[i]) return false;
		}
		return false;
	}

	bool operator==(const Natural&a) const {
		if(ndigs!=a.ndigs) return false;
		REP(i,ndigs) {
			if(digs[i]!=a.digs[i]) return false;
		}
		return true;
	}

	bool operator>(const Natural&a) const { return a<*this; }
	bool operator<=(const Natural&a) const { return !(a<*this); }
	bool operator>=(const Natural&a) const { return !(*this<a); }
	bool operator!=(const Natural&a) const { return !(*this==a); }

	/* wypisywanie */
	void write() const {
		if(ndigs==0) printf("0");
		else {
			printf("%d",digs[ndigs-1]);
			FORD(i,ndigs-2,0) printf("%0*d",BASEDIGS,digs[i]);
		}
	}

	void write(char *buf) const {
		if(ndigs==0) sprintf(buf,"0");
		else {
			int pos=0;
			pos+=sprintf(buf,"%d",digs[ndigs-1]);
			FORD(i,ndigs-2,0) pos+=sprintf(buf+pos,"%0*d",BASEDIGS,digs[i]);
		}
	}
};

int main(){
	int n;
	scanf("%d",&n);
	n++;

	Natural r=Natural(1);
	FOR(i,1,2*n) r*=i;
	REP(t,2) FOR(i,1,n) r/=i;
	r/=(n+1);
	r.write(); printf("\n");
	return 0;
}
