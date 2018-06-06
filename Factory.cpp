//============================================================================
// Name        : Factory.cpp
// Author      : Filip Przybysz
// Version     :
// Copyright   : Open Source
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<vector>
#include<iostream>
#include "CarAssemblyLine.hpp"
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
/*
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
*/

vector<node*> Nodes;
Nodes.reserve(17);
for (int i=0; i<4; i++) Nodes.emplace_back(new productionSite<tire>);           //0-3
for (int i=0; i<2; i++) Nodes.emplace_back(new productionSite<body>);           //4-5
for (int i=0; i<2; i++) Nodes.emplace_back(new productionSite<engine>);         //6-7
for (int i=0; i<2; i++) Nodes.emplace_back(new assemblySite<bodyPaint>);        //8-9
for (int i=0; i<2; i++) Nodes.emplace_back(new assemblySite<bodyTires>);        //10-11
for (int i=0; i<2; i++) Nodes.emplace_back(new assemblySite<bodyEngine>);       //12-13
for (int i=0; i<2; i++) Nodes.emplace_back(new assemblySite<bodyElectronics>);  //14-15
Nodes.emplace_back(new assemblySite<carElement>);                               //16

for (int i=0; i<=3; i++) {Nodes[i]->connect(*Nodes[10]); Nodes[i]->connect(*Nodes[11]);};
for (int i=4; i<=5; i++) {Nodes[i]->connect(*Nodes[8]); Nodes[i]->connect(*Nodes[9]);};
for (int i=6; i<=7; i++) {Nodes[i]->connect(*Nodes[12]); Nodes[i]->connect(*Nodes[13]);};
for (int i=8; i<=9; i++) {Nodes[i]->connect(*Nodes[10]); Nodes[i]->connect(*Nodes[11]);};
for (int i=10; i<=11; i++) {Nodes[i]->connect(*Nodes[12]); Nodes[i]->connect(*Nodes[13]);};
for (int i=12; i<=13; i++) {Nodes[i]->connect(*Nodes[14]); Nodes[i]->connect(*Nodes[15]);};
for (int i=14; i<=15; i++) Nodes[i]->connect(*Nodes[16]);


for (int i=0; i<10; i++)
{
for_each(Nodes.begin(),  Nodes.end()-1, [](node* N){N->run();});

}

for (int i=0; i<Nodes.size()-1; i++) delete Nodes[i];
	return 0;
}
