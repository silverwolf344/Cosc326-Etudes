#include <iostream>
#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

int main(int argc, const char * argv[]) {
	// insert code here...
	fflush(stdin);
	fflush(stdout);
	std::cout << "Kia ora!\n";
	
 	Integer myint = Integer(637285);
	Integer myint2 = Integer(482950);
	
	std::cout<<"MyInt to string test:"<<myint<< std::endl;
	/*std::cout<<"MyInt2 to string test:"<<myint2<< std::endl;
	std::cout<<"myint == myint2: "<<(myint == myint2)<< std::endl;
	std::cout<<"Correct Answer: 0"<< std::endl;
	Integer myint3 = myint - myint2;
	std::cout<<"myint - myint2 = "<<(myint3)<< std::endl;
	myint3 = myint + myint2;
	std::cout<<"myint + myint2 = "<<(myint3)<< std::endl;
	myint3 = myint / myint2;
	std::cout<<"MyInt : "<<myint<< std::endl;
	std::cout<<"MyInt2: "<<myint2<< std::endl;
	std::cout<<"myint / myint2 = "<<(myint3)<< std::endl;
	std::cout<<"Correct Answer:  56"<< std::endl;;
	myint3 = myint % myint2;
	std::cout<<"myint % myint2 = "<<(myint3)<< std::endl;*/
	Integer myint3 = myint * myint2;
	std::cout<<"myint * myint2 = "<<(myint3)<< std::endl;

	Rational myrat = Rational("1/2");
	Rational myrat2 = Rational("2/34");
	Rational myrat3 = myrat - myrat2;
	std::cout<<"MyRat : "<<myrat<< std::endl;
	std::cout<<"MyRat2: "<<myrat2<< std::endl;
	std::cout<<"myrat - myrat2 = "<<(myrat3)<< std::endl;
	return 0;
}
