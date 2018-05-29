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


#endif /* CARASSEMBLYLINE_HPP_ */
