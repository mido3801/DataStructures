# DataStructures
Code from Data Structures Assignments  

Final project is a program which takes two sets of integers and compares the efficacy of various hash collision resolution techniques. 
- Linear Probing
- Linked List Chaining
- Binary Search Tree Chaining
- Cuckoo Hashing  
  
Items from the datasets are hashed until the tables reach varying load factors, at which point timepoints of the insert, lookup, and delete functions for each collision resolution method are obtained. These timepoints are output to a csv file along with a record of how many items have been hashed. In the case of cuckoo hashing we instead output the number of times our table had to be rehashed.
