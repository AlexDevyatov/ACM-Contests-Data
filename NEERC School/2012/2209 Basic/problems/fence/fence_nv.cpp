#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
	long long x, y;
	point() {};
	point(int x,  int y): x(x), y(y) {};
};

long long area(point p1, point p2, point p3)
{
	return abs((p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p2.y));
}

int main()
{
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
	int n;
	scanf("%d\n", &n);
	vector<point> points(n);
	for (int i = 0; i < n; i++)
		scanf("%lld%lld\n", &points[i].x, &points[i].y);
	points.push_back(points[0]);
	point p;
	scanf("%lld%lld\n", &p.x, &p.y);
	long long min_area = (long long)9e18;
	int pos = -1;
	for (int i = 0; i < n; i++)
	{
		long long cur_area = area(p, points[i], points[i + 1]);
		if (cur_area < min_area)
		{
			pos = i;
			min_area = cur_area;
		}
	}
	printf("%d\n", n + 1);
	for (int i = 0; i < n; i++)
	{
		printf("%lld %lld\n", points[i].x, points[i].y);
		if (i == pos) 
			printf("%lld %lld\n", p.x, p.y);
	}
}
