//
// Created by sven_ on 12/11/2023.
//

#include <algorithm>
#include <iostream>
#include "framework/vc_domination.hpp"

vc_domination::vc_domination(const Graph &G) {
    graph = G;
    deleted.resize(graph.n(), false);
}

bool vc_domination::compare_neighborhoods(unsigned int domintor, unsigned int dominated) {
    std::vector<unsigned int> dominator_neighborhood = graph.neighbors(domintor);
    std::vector<unsigned int> dominated_neighborhood = graph.neighbors(dominated);
    std::sort(dominator_neighborhood.begin(), dominator_neighborhood.end());
    std::sort(dominated_neighborhood.begin(), dominated_neighborhood.end());
    unsigned j = 0;
    for (unsigned int i: dominated_neighborhood) {
        if (deleted[i]) {
            continue;
        }
        if (i == domintor) {
            continue;
        }
        while (j < dominator_neighborhood.size() && dominator_neighborhood[j] < i) {
            j++;
        }
        if (j == dominator_neighborhood.size() || dominator_neighborhood[j] > i) {
            return false;
        }
    }
    return true;
}

std::pair<int,int> vc_domination::get_kernel() {
    unsigned counter = 0;
    //iterate over all edges
    while (true) {
        find_dominated();
        if (dominating.empty()) {
            break;
        }
        counter++;
        for (unsigned int i: dominating) {
            deleted[i] = true;
        }
        dominating.clear();
    }
    delete_all_isolated();
    return std::pair<int, int>{std::count(deleted.begin(), deleted.end(), false), counter};
}

void vc_domination::find_dominated() {
    unsigned target;
    bool to_be_deleted;
    for (unsigned int i = 0; i < graph.n(); i++) {
        if (deleted[i]) {
            continue;
        }
        std::vector<unsigned int> neighbors = graph.neighbors(i);
        for (unsigned int neighbor: neighbors) {
            if (neighbor < i or deleted[neighbor]) {
                continue;
            }
            if (graph.degree(i) < graph.degree(neighbor)) {
                target = neighbor;
                to_be_deleted = compare_neighborhoods(neighbor, i);
            } else {
                target = i;
                to_be_deleted = compare_neighborhoods(i, neighbor);
            }
            if (to_be_deleted) {
                dominating.push_back(target);
            }

        }
    }
}

void vc_domination::delete_all_isolated() {
    for (unsigned int i = 0; i < graph.n(); i++) {
        if (deleted[i]) {
            continue;
        }
        bool isolated = true;
        for (unsigned int neighbor: graph.neighbors(i)) {
            if (!deleted[neighbor]) {
                isolated = false;
                break;
            }
        }
        if (isolated) {
            deleted[i] = true;
        }
    }
}
