/*
 * CarAssemblyLine.hpp
 *
 *  Created on: May 27, 2018
 *      Author: filip
 */

#ifndef CARASSEMBLYLINE_HPP_
#define CARASSEMBLYLINE_HPP_

#include "Graph.hpp"

class carElement {
	virtual ~carElement() {};
};

class tire: carElement {
	virtual ~tire();
};

class body: carElement {
	virtual ~body();
};

class bodyPaint: body {
	virtual ~bodyPaint();
};

class bodyTires: bodyPaint {
	virtual ~bodyTires();
};

class engine: carElement {
	virtual ~engine();
};

class bodyEngine: bodyTires {
	virtual ~bodyEngine();
};

class bodyElectronics: bodyEngine {
	virtual ~bodyElectronics();
};

template <class C> class conveyor : public edge {
C element;

public:
conveyor (): amt(0) {};
virtual ~conveyor(){};

virtual int size () const noexcept {return amt;};
virtual void take() noexcept {--amt;};
virtual void add() noexcept {++amt;};
};

template <class C> class productionSite : public node {
virtual bool space();
//virtual bool materials ();

public:
virtual ~productionSite() {};
virtual void run();
};

template <class C> class assemblySite : public node {
virtual bool space();
virtual bool materials ();

public:
virtual ~assemblySite() {};
virtual void run();
};

template <> class productionSite<tire> : public node{
virtual bool space() {

}

public:
virtual void run() {
if (this->space())
{

}
}
};
#endif /* CARASSEMBLYLINE_HPP_ */
