#include <iostream>
#include <map>
#include <string.h>
#include <assert.h>

using namespace std;

int dp[101][99 * 100 + 1][100];
string merchant_type[128];
int price[128], G, C, N, package_size[128];

int calc(int gold_coins, int silver_coins, int merchant_id){
	if(gold_coins < 0 || silver_coins < 0)return -N;
	if(merchant_id == N)return 0;
	int & res = dp[gold_coins][silver_coins][merchant_id];
	if(res == -1){
		res = calc(gold_coins, silver_coins, merchant_id + 1);
		if(merchant_type[merchant_id] != "generous" || silver_coins < price[merchant_id] || G == price[merchant_id]){
			// pay with gold:
			int change;
			if(merchant_type[merchant_id] == "generous") change = ((G - price[merchant_id] + package_size[merchant_id] - 1) / package_size[merchant_id]) * package_size[merchant_id];
			else if(merchant_type[merchant_id] == "greedy") change = ((G - price[merchant_id]) / package_size[merchant_id]) * package_size[merchant_id];
			else if(merchant_type[merchant_id] == "honest") change = ((G - price[merchant_id] + package_size[merchant_id] / 2) / package_size[merchant_id]) * package_size[merchant_id];
			else assert(false);
			res = max(res, 1 + calc(gold_coins - 1, silver_coins + change, merchant_id + 1));
		}
		// pay with silver
		res = max(res, 1 + calc(gold_coins, silver_coins - price[merchant_id], merchant_id + 1));
//		cerr << gold_coins << " " << silver_coins << " " << merchant_id << ": " << res << endl;
		return res;
	}
	return res;
}
int main(){
	memset(dp,-1,sizeof(dp));
	cin >> G >> C >> N;
	for(int i = 0; i < N; i++)
		cin >> merchant_type[i] >> package_size[i] >> price[i];
	cout << calc(C, 0, 0) << endl;
}
