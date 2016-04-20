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
	/**
	 * Constructor, accept matrix inline creation
	 */
	Graph(int v[], int e[][3], int v_size, int e_size, bool directed = false);
	/**
	 * @param int size
	 * @param int edge_max
	 * @param int weight_max = 1
	 * @param bool directed = false
	 * @param bool allow_loops = false
	 * Generates procedural graphs for given parameters
	 */
	Graph(int size, int edge_max, int weigth_max = 1, bool directed = false,
			bool allow_loops = false);
	virtual ~Graph();

	/**
	 * Internally generates graph_matrix
	 */
	void createMatrix();
	/**
	 * @param int i
	 * Returns "i" edge
	 */
	int * getEdge(int i);
	int ** getEdgesFromNode(int i);
	/**
	 * @param int i
	 * @return int
	 * Returns "i" vertex grade
	 */
	int getVertexGrade(int i);
	/**
	 * @return int
	 * Returns number of edges
	 */
	int getNumberOfEdges();
	/**
	 * Prints adjacency matrix using cout
	 */
	void printMatrix();

	/**
	 * @param const int x
	 * @param const int y
	 * @return int&
	 * Operator overloading for easy access to adjacency matrix position.
	 * Example:
	 * p(2,3)
	 * -> returns graph_matrix[2][3]
	 */
	int & operator()(const int x, const int y);

private:
	int ** graph_matrix;
	int * v;
	int ** e;
	int v_size, e_size;
	bool directed;
	bool allow_loops;
	void randomize(int node_number, int edge_max, int weigth_max = 1,
			bool directed = false, bool allow_loops = false);
};

#endif /* GRAPH_H_ */
