// Author: Caden Kroonenberg
// Date: November 8, 2021
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <iostream> // TODO: Remove

#ifndef MY_GRAPH
#define MY_GRAPH

class EdgeType {
    public:
        int _dist;
        bool _valid;
        EdgeType(int distance) : _dist(distance), _valid(true) {}
        void setValid(bool validity) {
            _valid = validity;
        }
};

class NodeType {
    friend class myGraph;
    public:
        std::string city;
        NodeType(std::string name) : city(name) {}
        NodeType(const NodeType& n) : city(n.city) {}
        ~NodeType() {}
    private:
        std::vector<std::pair<NodeType*, EdgeType*>> _paths;

        void addEdge(NodeType* n, EdgeType* e) {
            _paths.push_back(std::make_pair(n, e));
        }

        bool hasPathTo(NodeType* n) {
            if( std::find_if(_paths.begin(), _paths.end(), [n](std::pair<NodeType*, EdgeType*> p) { return p.first == n; }) != _paths.end() )
            {
                return true;
            }
            return false;
        }

        int getDegree() {
            return _paths.size();
        }

        EdgeType* getEdge(NodeType* n) {
            for(int i = 0; i < _paths.size(); i++) {
                if(_paths[i].first == n) {
                    return _paths[i].second;
                }
            }

            return nullptr;
        }
        
        bool deleteEdge(NodeType* node) {
            if(!hasPathTo(node)) {
                return false;
            }
            EdgeType* edge = getEdge(node);
            std::pair<NodeType*, EdgeType*> pair = std::make_pair(node, edge);
            _paths.erase(std::remove(_paths.begin(), _paths.end(), pair), _paths.end());
            return true;
        }
};

class myGraph {
    public:
        myGraph() {}
        ~myGraph() {}

        int addNode(const NodeType & n) {
            int idx = nextIdx();
            if(idx == nodes.size()) {
                nodes.push_back(n);
            } else {
                nodes[idx] = n;
            }
            return idx;
        }

        NodeType getNode(const int id) {
            int idx = (id-1) % nodes.size();
            return nodes[idx];
        }

        bool addEdge(EdgeType & e, const int id1, const int id2) {
            int idx1 = (id1-1) % nodes.size();
            int idx2 = (id2-1) % nodes.size();
            // std::cout << "addEdge(" << idx1 << "," << idx2 << ")\n";
            if(idx1 > nodes.size() || idx2 > nodes.size()) {
                return false;
            }
            nodes[idx1].addEdge(&nodes[idx2], &e);
            nodes[idx2].addEdge(&nodes[idx1], &e);
            return true;
        }

        bool isConnected(const int id1, const int id2) {
                int idx1 = (id1-1) % nodes.size();
                int idx2 = (id2-1) % nodes.size();
                return _isConnected(idx1, idx2);
        }

        EdgeType getEdge(const int id1, const int id2) {
            int idx1 = (id1-1) % nodes.size();
            int idx2 = (id2-1) % nodes.size();
            if(!isConnected(idx1, idx2)) {
                EdgeType e(-1);
                e.setValid(false);
                return e;
            }
            return *nodes[idx1].getEdge(&nodes[idx2]);
        }

        int getDegree(int id) {
            int idx = (id - 1) % nodes.size();
            // std::cout << "getDegree(" << idx << "):";
            return nodes[idx].getDegree();
        }

        bool deleteNode(const int id) {
            int idx = (id-1) % nodes.size();
            // std::cout << "deleteNode(" << idx << ")\n";
            if(idx > nodes.size() || std::find(_emptyIdxs.begin(), _emptyIdxs.end(), idx) != _emptyIdxs.end()) {
                // std::cout << "deleteNode() returning false\n";
                return false;
            }
            for(int i = 0; i < nodes.size(); i++) { // Delete all edges
                if(_isConnected(idx, i)) {
                    _deleteEdge(idx, i);
                }
            }
            _emptyIdxs.push_back(idx);
            //std::cout << "deleteNode() returning true\n";
            return true;
        }

        bool deleteEdge(const int id1, const int id2) {
            int idx1 = (id1 - 1) % nodes.size();
            int idx2 = (id2 - 1) % nodes.size();
            return _deleteEdge(idx1, idx2);
        }

    private:
        std::vector<NodeType> nodes;
        std::vector<int> _emptyIdxs;

        int nextIdx() {
            int idx; // Next available index
            if(_emptyIdxs.empty()) {
                idx = nodes.size();
            } else {
                idx = _emptyIdxs.back();
                _emptyIdxs.pop_back();
            }
            return idx;
        }

        bool _deleteEdge(const int idx1, const int idx2) {
            // std::cout << "_deleteEdge(" << idx1 << "," << idx2 << ")\n";
            return nodes[idx1].deleteEdge(&nodes[idx2]) && nodes[idx2].deleteEdge(&nodes[idx1]);
        }

        bool _isConnected(const int idx1, const int idx2) {
            for(int i = 0; i < nodes.size(); i++) {
                // std::cout << "&nodes[" << i << "]:\t\t" << &nodes[i] << "\n";
            }
            // std::cout << "_isConnected(" << idx1 << "," << idx2 << ")\n";
            bool returnVal = nodes[idx1].hasPathTo(&nodes[idx2]) && nodes[idx2].hasPathTo(&nodes[idx1]);
            // std::cout << "isConnected(" << idx1 << ", " << idx2 << "):\t" << returnVal << "\n";
            // std::cout << "nodes[" << idx1 << "].getDegree =\t" << nodes[idx1].getDegree() << "\n";
            // std::cout << "&nodes[" << idx1 << "]:\t\t" << &nodes[idx1] << "\n";
            for(int i = 0; i < nodes[idx1]._paths.size(); i++) {
                // std::cout << "nodes[" << idx1 << "] edge " << i << ":\t" << nodes[idx1]._paths[i].first << "\n";
            }
            // std::cout << "nodes[" << idx2 << "].getDegree =\t" << nodes[idx2].getDegree() << "\n";
            // std::cout << "&nodes[" << idx2 << "]:\t\t" << &nodes[idx2] << "\n";
            for(int i = 0; i < nodes[idx2]._paths.size(); i++) {
                // std::cout << "nodes[" << idx2 << "] edge " << i << ":\t" << nodes[idx2]._paths[i].first << "\n";
            }
            return returnVal;
        }
};
#endif // MY_GRAPH