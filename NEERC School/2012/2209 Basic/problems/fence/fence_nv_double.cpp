#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
	double x, y;
	point() {};
	point(double x,  double y): x(x), y(y) {};
};

double area(point p1, point p2, point p3)
{
	return fabs((p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p2.y));
}

int main()
{
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
	int n;
	cin >> n;
	vector<point> points(n);
	for (int i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y;
	points.push_back(points[0]);
	point p;
	cin >> p.x >> p.y;
	double min_area = 1e20;
	int pos = -1;
	for (int i = 0; i < n; i++)
	{
		double cur_area = area(p, points[i], points[i + 1]);
		if (cur_area < min_area)
		{
			pos = i;
			min_area = cur_area;
		}
	}
	cout << n + 1 << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << (int)points[i].x << " " << (int)points[i].y << "\n";
		if (i == pos) cout << (int)p.x << " " << (int)p.y << "\n";
	}
}