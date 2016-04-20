/*
 * Graph.cpp
 *
 *  Created on: 21 de abr. de 2016
 *      Author: valentin
 */

#include "Graph.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

Graph::Graph() {
	graph_matrix = new int *[1];
	graph_matrix[0] = NULL;
	v_size = e_size = 0;
	this->e = NULL;
	this->v = NULL;
	directed = false;
	allow_loops = false;
}

Graph::Graph(int v[], int e[][3], int v_size, int e_size, bool directed) {

	this->v = new int[v_size];
	for (int i = 0; i < v_size; i++) {
		this->v[i] = v[i];
	}

	this->e = new int *[e_size];
	for (int i = 0; i < e_size; i++) {
		this->e[i] = new int[3];
		this->e[i][0] = e[i][0];
		this->e[i][1] = e[i][1];
		this->e[i][2] = e[i][2];
	}
	this->v_size = v_size;
	this->e_size = e_size;
	this->directed = directed;
	allow_loops = false;

	createMatrix();
}

Graph::~Graph() {
	// Comento pues para valores muy grandes produce double free.
	// TODO: solucionar problemas de leaks de memoria
	/*for (int i = 0; i < v_size; i++) {
		delete[] graph_matrix[i];
	}
	for (int i = 0; i < e_size; i++) {
		delete[] e[i];
	}
	delete[] v;*/
}

void Graph::printMatrix() {
	for (int i = 0; i < v_size; i++) {
		for (int j = 0; j < v_size; j++) {
			cout << graph_matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int *Graph::getEdge(int i) {
	int * edge = new int[3];
	if (i < this->e_size) {
		edge[0] = e[i][0];
		edge[1] = e[i][1];
		edge[2] = e[i][2];
	} else {
		edge[0] = edge[1] = edge[2] = -1;
	}

	return edge;
}

int Graph::getNumberOfEdges() {
	return this->e_size;
}

Graph::Graph(int size, int edge_max, int weigth_max, bool directed,
		bool allow_loops) {
	graph_matrix = new int *[size];
	v_size = size;
	this->v = new int[size];
	this->directed = directed;
	this->allow_loops = allow_loops;
	randomize(size, edge_max, weigth_max, directed, allow_loops);
}

int Graph::getVertexGrade(int l) {
	int grade = 0;
	for (int i = 0; i < this->e_size; i++) {
		if (this->e[i][0] == l || this->e[i][1] == l) {
			grade++;
		}
	}
	if (!directed && grade % 2 == 0) {
		grade /= 2;
	} else if (!directed && grade % 2 == 0) {
		cout << "Execution error" << endl;
		grade = -1;
	}

	return grade;
}

void Graph::createMatrix() {
	this->graph_matrix = new int *[v_size];
	for (int i = 0; i < v_size; i++) {
		graph_matrix[i] = new int[v_size];
		for (int j = 0; j < v_size; j++) {
			graph_matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < this->e_size; i++) {
		//cout << "[" << this->e[i][0] - 1 << "][" << this->e[i][1] - 1 << "] = " << this->e[i][2] << endl;
		this->graph_matrix[this->e[i][0] - 1][this->e[i][1] - 1] =
				this->e[i][2];
		if (!this->directed) {
			this->graph_matrix[this->e[i][1] - 1][this->e[i][0] - 1] =
					this->e[i][2];
		}
	}
}

void Graph::randomize(int node_number, int edge_max, int weigth_max,
		bool directed, bool allow_loops) {
	srand(time(NULL));
	vector<int> aristas;
	vector<int>::iterator it;
	int total_aristas = 0;
	for (int current_node = 0; current_node < node_number; current_node++) {
		int r = rand() % edge_max + 1;
		aristas.push_back(r);
		total_aristas += r;
	}
	it = aristas.begin();
	this->e = new int*[total_aristas];
	this->e_size = total_aristas;
	int aristas_acumuladas = 0;
	for (int current_node = 0; current_node < node_number; current_node++) {
		for (int i = 0; i < aristas[current_node]; i++) {
			this->e[aristas_acumuladas] = new int[3];
			this->e[aristas_acumuladas][0] = current_node + 1;
			this->e[aristas_acumuladas][1] = rand() % node_number + 1;
			this->e[aristas_acumuladas][2] = rand() % weigth_max + 1;
			if (!allow_loops
					&& this->e[aristas_acumuladas][1]
							== this->e[aristas_acumuladas][0]) {
				if (this->e[aristas_acumuladas][1] < node_number) {
					this->e[aristas_acumuladas][1]++;
				} else {
					this->e[aristas_acumuladas][1]--;
				}
			}
			//cout << "[" << this->e[aristas_acumuladas][0] << ", " << this->e[aristas_acumuladas][1] << ", " << this->e[aristas_acumuladas][2] << "]" << endl;
			aristas_acumuladas++;
		}
	}

	this->v_size = node_number;
	this->v = new int[node_number];
	for (int current_node = 0; current_node < node_number; current_node++) {
		this->v[current_node] = current_node;
	}
	createMatrix();
}

