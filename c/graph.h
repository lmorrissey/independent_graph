/*
 * graph.h
 *
 *  Created on: Oct 8, 2014
 *      Author: Laura
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <utility>
#include <unordered_set>
#include <memory>
#include "pair_hasher.h"


class Graph
{
	public:
        typedef std::pair<uint32_t, uint32_t> Edge;
		typedef std::unordered_set<Edge, hash_pair::hash<Edge>> EdgeSet;

		Graph(uint32_t &v1, uint32_t &v2);
		~Graph();

		Graph(const Graph& rhs) = delete;
		Graph& operator=(const Graph& rhs) = delete;

		Graph(Graph&& rhs) noexcept : _edges(rhs._edges) {_edges.erase(_edges.begin()); }
		Graph& operator=(const Graph&& rhs) noexcept {
		    _edges = std::move(rhs._edges);
		return *this;}

		bool AlreadyExists(const uint32_t v1, const uint32_t v2);

		bool BothEdgesExist(const uint32_t v1, const uint32_t v2);

		bool OneEdgeExists(uint32_t v1, uint32_t v2);

		bool AddNewEdge(const uint32_t& v1, const uint32_t& v2);

		Edge OrderTheEdges(const uint32_t& v1, const uint32_t& v2);

		const bool IsDirtyGraph();

		void Print();

		const bool DirtyGraph(const bool d) { return _marked; }
private:

		EdgeSet _edges;
		bool _marked = false;
};



#endif /* GRAPH_H_ */
