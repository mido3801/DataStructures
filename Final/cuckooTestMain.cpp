#include "hash.h"

double averageTime(vector<duration<double, std::nano>> toAverage);
void getTimepointsCuckoo(int lastHundred[], HashTable myTable);
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
  int lastHundred[100]; //to save last 100 inputs for timepoints
  int count = 0; //to keep index for last 100
  int timesRehashedCurrent = 0;
  bool flags[8];

  for (int i = 0; i < 8; i++)
  {
    flags[i] = false;
  }

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

  //Rather than use load factors we use items hshed in the cuckoo tables and calculate the load factors and timepoints at that amount of items

  while (!hashPop.empty())
  {
    thisInt = hashPop.front();

    lastHundred[count] = thisInt;
    cout << "items hashed cuckoo "<< myTable.itemsHashedCuckoo << endl;
    cout << "Hashing Cuckoo" << endl;
    myTable.hashItemCuckoo(thisInt);

    if (count == 99)
    {
      count = 0;
    }
    else
    {
      count ++;
    }

    hashPop.pop();
    myTable.itemsHashedCuckoo++;

    if (flags[0] == false && myTable.itemsHashedCuckoo > 1000)
    {
      flags[0] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[1] == false && myTable.itemsHashedCuckoo > 2500)
    {
      flags[1] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[2] == false && myTable.itemsHashedCuckoo > 8000)
    {
      flags[2] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[3] == false && myTable.itemsHashedCuckoo > 10000)
    {
      flags[3] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[4] == false && myTable.itemsHashedCuckoo > 15000)
    {
      flags[4] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[5] == false && myTable.itemsHashedCuckoo >= 20000)
    {
      flags[5] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[6] == false && myTable.itemsHashedCuckoo >= 30000)
    {
      flags[6] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

    if (flags[7] == false && myTable.itemsHashedCuckoo >= 40000)
    {
      flags[7] = true;
      getTimepointsCuckoo(lastHundred,myTable);
    }

  }

  outfile.open("output.csv",ios::app);
  outfile << "Total Rehashes: " << myTable.timesRehashed;
  outfile.close();

  return 0;
}

double averageTime(vector<duration<double, std::nano>> toAverage)
{
  double sum = 0;
  for (int i = 0; i < toAverage.size();i++)
  {
    sum += toAverage[i].count();
  }
  return sum/100;
}

/*
  Get Timepoints function, called when we hit certain number of items hashed
  We have vectors to store the time points from each of the last hundred integers for each of our functions
  Starts high resolution clock from chrono library before function call and stops after it completes
  Stores the value as nanoseconds
  After all measurements are done average the values and print to our output file
*/


void getTimepointsCuckoo(int lastHundred[], HashTable myTable)
{
  fstream outfile;
  outfile.open("output.csv",ios::app);
  vector<duration<double,std::nano>> cuckooDeleteTimePoints;
  vector<duration<double,std::nano>> cuckooHashTimePoints;
  vector<duration<double,std::nano>> cuckooLookupTimePoints;

  for (int i = 0; i < 100; i++)
  {
    cout << "Deleting Cuckoo " << lastHundred[i] << endl;
    auto start = high_resolution_clock::now();
    myTable.deleteCuckoo(lastHundred[i]);
    auto stop = high_resolution_clock::now();
    duration<double,std::nano> myDuration = stop-start;
    cuckooDeleteTimePoints.push_back(myDuration);

    cout << "Hashing Cuckoo " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.hashItemCuckoo(lastHundred[i]);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    cuckooHashTimePoints.push_back(myDuration);

    cout << "Lookup Cuckoo " << lastHundred[i] << endl;
    start = high_resolution_clock::now();
    myTable.lookupCuckoo(lastHundred[i]);
    stop = high_resolution_clock::now();
    myDuration = stop-start;
    cuckooLookupTimePoints.push_back(myDuration);
  }

  outfile << "Cuckoo Hashing " << "\n";
  outfile << "Items cuckoo hasehd " << myTable.itemsHashedCuckoo << "\n";
  outfile << "Number of Rehashes so Far: " << myTable.timesRehashed << "\n";
  outfile << "Cuckoo Current Load Factor: " << double(myTable.itemsHashedCuckoo)/double(((myTable.cuckooTableSize)*2)) << "\n";
  outfile << "Deleting: " << averageTime(cuckooDeleteTimePoints) << "nanoseconds" << "\n";
  outfile << "Hashing: " << averageTime(cuckooHashTimePoints) << "nanoseconds" << "\n";
  outfile << "Lookup: " << averageTime(cuckooLookupTimePoints) << "nanoseconds" << "\n";
  outfile << "Std Dev Deleting: " << getDeviation(cuckooDeleteTimePoints,averageTime(cuckooDeleteTimePoints)) << "\n";
  outfile << "Std Dev Hashing: " << getDeviation(cuckooHashTimePoints,averageTime(cuckooHashTimePoints)) << "\n";
  outfile << "Std Dev Lookup: " << getDeviation(cuckooLookupTimePoints,averageTime(cuckooLookupTimePoints)) << "\n";
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
