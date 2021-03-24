#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "include/heap/binaryHeap.h"
#include "include/container/vector.h"
#include <iostream>
#include <fstream>

namespace Dijkstra {

namespace Exception {
	class Exception {};
	class WeightsNotMonotonic : public Exception {};
	class FileNotexist : public Exception {};
	class Outofbounds : public Exception {};
} // namespace Exception

template <typename Weight>
class Dijkstra {
	struct Edge {
		int from;
		int to;
		Weight weight;
		bool operator<(Edge other) const {
			return weight < other.weight;
		}
	};

	Container::Vector<Container::Vector<Edge>> graph;

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
			throw Exception::FileNotexist();
		}

		//file read;
		file >> length;

		parents.resize(length, -1);
		weights.resize(length, -1);
		graph.resize(length, Container::Vector<Edge>());
		for (int i = 0; i < length; i++) {
			int m;
			file >> m;
			for (int j = 0; j < m; j++) {
				Edge edge;
				edge.from = i;
				file >> edge.to;
				file >> edge.weight;
				graph[i].pushBack(edge);
			}
		}
		file.close();
	}

	/// @brief Calculates all the shortest paths from `startIndex`
	void solve() {
		Heap::BinaryHeap<Edge> priorityQueue;
		priorityQueue.insert(Edge{-1, 0, 0});
		while (!priorityQueue.empty()) {
			Edge current = priorityQueue.pop();

			if (weights[current.to] != -1) {
				continue;
			}
			weights[current.to] = current.weight;
			parents[current.to] = current.from;

			for (int i = 0; i < graph[current.to].length(); i++) {
				Edge next = graph[current.to][i];

				if (weights[next.to] != -1) {
					if (current.weight + next.weight < weights[next.to]) {
						throw Exception::WeightsNotMonotonic();
					}
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
	Container::Vector<Weight> weights;

	/// Number of nodes
	int length;

	/// Node's index from which the shortest paths are known
	int startIndex;

	/// @brief Prints path from `startIndex` to `to`
	/// @exception Dijkstra::ExceptionOutofbounds
	void printPath(int to) {
		if (to < 0 || to > parents.length()) {
			throw Exception::Outofbounds();
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
	/// @brief Reads then solves. First line should be the number of nodes.
	/// each i-th line after that should first contain the number of edges from that node
	/// and after that (edge's end, edge's weight) pairs all separated by whitespace.
	Dijkstra(char const *filename, int startIndex) {
		read(filename);
		this->startIndex = startIndex;
		solve();
	}
};

} // namespace Dijkstra

#endif