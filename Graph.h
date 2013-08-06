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

// -----
// Graph
// -----

class Graph {

    //Vertex Class
    class Vertex
    {
        public:

            Graph _g; /*!< the graph the vertex belongs to */

            std::size_t _id; /*!< id of the Vertex in the graph, each Vertex has unique id in different graph */
            std::size_t _preceder_num; /*!< keep track of how many preceders (number of vertices that points to this vertex) the Vertex has */

            std::map<std::size_t, Vertex> _targets; /*!< keep track of the adjacent vertices (vertices that this Vertex points to). Key is the id of the target */

        /**
         * constructor
         * @param id the id of the vertex
         * @param g the Graph the vertex belongs
         */
         Vertex(std::size_t id, Graph g) : _targets()
         {
            _id = id;
            _g = g;
            _preceder_num = 0;
         }

        /**
         * == operator for Vertex
         * @param lhs a Vertex
         * @param rhs a Vertex
         * @return a bool that indicates whether the Vertices are equal
         */
        friend bool operator == (const Vertex& lhs, const Vertex& rhs)
        {
            return (lhs._g == rhs._g) && (lhs._id == rhs._id);
        }

    };

    //Edge Class
    class Edge
    {
        public:

            Graph _g; /*!< the graph the vertex belongs to */

            std::size_t _source_id; /*!< id of the source vertex */
            std::size_t _target_id; /*!< id of the target vertex */

        /**
         * constructor
         * @param s the sourse Vertex
         * @param t the target Vertex
         * @param g the Graph the edge belongs
         */
         Edge(Vertex s, Vertex t, Graph g)
         {
            _g = g;
            _source_id = s.id;
            _target_id = t.id;
         }

        /**
         * == operator for Edge
         * @param lhs a Edge
         * @param rhs a Edge
         * @return a bool that indicates whether the Vertices are equal
         */
        friend bool operator == (const Edge& lhs, const Edge& rhs)
        {
            return (lhs._g == rhs._g) && (lhs._source_id == rhs._source_id) && (lhs._target_id == rhs._target_id);
        }

    };

    public:
        // --------
        // typedefs
        // --------

        typedef Vertex vertex_descriptor;
        typedef Edge edge_descriptor;

        typedef std::map::iterator vertex_iterator;
        typedef std::unordered_set::iterator edge_iterator;
        typedef std::map::iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * possibly add an edge between two given vertices to the graph
         * @param v1 a vertex_descriptor
         * @param v2 a vertex_descriptor
         * @return a pair where first of the pair is the edge_descriptor added and second of the pair indicates whether the edge has been successfully added
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor v1, vertex_descriptor v2, Graph& g) 
        {
            Edge e(v1, v2, g);

            //check if the edge exists in the graph
            if(_edges.find(e) == _edges.end())
            {
                _edges.insert(e); //add edge
                return std::make_pair(ed, false);
            }
            else
            {
                return std::make_pair(ed, true);
            }
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * add a vertex to the graph
         * @param g the graph where vertex is added
         * @return the vertex added
         */
        friend vertex_descriptor add_vertex (Graph& g) 
        {
            Vertex v(_vertex_id_counter++, g);
            return v;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * adjacent_vertices function
         * @param v a Vertex
         * @param g the graph where the vertex is
         * @return a pair of adjacency_iterators, where the first iterator can travel to the second one the eventually visit all the adjacent vertices of the vertex
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) 
        {
            return std::make_pair(v._targets.begin(), v._targets.end());
        }

        // ----
        // edge
        // ----

        /**
         * edge function
         * @param v1 a Vertex
         * @param v2 a Vertex
         * @param g the graph where the vertex is
         * @return a pair, where first is the edge between the vertices, second is a bool indicates whether the edge exists in the graph
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor v1, vertex_descriptor v1, const Graph& g) {
            // <your code>
            edge_descriptor ed;
            bool            b;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph&) {
            // <your code>
            edge_iterator b;
            edge_iterator e;
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph&) {
            // <your code>
            edges_size_type s;
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph&) {
            // <your code>
            vertices_size_type s;
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v;
            return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v;
            return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
            // <your code>
            vertex_descriptor vd;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            vertex_iterator b = vertex_iterator();
            vertex_iterator e = vertex_iterator();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::size_t _vertex_id_counter; /*!< used to assign the id of vertices in the graph */
        std::size_t _edge_id_counter; /*!< used to assign the id of edges in the graph */

        std::map<std::size_t, Vertex> _vertices; /*!< container of the vertices, where the key is the id of vertex */
        std::unordered_set<Edge> _edges; /*!< container of the edges */
        

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () 
        {

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
 * <your documentation>
 */
template <typename G>
bool has_cycle (const G& g) {
    return true;}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * <your documentation>
 * @throws Boost's not_a_dag exception if has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) {
    *x = 2;
    ++x;
    *x = 0;
    ++x;
    *x = 1;
    }

#endif // Graph_h
