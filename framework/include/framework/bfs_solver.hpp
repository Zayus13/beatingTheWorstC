//
// Created by sven_ on 12/11/2023.
//

#include <queue>
#include "graph.hpp"

// define a bidrectional bfs solver class
class BFSSolver {
public:
    // constructor
    BFSSolver(const Graph &G);

    unsigned solve_unidirectional(unsigned start, unsigned end);

    unsigned solve_bidirectional(unsigned start, unsigned end);

    // return the number of nodes in the graph
    unsigned n() const;

    // return the number of edges in the graph
    unsigned m() const;


private:
    Graph graph;
    std::queue<unsigned int> queue_from_start_node;
    std::queue<unsigned int> queue_from_end_node;
    std::vector<int> distance_from_start;
    std::vector<int> distance_from_end;
};
