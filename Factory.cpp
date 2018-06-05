//============================================================================
// Name        : Factory.cpp
// Author      : Filip Przybysz
// Version     :
// Copyright   : Open Source
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CarAssemblyLine.hpp"
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	conveyor<tire> CT;
	conveyor<bodyEngine> CE;
	productionSite<tire> PT;
	productionSite<tire> PTT;
	auto& ptr=PT, pttr=PTT;
	auto& ctr=CT;
	auto& cer=CE;

	connect(cer, ptr, pttr);
	cout<<cer.size()<<endl;
	ptr.run();
	cout<<cer.size()<<endl;

	return 0;
}
