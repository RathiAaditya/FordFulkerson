#ifndef ORIGINALGRAPH_HPP
#define ORIGINALGRAPH_HPP

#include "residualgraph.hpp"
#include <vector>

using namespace std;
class OriginalGraph
{
public:
    OriginalGraph(int n); // Constructor
    void add_edge(int u, int v, int w);
    int get_flow(int u, int v) const;
    int get_capacity(int u, int v) const;
    void set_flow(int u, int v, int f);
    void set_capacity(int u, int v, int c);
    std::vector<std::vector<int>> adj_original; // Adjacency list for original graph
    std::vector<std::vector<int>> flow;         // Flow matrix
    std::vector<std::vector<int>> capacity;     // Capacity matrix
    void initializeOriginalGraph(OriginalGraph &og, ResidualGraph &rg);
    void updateOriginalGraph(OriginalGraph &og, int bn, vector<int> &parent, int s, int t);
};

#endif /* ORIGINAL_HPP */