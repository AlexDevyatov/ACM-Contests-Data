// Solution by lukasP (Lukáš Poláček)
// Complexity O((iter * n)^2 * n), where iter is the maximum number of green cycles needed on a
// semaphore. It can be proven that iter <= n * 0.7.
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
const double eps = 1e-8;
typedef pair<double, double> pdd; // a node: (distance from start, time of departure)

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
double pass_two_middle(double delta, double d, double s)
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

vector<double> first, g, r; // semaphore information from the input
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

set<pdd> candidates, reachable; // candidate nodes, reachable nodes
map<pdd, pdd> previous; // previous position, for debugging
map<pdd, double> max_speed; // maximum speed for nodes that are at a semaphore

void improveSpeed(pdd a, double b, pdd prev)
{
    if (!max_speed.count(a))
        max_speed[a] = -1;
    if (b > max_speed[a])
    {
        max_speed[a] = b;
        previous[a] = prev;
    }
}

double arrival_time(pdd pos, double goal) // arrival time to goal starting from pos
{
    return pos.second + time(goal - pos.first, max_speed[pos]);
}

int main()
{
    int n; scanf("%d", &n);
    int iter = n - 1;

    first.assign(n, 0);
    g.assign(n, 0);
    r.assign(n, 0);
    g[0] = 1e10; // first semaphore is fake for the starting point

    rep(i,1,n)
        scanf("%lf %lf %lf", &first[i], &g[i], &r[i]);

    max_speed[pdd(0, 0)] = 0;
    reachable.insert(pdd(0, 0));

    map<pdd, vector<pdd>> goal; // The goal is always at the beginning of a green light.
    rep(i,0,n) rep(j,i+1,n) rep(l,0,iter)
    {
        double t2 = first[j] + l * (r[j] + g[j]);
        double time_to_leave = t2 - time(j - i);
        if (first_hit(i, time_to_leave) >= (size_t)j)
        {
            // hit the beginning of a green cycle at j starting from semaphore i
            candidates.insert(pdd(i, time_to_leave));
            goal[pdd(i, time_to_leave)].push_back(pdd(j, t2));
        }

        if (i > 0) rep(k,0,iter)
        {
            double t1 = first[i] + g[i] + k * (r[i] + g[i]);
            if (t1 < t2) // pass at the end and beginning of kth and lth green light respectively
            {
                double prefix_needed = pass_two_prefix(t2 - t1, j - i);
                pdd position = pdd(i - distance_covered(prefix_needed), t1 - prefix_needed);
                if (position.first >= 0 && position.second >= 0 &&
                    position.first < j &&
                    first_hit(position.first, position.second) >= (size_t)j)
                {
                    candidates.insert(position);
                    goal[position].push_back(pdd(j, t2));
                }
            }
        }
    }

    pdd last; // remember the last action before finish
    double res = n * (sqrt(2000) + 50) - 50; // simple upper-bound, can be improved
    while (!reachable.empty())
    {
        pdd pos = *reachable.begin(); // the earliest node to process
        reachable.erase(reachable.begin());
        while (!candidates.empty() && *candidates.begin() < pos) // remove unreachable
            candidates.erase(candidates.begin());

        if (max_speed.count(pos)) // at a semaphore, beginning of a green light
        {
            size_t hit = first_hit(pos.first, pos.second, max_speed[pos]);
            vector<pdd> to_erase;
            for (const pdd &o : candidates)
            {
                if (o.first > hit) break;
                double arrive = arrival_time(pos, o.first);
                if (o.first == hit)
                    arrive = next_green(arrive, hit);

                if (arrive <= o.second)
                {
                    if (o.first == hit)
                        improveSpeed(o, 0, pos);
                    previous[o] = pos;
                    to_erase.push_back(o);
                }
            }

            for (const pdd &o : to_erase)
            {
                candidates.erase(o);
                reachable.insert(o);
            }

            // arrived to the finish?
            if (first.size() == hit && res > arrival_time(pos, hit))
            {
                res = arrival_time(pos, hit);
                last = pos;
            }

            // pass at the earliest time of the lth green period on semaphore i, beginning or end of
            // the green period (e = 0 or e = 1)
            rep(i,pos.first + 1,n) rep(l,0,iter) rep(e,0,2)
            {
                double t = first[i] + l * (r[i] + g[i]) + e * g[i];
                if (t < pos.second) continue;

                double stop_time = pass_two_middle(t - pos.second, i - pos.first, max_speed[pos]);
                if (stop_time > eps && stop_time <= t - pos.second - eps)
                {
                    pdd midpos(pos.first + distance_covered(stop_time, max_speed[pos]),
                               stop_time + pos.second);
                    if (midpos.first < hit && first_hit(midpos.first, midpos.second) >= (size_t)i)
                    {   // Don't hit anything
                        goal[midpos].push_back(pdd(i, t));
                        previous[midpos] = pos;
                        reachable.insert(midpos);
                    }
                }
            }
        }

        for (pdd& next : goal[pos])
        {   // trying to hit the beginning of a green light from pos
            improveSpeed(next, time(next.first - pos.first), pos);
            candidates.erase(next);
            reachable.insert(next);
        }
    }

    printf("%.9lf\n", res);

    // Print the path
    // previous[pdd(0, 0)] = pdd(-1, -1);
    // while (last.first >= 0)
    // {
    //     cout << "distance " << last.first << ", time " << last.second << ", speed " << max_speed[last] << endl;
    //     last = previous[last];
    // }
}
