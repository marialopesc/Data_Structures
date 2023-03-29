///* Header:
// * author/student: Maria Bezerra
// * netID: 676493398
// * course: CS 251 - spring 2023
// * assignment: Shapes

#pragma once

#include "shape.h"
#include <iostream>

using namespace std;

class ShapeNode
{
    public:
        Shape *value;
        ShapeNode *next;
};

class CanvasList
{
    private:
        int listSize;
        ShapeNode *listFront;

    public:
    // default constructor
    CanvasList(){
            listSize = 0;
            listFront = nullptr;
        }

        // copy constructor
        CanvasList(const CanvasList & other);

        // assignment operator
        CanvasList operator=(const CanvasList & other){
            clear();

            ShapeNode* temp = other.listFront;
            while (temp != nullptr) {
                push_back(temp->value->copy());
                temp = temp->next;
            }
            return *this;
        }

        //used to delete all the nodes in the linked list. The clear() function is called to delete each node in the linked list
        virtual ~CanvasList(){
            clear();
        }

        void clear();
        
        void insertAfter(int, Shape *shape);
        void push_front(Shape *shape);
        void push_back(Shape *shape);
        
        void removeAt(int);
        Shape* pop_front();
        Shape* pop_back();

        ShapeNode* front() const;
        bool isempty() const;
        int size() const;

        int find(int x, int y) const;
        Shape* shapeAt(int) const;
        
        void draw() const;
        void printAddresses() const;
};

/*
 * These are used to create a deep copy of an existing CanvasList object. The copy constructor
 * initializes a new CanvasList object with the contents of another CanvasList object, and the
 * assignment operator overload assigns the contents of another CanvasList object to an existing
 * CanvasList object. Both functions use the push_back() function to copy the contents of the linked list.
 */
CanvasList::CanvasList(const CanvasList &other):CanvasList(){
    ShapeNode* temp = other.listFront;
    while (temp != nullptr) {
        push_back(temp->value->copy());
        temp = temp->next;
    }
}

void CanvasList::clear() {        // function to clear the list
    while (listFront != NULL) {
        ShapeNode *temp = listFront;
        listFront = listFront->next;
        delete temp->value;
        delete temp;
    }
    listSize = 0;
}

void CanvasList::insertAfter(int index, Shape *shape) {        // function to insert a Shape object after a specific index
    ShapeNode *temp = listFront;

    if(index < 0){
        return;
    }
    if(index >= listSize){
        return;
    }

    for (int i = 0; i < index && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        push_back(shape);
        return;
    }
    ShapeNode *newNode = new ShapeNode();
    newNode->value = shape;
    newNode->next = temp->next;
    temp->next = newNode;
    listSize++;
}

void CanvasList::push_front(Shape *shape) {        // function to push a Shape object to the front of the list
    ShapeNode *newNode = new ShapeNode();
    newNode->value = shape;
    newNode->next = listFront;
    listFront = newNode;
    listSize++;
}

void CanvasList::push_back(Shape *shape) {        // function to push a Shape object to the back of the list
    ShapeNode *newNode = new ShapeNode();
    newNode->value = shape;
    newNode->next = NULL;
    if (listFront == NULL) {
        listFront = newNode;
    } else {
        ShapeNode *temp = listFront;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    listSize++;
}

void CanvasList::removeAt(int index) {        // function to remove a Shape object at a specific index
    ShapeNode *temp = listFront;

    if(index < 0){
        return;
    }
    if(index >= listSize){
        return;
    }

    if (index == 0) {
        listFront = temp->next;
        delete temp->value;
        delete temp;
        listSize--;
        return;
    }
    for (int i = 0; i < index-1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        return;
    }
    ShapeNode *toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete->value;
    delete toDelete;
    listSize--;
}


Shape *CanvasList::pop_front() {         // function to remove and return the Shape object at the front of the list
    if (listFront == NULL) {
        return NULL;
    }
    Shape *result = listFront->value;
    ShapeNode *temp = listFront;
    listFront = listFront->next;
    delete temp;
    listSize--;
    return result;
}

Shape *CanvasList::pop_back() {        // function to remove and return the Shape object at the back of the list
    if (listFront == NULL) {
        return NULL;
    }
    Shape *result;
    if (listFront->next == NULL) {
        result = listFront->value;
        delete listFront;
        listFront = NULL;
    } else {
        ShapeNode *temp = listFront;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        result = temp->next->value;
        delete temp->next;
        temp->next = NULL;
    }
    listSize--;
    return result;
}

ShapeNode* CanvasList::front() const {        // function to return a pointer to the front of the list
    return listFront;
}

bool CanvasList::isempty() const {       // function to check if the list is empty
    return (listSize == 0);
}

int CanvasList::size() const {        // function to return the size of the list
    return listSize;
}

int CanvasList::find(int x, int y) const {        // function to find the index of a Shape object with specific coordinates
    int index = -1;
    int i = 0;
    ShapeNode *temp = listFront;
    while (temp != NULL) {
        if (temp->value->getX() == x && temp->value->getY() == y) {
            index = i;
            return index;
        }
        temp = temp->next;
        i++;
    }
    return index;
}

Shape* CanvasList::shapeAt(int index) const {        // function to return a pointer to a Shape object at a specific index
    if(index < 0 || index >= listSize){
        return nullptr;
    }
    ShapeNode *temp = listFront;

    for (int i = 0; i < index && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return NULL;
    } else {
        return temp->value;
    }
}

void CanvasList::draw() const {        // function to draw all the Shape objects in the list
    ShapeNode *temp = listFront;
    while (temp != NULL) {
        temp->value->printShape();
        temp = temp->next;
    }
}

void CanvasList::printAddresses() const {        // function to print the addresses of all the Shape objects in the list
    ShapeNode *temp = listFront;
    while (temp != NULL) {
        cout << temp->value << endl;
        temp = temp->next;
    }
}




