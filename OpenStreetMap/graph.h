// graph.h <Starter Code>
// Maria Bezerra
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Spring 2023
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {

private:
    map<VertexT, map<VertexT, WeightT>> adjacentMap;
    vector<VertexT>  Vertices;

public:

    // NumVertices
    //
    // Returns the # of vertices currently in the graph.
    //
    int NumVertices() const { ////DONE
        return adjacentMap.size();
    }

    //
    // NumEdges
    //
    // Returns the # of edges currently in the graph.
    //
    int NumEdges() const { ////DONE
        // loop through the adjacency matrix and count how many
        // edges currently exist:

        int count = 0;
        for (auto x : adjacentMap) {
            count += x.second.size();
        }
        return count;
    }

    // addVertex

    bool addVertex(VertexT v) { ////DONE
        map<VertexT, WeightT> newAdjacentMap;
        if (adjacentMap.count(v)) { //return false if the vertex is already inside the map
            return false;
        }

        adjacentMap[v] = newAdjacentMap;
        return true;

    }


    // addEdge
    bool addEdge(VertexT from, VertexT to, WeightT weight) { ////DONE
        if (!adjacentMap.count(from)) {
            return false;
        }

        if (!adjacentMap.count(to)) {
            return false;
        }

        adjacentMap[from][to] = weight;

        return true;
    }

    //
    // getWeight
    //
    // Returns the weight associated with a given edge.  If
    // the edge exists, the weight is returned via the reference
    // parameter and true is returned.  If the edge does not
    // exist, the weight parameter is unchanged and false is
    // returned.
    //
    bool getWeight(VertexT from, VertexT to, WeightT& weight) const { ////DONE
        if (adjacentMap.count(from) && adjacentMap.at(from).count(to)) {
            weight = adjacentMap.at(from).at(to);
            return true;
        }

        else {
            return false;
        }
    }

    //
    // neighbors
    //
    // Returns a set containing the neighbors of v, i.e. all
    // vertices that can be reached from v along one edge.
    // Since a set is returned, the neighbors are returned in
    // sorted order; use foreach to iterate through the set.
    //
    set<VertexT> neighbors(VertexT v) const { ////DONE
        set<VertexT>  S;
        if (adjacentMap.count(v) == 0) {
            return S;
        }

        // Iterate over all adjacent vertices and insert them into the set
        for (auto x : adjacentMap.at(v)) {
            S.insert(x.first);
        }
        return S;
    }

    //
    // getVertices
    //
    // Returns a vector containing all the vertices currently in
    // the graph.
    //
    vector<VertexT> getVertices() const { ////DONE
        vector<VertexT> vert;

        for(auto a: adjacentMap){
            vert.push_back(a.first);
        }
        return vert;  // returns a copy
    }


    void dump(ostream& output) const { ////DONE
        output << "***************************************************" << endl;
        output << "********************* GRAPH ***********************" << endl;

        output << "**Num vertices: " << this->NumVertices() << endl;
        output << "**Num edges: " << this->NumEdges() << endl;

        output << endl;
        output << "**Vertices:" << endl;
        for (auto const& vertex : this->adjacentMap) {
            output << " " << vertex.first << endl;
        }

        output << endl;
        output << "**Edges:" << endl;
        for (auto const& vertex : this->adjacentMap) {
            VertexT from = vertex.first;
            for (auto const& neighbor : vertex.second) {
                VertexT to = neighbor.first;
                WeightT weight = neighbor.second;
                output << " " << from << " -> " << to << " : " << weight << endl;
            }
        }
        output << "**************************************************" << endl;
    }

};
