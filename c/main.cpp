//============================================================================
// Name        : graph.cpp
// Author      : The Laura
// Version     :
// Copyright   : 
// Description : Hello World in C, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "graph.h"
#include <utility>
int main(int p_argc, char ** p_argv)
{
    uint32_t vertex1, vertex2 = 0;

    typedef std::shared_ptr<Graph> graphPtr;

    std::vector<graphPtr> graphs;

    int graphNo = 0;

    std::cout << "Ready..." << std::endl;

//	No console input
//	std::vector<std::pair<uint32_t, uint32_t>> inputSet;
//
//	inputSet.emplace_back(std::make_pair(1,2));
//	inputSet.emplace_back(std::make_pair(3,4));
//	inputSet.emplace_back(std::make_pair(5,6));
//	inputSet.emplace_back(std::make_pair(8,9));
//	inputSet.emplace_back(std::make_pair(10,12));
//	inputSet.emplace_back(std::make_pair(14,22));
//	inputSet.emplace_back(std::make_pair(15,23));
//	inputSet.emplace_back(std::make_pair(17,41));
//	inputSet.emplace_back(std::make_pair(11,29));


    while (true)
    {
        std::string inputLine;
        std::getline(std::cin, inputLine);

        if (!inputLine.empty())
        {
            std::istringstream sstr(inputLine);

            sstr >> vertex1 >> vertex2;

            std::cout << "Vertex 1, 2 are " << vertex1 << " " << vertex2
                    << std::endl;
            std::cout << "Next? " << std::endl;
            if (vertex1 == vertex2)
            {
                std::cout << "Invalid Input, no duplicates" << std::endl;
                break;
            }
            if (graphs.empty())
            {
                std::cout << "first graph" << std::endl;

                graphPtr seedGraph(new Graph(vertex1, vertex2));
                graphs.emplace_back(seedGraph);
                continue;

            }
            for (auto const& g : graphs)
            {
                if (g->AlreadyExists(vertex1, vertex2))
                {
                    //edges are always sorted prior to insertion;
                    //The graph is assumed to be undirected, so (2, 1) == (1,2)
                    std::cout << "Vertices " << "(" << vertex1 << ", "
                            << vertex2 << ") " << "are duplicates" << std::endl;
                    continue;
                }

                if (g->BothEdgesExist(vertex1, vertex2))
                {
                    std::cout << "Mark Dirty: Both edges exist in this graph"
                            << std::endl;
                    g->DirtyGraph(true);
                    g->AddNewEdge(vertex1, vertex2);

                }
                else if (g->OneEdgeExists(vertex1, vertex2))
                {
                    std::cout << "Adding Edge to existing graph" << std::endl;
                    g->AddNewEdge(vertex1, vertex2);
                }
                else //new graph.
                {
                    std::cout << "new graph" << std::endl;
                    graphPtr newGraph(new Graph(vertex1, vertex2));
                    graphs.emplace_back(newGraph);
                }
            }
        }
        else
        {
            break;
        }
    }

    std::cout << "Total Graphs: " << graphs.size() << std::endl;

    for (auto const& g : graphs)
    {
        if (g->IsDirtyGraph())
        {
            std::cout << "*Dirty Graph " << ++graphNo << std::endl;
        }
        else
        {
            std::cout << "Graph " << ++graphNo << std::endl;
        }
        g->Print();
    }

    return 0;
}
