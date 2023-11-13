//
// Created by sven_ on 12/11/2023.
//

#include <iostream>
#include "framework/bfs_solver.hpp"

BFSSolver::BFSSolver(const Graph &G) {
    graph = G;
    distance_from_start.resize(graph.n(), -1);
    distance_from_end.resize(graph.n(), -1);

}

unsigned BFSSolver::solve_unidirectional(unsigned int start, unsigned int end) {
    //reset distance from start
    std::fill(distance_from_start.begin(), distance_from_start.end(), -1);
    std::fill(distance_from_end.begin(), distance_from_end.end(), -1);
    queue_from_start_node = std::queue<unsigned int>();
    queue_from_start_node.push(start);
    distance_from_start[start] = 0;
    unsigned int edges_visited = 0;
    while (!queue_from_start_node.empty()) {
        unsigned int current_node = queue_from_start_node.front();
        queue_from_start_node.pop();
        for (unsigned int neighbor: graph.neighbors(current_node)) {
            if (distance_from_start[neighbor] == -1) {
                distance_from_start[neighbor] = distance_from_start[current_node] + 1;
                queue_from_start_node.push(neighbor);
                edges_visited++;
                if (neighbor == end) {
                    return edges_visited;
                }
            }
        }
    }
    return edges_visited;
}

//dibirectional bfs
// counting the number of edges visited
unsigned BFSSolver::solve_bidirectional(unsigned int start, unsigned int end) {
    std::fill(distance_from_start.begin(), distance_from_start.end(), -1);
    std::fill(distance_from_end.begin(), distance_from_end.end(), -1);
    queue_from_start_node = std::queue<unsigned int>();
    queue_from_end_node = std::queue<unsigned int>();
    queue_from_start_node.push(start);
    queue_from_end_node.push(end);
    distance_from_start[start] = 0;
    distance_from_end[end] = 0;
    unsigned int edges_visited = 0;
    while (!queue_from_start_node.empty() && !queue_from_end_node.empty()) {
        unsigned int current_node = queue_from_start_node.front();
        queue_from_start_node.pop();
        for (unsigned int neighbor: graph.neighbors(current_node)) {
            if (distance_from_start[neighbor] == -1) {
                distance_from_start[neighbor] = distance_from_start[current_node] + 1;
                queue_from_start_node.push(neighbor);
                edges_visited++;
                if (distance_from_end[neighbor] != -1) {
                    return edges_visited;
                }
            }
        }
        current_node = queue_from_end_node.front();
        queue_from_end_node.pop();
        for (unsigned int neighbor: graph.neighbors(current_node)) {
            if (distance_from_end[neighbor] == -1) {
                distance_from_end[neighbor] = distance_from_end[current_node] + 1;
                queue_from_end_node.push(neighbor);
                edges_visited++;
                if (distance_from_start[neighbor] != -1) {
                    return edges_visited;
                }
            }
        }
    }
    return edges_visited;
}