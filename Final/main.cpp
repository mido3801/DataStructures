#include "hash.h"

float averageTime(vector<nanoseconds> toAverage);
void getTimepoints(int lastHundred[], HashTable myTable);

int main(int argc, char* argv[])
{
  HashTable myTable;
  //string dataset = argv[1];
  fstream dataset1;
  fstream dataset2;
  dataset1.open("dataSetA.csv");
  string line;
  string toHashString;
  int toHash;
  int lastHundred[100];
  int count = 0;
  bool flags[6];
  for (int i = 0; i < 6; i++)
  {
    flags[i] = false;
  }

  while (getline(dataset1,line))
  {
    stringstream s(line);
    while (getline(s, toHashString, ','))
    {
      toHash = stoi(toHashString);
      //cout << "toHashString: " << toHashString << endl;
      if (myTable.loadFactor < 0.1)
      {
        lastHundred[count] = toHash;
        myTable.hashItem(toHash,1);
        myTable.hashItemLL(toHash,1);
        myTable.hashItemBST(toHash,1);
        myTable.loadFactor = myTable.itemsHashed/1019;
        if (count == 99)
        {
          count = 0;
        }
        else
        {
          count ++;
        }
      }

      if (flags[0] == false && myTable.loadFactor > 0.1)
      {
        flags[0] = true;
        getTimepoints(lastHundred,myTable);
      }

    }


  }






  return 0;
}

float averageTime(vector<nanoseconds> toAverage)
{
  float sum = 0;
  for (int i = 0; i < toAverage.size();i++)
  {
    sum += toAverage[i].count();
  }
  return sum/100;
}

void getTimepoints(int lastHundred[], HashTable myTable)
{
  fstream outfile;
  outfile.open("output.csv",ios::app);
  vector<nanoseconds> deleteTimePoints;
  vector<nanoseconds> hashTimePoints;
  vector<nanoseconds> lookupTimePoints;
  vector<nanoseconds> LLdeleteTimePoints;
  vector<nanoseconds> LLhashTimePoints;
  vector<nanoseconds> LLlookupTimePoints;
  vector<nanoseconds> BSTdeleteTimePoints;
  vector<nanoseconds> BSThashTimePoints;
  vector<nanoseconds> BSTlookupTimePoints;

  for (int i = 0; i < 100; i++)
  {
    cout << "deleting item" << endl;
    auto start = high_resolution_clock::now();
    myTable.deleteItem(lastHundred[i],1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop-start);
    deleteTimePoints.push_back(duration);

    cout << "hashing item" << endl;
    start = high_resolution_clock::now();
    myTable.hashItem(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    hashTimePoints.push_back(duration);

    cout << "lookup" << endl;
    start = high_resolution_clock::now();
    myTable.lookupItem(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    lookupTimePoints.push_back(duration);

    cout << "delete LL" << endl;
    start = high_resolution_clock::now();
    myTable.deleteLL(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    LLdeleteTimePoints.push_back(duration);

    cout << "hashLL" << endl;
    start = high_resolution_clock::now();
    myTable.hashItemLL(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    LLhashTimePoints.push_back(duration);

    cout << "lookupLL" << endl;
    start = high_resolution_clock::now();
    myTable.lookupLL(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    LLlookupTimePoints.push_back(duration);

    cout << "delete BST" << endl;
    start = high_resolution_clock::now();
    myTable.deleteBST(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    BSTdeleteTimePoints.push_back(duration);

    cout << "hash BST" << endl;
    start = high_resolution_clock::now();
    myTable.hashItemBST(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    BSThashTimePoints.push_back(duration);

    cout << "lookupBST" << endl;
    start = high_resolution_clock::now();
    myTable.lookupBST(lastHundred[i],1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);
    BSTlookupTimePoints.push_back(duration);
  }

  outfile << "Load Factor: " << myTable.loadFactor << "\n";
  outfile << "--------------------" << "\n";
  outfile << "Linear Probing" << "\n";
  outfile << "Deleting: " << averageTime(deleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(hashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(lookupTimePoints) << "nanoseconds" << "\n";
  outfile << "---------------------";
  outfile << "Linked List Chaining" << "\n";
  outfile << "Deleting: " << averageTime(LLdeleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(LLhashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(LLlookupTimePoints) << "nanoseconds" << "\n";
  outfile << "---------------------";
  outfile << "BST Chaining" << "\n";
  outfile << "Deleting: " << averageTime(BSTdeleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(BSThashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(BSTlookupTimePoints) << "nanoseconds" << "\n";
  outfile << "---------------------";
  outfile << "\n";

  outfile.close();

}
