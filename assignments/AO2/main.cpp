/**
*  Course: CMPS 2143 - OOP
*  Assignment: A02
*  Purpose: Create 2 lists, add them together, and print various values.
* 
*  @author Griffin Forsgren
*  @version 1.1 01/03/17
*/

#include <iostream>

using namespace std;

int A[100];

struct Node
{
    int val_1;
    Node *next;
     /**
     *  Initializes an empty Node
     *
     *  @param n/a
     *  @return n/a
     */

    Node()
    {
        val_1 = -1;
        next = NULL;
    }
    /**
     *  Initializes a Node with an int
     *
     *  @param {int} entry value in the node
     *  @return n/a
     */
    Node(int entry)
    {
        val_1 = entry;
        next = NULL;
    }
};

class List
{
  private:
    Node *Head;
    Node *Tail;
    int Size;

  public:
    /**
     *  Initializes an empty List
     *
     *  @param n/a
     *  @return n/a
     */
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
    /**
     *  Pushes a node with a value onto the end of a list
     *
     *  @param {int} val of the node pushed on
     *  @return n/a
     */

    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
    /**
     *  Inserts a node into a list
     *
     *  @param {int} val of the insterted node
     *  @return n/a
     */

    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }
    /**
     *  Prints the tail node of the list
     *
     *  @param n/a
     *  @return n/a
     */
    void PrintTail()
    {
        cout << Tail-> val_l << endl;
    }
    /**
    *  Prints every value of the list
    *
    *  @param n/a
    *  @return {string} list string of values in the list
    */
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->val_1) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented 
    /**
    *  Prints the tail node of the list
    *
    *  @param n/a
    *  @return {int} val_2 value of the popped node
    */
    int Pop()
    {
        Size--;
        return 0; //
    }
     /**
     *  Combines two lists
     *
     *  @param {List} Rhs the right hand list
     *  @return {List} NewList the sum of the two lists
     */

    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
     /**
     *  takes ints from list as though it were array
     *
     *  @param {int} index index number of supposed array
     *  @return {int} temp_>val_1 value at index
     */
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->val_1;
        }
    }
    
    /**
     *  Establishes ostream operator & as a friend
     *
     *  @param {ostream} os {List} L output stream and list
     *  @return {ostream} os output now friended with List
     */
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

//Controls operation of the program
int main(int argc, char **argv)
{
    List L1;
    List L2;
    //for i starting at 0, going up to 25 by ones
    for (int i = 0; i < 25; i++)
    {
        //push value of i onto L1
        L1.Push(i);
    }
    //for i starting at 50, going up to 100 by ones
    for (int i = 50; i < 100; i++)
    {
        //push value of i onto L2
        L2.Push(i);
    }

    //cout << L1 << endl;
    //Print the tails of bot L1 and L2
    L1.PrintTail();
    L2.PrintTail();
    
    //List L3 is the combination of L1 and L2
    List L3 = L1 + L2;
    
    //Print L3 and 5th node
    cout << L3 << endl;
    cout << L3[5] << endl;
    return 0;
}
