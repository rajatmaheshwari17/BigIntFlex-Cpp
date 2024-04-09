/*
Name - Rajat Maheshwari
Student Id - 1964136
Cruzid - ramahesh
Course - CSE 101 
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming Assignment - 6
Due Date - March 4, 2024
File Name - BigInteger.cpp
*/

#include <cctype>
#include <cmath>
#include <stdexcept>
#include "BigInteger.h"
#include "List.h"

using namespace std;

const ListElement BASE  = 1000000000;  
const int POWER = 9;

void removeZeros( List* L) {
    for(L->moveFront(); L->length() > 0 && !L->peekNext(); ) {
        L->eraseAfter();
    }
}

List tempList(long s, List *b, int* ctr) {
    List L;
    long carry = 0; long temp = 0;

    b->moveBack();
    while(b->position() > 0) {
        temp = (b->peekPrev() * s) + carry;
        carry = temp / BASE;
        temp %= BASE;
        L.insertAfter(temp);
        b->movePrev();
    }

    if (carry > 0) L.insertAfter(carry);
    L.moveBack();
    int i = 0;

    while(i < *ctr) {
        L.insertAfter(0);
        i++;
    }
    return L;
}

BigInteger::BigInteger() {
    digits = List();
    signum = 0;
}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
        return;
    }

   signum = (x < 0) ? -1 : (x > 0) ? 1 : 0;

    for (; x > 0; x /= BASE) {
        digits.insertBefore(x % BASE);
    }
}

BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    signum = 1;
    size_t start = 0;

    if (s[0] == '+' || s[0] == '-') {
        signum = (s[0] == '-') ? -1 : 1;
        start = 1;
        if (s.length() == 1) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    for (size_t i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    for (int i = s.length(); i > static_cast<int>(start); i -= POWER) {
        int len = (i - static_cast<int>(start) < POWER) ? i - static_cast<int>(start) : POWER;
        std::string numStr = s.substr(i - len, len);
        long num = std::stol(numStr, nullptr, 10);
        digits.insertAfter(num);
    }

    removeZeros(&digits);
}


BigInteger::BigInteger(const BigInteger& N) {
    digits = N.digits;
    signum = N.signum;
}

int BigInteger::sign() const{
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum) {
        return (signum > N.signum) ? 1 : -1;
    }

    if (signum == 0) {
        return 0;
    }

    int lengthA = digits.length();
    int lengthB = N.digits.length();

    if (lengthA != lengthB) {
        return (lengthA > lengthB) ? signum : -signum;
    }

    digits.moveFront();
    N.digits.moveFront();

    for (int i = 0; i < lengthA; i++) {
        ListElement elementA = digits.peekNext();
        ListElement elementB = N.digits.peekNext();
        
        if (elementA != elementB) {
            return (elementA > elementB) ? signum : -signum;
        }
        
        digits.moveNext();
        N.digits.moveNext();
    }

    return 0;
}

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum *= -1;
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger X = *this;
    BigInteger Y = N;
    BigInteger Z;

    if (X.sign() > 0 && Y.sign() < 0) {
        Y.negate();
        return X.sub(Y);
    }

    if (X.sign() < 0 && Y.sign() > 0) {
        X.negate();
        return Y.sub(X);
    }

    if (X.sign() < 0 && Y.sign() < 0) {
        X.negate();
        Y.negate();
        Z = X.add(Y);
        Z.negate();
        return Z;
    }

    if (X > Y) return Y.add(X);

    List x = X.digits;
    List y = Y.digits;
    List z = Z.digits;

    x.moveBack();
    y.moveBack();

    long carry = 0;
    long temp = 0;

    for (; x.position() > 0 && y.position() > 0; x.movePrev(), y.movePrev()) {
        temp = carry + x.peekPrev() + y.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        z.insertAfter(temp);
    }

    for (; y.position() > 0; y.movePrev()) {
        temp = carry + y.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        z.insertAfter(temp);
    }

    if (carry > 0) z.insertAfter(carry);

    Z.signum = 1;
    Z.digits = z;
    return Z;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;
    List a = A.digits;
    List b = B.digits;
    List c = C.digits;

    if (A == B) return C;

    if (A.sign() && !B.sign()) {
        A.negate();
        return A;  
    }

    if (!A.sign() && B.sign()) return B;

    if (A.sign() < 0 && B.sign() > 0) {
        B.negate();
        C = A.add(B);
        C.negate();
        return C;  
    }

    if (A.sign() > 0 && B.sign() < 0) {
        A.negate();
        C = A.add(B);
        return C;
    }

    if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        C = B.sub(A);
        C.negate();
        return C;  
    }

    if (A < B) {
        C = A.sub(B);
        C.negate();
        return C;  
    }

    long dist = 0;
    long temp = 0;
    a.moveBack();
    b.moveBack();

    for (int i = b.position(); i > 0; i--) {
        if (a.peekPrev() - dist < b.peekPrev()) {
            temp = a.peekPrev() + BASE - b.peekPrev() - dist;
            dist = 1;
        } else {
            temp = a.peekPrev() - dist - b.peekPrev();
            if (!(a.peekPrev() <= 0)) {
                dist = 0;
            }
        }
        c.insertAfter(temp);
        a.movePrev();
        b.movePrev();
    }

    for (; a.position() > 0; a.movePrev()) {
        if (a.peekPrev() - dist < 0) {
            temp = a.peekPrev() + BASE - dist;
            dist = 1;
        } else {
            temp = a.peekPrev() - dist;
            if (a.peekPrev() > 0) {
                dist = 0;
            }
        }
        c.insertAfter(temp);
    }

    C.digits = c;
    removeZeros(&(C.digits));  
    C.signum = -1;  
    return C;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger A = N; 
    BigInteger B = *this; 
    BigInteger C;

    List a = A.digits; 
    List b = B.digits;

    a.moveBack();
    b.moveBack();
    int p = a.position(); int ctr = 0;;
    int i = p;
    while (i > 0) {
        List temp = tempList(a.peekPrev(), &b, &ctr);
        BigInteger T;
        T.signum = 1;
        T.digits = temp;
        C += T;
        a.movePrev();
        ctr++;
        i--;
    }
    C.signum = A.signum * B.signum;  
    return C;
}

std::string BigInteger::to_string() {
    std::string out = "";
    if (this->signum == 0) return "0";
    if (signum == -1) out += "-";
    digits.moveFront();

    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string A = std::to_string(digits.peekNext());
        std::string B = "";
    
        while ((int)(B.length() + A.length()) < POWER && digits.position() != 0) {
            B += '0';
        }
        out += (B + A);
    }
    return out;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator!=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) != 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) < 0;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) > 0;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) >= 0;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    BigInteger I = A.sub(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    BigInteger I = A.mult(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A;
}