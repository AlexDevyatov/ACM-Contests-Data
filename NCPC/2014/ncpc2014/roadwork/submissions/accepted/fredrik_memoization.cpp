// Solution of problem Road Work
// Time complexity: O(n^3)
// Space complexity: O(n^2)
// Author: Fredrik Svensson
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX_N 350
int resetValue = 123*MAX_N;
const int maxTotalTime = 86400+MAX_N*3+2*MAX_N*180;

struct Car
{
	int arrival;
	int lastLeave;
};
vector<Car> toWest;
vector<Car> toEast;
int timeToPass;

int dp[MAX_N+1][MAX_N+1][MAX_N+1][2]; // totalTime = dp[drivenEast][drivenWest][numIrritated][lastToWest=0,lastToEast=1]

int calc(int drivenWest, int drivenEast, int numIrritated, int lastToEast)
{
	int &dpv = dp[drivenWest][drivenEast][numIrritated][lastToEast];
	if (dpv == 0x7f7f7f7f)
	{
		if ((lastToEast ? drivenEast : drivenWest) == 0)
			dpv = maxTotalTime;
		else
		{
			const Car &myCar = (lastToEast ? toEast[drivenEast-1] : toWest[drivenWest-1]);
			if (lastToEast)
				--drivenEast;
			else
				--drivenWest;
			dpv = maxTotalTime;
			// Check with one less to the east and one less to the west.
			for (int dir = 0; dir < 2; ++dir)
			{
				// Allow getting irritated
				if (numIrritated > 0)
					dpv = min(dpv, calc(drivenWest, drivenEast, numIrritated-1, dir) + (dir == lastToEast ? 3 : timeToPass));
				// Not getting irritated
				int myTime = calc(drivenWest, drivenEast, numIrritated, dir) + (dir == lastToEast ? 3 : timeToPass);
				if (myTime <= myCar.lastLeave)
					dpv = min(dpv, myTime);
			}
			if (dpv < maxTotalTime)
				dpv = max(myCar.arrival, dpv);
		}
	}
	return dpv;
}

int main()
{
	int n;
	cin >> timeToPass >> n;
	for (int i = 0; i < n; ++i)
	{
		string d;
		int maxStillTime;
		Car car;
		cin >> d >> car.arrival >> maxStillTime;
		car.lastLeave = car.arrival + maxStillTime;
		if (d == "W")
			toWest.push_back(car);
		else if (d == "E")
			toEast.push_back(car);
		else
			return -1;
	}
	// Dynamic programming
	// Reset
	memset(&dp[0][0][0][0], 0x7f7f7f7f, sizeof(dp));
	dp[0][0][0][0] = dp[0][0][0][1] = -3;
	// Run
	int numIrritated;
	for (numIrritated = 0; numIrritated <= n; ++numIrritated)
	{
		int t = min(
			calc((int)toWest.size(), (int)toEast.size(), numIrritated, 0),
			calc((int)toWest.size(), (int)toEast.size(), numIrritated, 1));
		if (t < maxTotalTime)
			break;
	}
	cout << numIrritated << endl;
	return 0;
}
