/*
Name - Rajat Maheshwari
Student Id - 1964136
Cruzid - ramahesh
Course - CSE 101 
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming Assignment - 6
Due Date - March 4, 2024
File Name - ListTest.cpp
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main() {
    List D, E, F;

    cout << "Testing Constructors and Destructor on a new List" << endl;

    for(int i = 100; i >= 20; i -= 20) {
        D.insertAfter(i);
    }
    cout << "D = " << D << endl;
    cout << "Length of D: " << D.length() << endl;
    cout << "Front of D: " << D.front() << endl;
    cout << "Back of D: " << D.back() << endl;

    D.moveFront();
    cout << "Position of cursor in D: " << D.position() << endl;
    D.moveNext();
    cout << "Element after cursor in D: " << D.peekNext() << endl;
    cout << "Element before cursor in D: " << D.peekPrev() << endl << endl;

    cout << "Testing Manipulation Procedures on D" << endl;
    D.clear();
    cout << "D after clear: " << D << endl;

    for(int i = 20; i <= 100; i += 20) {
        D.insertBefore(i);
    }
    cout << "D after inserts: " << D << endl;
    D.moveBack();
    cout << "Position of cursor in D after moveBack: " << D.position() << endl;
    cout << "Element before cursor in D: " << D.peekPrev() << endl;

    D.movePrev();
    cout << "Element passed over by movePrev: " << D.movePrev() << endl;
    cout << "D after movePrev: " << D << endl;
    D.setBefore(200);
    cout << "D after setBefore: " << D << endl;
    D.eraseBefore();
    cout << "D after eraseBefore: " << D << endl << endl;

    cout << "Testing Other Functions on new Lists" << endl;
    E = D;
    cout << "E = " << E << endl;
    cout << "D==E is " << (D==E ? "true" : "false") << endl;
    F = D.concat(E);
    cout << "F = " << F << endl;
    F.cleanup();
    cout << "F after cleanup: " << F << endl;

    return 0;
}

/*
Expected Output -
Testing Constructors and Destructor on a new List
D = (20, 40, 60, 80, 100)
Length of D: 5
Front of D: 20
Back of D: 100
Position of cursor in D: 0
Element after cursor in D: 40
Element before cursor in D: 20

Testing Manipulation Procedures on D
D after clear: ()
D after inserts: (20, 40, 60, 80, 100)
Position of cursor in D after moveBack: 5
Element before cursor in D: 100
Element passed over by movePrev: 80
D after movePrev: (20, 40, 60, 80, 100)
D after setBefore: (20, 40, 200, 80, 100)
D after eraseBefore: (20, 40, 80, 100)

Testing Other Functions on new Lists
E = (20, 40, 80, 100)
D==E is true
F = (20, 40, 80, 100, 20, 40, 80, 100)
F after cleanup: (20, 40, 80, 100)
*/