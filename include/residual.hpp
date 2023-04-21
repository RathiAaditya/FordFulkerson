#ifndef RESIDUAL_HPP
#define RESIDUAL_HPP

#include "edge.hpp"
#include <vector>

class ResidualGraph
{
public:
    ResidualGraph(int n); // Constructor
    void add_edge(int u, int v, int w);
    int get_forward_flow(int u, int v) const;
    int get_backward_flow(int u, int v) const;
    void set_forward_flow(int u, int v, int f);
    void set_backward_flow(int u, int v, int f);
    std ::vector<bool> visited;
    std::vector<int> parent;
    std::vector<std::vector<int>> adj_residual; // Adjacency list for residual graph

private:
    std::vector<std::vector<int>> forward_flow;  // Forward flow matrix
    std::vector<std::vector<int>> backward_flow; // Backward flow matrix
};

#endif /* RESIDUAL_HPP */
