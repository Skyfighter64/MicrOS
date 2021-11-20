#ifndef LIST_H
#define LIST_H

/**
  List object providing a memory-friendly way to store objects of type T
  Notes:
  - new Elements will be added at the beginnig of the list (like a stack, for performance reasons)
  - getNextPtr() can be used to iterate the list efficiently. However, it should not be reused within
    the iterating loop.
*/
template <class T>
class List
{
private:

  class ListNode
  {
  public:
    ListNode(T value) : value(value), next(nullptr) {}
    ListNode * next;
    T value;
  };
  //the root node of the list
  ListNode * root;
  //the previous element of the iteration with getNext()
  ListNode * previous;

public:
  /*
    default constructor
  */
  List(){}

  /*
    constructor for initializing the list with the given values
    Note: An initializer-list would be better but the Arduino Environment has no support for cpp stl
    (Third party versions need too much Memory or are buggy)
  */
  List(size_t size, T items[])
  {
      for(int i = 0; i < size; i++)
      {
        add(items[i]);
      }
  }

  /*
    destructor deleting all nodes of the list
  */
  ~List()
  {
    //remove all items from the list by chopping of the head until the
    //list is empty ;)
    while(root != nullptr)
    {
      //get the next node after the root node
      ListNode * nextNode = root->next;
      //delete the root element
      delete root;
      //set the next element to the root
      root = nextNode;
    }
  }

  // add a new element to the front of the list (bc. its easier then adding it to the back)
  void add(T value)
  {
    //create a new node and apply the new value to it
    ListNode * node = new ListNode(value);

    //put the new node at the first place of the list
    node->next = root;
    root = node;
  };

  //remove the first element with this value
  void remove(T value)
  {
    //iterate trough the List
    T * currentItemPtr = getFirstPtr();

    //check if the first element is the oe which should be deleted
    if(*currentItemPtr == value)
    {
        //delete the first element
        ListNode * newRoot = root->next;
        delete root;
        root = newRoot;
    }
    while(currentItemPtr != nullptr)
    {
      //check if the next item is the one which should be removed
      if(previous->next->value == value)
      {
          //temporarily store the new next element (next of next)
          ListNode * newNext = previous->next->next;

          //remove the next item
          delete previous->next;

          //set the pointer to skip the deleted element
          previous->next = newNext;

          //reset the previous element so it can be reused for iteration outside
          //this function
          previous = nullptr;
          return;
      }
      //iterate to the next item in the list
      currentItemPtr = getNextPtr();
    }
  };


  //get a pointer to the first element of the list
  //use this at the start of an iteration
  T * getFirstPtr()
  {
    previous = root;
    return root == nullptr? nullptr : &root->value;
  }

  // get a pointer to the next item in the list;
  // this can be used to iterate the list
  // returns a nullptr if the next item is the end of the list, or the root element on
  // its first call
  T * getNextPtr()
  {
    if(previous == nullptr)
    {
      //there is no previous iteration element
      //return the root element
      previous = root;
      return &root->value;
    }

    //move the iteration pointer to the next element
    previous = previous->next;
    //return the value of the next element or null if the end of the list was reached
    return previous == nullptr ? nullptr : &previous->value;

  }
  //function returning if the list is empty
  bool isEmpty()
  {
    return root == nullptr;
  }

  //function retuning the number of elements in the list with the same value as the given one
  int count(T value)
  {
    T * element = getFirstPtr();
    int count = 0;

    while (element != nullptr)
    {
      if(element == value)
      {
        count ++;
      }
      element = getNextPtr();
    }
    return count;
  }

  //function returning if the list contains the given element
  bool contains(T value)
  {
    return count(value) != 0;
  }

};

#endif
