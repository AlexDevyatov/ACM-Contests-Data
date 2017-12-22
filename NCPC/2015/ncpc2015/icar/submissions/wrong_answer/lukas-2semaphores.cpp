// Solution by lukasP (Lukáš Poláček)
// Works only for 2 semaphores
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
const double eps = 1e-8;

double time(double d, double s = 0) // time to travel d kilometers, starting with speed s
{
    return -s + sqrt(s * s + 2000 * d);
}

// distance in km covered in t seconds. s is the original speed.
// It's an inverse of time(d, s).
double distance_covered(double t, double s = 0)
{
    return (2 * s + t) * t / 2000;
}

// the "prefix" acceleration time needed to pass semaphores distance d from each other
// exactly delta seconds from each other
double pass_two_prefix(double delta, double d)
{
    return 1000 * d / delta - delta / 2;
}

// The stopping time between two semaphores, so that we pass two semaphores distance d from each
// other exactly delta seconds from each other, with starting speed s.
double pass_two_middle(double delta, double d = 1, double s = 0)
{
    double a = 0.0, b = 1.1;
    rep(i,0,50)
    {
        double m = (a + b) / 2;
        bool ok = false;
        double distance_left = d - distance_covered(m * delta, s);
        if (distance_left <= 0) ok = true;
        else if (time(distance_left) <= (1 - m) * delta) ok = true;

        if (ok) b = m;
        else a = m;
    }
    return b * delta;
}

// Calculate the phase of semaphore (first, r, g) at time t. return value < g means it's green, >= g
// indicates the semaphore is red. All return values are in [0, r + g)
double phase(double t, double first, double r, double g)
{
    return fmod(t - first + r + g + eps / 2, r + g);
}

int iter = 10;
vector<double> first, g, r; // semaphore information from the input
vector<double> earliest; // the earliest time we can be at a semaphore
double next_green(double time, int i) // the next time green appears on semaphore i after 'time'
{
    if (phase(time, first[i], r[i], g[i]) >= g[i] + eps)
        time += r[i] + g[i] - phase(time, first[i], r[i], g[i]);
    return time;
}

// the number of the first hit red light, starting from distance d at start_time, with starting
// speed s
size_t first_hit(double d, double start_time, double s = 0)
{
    int next = floor(d) + 1;
    rep(i,next,first.size())
        if (phase(start_time + time(i - d, s), first[i], r[i], g[i]) >= g[i] + eps)
            return i;
    return first.size(); // we made it to the finish
}

void improveMin(double &a, double b)
{
    a = min(a, b);
}

void go_from(int pos, double start) // start from semaphore 'pos'
{
    if (start >= earliest[pos])
    {
        int hit = first_hit(pos, start);
        double green_after = next_green(time(hit - pos) + start, hit);
        improveMin(earliest[hit], green_after);
    }
}

void all_from(int pos) // try all sensible starting times from semaphore 'pos'
{
    go_from(pos, earliest[pos]);
    rep(i,pos + 1,first.size())
        rep(k,0,iter)
            go_from(pos, first[i] + k * (g[i] + r[i]) - time(i - pos));
}

int main()
{
    int n; scanf("%d", &n);

    first.assign(n, 0);
    g.assign(n, 0);
    r.assign(n, 0);
    g[0] = 1e10; // first semaphore is fake for the starting point

    rep(i,1,n)
        scanf("%lf %lf %lf", &first[i], &g[i], &r[i]);

    earliest.assign(n + 1, 1e20);
    earliest[0] = 0;
    all_from(0);

    if (n == 3)
    {
        all_from(1);

        // latest and earliest pass
        rep(i,0,iter) rep(j,0,iter)
        {
            double t1 = first[1] + g[1] + i * (r[1] + g[1]);
            double t2 = first[2] + j * (r[2] + g[2]);
            if (t1 < t2)
            {
                double need = pass_two_prefix(t2 - t1, 1);
                if (need >= 0)
                {
                    double dist = 1 - distance_covered(need);
                    if (time(dist) + need <= t1)
                        improveMin(earliest[3], t1 - need + time(3 - dist));
                }
            }
        }
    }

    printf("%.9lf\n", earliest.back());
}
