/*
 * Graph.hpp
 *
 *  Created on: May 27, 2018
 *      Author: filip
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>

class edge;

class node
{
protected:
	std::vector<edge*> Ing;
	std::vector<edge*> Outg;

public:
	virtual ~node() {
		for (unsigned int i=0; i<Ing.size(); i++) Ing[i]->disconnect_end();
		for (unsigned int i=0; i<Outg.size(); i++) Outg[i]->disconnect_bgn();
	};

	friend edge;
	friend void connect (edge& edg, node& bgnn, node& endn);
	friend void disconnect (edge& edg);
	virtual void run()=0;
};

class edge
{
protected:
	node *bgn, *end;

	void connect_bgn(node& Nod) {bgn=&Nod;};
	void connect_end(node& Nod) {end=&Nod;};
	void disconnect_bgn() {bgn=nullptr;};
	void disconnect_end() {end=nullptr;};

public:
	edge(): bgn(nullptr), end(nullptr) {};
	virtual ~edge() {disconnect(*this);};

	friend node;
	friend void connect (edge& edg, node& bgnn, node& endn);
	friend void disconnect (edge& edg);
};

void connect (edge& edg, node& bgnn, node& endn) {
		edg.connect_bgn(bgnn);
		edg.connect_end(endn);
		bgnn.Outg.push_back(&edg);
		endn.Ing.push_back(&edg);
	}

void disconnect (edge& edg) {
	for (unsigned int i=0; i<edg.bgn->Outg.size(); i++)
	{
		if (edg.bgn->Outg[i]==&edg) {
			edg.bgn->Outg.erase (edg.bgn->Outg.begin()+i);
			break;
		}
	}
	for (unsigned int i=0; i<edg.end->Ing.size(); i++)
	{
		if (edg.bgn->Ing[i]==&edg) {
			edg.bgn->Ing.erase (edg.bgn->Ing.begin()+i);
			break;
		}
	}
	edg.disconnect_bgn();
	edg.disconnect_end();
}

#endif /* GRAPH_HPP_ */
