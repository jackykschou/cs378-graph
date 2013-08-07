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
#include <map>  // map
#include <unordered_set>  // unordered set
#include <iterator> //advance

// -----
// Graph
// -----

class Graph {

    public:
        // --------
        // typedefs
        // --------

        typedef std::size_t vertex_descriptor;
        typedef EdgeDescriptor edge_descriptor;

        typedef std::unordered_set::iterator vertex_iterator;
        typedef std::unordered_set::iterator edge_iterator;
        typedef std::unordered_set::iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    //EdgeDescriptor Class
    class EdgeDescriptor
    {
        public:

            vertex_descriptor _source; /*!< source vertex_descriptor */
            vertex_descriptor _target; /*!< target vertex_descriptor */

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
         EdgeDescriptor(vertex_descriptor s, vertex_descriptor t)
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
            return (lhs._source == rhs._source) && (lhs._target == rhs._target);
        }

    };

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
            if(g._edges.find(e) == g._edges.end())
            {
                //if the vertex_descriptors were not in the graph, add them to the graph. else, update the information only
                if(g._vertices.find(v1) == g._vertices.end())
                {
                    g._vertices.insert(v1);
                    g._targets.insert(v1, std::unordered_set<vertex_descriptor>());
                    g._preceder_num.insert(v1, 0);
                }
                g._targets[v1].insert(v2); //add v1's adjacent vertex_descriptor (which is v2)
                
                if(g._vertices.find(v2) == g._vertices.end())
                {
                    g._vertices.insert(v2);
                    g._targets.insert(v2, std::unordered_set<vertex_descriptor>());
                    g._preceder_num.insert(v2, 1);
                }
                else
                {

                    ++(g._preceder_num[v2]);
                }

                g._edges.insert(e); //add edge_descriptor

                return std::make_pair(e, true);
            }
            else
            {
                return std::make_pair(e, false);
            }
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
            vertex_descriptor v(g._vertex_counter++);
            g._vertices.insert(v);
            g._targets.insert(v, std::unordered_set<vertex_descriptor>());
            g._preceder_num(v, 0);
            return v;
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
            return std::make_pair(g._targets[v].begin(), g._targets[v].end());
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
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor v1, vertex_descriptor v1, const Graph& g) 
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
            return std::make_pair(g._edges.begin(), g._edges.end());
        }

        // ---------
        // num_edge
        // ---------

        /**
         * num_edge function
         * @param g a Graph
         * @return the number of edges in the given graph
         */
        friend edges_size_type num_edge (const Graph& g) 
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
            g._edges.find(e)._source;
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
        friend vertex_descriptor target (edge_descriptor e, const Graph&) 
        {
            g._edges.find(e)._target;
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
            vertex_iterator b = g._vertices.begin();
            std::advance(b, nth);
            return *b;
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
            return std::make_pair(g._vertices.begin(), g._vertices.end());
        }

    private:
        // ----
        // data
        // ----

        std::vertex_descriptor _vertex_counter; /*!< used to assign the vertex_descriptor in the graph */

        std::unordered_set<vertex_descriptor> _vertices; /*!< container of the vertices*/
        std::unordered_set<edge_descriptor> _edges; /*!< container of the EdgeDescriptors */

        std::map<vertex_descriptor, std::size_t> _preceder_num; /*!< keep track of how many preceders (number of vertex_descriptors that points to vertex_descriptor) the vertex_descriptors have (Key is the vertex_descriptor)*/
        std::map<vertex_descriptor, std::unordered_set<vertex_descriptor> > _targets; /*!< keep track of the adjacent vertices (vertex_descriptor that vertex_descriptors points to). Key is the vertex_descriptor that owns the adjacent vertex_descriptors*/
        

        // -----
        // valid
        // -----

        /**
         * valid function
         */
        bool valid () const 
        {
            // <your code>
            return true;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         *  default constructor
         */
        Graph () : _vertices(), _edges(), _preceder_num(), _targets()
        {
            _vertex_counter = 0;
            assert(valid());
        }

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

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
    return true;
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
    
}

#endif // Graph_h