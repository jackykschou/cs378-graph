#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h" //g test

#include "Graph.h"

using namespace std;
using namespace boost;

int main()
{

	/*
    typedef std::size_t vertex_descriptor;
    typedef EdgeDescriptor edge_descriptor;

    typedef std::deque<vertex_descriptor>::iterator vertex_iterator;
    typedef std::unordered_set<edge_descriptor>::iterator edge_iterator;
    typedef std::deque<vertex_descriptor>::iterator adjacency_iterator;

    typedef std::size_t vertices_size_type;
    typedef std::size_t edges_size_type;
    */

    Graph g;

    Graph::vertex_descriptor a = add_vertex(g);
    Graph::vertex_descriptor b = add_vertex(g);
    Graph::vertex_descriptor c = add_vertex(g);
    Graph::vertex_descriptor d = add_vertex(g);

    add_edge(a, b, g);



}