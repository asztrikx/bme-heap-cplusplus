#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "include/heap/binaryHeap.h"
#include "include/container/vector.h"
#include <iostream>
#include <fstream>

namespace Dijkstra {

enum Exception
{
	ExceptionFileNotexist,
	ExceptionOutofbounds,
};

class Dijkstra {
	struct edge {
		int from;
		int to;
		int weight;
		bool operator<(edge other) const {
			return weight < other.weight;
		}
		bool operator>(edge other) const {
			return weight > other.weight;
		}
	};

	Container::Vector<Container::Vector<edge>> graph;

	/// @brief Helper function for `printPath`
	void printPathRec(int to) {
		if (to == startIndex) {
			std::cout << startIndex;
			return;
		}
		printPathRec(parents[to]);
		std::cout << " " << to;
	}

	/// @brief Read file into `graph`
	/// @exception Dijkstra::ExceptionFileNotexist
	void read(char const *filename) {
		//file open
		std::ifstream file(filename, std::ifstream::in);
		if (file.fail()) {
			throw ExceptionFileNotexist;
		}

		//file read;
		int n;
		file >> n;

		parents.resize(n, -1);
		weights.resize(n, -1);
		graph.resize(n, Container::Vector<edge>());
		for (int i = 0; i < n; i++) {
			int mi;
			file >> mi;
			for (int j = 0; j < mi; j++) {
				edge e;
				e.from = i;
				file >> e.to;
				file >> e.weight;
				graph[i].pushBack(e);
			}
		}
		file.close();
	}

	/// @brief Calculates all the shortest paths from `startIndex`
	void solve() {
		Heap::BinaryHeap<edge> priorityQueue;
		priorityQueue.insert(edge{-1, 0, 0});
		while (!priorityQueue.empty()) {
			edge current = priorityQueue.pop();

			if (weights[current.to] != -1) {
				continue;
			}
			weights[current.to] = current.weight;
			parents[current.to] = current.from;

			for (int i = 0; i < graph[current.to].length; i++) {
				edge next = graph[current.to][i];

				if (weights[next.to] != -1) {
					continue;
				}
				priorityQueue.insert({
					next.from,
					next.to,
					current.weight + next.weight,
				});
			}
		}
	}

  public:
	/// Each node's parent index in the route-tree from `startIndex` to i
	Container::Vector<int> parents;

	/// Each node's weight in the route-tree from `startIndex` to i
	Container::Vector<int> weights;

	/// Node's index from which the shortest paths are known
	int startIndex;

	/// @brief Prints path from `startIndex` to `to`
	/// @exception Dijkstra::ExceptionOutofbounds
	void printPath(int to) {
		if (to < 0 || to > parents.length) {
			throw ExceptionOutofbounds;
		}

		std::cout << "(" << weights[to] << "): ";

		if (weights[to] == -1) {
			std::cout << "-";
		} else {
			printPathRec(to);
		}

		std::cout << std::endl;
	}

	//ctor
	Dijkstra(char const *filename, int startIndex) {
		read(filename);
		this->startIndex = startIndex;
		solve();
	}
};

} // namespace Dijkstra

#endif