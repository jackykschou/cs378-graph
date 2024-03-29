// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    g++ -pedantic -std=c++0x -Wall Graph.h TestGraph.c++ -o TestGraph -lgtest -lpthread -lgtest_main
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
//#include "boost/graph/topological_sort.hpp"// topological_sort use the sort in Graph.h

#include "gtest/gtest.h" //g test

#include "Graph.h"

using namespace std;
using namespace boost;

// ---------
// TestGraph
// ---------

template <typename T>
class TestGraph : public testing::Test 
{

    public:

    // --------
    // typedefs
    // --------

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // -----
    // tests used data
    // -----

    // directed, sparse, unweighted
    // possibly connected
    // possibly cyclic
    graph_type g;

    vertex_descriptor vdA;
    vertex_descriptor vdB;
    vertex_descriptor vdC;
    vertex_descriptor vdD;
    vertex_descriptor vdE;
    vertex_descriptor vdF;
    vertex_descriptor vdG;
    vertex_descriptor vdH;

    edge_descriptor edAB;
    edge_descriptor edAC;
    edge_descriptor edAE;
    edge_descriptor edBD;
    edge_descriptor edBE;
    edge_descriptor edCD;
    edge_descriptor edDE;
    edge_descriptor edDF;
    edge_descriptor edFD;
    edge_descriptor edFH;
    edge_descriptor edGH;

    graph_type empty_g;

    // -----
    // setUp
    // -----

    virtual void SetUp() 
    {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
        vdE  = add_vertex(g);
        vdF  = add_vertex(g);
        vdG  = add_vertex(g);
        vdH  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edAC = add_edge(vdA, vdC, g).first;
        edAE = add_edge(vdA, vdE, g).first;
        edBD = add_edge(vdB, vdD, g).first;
        edBE = add_edge(vdB, vdE, g).first;
        edCD = add_edge(vdC, vdD, g).first;
        edDE = add_edge(vdD, vdE, g).first;
        edDF = add_edge(vdD, vdF, g).first;
        edFD = add_edge(vdF, vdD, g).first;
        edFH = add_edge(vdF, vdH, g).first;
        edGH = add_edge(vdG, vdH, g).first;
    }
};

typedef ::testing::Types< Graph > MyTypes;
//typedef ::testing::Types< adjacency_list<setS, vecS, directedS> > MyTypes;

TYPED_TEST_CASE(TestGraph, MyTypes);

    // -------------
    // test_add_edge
    // -------------
    
    TYPED_TEST(TestGraph, TEST_ADD_EDGE_1) 
    {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
        ASSERT_TRUE(p.first  == this->edAB);
        ASSERT_TRUE(p.second == false);
    }

    TYPED_TEST(TestGraph, TEST_ADD_EDGE_2) 
    {
        //2 edges on same vertices but different direction
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdG, this->g);
        std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(this->vdG, this->vdA, this->g);
        ASSERT_TRUE(p.first  != p2.first);
        ASSERT_TRUE(p.second == true);
        ASSERT_TRUE(p2.second == true);
    }

    TYPED_TEST(TestGraph, TEST_ADD_EDGE_3) 
    {
        //try to add exact same edge 2 times
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdH, this->vdA, this->g);
        std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(this->vdH, this->vdA, this->g);
        ASSERT_TRUE(p.first  == p2.first);
        ASSERT_TRUE(p.second == true);
        ASSERT_FALSE(p2.second);
    }

    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    TYPED_TEST(TestGraph, TEST_ADJACENT_VERTICES_1) 
    {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdB);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdC);}
    }

    TYPED_TEST(TestGraph, TEST_ADJACENT_VERTICES_2) 
    {
        //empty adjacent vertices
        typename TestFixture::vertex_descriptor v = add_vertex(this->empty_g);
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(v, this->empty_g);
        ASSERT_TRUE(p.first == p.second);

    }

    TYPED_TEST(TestGraph, TEST_ADJACENT_VERTICES_3) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v3 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v4 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v5 = add_vertex(this->empty_g);
        add_edge(v1, v2, this->empty_g);
        add_edge(v1, v3, this->empty_g);
        add_edge(v1, v4, this->empty_g);
        add_edge(v1, v5, this->empty_g);
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(v1, this->empty_g);
        ASSERT_TRUE(distance(p.first, p.second) == 4);

    }

    // ---------
    // test_edge
    // ---------

    TYPED_TEST(TestGraph, TEST_EDGE_1) 
    {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
        ASSERT_TRUE(p.first  == this->edAB);
        ASSERT_TRUE(p.second == true);
    }

    TYPED_TEST(TestGraph, TEST_EDGE_2) 
    {
        //same edge, different graph
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdB, this->vdA, this->g);
        ASSERT_TRUE(p.second == false);
    }

    TYPED_TEST(TestGraph, TEST_EDGE_3) 
    {
        //non-existing edge
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(v1, v2, this->empty_g);
        ASSERT_TRUE(p.second == false);
    }

    // ----------
    // test_edges
    // ----------

    TYPED_TEST(TestGraph, TEST_EDGES_1) 
    {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g);
        typename TestFixture::edge_iterator                           b = p.first;
        typename TestFixture::edge_iterator                           e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_TRUE(ed == this->edAB);
        }
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_TRUE(ed == this->edAC);
        }
    }

    TYPED_TEST(TestGraph, TEST_EDGES_2) 
    {
        //empty edges
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->empty_g);
        ASSERT_TRUE(p.first == p.second);
    }

    TYPED_TEST(TestGraph, TEST_EDGES_3) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v3 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v4 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v5 = add_vertex(this->empty_g);
        add_edge(v1, v2, this->empty_g);
        add_edge(v1, v3, this->empty_g);
        add_edge(v1, v4, this->empty_g);
        add_edge(v1, v5, this->empty_g);
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->empty_g);
        ASSERT_TRUE(distance(p.first, p.second) == 4);
    }

    // --------------
    // test_num_edges
    // --------------

    TYPED_TEST(TestGraph, TEST_NUM_EDGES_1) 
    {
        typename TestFixture::edges_size_type es = num_edges(this->g);
        ASSERT_TRUE(es == 11);
    }

    TYPED_TEST(TestGraph, TEST_NUM_EDGES_2) 
    {
        //empty graph
        typename TestFixture::edges_size_type es = num_edges(this->empty_g);
        ASSERT_TRUE(es == 0);
    }

    TYPED_TEST(TestGraph, TEST_NUM_EDGES_3) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v3 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v4 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v5 = add_vertex(this->empty_g);
        add_edge(v1, v2, this->empty_g);
        add_edge(v1, v3, this->empty_g);
        add_edge(v1, v4, this->empty_g);
        add_edge(v1, v5, this->empty_g);
        typename TestFixture::edges_size_type es = num_edges(this->empty_g);
        ASSERT_TRUE(es == 4);
    }


    // -----------------
    // test_num_vertices
    // -----------------

    TYPED_TEST(TestGraph, TEST_NUM_VERTICES_1) 
    {
        typename TestFixture::vertices_size_type vs = num_vertices(this->g);
        ASSERT_TRUE(vs == 8);
    }

    TYPED_TEST(TestGraph, TEST_NUM_VERTICES_2) 
    {
        typename TestFixture::vertices_size_type vs = num_vertices(this->empty_g);
        ASSERT_TRUE(vs == 0);
    }

    TYPED_TEST(TestGraph, TEST_NUM_VERTICES_3) 
    {
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        typename TestFixture::vertices_size_type vs = num_vertices(this->empty_g);
        ASSERT_TRUE(vs == 5);
    }

    // -----------
    // test_source
    // -----------

    TYPED_TEST(TestGraph, TEST_SOURCE_1) 
    {
        typename TestFixture::vertex_descriptor vd = source(this->edAB, this->g);
        ASSERT_TRUE(vd == this->vdA);
    }

    TYPED_TEST(TestGraph, TEST_SOURCE_2) 
    {
        typename TestFixture::vertex_descriptor vd = source(this->edBD, this->g);
        ASSERT_TRUE(vd == this->vdB);
    }

    TYPED_TEST(TestGraph, TEST_SOURCE_3) 
    {
        typename TestFixture::vertex_descriptor vd = source(this->edBE, this->g);
        ASSERT_TRUE(vd == this->vdB);
    }

    TYPED_TEST(TestGraph, TEST_SOURCE_4) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::edge_descriptor e = add_edge(v1, v2, this->empty_g).first;
        typename TestFixture::vertex_descriptor vd = source(e, this->empty_g);
        ASSERT_TRUE(vd == v1);
    }

    // -----------
    // test_target
    // -----------

    TYPED_TEST(TestGraph, TEST_TARGET_1) 
    {
        typename TestFixture::vertex_descriptor vd = target(this->edAB, this->g);
        ASSERT_TRUE(vd == this->vdB);
    }

    TYPED_TEST(TestGraph, TEST_TARGET_2) 
    {
        typename TestFixture::vertex_descriptor vd = target(this->edBD, this->g);
        ASSERT_TRUE(vd == this->vdD);
    }

    TYPED_TEST(TestGraph, TEST_TARGET_3) 
    {
        typename TestFixture::vertex_descriptor vd = target(this->edBE, this->g);
        ASSERT_TRUE(vd == this->vdE);
    }

    TYPED_TEST(TestGraph, TEST_TARGET_4) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::edge_descriptor e = add_edge(v1, v2, this->empty_g).first;
        typename TestFixture::vertex_descriptor vd = target(e, this->empty_g);
        ASSERT_TRUE(vd == v2);
    }

    // -----------
    // test_vertex
    // -----------

    TYPED_TEST(TestGraph, TEST_VERTEX_1) 
    {
        typename TestFixture::vertex_descriptor vd = vertex(0, this->g);
        ASSERT_TRUE(vd == this->vdA);
    }

    TYPED_TEST(TestGraph, TEST_VERTEX_2) 
    {
        typename TestFixture::vertex_descriptor vd = vertex(1, this->g);
        ASSERT_TRUE(vd == this->vdB);
    }

    TYPED_TEST(TestGraph, TEST_VERTEX_3) 
    {
        typename TestFixture::vertex_descriptor vd = vertex(2, this->g);
        ASSERT_TRUE(vd == this->vdC);
    }

    TYPED_TEST(TestGraph, TEST_VERTEX_4) 
    {
        typename TestFixture::vertex_descriptor v = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor vd = vertex(0, this->g);
        ASSERT_TRUE(vd == v);
    }

    // -------------
    // test_vertices
    // -------------

    TYPED_TEST(TestGraph, TEST_VERTICES_1) 
    {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdA);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdB);}
    }

    TYPED_TEST(TestGraph, TEST_VERTICES_2) 
    {
        //empty graph
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->empty_g);
        ASSERT_TRUE(p.first == p.second);
    }

    TYPED_TEST(TestGraph, TEST_VERTICES_3) 
    {
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->empty_g);
        ASSERT_TRUE(distance(p.first, p.second) == 4);
    }

    // --------------
    // test_has_cycle
    // --------------

    TYPED_TEST(TestGraph, TEST_HAS_CYCLE_1) 
    {
        ASSERT_TRUE(has_cycle(this->g));
    }

    TYPED_TEST(TestGraph, TEST_HAS_CYCLE_2) 
    {
        ASSERT_TRUE(!has_cycle(this->empty_g));
    }

    TYPED_TEST(TestGraph, TEST_HAS_CYCLE_3) 
    {
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        add_vertex(this->empty_g);
        ASSERT_TRUE(!has_cycle(this->empty_g));
    }

    TYPED_TEST(TestGraph, TEST_HAS_CYCLE_4) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v3 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v4 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v5 = add_vertex(this->empty_g);
        add_edge(v1, v2, this->empty_g);
        add_edge(v2, v3, this->empty_g);
        add_edge(v3, v4, this->empty_g);
        add_edge(v4, v5, this->empty_g);
        add_edge(v5, v1, this->empty_g);
        ASSERT_TRUE(has_cycle(this->empty_g));
    }
    

    // ---------------------
    // test_topological_sort
    // ---------------------

    TYPED_TEST(TestGraph, TEST_TOPOLOGICAL_SORT_1) 
    {
        std::ostringstream out;
        ASSERT_THROW(topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " ")), not_a_dag);
    }

    TYPED_TEST(TestGraph, TEST_TOPOLOGICAL_SORT_2) 
    {
        typename TestFixture::vertex_descriptor v1 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v2 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v3 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v4 = add_vertex(this->empty_g);
        typename TestFixture::vertex_descriptor v5 = add_vertex(this->empty_g);
        add_edge(v1, v2, this->empty_g);
        add_edge(v2, v3, this->empty_g);
        add_edge(v3, v4, this->empty_g);
        add_edge(v4, v5, this->empty_g);
        std::ostringstream out;
        topological_sort(this->empty_g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_TRUE(out.str() == "4 3 2 1 0 ");
    }

