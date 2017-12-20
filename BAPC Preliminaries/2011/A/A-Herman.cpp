#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <stdlib.h>

int dp(int n, int k)
{
  const int K = k+1;
  const int KK = K*K;
  const int KKK = K*KK;
  
  int* T = (int*) malloc((n+1) * KKK * sizeof(int));
  for (int ship = n; ship > 1; --ship)
    for (int remainingPirates = 0; remainingPirates <= k; ++remainingPirates)
      for (int strengthOfPreviousShip = 0; strengthOfPreviousShip <= k; ++strengthOfPreviousShip)
        for (int threatFromPreviousShip = 0; threatFromPreviousShip <= k; ++threatFromPreviousShip)
        {
          int maxDisloyalOnShipAndFollowingShips = -1;
          if (ship == n)
          {
            // look for the lowest number of disloyal pirates that cannot be accommodated
            int disloyalOnShip = 0;
            for (; disloyalOnShip <= strengthOfPreviousShip; ++disloyalOnShip)
            {
              int minLoyalOnShip = disloyalOnShip + threatFromPreviousShip;
              if (minLoyalOnShip == 0) minLoyalOnShip = 1;
              if (disloyalOnShip + minLoyalOnShip > remainingPirates) break;
            }
            maxDisloyalOnShipAndFollowingShips = disloyalOnShip - 1;
          }
          else
          {
            for (int disloyalOnShip = 0; disloyalOnShip <= strengthOfPreviousShip; ++disloyalOnShip)
            {
              int minLoyalOnShip = disloyalOnShip + threatFromPreviousShip;
              if (minLoyalOnShip == 0) minLoyalOnShip = 1;
              for (int loyalOnShip = minLoyalOnShip; loyalOnShip + disloyalOnShip <= remainingPirates; ++loyalOnShip)
              {
                int maxDisloyalOnFollowingShips = T[
                  (ship + 1) * KKK +
                  (remainingPirates - loyalOnShip - disloyalOnShip) * KK +
                  (loyalOnShip - threatFromPreviousShip - disloyalOnShip) * K +
                  disloyalOnShip
                ];
                if (maxDisloyalOnFollowingShips >= 0 && disloyalOnShip + maxDisloyalOnFollowingShips > maxDisloyalOnShipAndFollowingShips)
                  maxDisloyalOnShipAndFollowingShips = disloyalOnShip + maxDisloyalOnFollowingShips;
              }
            }
          }
          T[ship*KKK + remainingPirates*KK + strengthOfPreviousShip*K + threatFromPreviousShip] = maxDisloyalOnShipAndFollowingShips;
        }
  // finally the case of ship 1, with remainingPirates = k, strengthOfPreviousShip = k, threatFromPreviousShip = 0;
  int maxDisloyalOnShipAndFollowingShips = -1;
  if (1 == n)
  {
    // look for the lowest number of disloyal pirates that cannot be accommodated
    int disloyalOnShip = 0;
    for (; disloyalOnShip <= k; ++disloyalOnShip)
    {
      int minLoyalOnShip = disloyalOnShip;
      if (minLoyalOnShip == 0) minLoyalOnShip = 1;
      if (disloyalOnShip + minLoyalOnShip > k) break;
    }
    maxDisloyalOnShipAndFollowingShips = disloyalOnShip - 1;
  }
  else
  {
    for (int disloyalOnShip = 0; disloyalOnShip <= k; ++disloyalOnShip)
    {
      int minLoyalOnShip = disloyalOnShip;
      if (minLoyalOnShip == 0) minLoyalOnShip = 1;
      for (int loyalOnShip = minLoyalOnShip; loyalOnShip + disloyalOnShip <= k; ++loyalOnShip)
      {
        int maxDisloyalOnFollowingShips = T[
          2 * KKK + 
          (k - loyalOnShip - disloyalOnShip) * KK +
          (loyalOnShip - disloyalOnShip) * K + 
          disloyalOnShip
        ];
        if (maxDisloyalOnFollowingShips >= 0 && disloyalOnShip + maxDisloyalOnFollowingShips > maxDisloyalOnShipAndFollowingShips)
          maxDisloyalOnShipAndFollowingShips = disloyalOnShip + maxDisloyalOnFollowingShips;
      }
    }
  }
  delete T;
  return maxDisloyalOnShipAndFollowingShips;
}

int simple(int n, int k)
{
  if (n == 1) return (k/2);
  if (k < n) return -1;
  if (k < n + (n+4)/3) return k - n;
  return ((k - (n-2)/3) / 3);
}

int main()
{
  int nrTests; cin >> nrTests;
  for (int test = 1; test <= nrTests; ++test)
  {
    int n; int k; cin >> n >> k;
    if (n > 15) cerr << "Too many ships!" << endl;
    if (n < 1) cerr << "Too few ships!" << endl;
    if (k < n) cerr << "Not enough pirates to operate the ship(s)" << endl;
    if (k > 40) cerr << "Too many pirates" << endl;
    int quick = simple(n, k);
    int slow = dp(n, k);
    if (quick != slow) cerr << "ERROR!" << endl;
    cout << quick << endl;
  }
}

