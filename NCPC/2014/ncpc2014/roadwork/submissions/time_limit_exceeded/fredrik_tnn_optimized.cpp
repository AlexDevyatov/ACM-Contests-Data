// Too slow solution by Fredrik Svensson
// Time complexity: O(timeToPass*n^2)
// Space complexity: O(n^2)*big_factor
#include <algorithm>
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
	vector<pair<int, int>> arrivalsAndLastLeaves;
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
		arrivalsAndLastLeaves.push_back(make_pair(car.arrival, car.lastLeave));
	}
	// Dynamic programming
	// Reset
	memset(&dp[0][0][0][0], 0x3f3f3f3f, sizeof(dp));
	for (int t = 0; t < timePassArraySize; ++t)
		dp[t][0][0][0] = dp[t][0][0][1] = 0; // No irritated
	// Find the best result
	unsigned short ret = 0x3f3f;
	// Run
	int curCar = 0;
	int t = 0;
	int runUntil = -1;
	for (int t = 0; ; ++t)
	{
		int nextT = t;
		if (t > runUntil)
		{
			if (curCar >= arrivalsAndLastLeaves.size())
				break;
			// Just skip over time until the next car arrives.
			nextT = arrivalsAndLastLeaves[curCar].first;
			runUntil = max(nextT, arrivalsAndLastLeaves[curCar].second + 2*timeToPass + 3*n + 1);
			for (; curCar < arrivalsAndLastLeaves.size(); ++curCar)
			{
				if (runUntil < arrivalsAndLastLeaves[curCar].first)
					break;
				runUntil = max(runUntil, arrivalsAndLastLeaves[curCar].second + 2*timeToPass + 3*n + 1);
			}
		}
		{
			const int copyCount = min(nextT - t + 1, timePassArraySize-1);
			const auto &prevDp = dp[(t-1+timePassArraySize) % timePassArraySize];
			for (int i = 0; i < copyCount; ++i)
			{
				auto &curDp = dp[(t+i) % timePassArraySize];
				for (int drivenWest = 0; drivenWest <= toWest.size(); ++drivenWest)
					memcpy(&curDp[drivenWest][0][0], &prevDp[drivenWest][0][0], sizeof(curDp[drivenWest][0]) * (toEast.size()+1)); // The same state as last second if no one is driving.
			}
		}
		t = nextT;
		auto &curDp = dp[t % timePassArraySize];
		{
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
		}
		ret = min(ret, curDp[toWest.size()][toEast.size()][0]);
		ret = min(ret, curDp[toWest.size()][toEast.size()][1]);
	}
	cout << ret << endl;
	return 0;
}
