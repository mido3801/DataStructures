#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

struct wordItem
{
  string word;
  int count;
} tempStruct;

int main(int argc, char const *argv[])
{
  //string readFileName = argv[1];
  int timesDoubled = 0;
  wordItem* uncommonWords;
  uncommonWords = new wordItem[50];
  bool inArray = false;
  string line2;
  int length = 0;
  int max = 50;

  ifstream readFile(argv[1]);

  if (readFile.fail())
  {
    cout << "Failed to open file" << endl;
    return 0;
  }

  while(readFile>>line2)
    {
      inArray = false;
      if (length == 0)
      {
        tempStruct.word = line2;
        tempStruct.count = 1;
        uncommonWords[0] = tempStruct;
        length++;
      }
      else
      {
      if (length == max)
      {
        timesDoubled++;
        max = max*2;
        wordItem* doubler = new wordItem[max];
        for (int i = 0; i<length; i++)
        {
          doubler[i] = uncommonWords[i];
        }
        delete[] uncommonWords;
        uncommonWords = doubler;
      }
      for (int w = 0; w < length; w++)
      {
        //cout << length; // length isnt getting incremented
        if (line2 == uncommonWords[w].word)
        {
          uncommonWords[w].count++;
          inArray = true;
          break;
        }
      }
      if (inArray == false)
      {
        tempStruct.word = line2;
        tempStruct.count = 1;
        uncommonWords[length] = tempStruct;
        length++;
      }
    }
    }
    for (int c = 0; c<length; c++)
    {
      cout << uncommonWords[c].word << uncommonWords[c].count << endl;
    }
return 0;
}
