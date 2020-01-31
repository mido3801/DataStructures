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

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);
void arraySort(wordItem uniqueWords[], int length);
void printNext10(wordItem uniqueWords[], int N, int totalNumWords);

int main(int argc, char const *argv[])
{
  int  N = stoi(argv[1]);
  string readFileName = argv[2];
  //char stopWordsFile = argv[3];

  string ignoreWords[50];
  wordItem* uncommonWords;
  uncommonWords = new wordItem[100];
  int timesDoubled = 0;
  int totalNumWords = 0;
  int length = 0;
  int totalUncommon = 0;

  getStopWords(argv[3], ignoreWords);

  string line2;
  string currentWord;
  bool isStop, inArray = false;
  ifstream readFile(readFileName);

  while(getline(readFile,line2, ' '))
  {
    //getline(line2,currentWord, " ");
    inArray = false;
    isStop = isStopWord(line2,ignoreWords);
    if (isStop == true)
    {
      totalNumWords++;
    }
    else
    {
      if (length == 0)
      {
        tempStruct.word = line2;
        tempStruct.count = 1;
        uncommonWords[0] = tempStruct;
        length ++;
      }
      if (length == (50 * (2^timesDoubled)))
      {
        timesDoubled++;
        wordItem* doubler;
        doubler = new wordItem[50*(2^timesDoubled)];
        for (int p = 0; p < length; p++)
        {
          doubler[p] = uncommonWords[p];
        }
        delete[] uncommonWords;
        wordItem* uncommonWords;
        uncommonWords = new wordItem[50*(2^timesDoubled)];
        uncommonWords = doubler;
        delete[] doubler;
      }
      for (int w = 0; w < length; w++)
        {
          if (line2 == uncommonWords[w].word)
          {
            uncommonWords[w].count++;
            inArray=true;
            totalUncommon++;
            totalNumWords++;
            break;
          }
        }
        if (inArray == false)
        {
          tempStruct.word = line2;
          tempStruct.count = 1;
          uncommonWords[length] = tempStruct;
          length++;
          totalUncommon++;
          totalNumWords++;
        }
    }
  }

  cout << "Array doubled: " << timesDoubled << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << length << endl;
  cout << "#" << endl;
  cout << "Total non-common words: " << totalUncommon << endl;
  cout << "#" << endl;
  printNext10(uncommonWords, N, totalNumWords);

  return 0;
}

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]) //DONE
{
  string line;
  ifstream ignoreFile(ignoreWordFileName);
  int x = 0;

  if (ignoreFile.fail())
  {
    cout << " Failed to open " << ignoreWordFileName << endl;
  }

  while (getline(ignoreFile,line))
  {
    ignoreWords[x] = line;
    x++;
  }
}

bool isStopWord(string word, string ignoreWords[])
{
  bool flag = false;
  for ( int i = 0; i < 50; i++)
  {
    if (word == ignoreWords[i])
    {
      flag = true;
    }
  }
  return flag;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length) //DONE
{
  int numWords = 0;
  for (int i = 0; i < length; i++)
  {
    numWords = numWords + uniqueWords[i].count;
  }
  return numWords;
}

void arraySort(wordItem uniqueWords[], int length)
{
  wordItem tempArray[length]; //create temporary array to do the sorting
  int x = 0;

  for (int i = 0; i<length; i++) //begin to iterate through the uniqueWords array
  {
    if (i == 0) //if its the first entry just put it at the beginning of tempArray
    {
      tempArray[i] = uniqueWords[0];
      x++;
    }

    else //for all subsequent words check against existing sorted entries
    {
      if(uniqueWords[i].count < tempArray[i-1].count) //if the current word is less common than the rightmost entry then add to end
      {
        tempArray[i] = uniqueWords[i];
        x++;
      }
      else
      {
        for (int j = 0; j < x; j++) //begin iterating through sorted entries
        {
          if (uniqueWords[i].count > tempArray[j].count)
          {
            for (int h = x; h > j; h--)
            {
              tempArray[h] = tempArray[h-1];
            }
            tempArray[j] = uniqueWords[i];
            break;
          }
          else
          {
            tempArray[x] = uniqueWords[i];
          }
        }
        x++;
      }
    }

    }
    for (int z = 0; z < x; z++)
    {
      uniqueWords[z] = tempArray[z];
    }
  }

  void printNext10(wordItem uniqueWords[], int N, int totalNumWords)
  {
  // print next 10 words after starting index with probability up to 4 decimal places
      float probabilityOfOccurrence;
      string buffer;
    cout << "Probability of next 10 words from rank " << N << endl;
    cout << "---------------------------------------" << endl;
    for (int i = N; i < N+10; i++)
      {
        probabilityOfOccurrence = (float)uniqueWords[i].count/(float)totalNumWords;
        probabilityOfOccurrence += .00005;
        buffer = to_string(probabilityOfOccurrence);

        for (int j = 0; j < 6; j++)
        {
            cout << buffer[j];
        }
        cout << " - " << uniqueWords[i].word << endl;
      }
  }
