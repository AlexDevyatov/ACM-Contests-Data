#include <cstdio>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int maxa = 360000;

int size;
vector<int> a,b;

bool identical = false;

int main(int argc, char **argv)
{
	if ( argc<=1 ) {
		printf("size argument required\n");
		return 1;
	}
	size = atoi(argv[1]);

	if ( argc>2 ) identical = true;

	srand(time(NULL));

	for(int i=0; i<size; i++) a.push_back(rand()%maxa);
	for(int i=0; i<size; i++) b.push_back(rand()%maxa);

	if ( identical ) {
		int shift = rand();
		for(int i=0; i<size; i++) b[i] = (a[i]+shift)%maxa;
		random_shuffle(b.begin(),b.end());
	}

	printf("%d\n",size);

	printf("%d",a[0]);
	for(int i=1; i<size; i++) printf(" %d",a[i]);
	printf("\n");

	printf("%d",b[0]);
	for(int i=1; i<size; i++) printf(" %d",b[i]);
	printf("\n");

	return 0;
}
