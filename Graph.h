// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2013
// Glenn P. Downing
// assignment done by Ka Seng Chou
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <deque>  // deque
#include <unordered_map>  // unordered_map
#include <unordered_set>  // unordered set
#include <iterator>
#include <algorithm> 
#include "boost/graph/exception.hpp"// not_a_dag exception

using std::rel_ops::operator!=;

// -----
// Graph
// -----

class Graph 
{

    public:

        //EdgeDescriptor Class
    class EdgeDescriptor
    {
        public:
            std::size_t _source; /*!< source vertex_descriptor */
            std::size_t _target; /*!< target vertex_descriptor */

        /**
         * default constructor
         */
         EdgeDescriptor()
         {}

        /**
         * constructor
         * @param s the sourse vertex_descriptor
         * @param t the target vertex_descriptor
         */
         EdgeDescriptor(std::size_t s, std::size_t t)
         {
            _source = s;
            _target = t;
         }

        /**
         * == operator for EdgeDescriptor
         * @param lhs a EdgeDescriptor
         * @param rhs a EdgeDescriptor
         * @return a bool that indicates whether the EdgeDescriptors are equal
         */
        friend bool operator == (const EdgeDescriptor& lhs, const EdgeDescriptor& rhs)
        {
            return true;
        }

    };

        // --------
        // typedefs
        // --------

        typedef std::size_t vertex_descriptor;
        typedef EdgeDescriptor edge_descriptor;

        typedef std::deque<vertex_descriptor>::iterator vertex_iterator;
        typedef std::unordered_set<edge_descriptor>::iterator edge_iterator;
        typedef std::deque<vertex_descriptor>::iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * possibly add an edge_descriptor between two given vertex_descriptor to the graph
         * @param v1 a vertex_descriptor
         * @param v2 a vertex_descriptor
         * @return a pair where first of the pair is the edge_descriptor added and second of the pair indicates whether the EdgeDescriptor has been successfully added
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor v1, vertex_descriptor v2, Graph& g) 
        {
            edge_descriptor e(v1, v2);
            //check if the edge_descriptor exists in the graph
            //if(g._edges.find(e) == g._edges.end())
            {
                /* If the VertexList selector is vecS, and if either vertex descriptor u or v (which are integers) has a value greater than the current number of vertices in the graph, 
                the graph is enlarged so that the number of vertices is std::max(u,v) + 1. */
                /*if((v1 >= g._vertices.back()) || (v2 >=  g._vertices.back()))
                {
                    vertices_size_type new_size = std::max(v1, v2) + 1;
                    g._vertices.resize(new_size);
                 }

                g._targets[v1].push_back(v2); //add v1's adjacent vertex_descriptor (which is v2)

                g._edges.insert(e); //add edge_descriptor

                return std::make_pair(e, true);
                */
            }
            //else
            {
                //return std::make_pair(e, false);
            }
            
            return std::make_pair(e, true);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * add a vertex_descriptor to the graph
         * @param g the graph where vertex_descriptor is added
         * @return the vertex_descriptor added
         */
        friend vertex_descriptor add_vertex (Graph& g) 
        {
            g._vertices.push_back((g._vertices.size()) + 1);
            return g._vertices.back();
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * adjacent_vertices function
         * @param v a vertex_descriptor
         * @param g the graph where the vertex_descriptor is
         * @return a pair of adjacency_iterators, where the first iterator can travel to the second one the eventually visit all the adjacent vertices of the vertex_descriptor
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) 
        {
            Graph& cg = const_cast<Graph&>(g);
            adjacency_iterator b = ((cg._targets.find(v))->second).begin();
            adjacency_iterator e = ((cg._targets.find(v))->second).end();
            return std::make_pair(b, e);
        }

        // ----
        // edge
        // ----

        /**
         * edge function
         * @param v1 a vertex_descriptor
         * @param v2 a vertex_descriptor
         * @param g the graph where the vertex_descriptor is
         * @return a pair, where first is the edge_descriptor between the vertices, second is a bool indicates whether the edge_descriptor exists in the graph
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor v1, vertex_descriptor v2, const Graph& g) 
        {
            edge_descriptor e(v1, v2);
            if(g._edges.find(e) == g._edges.end())
            {
                return std::make_pair(e, true);
            }
            else
            {
                return std::make_pair(e, false);
            }
        }

        // -----
        // edges
        // -----

        /**
         * edges function
         * @param g a Graph
         * @return a pair of edge_iterator in which the first can travel to the second one the eventually visits all the edges in the given graph
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) 
        {
            Graph& cg = const_cast<Graph&>(g);
            edge_iterator b = cg._edges.begin();
            edge_iterator e = cg._edges.end();
            return std::make_pair(b, e);
        }

        // ---------
        // num_edge
        // ---------

        /**
         * num_edge function
         * @param g a Graph
         * @return the number of edges in the given graph
         */
        friend edges_size_type num_edges (const Graph& g) 
        {
            return g._edges.size();
        }

        // ------------
        // num_vertices
        // ------------

        /**
         * num_vertices function
         * @param g a Graph
         * @return the number of vertices in the given graph
         */
        friend vertices_size_type num_vertices (const Graph& g) 
        {
            return g._vertices.size();
        }

        // ------
        // source
        // ------

        /**
         * source function
         * @param r an edge_descriptor
         * @param g a Graph
         * @return the source vertex_descriptor of a given edge_descriptor in the given graph
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) 
        {
            return (g._edges.find(e))->_source;
        }

        // ------
        // target
        // ------

        /**
         * target function
         * @param e an edge_descriptor
         * @param g a Graph
         * @return the target vertex_descriptor of a given edge_descriptor in the given graph
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) 
        {
            return (g._edges.find(e))->_target;
        }

        // ------
        // vertex
        // ------

        /**
         * vertex function
         * @param nth integral value represents the n term index of the vertex
         * @param g a Graph
         * @return the nth vertex_descriptor of the graph
         */
        friend vertex_descriptor vertex (vertices_size_type nth, const Graph& g) 
        {
            return g._vertices[nth];
        }

        // --------
        // vertices
        // --------

        /**
         * vertices function
         * @param g a Graph
         * @return a pair of vertex_iterator in which the first can travel to the second one the eventually visits all the vertices in the given graph
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) 
        {
            Graph& cg = const_cast<Graph&>(g);
            vertex_iterator b = cg._vertices.begin();
            vertex_iterator e = cg._vertices.end();
            return std::make_pair(b, e);
        }

    private:
        // ----
        // data
        // ----

        std::deque<vertex_descriptor> _vertices; /*!< container of the vertex_descriptors */

        std::unordered_set<edge_descriptor> _edges; /*!< container of the edge_descriptors */

        std::unordered_map<vertex_descriptor, std::deque<vertex_descriptor> > _targets; /*!< keep track of the adjacent vertices (vertex_descriptor that vertex_descriptors points to). Key is the vertex_descriptor that owns the adjacent vertex_descriptors*/
        

        // -----
        // valid
        // -----

        /**
         * valid function
         */
        bool valid () const 
        {
            return _vertices.size() == 0 && _edges.size() == 0 && _targets.size() == 0;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         *  default constructor
         */
        Graph () : _vertices(), _edges(), _targets()
        {
            assert(valid());
        }

        /**
         * equal operator
         * @lhs a Graph
         * @rhs a Graph
         */
        friend bool operator == (const Graph& lhs, const Graph& rhs) 
        {
            return lhs._vertices == rhs._vertices && lhs._edges == rhs._edges;
        }

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
};

//helper function for has_cycle
template <typename G>
bool has_grey_neighbour (const G& g, typename G::vertex_descriptor v, std::vector<int>& colors)
{
    return std::any_of(adjacent_vertices(v, g).first, adjacent_vertices(v, g).second, [&colors](typename G::vertex_descriptor v)
        {
            return colors[v] == 1;
        });
}

//helper function for DFS (return -1 if no)
template <typename G>
int get_white_vertex (const G& g, std::vector<int>& colors)
{
    int result = -1;
    int count = 0;
    while((std::size_t)count < colors.size() && result == -1)
    {
        if(colors[count] == 0)
        {
            result = count;
        }
        ++count;
    }
    return result;
}

//helper function for DFS (return -1 if no white neighbour)
template <typename G>
int get_white_neighbour (const G& g, typename G::vertex_descriptor v, std::vector<int>& colors)
{
    typename G::adjacency_iterator match;
    match = std::find_if(adjacent_vertices(v, g).first, adjacent_vertices(v, g).second, [&colors](typename G::vertex_descriptor v)
        {
            return colors[v] == 0;
        });
    if(match == adjacent_vertices(v, g).second)
    {
        return -1;
    }
    else
    {
        return (int)(*match);
    }
}

// ---------
// has_cycle
// ---------

/**
 * depth-first traversal
 * three colors
 * @param g a Graph
 * @return bool indicates whether the graph is cyclic
 */
template <typename G>
bool has_cycle (const G& g) 
{
    if(num_vertices(g) == 0)
    {
        return false;
    }

    std::vector<int> colors(num_vertices(g), 0); //keep track of the different colors of vertices (0 while, 1 grey, 2 black)
    std::deque<typename G::vertex_descriptor> s; //use as a stack
    typename G::vertex_descriptor current_vertex;
    int current_vertex_index;
    int next_vertex_index;
    bool stack_empty;

    while(get_white_vertex(g, colors) != -1)
    {
        current_vertex_index = get_white_vertex(g, colors);
        current_vertex = vertex(current_vertex_index, g);
        colors[current_vertex_index] = 1;
        do
        {
            if(has_grey_neighbour(g, current_vertex, colors))
            {
                return true;
            }
            if((next_vertex_index = get_white_neighbour(g, current_vertex, colors)) != -1)
            {
                colors[next_vertex_index] = 1;
                s.push_back(current_vertex);
                current_vertex = vertex(next_vertex_index, g);
                current_vertex_index = (int)current_vertex;
            }
            else
            {
                colors[current_vertex_index] = 2;
                if(!(stack_empty = s.empty()))
                {
                    current_vertex = s.back();
                    current_vertex_index = (int)current_vertex;
                    s.pop_back();
                }
            }
        }while(!stack_empty);
    }
    return false;
}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * performs a topological sort on a graph and stream the outoput to an output iterator
 * @param g a Graph
 * @param x an output iteration
 * @throws Boost's not_a_dag exception if has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) 
{
    if(has_cycle(g))
    {
        throw boost::not_a_dag();
    }
    else
    {
        std::vector<int> colors(num_vertices(g), 0); //keep track of the different colors of vertices (0 while, 1 grey, 2 black)
        std::deque<typename G::vertex_descriptor> s; //use as a stack
        int current_vertex_index;
        int next_vertex_index;
        bool stack_empty;
        typename G::vertex_descriptor current_vertex;

        std::deque<typename G::vertex_descriptor> result;

   while((current_vertex_index = get_white_vertex(g, colors)) != -1)
    {
        current_vertex = vertex(current_vertex_index, g);
        colors[current_vertex_index] = 1;
        do
        {
            if((next_vertex_index = get_white_neighbour(g, current_vertex, colors)) != -1)
            {
                colors[next_vertex_index] = 1;
                s.push_back(current_vertex);
                current_vertex = vertex(next_vertex_index, g);
                current_vertex_index = (int)current_vertex;
            }
            else
            {
                colors[current_vertex_index] = 2;
                if(!(stack_empty = s.empty()))
                {
                    current_vertex = s.back();
                    current_vertex_index = (int)current_vertex;
                    s.pop_back();
                }
            }
        }while(!stack_empty);
    }  

        while(!result.empty())
        {
            *x = result.back();
            result.pop_back();
            ++x;
        }
    }
}

#endif // Graph_h