// Too slow solution by Fredrik Svensson
// Time complexity: O(n^3)
// Space complexity: O(n^2)*big_factor
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX_N 1000
const int timePassArraySize = 180+3+1;

struct Car
{
	int arrival;
	int lastLeave;
};

unsigned short dp[timePassArraySize][MAX_N+1][MAX_N+1][2]; // numIrritated = dp[time][drivenWest][drivenEast][lastToWest=0,lastToEast=1]


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
	memset(&dp[0][0][0][0], 0x3f3f3f3f, sizeof(dp));
	int tStart = (timeToPass - min(3, timeToPass) + timePassArraySize) % timePassArraySize;
	dp[tStart][0][0][0] = dp[tStart][0][0][1] = 0; // No irritated
	// Find the best result
	unsigned short ret = 0x3f3f;
	// Run
	const int maxTotalTime = n*max(3, timeToPass);
	for (int t = 0; t < maxTotalTime; ++t)
	{
		auto &curDp = dp[t % timePassArraySize];
		{
			const auto &prevDp = dp[(t-1+timePassArraySize) % timePassArraySize];
			for (int drivenWest = 0; drivenWest <= toWest.size(); ++drivenWest)
				memcpy(&curDp[drivenWest][0][0], &prevDp[drivenWest][0][0], sizeof(curDp[drivenWest])); // The same state as last second if no one is driving.
		}
		for (int drivenWest = 0; drivenWest <= toWest.size(); ++drivenWest)
		{
			for (int drivenEast = 0; drivenEast <= toEast.size(); ++drivenEast)
			{
				if (drivenWest > 0)
				{
					const Car &car = toWest[drivenWest-1];
					if (t >= car.arrival+timeToPass)
					{
						unsigned short newIrritated = (t-timeToPass > car.lastLeave ? 1 : 0) + min(
							dp[(t+timePassArraySize-3) % timePassArraySize][drivenWest-1][drivenEast][0],
							dp[(t+timePassArraySize-timeToPass) % timePassArraySize][drivenWest-1][drivenEast][1]);
						curDp[drivenWest][drivenEast][0] = min(curDp[drivenWest][drivenEast][0], newIrritated);
					}
				}
				if (drivenEast > 0)
				{
					const Car &car = toEast[drivenEast-1];
					if (t >= car.arrival+timeToPass)
					{
						unsigned short newIrritated = (t-timeToPass > car.lastLeave ? 1 : 0) + min(
							dp[(t+timePassArraySize-timeToPass) % timePassArraySize][drivenWest][drivenEast-1][0],
							dp[(t+timePassArraySize-3) % timePassArraySize][drivenWest][drivenEast-1][1]);
						curDp[drivenWest][drivenEast][1] = min(curDp[drivenWest][drivenEast][1], newIrritated);
					}
				}
			}
		}
		ret = min(ret, curDp[toWest.size()][toEast.size()][0]);
		ret = min(ret, curDp[toWest.size()][toEast.size()][1]);
		if (ret < n+1)
			break; // This is too greedy, it may take longer to get all to pass
	}
	cout << ret << endl;
	return 0;
}
