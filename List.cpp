/*
Name - Rajat Maheshwari
Student Id - 1964136
Cruzid - ramahesh
Course - CSE 101 
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming Assignment - 6
Due Date - March 4, 2024
File Name - List.cpp
*/

#include "List.h"
#include <iostream>
#include <set>
#include <stdexcept>

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

List::List() : frontDummy(new Node(0)), backDummy(new Node(0)), pos_cursor(0), num_elements(0) {
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
}

List::List(const List& L) : List() {
    Node* node = L.frontDummy->next;
    while (node != L.backDummy) {
        insertBefore(node->data);
        moveNext();
        node = node->next;
    }
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (length() <= 0) {
        throw std::out_of_range("List::front() called on an empty list.");
    }
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (length() <= 0) {
        throw std::out_of_range("List::back() called on an empty list.");
    }
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::out_of_range("List::peekNext() called at the end of the list.");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (position() <= 0) {
        throw std::out_of_range("List::peekPrev() called at the beginning of the list.");
    }
    return beforeCursor->data;
}

void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}

void List::moveFront() const {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
}

void List::moveBack() const {
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = afterCursor->prev;
}

ListElement List::moveNext() const {
    if (position() >= (num_elements)) {
        return ListElement();
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() const {
    if (position() <= 0) {
        throw std::out_of_range("List::movePrev() called at the beginning of the list.");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    afterCursor = newNode;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    beforeCursor = newNode;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (position() < length()) {
        afterCursor->data = x;
    } else {
        throw std::out_of_range("List::setAfter() called at the end of the list.");
    }
}

void List::setBefore(ListElement x) {
    if (position() > 0) {
        beforeCursor->data = x;
    } else {
        throw std::out_of_range("List::setBefore() called at the beginning of the list.");
    }
}

void List::eraseAfter() {
    if (position() >= length()) {
       throw std::out_of_range("List::eraseAfter() called at the end of the list.");
    }
    Node* temp = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete temp;
    num_elements--;
}

void List::eraseBefore() {
    if (position() <= 0) {
        throw std::out_of_range("List: eraseBefore(): cursor at front");
    }
    Node* temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete temp;
    num_elements--;
    pos_cursor--;
}

int List::findNext(ListElement x) {
    Node* temp = afterCursor;
    int r = 1;
    while (temp != backDummy) {
        if (temp->data == x) {
            beforeCursor = temp;
            afterCursor = temp->next;
            pos_cursor += r;
            return pos_cursor;
        }
        temp = temp->next;
        r++;
    }
    afterCursor = backDummy;
    beforeCursor = afterCursor->prev;
    pos_cursor = length();
    return -1;
}

int List::findPrev(ListElement x) {
    Node* temp = beforeCursor;
    int l = 1;
    while (temp != frontDummy) {
        if (temp->data == x) {
            afterCursor = temp;
            beforeCursor = temp->prev;
            pos_cursor -= l;
            return pos_cursor;
        }
        temp = temp->prev;
        l++;
    }
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
    pos_cursor = 0;
    return -1;
}

void List::cleanup() {
    Node* current = frontDummy->next;
    int outer_pos = 0;

    while (current != backDummy) {
        Node* runner = current->next;
        int inner_pos = outer_pos + 1;

        while (runner != backDummy) {
            if (runner->data == current->data) {
                Node* toDelete = runner;
                runner = runner->next;

                toDelete->prev->next = runner;
                runner->prev = toDelete->prev;

                delete toDelete;
                num_elements--;

                if (inner_pos <= pos_cursor) {
                    pos_cursor--;
                }
            } else {
                runner = runner->next;
            }
            inner_pos++;
        }
        outer_pos++;
        current = current->next;
    }

    Node* temp = frontDummy->next;
    int temp_pos = 0;
    while (temp_pos < pos_cursor && temp != backDummy) {
        temp = temp->next;
        temp_pos++;
    }
    beforeCursor = temp->prev;
    afterCursor = temp;
}

List List::concat(const List& L) const{
    List newList;
    newList.moveBack();
    Node* New;

    New = frontDummy->next;
    while(New != backDummy){
        newList.insertBefore(New->data);
        New = New->next;
    }
   
    New = L.frontDummy->next;
    while(New != L.backDummy){
        newList.insertBefore(New->data);
        New = New->next;
    }
    newList.beforeCursor = newList.frontDummy;
    newList.afterCursor = newList.beforeCursor->next;
    newList.pos_cursor = 0;
    return newList;
}



std::string List::to_string() const {
    std::string str = "(";
    Node* temp = frontDummy->next;
    while (temp != backDummy) {
        str += std::to_string(temp->data);
        if (temp->next != backDummy) {
            str += ", ";
        }
        temp = temp->next;
    }
    str += ")";
    return str;
}

bool List::equals(const List& R) const {
    bool equal = (this->num_elements == R.num_elements);
    Node* thisTemp = this->frontDummy->next;
    Node* rTemp = R.frontDummy->next;
    while (equal && thisTemp != this->backDummy) {
        if (thisTemp->data != rTemp->data) {
            equal = false;
        }
        thisTemp = thisTemp->next;
        rTemp = rTemp->next;
    }
    return equal;
}

std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        clear();
        for (Node* node = L.frontDummy->next; node != L.backDummy; node = node->next) {
            insertBefore(node->data);
            moveNext();
        }
    }
    return *this;
}
