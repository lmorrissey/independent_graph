/*
 * graph.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: Laura
 */
#include "graph.h"

Graph::Graph(uint32_t &v1, uint32_t &v2)
{
    AddNewEdge(v1,v2);
}
Graph::~Graph()
{
    _edges.erase(_edges.begin());
}

bool Graph::AlreadyExists(const uint32_t v1, const uint32_t v2)
{
    auto checkit = OrderTheEdges(v1, v2);
    return ((_edges.find(checkit) == _edges.end()) ? false : true);
}

bool Graph::BothEdgesExist(const uint32_t v1, const uint32_t v2)
{
    bool v1_found, v2_found = false;
    for (auto const& it : _edges)
    {
        if (it.first == v1 || it.second == v1)
        {
            v1_found = true;
        }
        if (it.first == v2 || it.second == v2)
        {
            v2_found = true;
        }
    }
    _marked = v1_found && v2_found;
    return _marked;
}

bool Graph::OneEdgeExists(uint32_t v1, uint32_t v2)
{
    bool v_found = false;
    for (auto const& it : _edges)
    {
        if (v_found = (v1 == it.first || v1 == it.second)
                || (v2 == it.first || v2 == it.second))
            return v_found;
    }
    return v_found;

}

bool Graph::AddNewEdge(const uint32_t& v1, const uint32_t& v2)
{
    auto orderededge = OrderTheEdges(v1, v2);
    auto ret = _edges.emplace(orderededge);
    return (!ret.second ? false : true);
}

Graph::Edge Graph::OrderTheEdges(const uint32_t& v1, const uint32_t& v2)
{
    return (v1 < v2 ? std::make_pair(v1, v2) : std::make_pair(v2, v1));
}

const bool Graph::IsDirtyGraph()
{
    return _marked;
}

void Graph::Print()
{
    for (auto const& v : _edges)
    {
        std::cout << "( " << v.first << ", " << v.second << " )" << std::endl;
    }
}

