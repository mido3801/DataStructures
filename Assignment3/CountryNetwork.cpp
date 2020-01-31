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
  head = NULL;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) //DONE
{

  if (previous == NULL)
  {
    Country* newCountry = new Country;
    newCountry->next = head;
    newCountry->name = countryName;
    newCountry->numberMessages = 0;
    head = newCountry;

    cout << "adding: " << countryName << " (HEAD)" << endl;
  }

  else
  {
    Country* newCountry = new Country;
    newCountry->name = countryName;
    newCountry->numberMessages = 0;
    newCountry->next = previous->next;
    previous->next = newCountry;

    cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
  }

}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() //DONE
{

  Country* temp = new Country;
  temp = head;

  insertCountry(temp, "United States");

  temp = head;
  insertCountry(temp, "Canada");

  temp = temp->next;
  insertCountry(temp, "Brazil");

  temp = temp->next;
  insertCountry(temp, "India");

  temp = temp->next;
  insertCountry(temp, "China");

  temp = temp->next;
  insertCountry(temp, "Australia");

}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName) //DONE
{


  Country* temp = new Country;

  if (head == NULL)
  {
    return NULL;
  }

  temp = head;
  while (temp != NULL)
  {
    if (temp->name == countryName)
    {
      return temp;
    }
    temp = temp->next;
  }

  return temp;
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  if (head == NULL)
  {
    cout << "Empty list" << endl;
    return;
  }

  Country* temp = new Country;
  Country* end = new Country;
  temp = head;
  bool flag = false;

  while (temp != NULL)
  {
    if(temp->name == receiver)
    {
      flag = true;
      end = temp->next;
      break;
    }
    temp = temp->next;
  }

  temp = head;

  if (flag == true)
  {
    while (temp != end)
    {
      temp->message = message;
      temp->numberMessages++;
      cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;
      temp = temp->next;
    }
  }

  else
  {
    cout << "Country not found" << endl;
  }

}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
  Country* temp = new Country;
  temp = head;

  cout << "== CURRENT PATH ==" << endl;

  if (head == NULL)
  {
    cout << "nothing in path" << endl;
    cout << "===" << endl;
    return;
  }



  while (temp != NULL)
  {
    cout << temp->name << " -> ";
    temp = temp->next;
  }

  cout << "NULL" << endl;
  cout << "===" << endl;

}
