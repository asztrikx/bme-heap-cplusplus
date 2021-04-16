#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "../heap/binaryHeap.h"
#include "../container/vector.h"
#include <iostream>
#include <fstream>
#include "../../memtrace.h"

namespace Dijkstra {

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
	virtual void printPathRec(int to) {
		if (to == startIndex) {
			std::cout << startIndex;
			return;
		}
		printPathRec(parents[to]);
		std::cout << " " << to;
	}

	/// @brief Read file into `graph`
	/// @exception std::ios_base::failure
	virtual void read(char const *filename) {
		//file open
		std::ifstream file(filename, std::ifstream::in);
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		//file read;
		int length;
		file >> length;

		graph.resize(length, Container::Vector<Edge>());
		parents.resize(length, -1);
		weights.resize(length, -1);
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
	/// @exception std::invalid_argument if sum of weights along a path don't form a monotonic function
	void solve() {
		Heap::BinaryHeap<Edge> priorityQueue;

		//helper virtual edge
		priorityQueue.insert(Edge{-1, 0, 0});
		while (!priorityQueue.empty()) {
			Edge current = priorityQueue.pop();

			// already done
			if (weights[current.to] != -1) {
				continue;
			}
			weights[current.to] = current.weight;
			parents[current.to] = current.from;

			// add neighbours
			for (int i = 0; i < graph[current.to].length(); i++) {
				Edge next = graph[current.to][i];

				// neighbour already done
				if (weights[next.to] != -1) {
					// can be reached in shorter distance <=>
					if (current.weight + next.weight < weights[next.to]) {
						throw std::invalid_argument("weights not monotonic");
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

	/// Node's index from which the shortest paths are known
	int startIndex;

  public:
	/// @brief Number of nodes
	int length() const {
		return graph.length();
	}

	/// Each node's parent index in the route-tree from `startIndex` to i
	Container::Vector<int> parents;

	/// Each node's weight in the route-tree from `startIndex` to i
	Container::Vector<Weight> weights;

	/// @brief Prints path from `startIndex` to `to`
	/// @exception std::out_of_range
	virtual void printPath(int to) {
		if (to < 0) {
			throw std::out_of_range("[under]");
		}
		if (to > parents.length()) {
			throw std::out_of_range("[over]");
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
	/// @exception std::ios_base::failure if file not found or if file is malformed
	/// @exception std::invalid_argument if sum of weights along a path don't form a monotonic function
	Dijkstra(char const *filename, int startIndex) {
		read(filename);
		this->startIndex = startIndex;
		solve();
	}
};

} // namespace Dijkstra

#endif