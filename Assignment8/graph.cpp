#include "Graph.hpp"
#include <iostream>
#include <string>
#include <queue>
using namespace std;


void Graph::addVertex(string name) // Add new vertex by allocating memory and add to vertices vector
{
  vertex* newVertex = new vertex;
  newVertex->name = name;
  vertices.push_back(newVertex);
}


void Graph::addEdge(string v1, string v2)
{
  vertex* temp1 = NULL;
  vertex* temp2 = NULL;
  for (int i=0; i < vertices.size();i++)
  {
    if(vertices[i]->name == v1)
    {
      temp1 = vertices[i];
    }
    if(vertices[i]->name == v2)
    {
      temp2 = vertices[i];
    }
  }
  if (temp1 != NULL && temp2 != NULL)
  {
    adjVertex* newAdjVert1 = new adjVertex;
    adjVertex* newAdjVert2 = new adjVertex;
    newAdjVert1->v = temp2;
    newAdjVert2->v = temp1;
    temp1->adj.push_back(*newAdjVert1);
    temp2->adj.push_back(*newAdjVert2);
  }

}

void Graph::displayEdges()
{
  for (int i = 0; i < (int)vertices.size();i++)
  {
    cout << vertices[i]->name << " --> ";
    for (int j = 0; j < (int)vertices[i]->adj.size();j++)
    {
        cout << vertices[i]->adj[j].v->name << " ";
    }

    cout << endl;
  }
}

void Graph::breadthFirstTraverse(string sourceVertex)
{
  vertex* temp;
  for (int i = 0; i < (int)vertices.size();i++)
  {
    if (vertices[i]->name == sourceVertex)
    {
      temp = vertices[i];
      temp->visited = true;
      temp->distance = 0;
    }
  }
  cout << "Starting vertex (root): " << temp->name << "-> ";

  queue<vertex*> bstQueue;
  bstQueue.push(*temp);
  while(!bstQueue.empty())
  {
    vertex* curr = bstQueue.front();
    bstQueue.pop();

    for (int i = 0; i<(int)curr->adj.size();i++)
    {
      if (!(curr->adj[i].v->visited))
      {
        (curr->adj[i].v)->distance = curr->distance+1;
        curr->adj[i].v->visited = true;
        bstQueue.push(curr->adj[i].v);
        cout << curr->adj[i].v->name << "(" << curr->adj[i].v->distance << ")" << " ";
      }
    }
    curr->visited = true;
  }

}

int Graph::getConnectedComponents()
{
  streambuf* orig_buf = cout.rdbuf();
  cout.rdbuf(NULL);
  int numComponents = 1;
  breadthFirstTraverse(vertices[0]->name);

  for (int i = 0; i < (int)vertices.size();i++)
  {
    if (vertices[i]->visited == false)
    {
      numComponents++;
      breadthFirstTraverse(vertices[i]->name);
    }
  }
  cout.rdbuf(orig_buf);
  return numComponents;
}

bool Graph::checkBipartite()
{
  streambuf* orig_buf = cout.rdbuf();
  cout.rdbuf(NULL);
  breadthFirstTraverse(vertices[0]->name);
  for (int i = 0; i < (int)vertices.size();i++)
  {
    if (vertices[i]->visited == false)
    {
      breadthFirstTraverse(vertices[i]->name);
    }
    if (vertices[i]->adj.size() > 2)
    {
      cout.rdbuf(orig_buf);
      return false;
    }
    for (int j = 0; j < (int)vertices[i]->adj.size(); j++)
    {
      if (vertices[i]->distance == vertices[i]->adj[j].v->distance)
      {
        cout.rdbuf(orig_buf);
        return false;
      }
    }
  }
  cout.rdbuf(orig_buf);
  return true;
}
