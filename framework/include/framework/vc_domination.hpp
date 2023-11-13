//
// Created by sven_ on 12/11/2023.
//

#include "graph.hpp"

class vc_domination {
public:
    // constructor
    explicit vc_domination(const Graph &G);

    unsigned get_kernel();

private:
    Graph graph;

    bool compare_neighborhoods(unsigned domintor, unsigned dominated);

    std::vector<bool> deleted;
    std::vector<unsigned> dominating;

    void find_dominated();
};