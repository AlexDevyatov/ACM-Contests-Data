#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
using namespace std;

int T;

struct trie {
  unordered_map<string,trie*> x;
  unordered_map<string,int> ans;
  vector<double> dp;
  int size;
  double chance;
  
  trie() : dp(T+1,-1), size(0) {}
  double expect(int t);
  void update_chance();
}* questions;

string operator >> (istream& i, trie& t) {
  t.size++;
  string s;
  i >> s;
  trie*& ts = t.x[s];
  string ans;
  if (s.back()=='?') {
    i >> ans;
  }
  else {
    if (ts==NULL) ts = new trie;
    ans = i >> *ts;
  }
  t.ans[ans]++;
  return ans;
}

void trie::update_chance() {
  int most=0;
  for (const auto& it : ans) most=max(most,it.second);
  chance=double(most)/size;
  for (const auto& it : x) {
    if (it.second) it.second->update_chance();
  }
}

double trie::expect(int t) {
  double& e=dp[t];
  if (e!=-1) return e;
  if (t==0) return e=0;
  // Lenient time
  //if (t==1) return e=1;
  // Strict time
  if (t==1) return e=chance;
  double answer = chance + questions->expect(t-1);
  if (chance==1) return e=answer;
  double pass = 0;
  for (const auto& node : x) {
    if (node.second) pass += node.second->expect(t-1)*node.second->size;
    else pass += 1 + questions->expect(t-2);
  }
  pass/=size;
  return e=max(answer,pass);
}

int main() {
  int n;
  cin >> T >> n;
  questions = new trie;
  string line;
  getline(cin,line);
  while(getline(cin,line)) {
    istringstream stream(line);
    stream >> *questions;
  }
  questions->update_chance();
  cout.precision(10);
  cout << questions->expect(T) << endl;
}
