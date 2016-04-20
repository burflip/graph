/*
 * main.cpp
 *
 *  Created on: 21 de abr. de 2016
 *      Author: valentin
 */
#include <iostream>
#include "src/Graph.h"

using namespace std;

int main() {
	Graph p = Graph(30, 10);
	p.printMatrix();
	cout << p(100, 100) << endl;
}
