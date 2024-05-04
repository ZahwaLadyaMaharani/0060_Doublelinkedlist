#include <iostream>
#include <string>
using namespace std;
struct Node
{
    int noMhs;
    string name;
    Node* next;
    Node* prev;
};
Node* START = NULL;

void addNode() {
    Node* newNode = new Node(); // step 1: create a new node
    cout << "\nEnter the roll number of the student:";
    cin >> newNode->noMhs; // assign value to the rollNumber field of the new node 
    cout << "\nEnter the name of the student:";
    cin >> newNode->name; // assign value to the name field of the new node

    if (START == NULL || newNode->noMhs <= START->noMhs) {
        // Step 2: insert the new node
        if (START != NULL && newNode->noMhs == START->noMhs) {
            cout << "\033[31mDuplicate roll number not allowed\033[0m" << endl;
            return;
        }
        // If the list is empty, make the new node the START
        newNode->next = START; // Step 3: make the new node point to the first node
        if (START != NULL) {
            START->prev = newNode; // Step 4: make the first node point to the new node

        }
        newNode->prev = NULL; // Step 5: make the new node point to NULL
        START = newNode; // Step 6: make the new node the first node

    }
    else {
        // Insert the new node in the middle or at the end
        Node* current = START; // Step 1.a: start from the first node
        Node* previous = NULL; // Step 1.b: previous node is Null Initiality

        while (current != NULL && current->noMhs < newNode->noMhs) { // Step 1.c: traverse
            previous = current; // Step 1.d: move the previous to the current node
            current = current->next; // Step 1.e: move the current to the next node
        }
        newNode->next = current; // Step 4: make the next field of the new node point
        newNode->prev = previous; // Step 5: make the previous field of the new node point

        if (current != NULL) {
            current->prev = newNode; // Step 6: make the previous field of the current point to the new node
        }
        if (previous != NULL) {
            previous->next = newNode; // Step 7: make the next field of the previous node point to the new node
        }
        else {
            // If previous is still NULL, it means newNode is now the first node
            START = newNode;
        }
    }
}

bool search(int rollNo, Node** previous, Node** current)
{
    *previous = NULL;
    *current = START;
    while (*current != NULL && (*current)->noMhs != rollNo)
    {
        *previous = *current;
        *current = (*current)->next;
    }
    return (*current != NULL);
}
void deleteNode()
{
    Node* previous, * current; //
    int rollNo;

    cout << "\nEnter the roll number of the student whose record is to be deleted:  ";
    cin >> rollNo; // step 3: get the roll number to be deleted

    if (START == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    current = START; //step 1: start from the first node
    previous = NULL;

    //locate the node to be deleted
    while (current != NULL && current->noMhs != rollNo)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "\033[31mThe record with roll number" << rollNo << " not found\033[0m" << endl;
        return;
    }
    // Node to be deleted is the first node
    if (current == START)
    {
        START = START->next; //step 2: update the START pointer
        if (START != NULL)
        {
            START->prev = NULL; //  Step 3: make the new node point to the first node
        }
    }
    else
    {
        // Node to be deleted is not the first node
        previous->next = current->next;
        if (current->next != NULL)
        {
            // if there's a seccessor, update its prev pointer
            current->next->prev = previous;

        }
    }
    // Release the memory of the node marked as current
    delete current;
    cout << "\x1b[32mRecord with roll number " << rollNo << "deleted\x1b[0m" << endl;

}

bool listEmpty()
{
    return (START == NULL);
}

void traverse()
{
    if (listEmpty())
        cout << "\nList is empty" << endl;
    else
    {
        cout << "\nRecords in ascending order of roll number are:" << endl;
        Node* currentNode = START; //step 1
        while (currentNode != NULL) // step 2
        {
            cout << currentNode->noMhs << " " << currentNode->name << endl; // step 3
            currentNode = currentNode->next;                               // step 4

        }
    }
}
void revtraverse()
{
    if (listEmpty())
        cout << "\nList is empty" << endl;
    else
    {
        cout << "\nRecords in descending order of roll number are:" << endl;
        Node* currentNode = START;
        while (currentNode->next != NULL)
            currentNode = currentNode->next;
        while (currentNode != NULL)
        {
            cout << currentNode->noMhs << " " << currentNode->name << endl;
            currentNode = currentNode->prev;
        }
    }
}
void searcData()
{
    if (listEmpty() == true)
    {
        cout << "\nList is empty" << endl;
    }
    Node* prev, * curr;
    prev = curr = NULL;
    cout << "\nEnter the roll number student whose record you want to serrch:";
    int num;
    cin >> num;
    if (search(num, &prev, &curr) == false)
        cout << "\nRecord not found" << endl;
    else
    {
        cout << "\nRecord found" << endl;
        cout << "\nRecord number: " << curr->noMhs << endl;
        cout << "\nName:" << curr->name << endl;
    }
}
int main()
{
    while (true)
    {
        try
        {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. view all records in the ascesding of roll numbers" << endl;
            cout << "4. view all record in the descending ordr of roll number" << endl;
            cout << "5. search for a record in the list" << endl;
            cout << "6. exit" << endl;
            char ch;
            cin >> ch;
            switch (ch)
            {
            case '1':
                addNode();
                break;
            case '2':
                deleteNode();
                break;
            case '3':
                traverse();
                break;
            case '4':
                revtraverse();
                break;
            case '5':
                searcData();
                break;
            case '6':
                return 0;
            default:
                cout << "\nInvalid option" << endl;
                break;
            }

        }
        catch (exception& e)
        {
            cout << "check for the values entered." << endl;
        }
    }
}