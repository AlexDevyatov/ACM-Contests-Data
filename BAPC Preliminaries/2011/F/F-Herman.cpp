#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
using std::max;
using std::min;

int main()
{
  int nrCases;
  for (cin >> nrCases; nrCases > 0; --nrCases)
  {
    int nrPirates; cin >> nrPirates;
    int nrItems;   cin >> nrItems;    
    vector<int> value;
    value.resize(nrItems);            
    for (int i = 0; i < nrItems; ++i) cin >> value[i];
    sort(value.begin(), value.end()); 
    int iCanGet = 0;
/* 
    // solution without thinking  
    if (nrPirates == 0)
      iCanGet = nrItems;
    else
    {
      for (int othersGet = nrItems/nrPirates; othersGet > iCanGet; --othersGet)
      {
        iCanGet = max(iCanGet, min(othersGet, nrItems - nrPirates*othersGet));
      }
    }
*/ 
    // solution according to Kevin, who is into thinking
    iCanGet = nrItems / (nrPirates + 1);
    int total = 0;
    for (int i = nrItems-iCanGet; i < nrItems; ++i)
      total += value[i];
    cout << total << endl;
  }
}
