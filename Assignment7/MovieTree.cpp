#include 'MovieTree.hpp'
#include <iostream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void printNode(TreeNode* node);
void printLetter(TreeNode* node);
TreeNode* findTreeNode(TreeNode*, char character);

void MovieTree::printMovieInventory()
{
  TreeNode* head = root;
  if (temp == NULL)
  {
    cout << "Tree is Empty. Cannot print" << endl;
  }
  else{
    printNode(temp);
  }
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  LLMovieNode* newLLNode = new LLMovieNode(ranking, title, year, rating);
  TreeNode* temp = root;
  char firstChar = title[0];


  if (temp == NULL)
  {
    TreeNode* newTreeNode = new TreeNode;
    newTreeNode->titleChar = title[0];
    root = newTreeNode;
    temp = newTreeNode;
    temp->head = newLLNode;
    return;
  }

  if (temp->leftChild == NULL)
  {
    if (firstChar < root->titleChar)
    {
      TreeNode* newTreeNode = new TreeNode;
      newTreeNode->titleChar = firstChar;
      root->leftChild = newTreeNode;
      newTreeNode->head = newLLNode;
      return;
    }
  }

  if (temp->rightChild == NULL)
  {
    if (firstChar > root->titleChar)
    {
      TreeNode* newTreeNode = new TreeNode;
      newTreeNode->titleChar = firstChar;
      root->rightChild = newTreeNode;
      newTreeNode->head = newLLNode;
      return;
    }
  }

  TreeNode* targetTreeNode = findTreeNode(temp,firstChar);


  LLMovieNode* prevNode;
  if (targetTreeNode != NULL)
  {
    LLMovieNode* tempMovieNode = targetTreeNode->head;
    if (title < tempMovieNode->title)
    {
      newLLNode->next = tempMovieNode;
      targetTreeNode->head = newLLNode;
      return;
    }

    else
    {
      while (tempMovieNode != NULL)
      {

        if (title < tempMovieNode->title)
        {
          prevNode->next = newLLNode;
          newLLNode->next = tempMovieNode;
          return;
        }
        prevNode = tempMovieNode;
        tempMovieNode = tempMovieNode->next;
      }
      prevNode->next = newLLNode;
      return;
    }
  }

  else
  {
    TreeNode* temp = root;

    while(!(temp->leftChild == NULL && temp->rightChild == NULL))
    {
      if (firstChar < temp->titleChar)
      {
        if (temp->leftChild != NULL)
        {
          temp = temp->leftChild;
        }
        else
        {
          TreeNode* newTreeNode = new TreeNode;
          newTreeNode->titleChar = firstChar;
          temp->leftChild = newTreeNode;
          newTreeNode->head = newLLNode;
          return;
        }
      }
      else if (firstChar > temp->titleChar)
      {
        if (temp->rightChild != NULL)
        {
          temp = temp->rightChild;
        }
        else
        {
          TreeNode* newTreeNode = new TreeNode;
          newTreeNode->titleChar = firstChar;
          temp->rightChild = newTreeNode;
          newTreeNode->head = newLLNode;
          return;
        }
      }
    }
    if (firstChar < temp->titleChar)
  {
    TreeNode* newTreeNode = new TreeNode;
    temp->leftChild = newTreeNode;
    newTreeNode->titleChar = firstChar;
    newTreeNode->head = newLLNode;
    return;
  }

  else if (firstChar > temp->titleChar)
  {
    TreeNode* newTreeNode = new TreeNode;
    temp->rightChild = newTreeNode;
    newTreeNode->titleChar = firstChar;
    newTreeNode->head = newLLNode;
    return;
  }
  }



}

void MovieTree::deleteMovie(string title)
{
  char firstChar = title[0];

}

void printNode(TreeNode* node)
{
  if (node->left != NULL)
  {
    printNode(node->left);
  }
  printLetter(node);
  if (node->right != NULL)
  {
    printNode(node->right);
  }
}

void printLetter(TreeNode* node)
{
  LLMovieNode* temp = node->head;
  cout << "Movies starting with letter: " << node->titleChar << endl;
  while (temp!= NULL)
  {
    cout << " >> " << temp->title << " " << temp->rating << endl;
  }
}

TreeNode* findTreeNode(TreeNode* node, char character)
{
  if (node->titleChar == character)
  {
    return node;
  }
  if (node->leftChild != NULL)
  {
    findTreeNode(node->leftChild,character);
  }
  if (node->rightChild != NULL)
  {
    findTreeNode(node->rightChild,character);
  }
  return NULL;
}
