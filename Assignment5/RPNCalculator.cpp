#include "RPNCalculator.hpp"
#include <iostream>
using namespace std;


RPNCalculator::RPNCalculator()
{
  stackHead = NULL;
}

RPNCalculator::~RPNCalculator()
{
  Operand* temp = stackHead;
  while (!isEmpty())
  {
    pop();
  }
  stackHead = NULL;
}

bool RPNCalculator::isEmpty()
{
  if (stackHead == NULL)
  {
    return true;
  }
  return false;
}

void RPNCalculator::push(float number)
{
  Operand* temp;
  temp = new Operand;
  temp->next = stackHead;
  temp->number = number;
  stackHead = temp;
}

void RPNCalculator::pop()
{
  if (stackHead == NULL)
  {
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }

  Operand* temp;
  temp =  stackHead;
  if (temp->next != NULL)
  {
    stackHead = temp->next;
  }
  else
  {
    stackHead = NULL;
  }

  delete temp;
  return;
}

Operand* RPNCalculator::peek()
{
  if (stackHead == NULL)
  {
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }

  return stackHead;
}

bool RPNCalculator::compute(string symbol)
{

  if (stackHead == NULL)
  {
    cout << "err: not enough operands" << endl;
    return false;
  }

  if (symbol != "*" && symbol != "+")
  {
    cout << "err: invalid operation" << endl;
    return false;
  }

  float answer;
  Operand* first = stackHead;
  float float1 = first->number;

  pop();
  if (stackHead == NULL)
  {
    cout << "err: not enough operands" << endl;
    push(float1);
    return false;
  }

  first = stackHead;
  float float2 = first->number;
  pop();

  if (symbol == "*")
  {
    answer = float1*float2;
    push(answer);
  }
  else
  {
    answer = float1 + float2;
    push(answer);
  }
  return true;

}
