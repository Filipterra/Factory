/*
 * CarAssemblyLine.hpp
 *
 *  Created on: May 27, 2018
 *      Author: filip
 */

#ifndef CARASSEMBLYLINE_HPP_
#define CARASSEMBLYLINE_HPP_

#include "Graph.hpp"
#include <algorithm>
//#include <typeinfo>

class carElement {
	public: virtual ~carElement() {};
};

class tire: public carElement {
public: virtual ~tire(){};
};

class body: public carElement {
public: virtual ~body(){};
};

class bodyPaint: public body {
public: virtual ~bodyPaint(){};
};

class bodyTires: public bodyPaint, public tire{
public: virtual ~bodyTires(){};
};

class engine: public carElement {
public: virtual ~engine(){};
};

class bodyEngine: public bodyTires, public engine {
public: virtual ~bodyEngine(){};
};

class bodyElectronics: public bodyEngine {
public: virtual ~bodyElectronics(){};
};

template <class C> class conveyor : public edge {
C element;

public:
conveyor () {};
virtual ~conveyor(){};

virtual int size () const noexcept {return amt;};
virtual void take() noexcept {--amt;};
virtual void add() noexcept {++amt;};
};

template <class C> class productionSite : public node {
	virtual bool space() {
		if (Outg.size()==0) return 0;
	return any_of(Outg.begin(), Outg.end(), [](edge* ed) {
		conveyor<C>* edptr= dynamic_cast<conveyor<C>*>(ed);
		if(ed->size()<10 && edptr) return 1;
		return 0;
	});
	}
//virtual bool materials ();

public:
virtual ~productionSite() {};
virtual void run() {
if (this->space())
{
edge* min;
for(int i=0; i<Outg.size(); i++) {if (auto edptr=dynamic_cast<conveyor<C>*>(Outg[i])) min=Outg[i]; break;};
for_each(Outg.begin(), Outg.end(), [&min](edge* ed) {if (auto edptr=dynamic_cast<conveyor<C>*>(ed) && ed->size()<min->size()) min=ed;});
min->add();
}
}
};

template <class C> class assemblySite : public node {
virtual bool space() {
		if (Outg.size()==0) return 0;
	return any_of(Outg.begin(), Outg.end(), [](edge* ed) {
		conveyor<C>* edptr= dynamic_cast<conveyor<C>*>(ed);
		if(ed->size()<10 && edptr) return 1;
		return 0;
	});
	}
virtual bool materials ();
virtual void take_materials();

public:
virtual ~assemblySite() {};
virtual void run() {
if (this->space() && this->materials())
{
edge* min;
for(int i=0; i<Outg.size(); i++) {if (auto edptr=dynamic_cast<conveyor<C>*>(Outg[i])) min=Outg[i]; break;};
for_each(Outg.begin(), Outg.end(), [&min](edge* ed) {if (auto edptr=dynamic_cast<conveyor<C>*>(ed) && ed->size()<min->size()) min=ed;});
this->take_materials();
min->add();
}
}
};

template<> bool assemblySite<bodyPaint>::materials(){
	if (Ing.size()==0) return 0;
		return any_of(Ing.begin(), Ing.end(), [](edge* ed) {
			conveyor<body>* edptr= dynamic_cast<conveyor<body>*>(ed);
			if(ed->size()>0 && edptr) return 1;
			return 0;
		});
}

template<> bool assemblySite<bodyElectronics>::materials(){
	if (Ing.size()==0) return 0;
		return any_of(Ing.begin(), Ing.end(), [](edge* ed) {
			conveyor<bodyEngine>* edptr= dynamic_cast<conveyor<bodyEngine>*>(ed);
			if(ed->size()>0 && edptr) return 1;
			return 0;
		});
}

template<> bool assemblySite<bodyEngine>::materials(){
	if (Ing.size()==0) return 0;
		bool be=any_of(Ing.begin(), Ing.end(), [](edge* ed) {
			conveyor<engine>* edptr= dynamic_cast<conveyor<engine>*>(ed);
			if(ed->size()>0 && edptr) return 1;
			return 0;
		});
		bool bbt=any_of(Ing.begin(), Ing.end(), [](edge* ed) {
			conveyor<bodyTires>* edptr= dynamic_cast<conveyor<bodyTires>*>(ed);
			if(ed->size()>0 && edptr) return 1;
			return 0;
		});
		return (be && bbt);
}

template<> bool assemblySite<bodyTires>::materials(){
	if (Ing.size()==0) return 0;
		bool bbp=any_of(Ing.begin(), Ing.end(), [](edge* ed) {
			conveyor<bodyPaint>* edptr= dynamic_cast<conveyor<bodyPaint>*>(ed);
			if(ed->size()>0 && edptr) return 1;
			return 0;
		});
		int it;
		for_each(Ing.begin(), Ing.end(), [&it](edge* ed) {
			if (conveyor<bodyPaint>* edptr= dynamic_cast<conveyor<bodyPaint>*>(ed)) it+=ed->size();
		});
		return (bbp && it>=4);
}

template<> void assemblySite<bodyPaint>::take_materials(){
edge* max;
for(int i=0; i<Ing.size(); i++) {if (auto edptr=dynamic_cast<conveyor<bodyEngine>*>(Ing[i])) max=Ing[i]; break;};
for_each(Ing.begin(), Ing.end(), [&max](edge* ed) {if (auto edptr=dynamic_cast<conveyor<body>*>(ed) && ed->size()>max->size()) max=ed;});
max->take();
}

template<> void assemblySite<bodyElectronics>::take_materials(){
edge* max;
for(int i=0; i<Ing.size(); i++) {if (auto edptr=dynamic_cast<conveyor<bodyEngine>*>(Ing[i])) max=Ing[i]; break;};
for_each(Ing.begin(), Ing.end(), [&max](edge* ed) {if (auto edptr=dynamic_cast<conveyor<bodyEngine>*>(ed) && ed->size()>max->size()) max=ed;});
max->take();
}

template<> void assemblySite<bodyEngine>::take_materials(){
edge* max;
for(int i=0; i<Ing.size(); i++) {if (auto edptr=dynamic_cast<conveyor<bodyTires>*>(Ing[i])) max=Ing[i]; break;};
for_each(Ing.begin(), Ing.end(), [&max](edge* ed) {if (auto edptr=dynamic_cast<conveyor<bodyTires>*>(ed) && ed->size()>max->size()) max=ed;});
max->take();
for(int i=0; i<Ing.size(); i++) {if (auto edptr=dynamic_cast<conveyor<engine>*>(Ing[i])) max=Ing[i]; break;};
for_each(Ing.begin(), Ing.end(), [&max](edge* ed) {if (auto edptr=dynamic_cast<conveyor<engine>*>(ed) && ed->size()>max->size()) max=ed;});
max->take();
}

template<> void assemblySite<bodyTires>::take_materials(){
edge* max;
for(int i=0; i<Ing.size(); i++) {if (auto edptr=dynamic_cast<conveyor<bodyPaint>*>(Ing[i])) max=Ing[i]; break;};
for_each(Ing.begin(), Ing.end(), [&max](edge* ed) {if (auto edptr=dynamic_cast<conveyor<bodyPaint>*>(ed) && ed->size()>max->size()) max=ed;});
max->take();
for (int j=0; j<4; j++){
	for(int i=0; i<Ing.size(); i++) {if (auto edptr=dynamic_cast<conveyor<tire>*>(Ing[i])) max=Ing[i]; break;};
	for_each(Ing.begin(), Ing.end(), [&max](edge* ed) {if (auto edptr=dynamic_cast<conveyor<tire>*>(ed) && ed->size()>max->size()) max=ed;});
	max->take();
}
}

#endif /* CARASSEMBLYLINE_HPP_ */
