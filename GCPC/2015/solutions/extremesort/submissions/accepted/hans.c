#include <stdio.h>

int testcase() {
	int N, cur, prev = -1;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &cur);
		if (cur < prev)
			return 0;
		prev = cur;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	puts(testcase() ? "yes" : "no");
	return 0;
}
