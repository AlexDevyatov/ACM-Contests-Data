#include <cstdio>
#include <cstring>
char word[512];
int shift[3] = {1,2,0};
char per[4] = "PER";

int main() {
	scanf("%s", word);
	int ct = 0;
	for(int i = 0; i < strlen(word); ++i)
		if(word[i] != per[i%3]) ++ct;
	printf("%d\n",ct);
}
