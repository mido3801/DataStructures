/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {

  Country* temp;
  Country* prev;
  temp = head;
  bool isPresent = false;

  while (temp != NULL)
  {
    if (temp == head && temp->name == countryName)
    {
      head = temp->next;
      delete temp;
      isPresent = true;
      break;
    }

    if (countryName == temp->name)
    {
      prev->next = temp->next;
      delete temp;
      isPresent = true;
      break;
    }

    prev = temp;
    temp = temp->next;
  }
  if (isPresent == false)
  {
    cout << "Country does not exist." << endl;
  }

}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName) {
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
  Country* temp;
  Country* prev;
  temp = head;

  if (head == NULL)
  {
    return;
  }

  while (temp != NULL)
  {
    prev = temp;
    temp = temp->next;
    cout << "deleting: " << prev->name << endl;
    delete prev;
  }

  head = NULL;
  cout <<"Deleted network" << endl;

}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
 void CountryNetwork :: rotateNetwork(int n)
 {
   int count = 0;
   Country* current;
   Country* first;
   Country* end:

   first,current = head;

   if (head == NULL)
   {
     cout << "Linked List is Empty" << endl;
     return;
   }

   while (count < n)
   {
     if (current == NULL)
     {
       cout << "Rotate not possible" << endl;
       return;
     }
     current = current->next;
     count++;
   }

   end = current;
   current = head;

   while (current->next != NULL)
   {
     current = current->next;
   }

   head=end->next;
   end->next = NULL;
   current->next = first;

   cout << "Rotate Complete" << endl;

}

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
 void CountryNetwork::reverseEntireNetwork()
 {
   Country* next;
   Country* prev;
   Country* current;

   current = head;
   prev = NULL;
   next = NULL;

   while (current != NULL)
   {
     next = current->next;
     current->next = prev;
     prev = current;
     current = next;
   }

   head = prev;


 }

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {

}
