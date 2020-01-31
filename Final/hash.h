#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <chrono>
#include <algorithm>
#include <queue>
#include <ctime>

using namespace std;
using namespace std::chrono;


struct LLNode
{
  LLNode* next;
  bool head;
  int key;
};

struct BSTNode
{
  int key;
  BSTNode* left;
  BSTNode* right;
  BSTNode* parent;
};

class HashTable
{
  int* table1;
  int* cuckooTable1;
  int* cuckooTable2;
  LLNode* LLTable;
  BSTNode* BSTTable;
  int h(int toHash);
  int hPrime(int toHash);
  int cuckooHash(int toHash);
  int cuckooHashPrime(int toHash);


public:
  int TABLE_SIZE = 10009;
  int cuckooTableSize=10009;
  int rehashIndex = 0;
  double itemsHashed = 0;
  int itemsHashedLL = 0;
  int itemsHashedBST = 0;
  int itemsHashedCuckoo = 0;
  double loadFactor=0;
  int timesRehashed = 0;

  HashTable();
  void hashItem(int toHash, int funcChoice);
  void hashItemLL(int toHash, int funcChoice);
  void hashItemBST(int toHash, int funcChoice);
  void hashItemCuckoo(int toHash);
  bool lookupItem(int toFind, int funcChoice);
  bool lookupLL(int toFind, int funcChoice);
  bool lookupBST(int toFind, int funcChoice);
  bool lookupCuckoo(int toFind);
  void deleteItem(int toDelete, int funcChoice);
  void deleteLL(int toDelete, int funcChoice);
  void deleteBST(int toDelete, int funcChoice);
  void deleteCuckoo(int toDelete);
  int linearProbing(int toHash);
  void cuckooRehash();
  int nextPrime(int currentTableSize);
  bool isPrime(int checkPrime);

};
