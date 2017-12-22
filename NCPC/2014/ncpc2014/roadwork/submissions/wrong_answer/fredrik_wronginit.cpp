// Solution of problem Road Work
// Time complexity: O(n^3)
// Space complexity: O(n^2)
// Author: Fredrik Svensson
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX_N 1000
const int maxTotalTime = 86400+1000*3+2*MAX_N*180;

struct Car
{
	int arrival;
	int lastLeave;
};

int dp[2][MAX_N+1][MAX_N+1][2]; // totalTime = dp[drivenWest][numIrritated][lastToWest=0,lastToEast=1]


int main()
{
	int timeToPass, n;
	cin >> timeToPass >> n;
	vector<Car> toWest;
	vector<Car> toEast;
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
	memset(&dp[0][0][0][0], 0x7f7f7f7f, sizeof(dp[0]));
	dp[0][0][0][0] = dp[0][0][0][1] = -2; // Should be -3
	// Run
	for (int totalDriven = 0; totalDriven < n; ++totalDriven)
	{
		auto &prevDp = dp[totalDriven % 2];
		auto &curDp = dp[(totalDriven + 1) % 2];
		memset(&curDp[0][0][0], 0x7f7f7f7f, sizeof(curDp));
		for (int drivenWest = 0; drivenWest <= toWest.size(); ++drivenWest)
		{
			int drivenEast = totalDriven - drivenWest;
			for (int numIrritated = 0; numIrritated <= n; ++numIrritated)
			{
				if (drivenWest < toWest.size())
				{
					const Car &car = toWest[drivenWest];
					int nextDrive = max(car.arrival, min(prevDp[drivenWest][numIrritated][0]+3, prevDp[drivenWest][numIrritated][1]+timeToPass));
					int newIrritated = numIrritated + (nextDrive > car.lastLeave ? 1 : 0);
					curDp[drivenWest+1][newIrritated][0] = min(curDp[drivenWest+1][newIrritated][0], nextDrive);
				}
				if (drivenEast < toEast.size())
				{
					const Car &car = toEast[drivenEast];
					int nextDrive = max(car.arrival, min(prevDp[drivenWest][numIrritated][1]+3, prevDp[drivenWest][numIrritated][0]+timeToPass));
					int newIrritated = numIrritated + (nextDrive > car.lastLeave ? 1 : 0);
					curDp[drivenWest][newIrritated][1] = min(curDp[drivenWest][newIrritated][1], nextDrive);
				}
			}
		}
	}
	// Find the best result
	int ret;
	{
		const auto &curDp = dp[n % 2];
		for (ret = 0; ; ++ret)
		{
			if (curDp[toWest.size()][ret][0] < maxTotalTime)
				break;
			if (curDp[toWest.size()][ret][1] < maxTotalTime)
				break;
		}
	}
	cout << ret << endl;
	return 0;
}
