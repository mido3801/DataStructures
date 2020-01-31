/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer myQueue;
	bool run = true;
	int choice;
	while (run == true)
	{
		menu();
		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter the number of items to be produced:" << endl;
			int toProduce;
			string toAdd;
			cin.ignore();
			cin >> toProduce;

			for (int i = 0; i < toProduce; i++)
			{
				cout << "Item" << i+1 <<":" << endl;
				cin.ignore();
				cin >> toAdd;
				myQueue.enqueue(toAdd);
			}
		}

		if (choice == 2)
		{
			cout << "Enter the number of items to be consumed:" << endl;
			int toRemove;
			cin.ignore();
			cin>>toRemove;

			for (int i = 0; i < toRemove; i++)
			{
				if (myQueue.isEmpty())
				{
					cout << "No more items to consume from queue" << endl;
					break;
				}
				cout << "Consumed: " << myQueue.peek() << endl;
				myQueue.dequeue();
			}
		}

		if (choice == 3)
		{
			cout << "Number of items in the queue:" << myQueue.queueSize();
			return 0;
		}


	}

}
