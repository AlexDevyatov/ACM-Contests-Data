// Solution for NCPC/UKIEPC 2014 problem "clockpictures"
// Written by Jaap Eldering
// Uses KMP substring search to find difference sequence X of first
// set of hand angles in Y+Y of second difference sequence Y.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxa = 360000;

vector<int> readhands(int n)
{
	vector<int> a(n);

	for(int i=0; i<n; i++) cin >> a[i];

	sort(a.begin(),a.end());

	int tmp = a[n-1];
	for(int i=n-1; i>0; i--) a[i] -= a[i-1];
	a[0] = (a[0] - tmp + maxa)%maxa;

	return a;
}

int kmp_search(vector<int> needle, vector<int> hay)
{
	if ( needle.size()==0 ) return 0;

	vector<int> table(needle.size());
	table[0] = -1;
	if ( needle.size()>=1 ) table[1] = 0;

	int pos = 2;
	int cnd = 0;
	while ( pos<needle.size() ) {
		if ( needle[pos-1]==needle[cnd] ) {
			cnd++;
			table[pos++] = cnd;
		} else if ( cnd!=0 ) {
			cnd = table[cnd];
		} else {
			table[pos] = 0;
			pos++;
		}
	}

	int m = 0, i = 0;
	while ( m+i<hay.size() ) {
		if ( needle[i]==hay[m+i] ) {
			if ( ++i==needle.size() ) return m;
		} else {
			if ( table[i]>-1 ) {
				m = m + i - table[i];
				i = table[i];
			} else {
				m++;
				i = 0;
			}
		}
	}

	return -1;
}

int main()
{
	int n;
	cin >> n;

	vector<int> a, b;
	a = readhands(n);
	b = readhands(n);

	for(int i=0; i<n; i++) a.push_back(a[i]);

	if ( kmp_search(b,a)>=0 ) {
		cout << "possible" << endl;
	} else {
		cout << "impossible" << endl;
	}

	return 0;
}
