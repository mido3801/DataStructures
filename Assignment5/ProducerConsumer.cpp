#include "ProducerConsumer.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

ProducerConsumer::ProducerConsumer()
{
  queueFront = 0;
  queueEnd = 0;
  for (int i = 0; i < SIZE; i++)
  {
    queue[i] = "";
  }
}

bool ProducerConsumer::isEmpty()
{
  for (int i = 0; i < SIZE; i++)
  {
    if(queue[i] != "")
    {
      return false;
    }
  }
  return true;
}

bool ProducerConsumer::isFull()
{
  if (queueFront == queueEnd && queue[queueFront] != "")
  {
    return true;
  }

  return false;
}

void ProducerConsumer::enqueue(string item)
{
  if (isFull())
  {
    cout << "Queue full, cannot add new item" << endl;
    return;
  }

  queue[queueEnd] = item;

  if (queueEnd == 19)
  {
    queueEnd = 0;
    return;
  }

  queueEnd++;

}

void ProducerConsumer::dequeue()
{
  if (isEmpty())
  {
    cout << "Queue empty, cannot dequeue an item" << endl;
    return;
  }

  queue[queueFront] = "";

  if (queueFront == 19)
  {
    queueFront = 0;
  }
  else
  {
    queueFront++;
  }

}

int ProducerConsumer::queueSize()
{
  int size = 0
  for (int i = 0; i < SIZE; i++)
  {
    if (queue[i] != "")
    {
      size++;
    }
  }
  return size;
}

string ProducerConsumer::peek()
{
  if (isEmpty())
  {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
  return queue[queueFront];
}
