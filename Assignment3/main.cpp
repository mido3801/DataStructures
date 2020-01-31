/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

// declarations for main helper-functions
void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    bool run = true;
    int choice;
    while (run == true)
    {

      displayMenu();
      cin >> choice;

      if (choice == 1)
      {
        CountryNet.loadDefaultSetup();
        CountryNet.printPath();
      }

      if (choice == 2)
      {
        CountryNet.printPath();
      }

      if (choice == 3)
      {
        char message[50];
        char name[50];

        cout << "Enter name of the country to receive the message:";
        cin.ignore();
        cin.getline(name,50);
        cout << "\nEnter the message to send:" << endl;
        cin.getline(message,50);
        cout << endl;

        CountryNet.transmitMsg(name,message);
      }

      if (choice == 4)
      {
        char newCountry[50];
        char previous[50];
        int count = 0;

        bool flag = true;


          cout << "Enter a new country name:";
          cin.ignore();
          cin.getline(newCountry,50);
          cout << endl;

          newCountry[0] = toupper(newCountry[0]);




          do{
            if (count == 0)
            {
            cout << "Enter the previous country name (or First):";
            }
            cin.getline(previous,50);
            cout << endl;

            char check[5] = {'F','i','r','s','t'};


          if (previous[0] == check[0] && previous[1] == check[1] && previous[2] == check[2])
          {
            CountryNet.insertCountry(NULL, newCountry);
            CountryNet.printPath();
            flag = false;
            break;
          }

          Country* temp = new Country;
          temp = CountryNet.searchNetwork(previous);

          if (temp != NULL)
          {

            CountryNet.insertCountry(temp, newCountry);
            CountryNet.printPath();
            flag = false;
            break;
          }
          count++;
          cout << "INVALID(previous country name)...Please enter a VALID previous country name!";

        }while(flag==true);



      }

      if (choice == 5)
      {
        cout << "Quitting..." << endl;
        cout << "Goodbye!" << endl;
        run = false;
      }



    }


    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
