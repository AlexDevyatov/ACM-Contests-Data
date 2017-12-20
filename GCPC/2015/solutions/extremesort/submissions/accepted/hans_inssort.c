#include <stdio.h>
#include <assert.h>

#define MAX_N (1024)

static int input[MAX_N];
static int work[MAX_N];

static void inssort(int *data, int n) {
	for (int cur = 0; cur < n; cur++) {
		int elem = data[cur];
		int target = cur;
		while (target > 0 && data[target-1] > elem) {
			data[target] = data[target-1];
			target--;
		}
		data[target] = elem;

		fprintf(stderr, "[cur=%d]", cur);
		for (int i = 0; i < n; i++)
			fprintf(stderr, " %d", data[i]);
		fprintf(stderr, "\n");
	}
}

static int testcase() {
	int n;
	scanf("%d", &n);
	assert(n <= MAX_N);

	for (int i = 0; i < n; i++) {
		scanf("%d", &input[i]);
		work[i] = input[i];
	}

	inssort(work, n);

	for (int i = 0; i < n; i++)
		if (work[i] != input[i])
			return 0;

	return 1;
}

int main(int argc, char *argv[]) {
	puts(testcase() ? "yes" : "no");
	return 0;
}
