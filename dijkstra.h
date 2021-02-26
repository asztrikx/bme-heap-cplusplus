#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "include/container/vector.h"
#include <iostream>
#include "include/heap/binaryHeap.h"
#include "include/container/vector.h"
#include <fstream>

namespace Dijkstra {

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
	void printPathRec(int to) {
		if (to == start) {
			std::cout << start;
			return;
		}
		printPathRec(parents[to]);
		std::cout << " " << to;
	}
	Container::Vector<Container::Vector<edge>> graph;
	void read(char const *filename, int start) {
		//file open
		std::ifstream file(filename, std::ifstream::in);
		if (file.fail()) {
			throw "file not found";
		}

		//file read;
		int n;
		file >> n;
		this->start = start;
		parents.resize(n, -1);
		times.resize(n, -1);
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

  public:
	Container::Vector<int> parents;
	Container::Vector<int> times;
	int start;
	void printPath(int to) {
		if (to < 0 || to > parents.length) {
			throw "Dijkstra::printPath() to out of bound";
		}
		std::cout << "(" << times[to] << "): ";
		printPathRec(to);
		std::cout << std::endl;
	}
	Dijkstra(char const *filename, int start) {
		read(filename, start);

		Heap::BinaryHeap<edge> priorityQueue;
		priorityQueue.insert(edge{-1, 0, 0});
		while (!priorityQueue.empty()) {
			edge current = priorityQueue.pop();

			if (times[current.to] != -1) {
				continue;
			}
			times[current.to] = current.weight;
			parents[current.to] = current.from;

			for (int i = 0; i < graph[current.to].length; i++) {
				edge next = graph[current.to][i];

				if (times[next.to] != -1) {
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
};

} // namespace Dijkstra

#endif