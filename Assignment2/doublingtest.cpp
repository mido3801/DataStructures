#include <iostream>
#include <array>
#include <string>
using namespace std;

int main()
{
  int timesDoubled = 0;
  int max = 50;
  int* baseArray = new int[max];
  int length = 0;


  for (int i = 0; i<800; i++)
  {
    baseArray[i] = 1;
    length++;
    if (length == max)
    {
      timesDoubled++;
      max = max*2;
      int*  doubler = new int[max];
      for(int j = 0; j<length;j++)
      {
        doubler[j] = baseArray[j];
      }
      delete[] baseArray;
      baseArray = doubler;
      cout << "Doubled";
    }
  }
  /*for (int z = 0; z<length; z++)
  {
    cout << baseArray[z];
  }*/
  cout << timesDoubled << endl;
  return 0;
}
