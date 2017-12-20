#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

//const struct timespec delay = { 0, 1000000 }; /* 1 millisec. */

FILE *in, *out;
int run,  nruns;
int N, P;
bool heavier;

struct Range {
	int a, b;
	bool isEmpty() {return (b < a);};
};

bool disjointRange(Range r1, Range r2) {
	return (r1.b < r2.a || r2.b < r1.a || r1.isEmpty() || r2.isEmpty());
}

vector<string> split(string s, char c) {
	vector<string> v;
	int a = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == c) {
			v.push_back(s.substr(a, i - a));
			a = i;
			while (a < s.size() && s[a] == c) a++;
			i = a;
		}
	}
	if (a < s.size()) v.push_back(s.substr(a, s.size() - a));
	return v;
}

bool makeRange(string s, Range& r) {
	vector<string> bounds = split(s, '-');
	if (bounds.size() == 1) {
		r.a = atoi(bounds[0].c_str());
		r.b = r.a;
		return (r.a >= 1 && r.a <= N);
	}
	else if (bounds.size() == 2) {
		r.a = atoi(bounds[0].c_str());
		r.b = atoi(bounds[1].c_str());
		if (r.b < r.a) r.b = r.a - 1; // empty range
		return (r.a >= 1 && r.a <= N && r.b >= 1 && r.b <= N);
	}
	else return false;
}

bool containsPirate(Range r) {
	return (r.a <= P && P <= r.b);
}


bool talk()
{
	char line[256];
	string Q;
	int counter = 0;
	int maxCounter = 0;
	int x = 1;
	while (x < 2 * N + 3) {
		x *= 3; maxCounter++;
	}


	printf("%ld\n",N); fflush(NULL);

	do {
		if (counter > maxCounter) {
			fprintf(out,"Exceeded number of queries: %d\n",maxCounter);
			return false;
		}
		fgets(line,255,stdin);
		for (int i = strlen(line) - 1; i >= 0 && line[i] == '\n'; i--) line[i] = 0;
		Q = line;

		if (Q.find("Ninja") == 0) {
			fprintf(out,"%s\n",line);
			return true;			
		}
		else {
			// split sides
			vector<string> sides = split(Q, '+');
			if (sides.size() != 2) {
				fprintf(out,"invalid query '%s'\n",line);
				return false;
			}

			// parse sides
			vector<string> lSide = split(sides[0], ' ');
			while (lSide.begin()->empty()) lSide.erase(lSide.begin());
			while (lSide.back().empty()) lSide.erase(--lSide.end());
			vector<string> rSide = split(sides[1], ' ');
			while (rSide.begin()->empty()) rSide.erase(rSide.begin());
			while (rSide.back().empty()) rSide.erase(--rSide.end());
			if (lSide.size() > 4 || rSide.size() > 4) {
				fprintf(out,"invalid query '%s'\n",line);
				return false;
			}

			// make ranges
			Range R[4];
			Range L[4];
			int cL = lSide.size();
			int cR = rSide.size();
			for (int i = 0; i < cL; i++) {
				if (!makeRange(lSide[i], L[i])) {
					fprintf(out,"invalid query '%s'\n",line);
					return false;
				}
			}
			for (int i = 0; i < cR; i++) {
				if (!makeRange(rSide[i], R[i])) {
					fprintf(out,"invalid query '%s'\n",line);
					return false;
				}
			}

			// check for disjointness
			for (int i = 0; i < cL; i++) {
				for (int j = i+1; j < cL; j++) {
					if (!disjointRange(L[i], L[j])) {
						fprintf(out,"invalid query '%s'\n",line);
						return false;
					}
				}
			}
			for (int i = 0; i < cR; i++) {
				for (int j = i+1; j < cR; j++) {
					if (!disjointRange(R[i], R[j])) {
						fprintf(out,"invalid query '%s'\n",line);
						return false;
					}
				}
			}
			for (int i = 0; i < cL; i++) {
				for (int j = 0; j < cR; j++) {
					if (!disjointRange(L[i], R[j])) {
						fprintf(out,"invalid query '%s'\n",line);
						return false;
					}
				}
			}

			// do evaluation
			//nanosleep(&delay,NULL); // delay
			int countL = 0, countR = 0;
			for (int i = 0; i < cL; i++) countL += L[i].b - L[i].a + 1;
			for (int i = 0; i < cR; i++) countR += R[i].b - R[i].a + 1;
			if (countL > countR) {
				printf("L\n");
			}
			else if (countR > countL) {
				printf("R\n");
			}
			else {
				char res = 'E';
				for (int i = 0; i < cL; i++) if (containsPirate(L[i])) res = (heavier ? 'L' : 'R');
				for (int i = 0; i < cR; i++) if (containsPirate(R[i])) res = (heavier ? 'R' : 'L');
				printf("%c\n", res);
			}
			fflush(NULL);
			counter++;
		}
	} while ( 1 );

	return true;
}


int main(int argc, char *argv[]) 
{
	long i;
	size_t nbuf;
	char buf[256];

	if ( argc-1!=2 ) {
		fprintf(stderr,"error: invalid number of arguments: %d, while 2 expected\n",argc-1);
		exit(1);
	}

	/* Make stdin/stdout unbuffered, just to be sure */
	if ( setvbuf(stdin,  NULL, _IONBF, 0)!=0 ||
	     setvbuf(stdout, NULL, _IONBF, 0)!=0 ) {
		fprintf(stderr,"error: cannot set unbuffered I/O\n");
		exit(1);
	}

	in  = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	if ( in==NULL || out==NULL ) {
		fprintf(stderr,"error: could not open input and/or output file\n");
		exit(1);
	}

	fscanf(in,"%d\n",&nruns);
	printf("%d\n",nruns);
	fflush(NULL);

	for(run=1; run<=nruns; run++) {
		fscanf(in,"%ld %ld\n",&N,&P);
		if (P < 0) {
			heavier = false; P = -P;
		}
		else heavier = true;
		if (!talk()) break;
	}

	/* We're done, send EOF */
	fclose(stdout);

	/* Copy any additional data from program */
	//while ( (nbuf=fread(buf,1,256,stdin))>0 ) fwrite(buf,1,nbuf,out);

	fprintf(stderr,"jury program exited successfully\n");
	return 0;
}
