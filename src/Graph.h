/*
 * Graph.h
 *
 *  Created on: 21 de abr. de 2016
 *      Author: valentin
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
	Graph();
	Graph(int v[], int e[][3], int v_size, int e_size, bool directed = false);
	Graph(int size, int edge_max, int weigth_max = 1, bool directed = false, bool allow_loops = false);
	virtual ~Graph();

	void createMatrix();
	int * getEdge(int i);
	int ** getEdgesFromNode(int i);
	int getVertexGrade(int i);
	int getNumberOfEdges();
	void printMatrix();

private:
	int ** graph_matrix;
	int * v;
	int ** e;
	int v_size, e_size;
	bool directed;
	bool allow_loops;
	void randomize(int node_number, int edge_max, int weigth_max = 1, bool directed = false, bool allow_loops = false);
};

#endif /* GRAPH_H_ */
