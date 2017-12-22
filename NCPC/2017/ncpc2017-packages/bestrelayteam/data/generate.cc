#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const double MIN_TIME = 8.00;
const double MAX_TIME = 19.99;
const int MAX_N = 500;

string rand_name() {
  string name = "";
  int len = rand()%18+3;
  for(int i=0;i<len;i++) {
    name += (char)('A'+rand() % 26);
  }
  return name;
}

double rand_time(double min, double max) {
  double r = ((double) rand() / (RAND_MAX));
  return (max-min) * r + min;
}


int crazy_random(int n, int case_no) {
  ofstream infile("secret/" + to_string(case_no) + "-crazy.in");
  infile << n << endl;
  infile << fixed << setprecision(2);
  for(int i=0;i<n;i++) {
    double t1 = rand_time(MIN_TIME, MAX_TIME);
    double t2 = rand_time(MIN_TIME, MAX_TIME);
    if (t1 < t2) swap(t1, t2);
    infile << rand_name() << " " <<  t1 << " " << t2 << endl;
  }
  infile.close();
  return 0;
}

int relative_random(int n, int case_no) {
  ofstream infile("secret/" + to_string(case_no) + "-relative.in");
  infile << n << endl;
  infile << fixed << setprecision(2);
  for(int i=0;i<n;i++) {
    double t1 = rand_time(MIN_TIME + 1.5, MAX_TIME);
    double t2 = t1 - rand_time(0, 1.5);
    infile << rand_name() << " " <<  t1 << " " << t2 << endl;
  }
  infile.close();
  return 0;
}

int sequential(int n, int case_no, double t1, double d1, double t2, double d2) {
  ofstream infile("secret/" + to_string(case_no) + "-sequential.in");
  infile << n << endl;
  infile << fixed << setprecision(2);
  for(int i=0;i<n;i++) {
    infile << rand_name() << " " <<  t1 << " " << t2 << endl;
    t1 += d1;
    t2 += d2;
  }
  infile.close();
  return 0;
}

int main() {
  srand(0);

  crazy_random(10, 1);
  crazy_random(50, 2);
  crazy_random(100, 3);
  crazy_random(MAX_N / 2, 4);
  crazy_random(MAX_N, 5);

  relative_random(10, 6);
  relative_random(50, 7);
  relative_random(100, 8);
  relative_random(MAX_N / 2, 9);
  relative_random(MAX_N, 10);

  sequential(MAX_N, 11, MIN_TIME, 0.01, MIN_TIME, 0.01);
  sequential(MAX_N, 12, MIN_TIME, 0.01, MIN_TIME, 0.005);
  sequential(MAX_N, 13, MIN_TIME + 1.00, 0.01, MIN_TIME, 0.005);
  sequential(MAX_N, 14, MAX_TIME, -0.01, MIN_TIME, 0.01);
  sequential(MAX_N, 15, MAX_TIME, -0.01, MAX_TIME, -0.01);
  sequential(MAX_N, 16, MAX_TIME, -0.005, MAX_TIME, -0.01);

  // Some small random cases
  for(int i=17; i<25; i++) {
    crazy_random(4 + rand() % 5, i);
  }

  return 0;
}
