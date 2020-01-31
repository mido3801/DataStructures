#include "hash.h"

double averageTime(vector<duration<double, std::nano>> toAverage);
void getTimepoints(int lastHundred[], HashTable myTable);
double getDeviation(vector<duration<double,std::nano>> timePoints, double mean);

int main(int argc, char* argv[])
{
  HashTable myTable;
  string datasetName = argv[1];
  fstream dataset;
  dataset.open(datasetName);
  string line;
  string toHashString;
  queue<int> hashPop;
  int toHash;
  int lastHundred[100];
  int count = 0;
  int timesRehashedCurrent;
  bool flags[6];

  for (int i = 0; i < 6; i++)
  {
    flags[i] = false;
  }

  //grab all integers from dataset and put in queue to be read to tables
  while (getline(dataset,line))
  {
    stringstream s(line);
    while (getline(s, toHashString, ','))
    {
      toHash = stoi(toHashString);
      hashPop.push(toHash);
    }
  }

  dataset.close();

  fstream outfile;
  outfile.open("output.csv",ios::app);
  outfile << "Using Dataset: " << datasetName << "\n";
  outfile << "--------------------" << "\n";
  outfile.close();

  int thisInt;

  //continuosly pop from queue, checking if we have reached the desired load factors to measure at
  while (!hashPop.empty())
  {
    thisInt = hashPop.front();

    if (flags[0] == false && myTable.loadFactor > 0.1)
    {
      flags[0] = true;
      getTimepoints(lastHundred,myTable);
    }

    else if (flags[1] == false && myTable.loadFactor > 0.2)
    {
      flags[1] = true;
      getTimepoints(lastHundred,myTable);
    }

    else if (flags[2] == false && myTable.loadFactor > 0.5)
    {
      flags[2] = true;
      getTimepoints(lastHundred,myTable);
    }

    else if (flags[3] == false && myTable.loadFactor > 0.7)
    {
      flags[3] = true;
      getTimepoints(lastHundred,myTable);
    }

    else if (flags[4] == false && myTable.loadFactor > 0.9)
    {
      flags[4] = true;
      getTimepoints(lastHundred,myTable);
    }

    else if (flags[5] == false && myTable.loadFactor == 1)
    {
      flags[5] = true;
      getTimepoints(lastHundred,myTable);
      break;
    }

    myTable.hashItem(thisInt,2);
    myTable.hashItemLL(thisInt,2);
    myTable.hashItemBST(thisInt,2);

    myTable.loadFactor = myTable.itemsHashed/myTable.TABLE_SIZE;

    lastHundred[count] = thisInt;

    if (count == 99)
    {
      count = 0;
    }
    else
    {
      count ++;
    }

    hashPop.pop();
    myTable.itemsHashed++;

  }

  return 0;
}

//get average time from vector of timepoints
double averageTime(vector<duration<double,std::nano>> toAverage)
{
  double sum = 0;
  for (int i = 0; i < toAverage.size();i++)
  {
    sum += toAverage[i].count();
  }
  return sum/100;
}

/*
  Get Timepoints function, called when the load factor first hits the desired values
  We have vectors to store the time points from each of the last hundred integers for each of our functions
  Starts high resolution clock from chrono library before function call and stops after it completes
  Stores the value as nanoseconds
  After all measurements are done average the values and print to our output file
*/

void getTimepoints(int lastHundred[], HashTable myTable)
{
  //create our output file
  fstream outfile;
  outfile.open("output.csv",ios::app);
  vector<duration<double,std::nano>> deleteTimePoints;
  vector<duration<double,std::nano>> hashTimePoints;
  vector<duration<double,std::nano>> lookupTimePoints;
  vector<duration<double,std::nano>> LLdeleteTimePoints;
  vector<duration<double,std::nano>> LLhashTimePoints;
  vector<duration<double,std::nano>> LLlookupTimePoints;
  vector<duration<double,std::nano>> BSTdeleteTimePoints;
  vector<duration<double,std::nano>> BSThashTimePoints;
  vector<duration<double,std::nano>> BSTlookupTimePoints;
  double average;

  //for each of the last 100 integers inputted run the functions for each collision resolution mechanism and get times
  //then get average and write to output file

  for (int i = 0; i < 100; i++)
  {
    cout << "Deleting " << lastHundred[i] << endl;
    auto start = high_resolution_clock::now();
    myTable.deleteItem(lastHundred[i],2);
    auto stop = high_resolution_clock::now();
    duration<double,std::nano> myDuration = stop-start;
    deleteTimePoints.push_back(myDuration);

    cout << "Hashing " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.hashItem(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    hashTimePoints.push_back(myDuration);

    cout << "Lookup " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.lookupItem(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    lookupTimePoints.push_back(myDuration);

    cout << "Deleting LL " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.deleteLL(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    LLdeleteTimePoints.push_back(myDuration);

    cout << "Hashing LL " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.hashItemLL(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    LLhashTimePoints.push_back(myDuration);

    cout << "Lookup LL " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.lookupLL(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    LLlookupTimePoints.push_back(myDuration);

    cout << "Deleting BST " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.deleteBST(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    BSTdeleteTimePoints.push_back(myDuration);

    cout << "Hashing BST " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.hashItemBST(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    BSThashTimePoints.push_back(myDuration);

    cout << "Lookup BST " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.lookupBST(lastHundred[i],2);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    BSTlookupTimePoints.push_back(myDuration);

  }

  outfile << "Load Factor: " << myTable.loadFactor << "\n";
  outfile << "--------------------" << "\n";
  outfile << "Linear Probing" << "\n";
  outfile << "Items hashed " << myTable.itemsHashed << "\n";
  outfile << "Deleting: " << averageTime(deleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(hashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(lookupTimePoints) << "nanoseconds" << "\n";
  outfile << "Std Dev Deleting: " << getDeviation(deleteTimePoints,averageTime(deleteTimePoints)) << "\n";
  outfile << "Std Dev Hashing: " << getDeviation(hashTimePoints,averageTime(hashTimePoints)) << "\n";
  outfile << "Std Dev Lookup: " << getDeviation(lookupTimePoints,averageTime(lookupTimePoints)) << "\n";
  outfile << "---------------------" << "\n";
  outfile << "Linked List Chaining" << "\n";
  outfile << "Deleting: " << averageTime(LLdeleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(LLhashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(LLlookupTimePoints) << "nanoseconds" << "\n";
  outfile << "Std Dev Deleting: " << getDeviation(LLdeleteTimePoints,averageTime(LLdeleteTimePoints)) << "\n";
  outfile << "Std Dev Hashing: " << getDeviation(LLhashTimePoints,averageTime(LLhashTimePoints)) << "\n";
  outfile << "Std Dev Lookup: " << getDeviation(LLlookupTimePoints,averageTime(LLlookupTimePoints)) << "\n";
  outfile << "---------------------" << "\n";
  outfile << "BST Chaining" << "\n";
  outfile << "Deleting: " << averageTime(BSTdeleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(BSThashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(BSTlookupTimePoints) << "nanoseconds" << "\n";
  outfile << "Std Dev Deleting: " << getDeviation(BSTdeleteTimePoints,averageTime(BSTdeleteTimePoints)) << "\n";
  outfile << "Std Dev Hashing: " << getDeviation(BSThashTimePoints,averageTime(BSThashTimePoints)) << "\n";
  outfile << "Std Dev Lookup: " << getDeviation(BSTlookupTimePoints,averageTime(BSTlookupTimePoints)) << "\n";
  outfile << "---------------------";
  outfile << "\n";

  outfile.close();

}

double getDeviation(vector<duration<double,std::nano>> timePoints, double mean)
{
  double temp = 0.0;
  for (int i = 0; i < timePoints.size(); i++)
  {
    temp+=(timePoints[i].count()-mean)*(timePoints[i].count()-mean);
  }
  double stdDev = sqrt(1/(double(timePoints.size())*temp));
  return stdDev;
}
