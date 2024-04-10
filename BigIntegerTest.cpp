#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "12345678901234567890";
   string s2 = "234567890123456789012";
   string s3 = "3456789012345678901234";
   string s4 = "45678901234567890123456";
   string s5 = "-2345678901234567890123";

   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);
   BigInteger C = BigInteger(s3);
   BigInteger D = BigInteger(s4);
   BigInteger E = BigInteger(s5);

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl << endl;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << "A+B = " << A+B << endl;
   cout << "B-A = " << B-A << endl;
   cout << "C*D = " << C*D << endl << endl;

   cout << "A+E = " << A+E << endl;
   cout << "B-E = " << B-E << endl;
   cout << "C*E = " << C*E << endl << endl;

   cout << "A*A = " << A*A << endl;
   cout << "B*71 = " << B*71 << endl;
   cout << "A * A * A * A * 9 + B * B * B * B * B * 16 = " << A * A * A * A * 9 + B * B * B * B * B * 16 << endl << endl;

   cout << "A*B*C*D*E = " << A*B*C*D*E << endl;
   return EXIT_SUCCESS;
}

/*
Expected Output -
A = 12345678901234567890
B = 234567890123456789012
C = 3456789012345678901234
D = 45678901234567890123456
E = -2345678901234567890123

(A==B) = False
(A<B)  = True
(A<=B) = True
(A>B)  = False
(A>=B) = False

A+B = 246913569024691356902
B-A = 222222211222222221122
C*D = 157902323883677749535127858622125910690744704

A+E = -2333333222333333322233
B-E = 2580246791358024679135
C*E = -8108517052278739222371751562832496281111782

A*A = 152415787532388367501905199875019052100
B*71 = 16654320198765432019852
A * A * A * A * 9 + B * B * B * B * B * 16 = 11362209434436691455117861900339387975756817817762183243204831443907436355625899817118352546846849991312

A*B*C*D*E = -1072606987581381872560756346946476585467653122414055973697202445313426700101487303550785712096669034050560
*/
