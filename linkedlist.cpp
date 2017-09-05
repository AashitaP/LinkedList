#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef string ItemType;

struct Node {
    ItemType value;
    Node *next;
};

class LinkedList {
    
private:
    Node *head;
    
public:
    
    // default constructor
    LinkedList() : head(nullptr) {;}
    
    // copy constructor
    LinkedList(const LinkedList& rhs)
    {
        head = nullptr;
        Node* p = nullptr;
        Node* other = rhs.head;
        while (other != nullptr)
        {
            Node* newNode = new Node; //dynamically allocate new Nodes to form a list
            newNode -> next = nullptr;
            newNode -> value = other -> value;
            if (p != nullptr)
                p -> next = newNode;
            if (head == nullptr)
                head = newNode;
            p = newNode;
            other = other -> next;
        }
    }
    
    // Destroys all the dynamically allocated memory
    // in the list.
    ~LinkedList()
    {
        
        for (Node *n = head; n!= nullptr;)
        {
            Node* temp = n;
            n = n-> next;
            delete temp;
        }
    }
    
    // assignment operator
    const LinkedList& operator=(const LinkedList& rhs)
    {
        if (this == &rhs)
            return *this;
        LinkedList copy = LinkedList(rhs);
        this -> swap(copy); //swaps heads of linked lists
        return *this;
    }
    
    // Inserts val at the front of the list
    void insertToFront(const ItemType &val)
    {
        
        Node* newNode = new Node;
        newNode -> value = val;
        newNode -> next = head;
        head = newNode;
        
    }
    
    // Prints the LinkedList
    void printList() const
    {
        
        for (Node* n = head; n != nullptr; n = n-> next)
            cout << n->value << " ";
        cout << endl;
        
    }
    
    // Sets item to the value at position i in this
    // LinkedList and return true, returns false if
    // there is no element i
    bool get(int i, ItemType& item) const
    {
        int count = 0;
        for (Node *n = head; n != nullptr; n = n-> next)
        {
            if (count == i)
            {
                item = n->value;
                return true;
            }
            count++;
        }
        return false;
    }
    
    
    // Reverses the LinkedList
    void reverseList()
    {
        Node* current = head;
        Node* prev = nullptr;
        
        while (current != nullptr)
        {
            Node* temp = current;
            current = current -> next;
            temp -> next = prev; //reverses list by setting next pointer to prev
            prev = temp;
        }
     
        head = prev;
    }
    
    // Prints the LinkedList in reverse order
    void printReverse() const
    {
        
        LinkedList copy = LinkedList(*this); //create a copy
        Node* current = copy.head;
        Node* prev = nullptr;
        
        while (current != nullptr) //reverse copy
        {
            Node* temp = current;
            current = current -> next;
            temp -> next = prev;
            prev = temp;
        }
        copy.head = prev;
        copy.printList(); //print copy
    }
    
    // Appends the values of other onto the end of this
    // LinkedList.
    void append(const LinkedList &other)
    {
        
        Node* n = head;
        while (n != nullptr)
        {
            if (n -> next == nullptr)
                break;
            n = n-> next;
        }
        
        int appendsize = other.size();
        Node* appendhead = other.head;
        for (int i = 0; i < appendsize; i++) //iterate through list
        {
            Node* newNode = new Node; //dynamically allocate new nodes to form a list
            newNode -> next = nullptr;
            newNode -> value = appendhead -> value; //using values from other list
            n->next = newNode;
            n = n-> next;
            appendhead = appendhead->next;
        }
    }
    
    // Exchange the contents of this LinkedList with the other one.
    void swap(LinkedList &other)
    {
        std::swap(head, other.head);
    }
    
    // Returns the number of items in the Linked List.
    int size() const
    {
        int count = 0;
        for (Node* n = head; n != nullptr; n = n-> next)
            count++;
        return count;
    }
};


int main()
{
    LinkedList ls;
    ls.insertToFront("d");
    ls.insertToFront("c");
    ls.insertToFront("b");
    ls.insertToFront("a");
    
    for (int k = 0; k < ls.size(); k++)
    {
        string x;
        ls.get(k, x);
        cout << x << endl; // a b c d
    }
    
    LinkedList ls2;
    ls2.insertToFront("d");
    ls2.insertToFront("c");
    ls2.insertToFront("b");
    ls2.insertToFront("a");
    
    ls2.printList(); //abcd
    ls2.printReverse(); //dcba
    
    
    LinkedList e1;
    e1.insertToFront("5");
    e1.insertToFront("4");
    e1.insertToFront("3");
    LinkedList e2;
    e2.insertToFront("2");
    e2.insertToFront("1");
    e1.append(e2);  // adds contents of e2 to the end of e1
    string s;
    assert(e1.size() == 5 && e1.get(4,s) && s == "2");
   
    LinkedList e3;
    e3.insertToFront("Sam");
    e3.insertToFront("Carla");
    e3.insertToFront("Cliff");
    e3.insertToFront("Norm");
    
    e3.reverseList();  // reverses the contents of e1
    string j;
    assert(e3.size() == 4  &&  e3.get(0, j)  &&  j == "Sam");
    
    LinkedList e4;
    e4.insertToFront("A");
    e4.insertToFront("B");
    e4.insertToFront("C");
    e4.insertToFront("D");
    LinkedList e5;
    e5.insertToFront("X");
    e5.insertToFront("Y");
    e5.insertToFront("Z");
    e5.swap(e4);  // exchange contents of e5 and e4
    string q;
    assert(e4.size() == 3  &&  e4.get(0, q)  &&  q == "Z");
    assert(e5.size() == 4  &&  e5.get(2, q)  &&  q == "B");
    
    LinkedList pls;
    pls.insertToFront("so");
    pls.insertToFront("lmao");
    pls.insertToFront("okay");
    e4 = pls;
    e4.printList(); //okay lmao so
    
    LinkedList ugh(pls); //copy construct
    ugh.printList(); //okay lmao so
    
    ugh = ugh; //check assigning to self
    ugh.printList(); //okay lmao so
    
    ugh = e5;
    
    ugh.reverseList();
    ugh.printList(); //a b c d
    
    string okay;
    if(!ugh.get(4, okay)) //to check if it returns false
        cout << "okay";

    ugh.append(pls);
    ugh.printList(); //a b c d okay lmao so
    
    ugh.swap(pls);
    cout << ugh.size(); //3
    
    ugh.append(ugh);
    ugh.printList(); //okay lmao so okay lmao so
    cout << ugh.size() << endl; //6
    
    ugh.append(ugh);
    string check;
    ugh.get(8, check);
    cout << check << endl; //so
    
    ugh.printReverse(); //so lmao okay x4
}
