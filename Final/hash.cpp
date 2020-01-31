#include "hash.h"

HashTable::HashTable()
{
  //Start off by initializing our tables and setting everything to -1, or NULL
  table1 = new int[TABLE_SIZE];
  LLTable = new LLNode[TABLE_SIZE];
  BSTTable = new BSTNode[TABLE_SIZE];
  cuckooTable1 = new int[cuckooTableSize];
  cuckooTable2 = new int[cuckooTableSize];
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    table1[i] = -1;
    LLTable[i].key = -1;
    LLTable[i].next = NULL;
    BSTTable[i].key = -1;
    BSTTable[i].left = NULL;
    BSTTable[i].right = NULL;
    BSTTable[i].parent = NULL;
    cuckooTable1[i] = -1;
    cuckooTable2[i] = -1;
  }
}

//First hash fnx
int HashTable::h(int toHash)
{
  return toHash % TABLE_SIZE;
}

//Separate cuckoohash fnx because of variable table size
int HashTable::cuckooHash(int toHash)
{
  return (toHash % cuckooTableSize);
}

//Second hash fnx
int HashTable::hPrime(int toHash)
{
  return floor(toHash/TABLE_SIZE);
}

//Second cuckoo hash fnx
int HashTable::cuckooHashPrime(int toHash)
{
  return floor(toHash/cuckooTableSize);
}

//Go to next index in table and check if empty, if it is return that index.
//If i becomes too large wrap around to beginning of array
int HashTable::linearProbing(int toHash)
{

  int iStart = h(toHash);
  for(int i = iStart;i!=-1;i++)
  {
    if(i == TABLE_SIZE)
    {
      i=0;
    }

    //checks for -1 or -2 for reasons explained in delete fnx
    if(table1[i]==-1 || table1[i] == -2)
    {
      return i;
    }

    if (i == iStart)
    {
      return -1;
    }
  }

}


/*-----Hash Functions--------
  First is regular hash fnx. If a collision is found calls the linear probing fnx.
  Second is Linked List hash fnx.  Bascially same as the one from prior projects. No head member of class or anything, head is basically the node
  accessed by the array itself. If that node is populated then start linking
  Third is BST Hash fnx. Works same as one from prior projects. Like the linked list fnx there is no root, just the node that is accessed by the array. if
  that is populated then start working through the tree. Makes sure to set parent as well.

  First three fnx have the funcChoice argument which determines which hash function we're using
*/
void HashTable::hashItem(int toHash, int funcChoice)
{

  if (itemsHashed == TABLE_SIZE)
  {
    //Originally had cout statement with message saying table is full, but that affected process time a lot
    return;
  }

  //decide which hash function to use
  int h1;
  if (funcChoice == 1)
  {
    h1 = h(toHash);
  }

  else if(funcChoice == 2)
  {
    h1 = hPrime(toHash);
  }

  //Checks for -1 for -2 for reasons explained in deletion fnx
  if (table1[h1] == -1 || table1[h1] == -2)
  {
    table1[h1] = toHash;

    return;
  }

  int nextIndex = linearProbing(toHash);

  if (nextIndex == -1)
  {
    return;
  }
  table1[nextIndex] = toHash;

}

void HashTable::hashItemLL(int toHash, int funcChoice)
{

  //decide hash function
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toHash);
      break;
    }
    case 2:
    {
      h1 = hPrime(toHash);
      break;
    }
  }

//check if item is there, or if node is empty
  if (LLTable[h1].key == toHash)
  {
    return;
  }

  if (LLTable[h1].key==-1)
  {
    LLTable[h1].key = toHash;
    return;
  }

//iterate to end of LL at that index and add new node with input data value
  LLNode* newLLnode = new LLNode;
  newLLnode->key = toHash;
  newLLnode->next = NULL;
  LLNode* temp = &LLTable[h1];
  while(temp->next!=NULL)
  {
    temp = temp->next;
    if (temp->key == toHash)
    {
      return;
    }
  }
  temp->next = newLLnode;
  return;
}

void HashTable::hashItemBST(int toHash, int funcChoice)
{
  //choose hash function
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toHash);
      break;
    }
    case 2:
    {
      h1 = hPrime(toHash);
      break;
    }
  }

  //check if initial table is empty
  if (BSTTable[h1].key == -1)
  {
    BSTTable[h1].key = toHash;
    return;
  }
  //walk through tree until we hit end of tree, then add new node
  BSTNode* newBSTNode = new BSTNode;
  newBSTNode->key = toHash;
  newBSTNode->left = NULL;
  newBSTNode->right = NULL;
  newBSTNode->parent = NULL;
  BSTNode* temp = &BSTTable[h1];
  while (temp != NULL)
  {
    if (toHash == temp->key)
    {
      return;
    }
    if(toHash < temp->key)
    {
      if (temp->left != NULL)
      {
        temp = temp->left;
      }

      else
      {
        temp->left = newBSTNode;
        newBSTNode->parent = temp;
        return;
      }

    }
    else if(toHash > temp->key)
    {
      if (temp->right != NULL)
      {
        temp = temp->right;
      }

      else
      {
        temp->right = newBSTNode;
        newBSTNode->parent = temp;
        return;
      }

    }
  }
}


void HashTable::hashItemCuckoo(int toHash)
{

  int h1 = cuckooHash(toHash);
  int originalIndex = h1;
  int h2;
  int temp1 = cuckooTable1[h1];
  int temp2;
  int switchInt = 0;
  bool flag = false;
  double n = 0;

//check if first location empty
  if (temp1 == -1)
  {
    cuckooTable1[h1] = toHash;
    return;
  }

  temp1 = cuckooTable1[h1];
  cuckooTable1[h1] = toHash;


  //begin to move items between their alternate locations, breaking if we pick up the first item we tried to hash or if we hit too many cylesc
  while(flag == false)
  {

    if (n > 10000)
    {
      flag = true;
      break;
    }

    if (switchInt == 1)
    {
      h1 = cuckooHash(temp2);
      temp1 = cuckooTable1[h1];
      if (temp1 == toHash)
      {
        flag = true;
        break;
      }
      else if (temp1 == -1)
      {
        cuckooTable1[h1] = temp2;
        return;
      }
      switchInt = 0;
    }

    if (switchInt == 0)
    {

      h2 = cuckooHashPrime(temp1);
      temp2 = cuckooTable2[h2];
      if (temp2 == toHash)
      {
        flag = true;
        break;
      }
      if (temp2 == -1)
      {
        cuckooTable2[h2] = temp1;
        return;
      }
      switchInt = 1;
    }

    n++;
  }

  //if we break call the rehash function
  if (flag == true)
  {
    cuckooRehash();
    //hashItemCuckoo(toHash);
    timesRehashed++;
    return;
  }

}

/*
First function looks through array for value. If it reaches a -1 it stops because number can't be in table1
Second fnx steps through list if applicable
Third fnx steps through tree if applicable
Fourth checks both possible locations
*/
bool HashTable::lookupItem(int toFind, int funcChoice)
{
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toFind);
      break;
    }
    case 2:
    {
      h1 = hPrime(toFind);
      break;
    }
  }

  if (table1[h1]==-1)
  {
    return false;
  }

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    if (table1[i] == toFind)
    {
      return true;
    }

    if (table1[i] == -1)
    {
      return false;
    }
  }
}

bool HashTable::lookupLL(int toFind, int funcChoice)
{
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toFind);
      break;
    }
    case 2:
    {
      h1 = hPrime(toFind);
      break;
    }
  }

  if (LLTable[h1].key == -1)
  {
    return false;
  }
  if (LLTable[h1].next != NULL)
  {
    LLNode* temp = &LLTable[h1];
    while (temp->next != NULL)
    {
      if (temp->key == toFind)
      {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

}

bool HashTable::lookupBST(int toFind, int funcChoice)
{
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toFind);
      break;
    }
    case 2:
    {
      h1 = hPrime(toFind);
      break;
    }
  }

  if (BSTTable[h1].key == -1)
  {
    return false;
  }
  if (BSTTable[h1].left == NULL && toFind < BSTTable[h1].key)
  {
    return false;
  }
  if (BSTTable[h1].right == NULL && toFind > BSTTable[h1].key)
  {
    return false;
  }

  //step through table until we find value or hit end
  BSTNode* temp = &BSTTable[h1];
  while (temp != NULL)
  {
    if (temp->key == toFind)
    {
      return true;
    }
    if (toFind < temp->key)
    {
      if (temp->left == NULL)
      {
        break;
      }
      temp = temp->left;
    }
    else if (toFind > temp->key)
    {
      if (temp->right == NULL)
      {
        break;
      }
      temp = temp->right;
    }
  }
  return false;
}

bool HashTable::lookupCuckoo(int toFind)
{
  //check both possible locations
  int h1=h(toFind);
  int h2=hPrime(toFind);
  return !(cuckooTable1[h1]!= toFind && cuckooTable2[h2] != toFind);
}

/*
The linear probing delete function replaces the value present (not -1) with -2 to differentiate open vs empty
The linked list delete function is the lookup function but if it find s the value then it deletes the node and sets the previous node's Next values
The BST delete function works the same as the lookup function but if it finds the value it replaces it with the minimum of its right subtree
*/

void HashTable::deleteItem(int toDelete, int funcChoice)
{
  int h1;
  int iStart;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toDelete);
      break;
    }
    case 2:
    {
      h1= hPrime(toDelete);
      break;
    }
  }
  iStart = h1;
  for (int i = h1; i < TABLE_SIZE; i++)
  {
    if (table1[i]==toDelete)
    {
      table1[i] = -2;
      return;
    }
    if (table1[i] == -1)
    {
      return;
    }
    if (i == TABLE_SIZE-1)
    {
      i = -1;
    }
    if (i == iStart)
    {
      return;
    }
  }
}

void HashTable::deleteLL(int toDelete, int funcChoice)
{
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toDelete);
      break;
    }
    case 2:
    {
      h1 = hPrime(toDelete);
      break;
    }
  }

  if (LLTable[h1].key == -1)
  {
    return;
  }

  if (LLTable[h1].key == toDelete && LLTable[h1].next == NULL)
  {
    LLTable[h1].key = -1;
    return;
  }

  LLNode* temp = &LLTable[h1];
  LLNode* prev = NULL;
  while (temp != NULL)
  {

    if (temp->key == toDelete)
    {
      if (prev == NULL)
      {
        prev = temp->next;
        temp->key = prev->key;
        temp->next = prev->next;
        prev->next = NULL;
        delete prev;
        return;
      }
      prev->next = temp->next;
      delete temp;
      return;
    }
    prev = temp;
    temp = temp->next;

  }
  return;
}

void HashTable::deleteBST(int toDelete, int funcChoice)
{
  int h1;
  switch(funcChoice)
  {
    case 1:
    {
      h1 = h(toDelete);
      break;
    }
    case 2:
    {
      h1 = hPrime(toDelete);
      break;
    }
  }

  if (BSTTable[h1].key == -1)
  {
    return;
  }

  if (BSTTable[h1].left == NULL && toDelete < BSTTable[h1].key)
  {
    return;
  }

  if (BSTTable[h1].right == NULL && toDelete > BSTTable[h1].key)
  {
    return;
  }

  if(BSTTable[h1].key == toDelete && BSTTable[h1].left == NULL && BSTTable[h1].right == NULL)
  {
    BSTTable[h1].key = -1;
    return;
  }

  BSTNode* temp = &BSTTable[h1];
  while (temp != NULL)
  {

    if (toDelete < temp->key)
    {
      if (temp->left != NULL)
      {
        temp = temp->left;
      }
      else
      {
        return;
      }
    }
    else if (toDelete > temp->key)
    {
      if (temp->right != NULL)
      {
        temp = temp->right;
      }
      else
      {
        return;
      }
    }

    if (toDelete == temp->key)
    {
      BSTNode* temp2;
      if (temp->left == NULL && temp->right  == NULL)
      {
        temp2 = temp->parent;
        if (temp == temp2->right)
        {
          temp2->right = NULL;
        }
        else
        {
          temp2->left = NULL;
        }

        delete temp;
        return;
      }

      temp2 = temp;

      if (temp->right == NULL)
      {
        temp = temp->left;
      }
      else
      {
        temp = temp->right;
        while (temp->left != NULL)
        {
          temp = temp->left;
        }
      }


      BSTNode* thisparent = temp->parent;

      temp2->key = temp->key;
      thisparent->left = NULL;
      delete temp;

    }

  }
}

//Checks to see if either location ahs the value and sets to -1 if it does
void HashTable::deleteCuckoo(int toDelete)
{
  int h1 = h(toDelete);
  int h2 = hPrime(toDelete);
  if (cuckooTable1[h1]==toDelete)
  {
    cuckooTable1[h1] = -1;
  }
  if (cuckooTable2[h2] == toDelete)
  {
    cuckooTable2[h2] = -1;
  }
}

//Fucntion to be used with rehashing to check if the new table size is prime
bool HashTable::isPrime(int checkPrime)
{
  if (checkPrime <= 1)
  {
    return false;
  }

  if (checkPrime%2 == 0 || checkPrime%3 == 0)
  {
    return false;
  }

  for (int i = 5; i*i <= checkPrime; i = i+6)
  {
    if (checkPrime%i==0 || checkPrime % (i+2)==0)
    {
      return false;
    }
  }

  return true;
}

//Function to use with rehashing to get next prime after current table size
int HashTable::nextPrime(int currentTableSize)
{
  int testPrime = currentTableSize;
  bool prime = false;
  while(prime == false)
  {
    testPrime++;

    if (isPrime(testPrime))
    {
      prime = true;
    }

  }

  return testPrime;
}

//Rehash function
// Gets next highest prime number after current table size
// Creates temporary tables with new size and rehashes the values from the old tables to their new spots in the temporary table
// Delete old tables
// Set to temp tables
void HashTable::cuckooRehash()
{
  int h1,h2;
  int toRehash;
  int oldTableSize = cuckooTableSize;
  int newSize = nextPrime(cuckooTableSize);
  cuckooTableSize = newSize;
  int* tempHash1 = new int[newSize];
  int* tempHash2 = new int[newSize];
  for (int i = 0; i < newSize; i++)
  {
    tempHash1[i] = -1;
    tempHash2[i] = -1;
  }


  for (int i = 0; i < oldTableSize; i++)
  {
    if (cuckooTable1[i]!=-1)
    {
      toRehash = cuckooTable1[i];
      h1 = cuckooHash(toRehash);
      tempHash1[h1] = toRehash;
    }

    if (cuckooTable2[i]!=-1)
    {
      toRehash = cuckooTable2[i];
      h2 = cuckooHashPrime(toRehash);
      tempHash2[h2] = toRehash;
    }
  }

/* ***********************************************
NOTE: These 2 delete statements need to be commented out for the program to run. It will compile if they are uncommented but will crash. Please see Appendix A of
the report for more details
**********************************************/

  // delete[] cuckooTable1;
  // delete[] cuckooTable2;
  cuckooTable1 = tempHash1;
  cuckooTable2 = tempHash2;
  timesRehashed++;
}
