// Author: Caden Kroonenberg
// Date: November 8, 2021
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <utility>
#include <list>
#include <vector>
#include <iostream> // TODO: Remove
#include <limits.h>

#ifndef MY_GRAPH
#define MY_GRAPH

class EdgeType {
    public:
        int _dist;
        bool _valid;
        EdgeType(int distance) : _dist(distance), _valid(true) {}
        EdgeType(const EdgeType& e) : _dist(e._dist), _valid(e._valid) {}
        void setValid(bool validity) {
            _valid = validity;
        }
};

class NodeType {
    friend class myGraph;
    public:
        int id;
        std::string city;
        NodeType(std::string name) : city(name), _visited(false), id(-1) {}
        NodeType(const NodeType& n) : city(n.city), _visited(n._visited), id(n.id) {}
        ~NodeType() {}
        void setID(int ID ) {
            id = ID;
        }
        int getID() {
            return id;
        }
    private:
        bool _visited;
        std::vector<std::pair<NodeType*, EdgeType>> _paths;

        void addEdge(NodeType* n, EdgeType& e) {
            // std::cout << "node " << city << " addEdge(" << n->city << "," << e._dist << ")\n";
            _paths.push_back(std::make_pair(n, e));
        }

        bool hasPathTo(NodeType* n) {
            if( std::find_if(_paths.begin(), _paths.end(), [n](std::pair<NodeType*, EdgeType> p) { return p.first == n; }) != _paths.end() )
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
                    return &_paths[i].second;
                }
            }

            return nullptr;
        }
        
        bool deleteEdge(NodeType* node) {
            if(!hasPathTo(node)) {
                return false;
            }
            // EdgeType edge = *getEdge(node);
            std::pair<NodeType*, EdgeType> pair = std::make_pair(node, *getEdge(node));
            // _paths.erase(std::remove(_paths.begin(), _paths.end(), pair), _paths.end());
            
            std::vector<std::pair<NodeType *, EdgeType>>::iterator position = std::find_if(_paths.begin(), _paths.end(), [node](std::pair<NodeType*, EdgeType> p) { return p.first == node; });
            if (position != _paths.end()) {// == _paths.end() means the element was not found
                _paths.erase(position);
            }
            return true;
        }

        void printPaths() {
            std::cout << city << "\n";
            for(int i = 0; i < getDegree(); i++) {
                std::cout << "\t" << _paths[i].first->city << "\t" << _paths[i].second._dist << "\n";
            }
        }
};

class myGraph {
    public:
        myGraph() {}
        ~myGraph() {}

        int addNode(NodeType n) {
            int idx = nextIdx();
            if(idx == nodes.size()) {
                nodes.push_back(n);
            } else {
                nodes[idx] = n;
            }
            nodes[idx].id = idx; // +1;
            // std::cout << "addNode - " << idx << " - " << nodes[idx].city << " - " << nodes[idx].getID() << "\n";
            return idx;
        }

        NodeType getNode(const int id) {
            // int idx = (id-1) % nodes.size();
            return nodes[id];
        }

        bool addEdge(EdgeType& e, const int id1, const int id2) {
            // int idx1 = (id1-1) % nodes.size();
            // int idx2 = (id2-1) % nodes.size();
            // std::cout << "addEdge(" << e._dist << "," << id1 << "," << id2 << ")\n";
            if(id1 > nodes.size() || id2 > nodes.size()) {
                // std::cout << "addEdge returning false\n";
                return false;
            }
            nodes[id1].addEdge(&nodes[id2], e);
            nodes[id2].addEdge(&nodes[id1], e);
            return true;
        }

        bool isConnected(const int id1, const int id2) {
                // int idx1 = (id1-1) % nodes.size();
                // int idx2 = (id2-1) % nodes.size();
                return _isConnected(id1, id2);
        }

        EdgeType getEdge(const int id1, const int id2) {
            // int idx1 = (id1-1) % nodes.size();
            // int idx2 = (id2-1) % nodes.size();
            if(!isConnected(id1, id2)) {
                EdgeType e(-1);
                e.setValid(false);
                return e;
            }
            return *nodes[id1].getEdge(&nodes[id2]);
        }

        int getDegree(int id) {
            // int idx = (id - 1) % nodes.size();
            // std::cout << "getDegree(" << idx << "):";
            return nodes[id].getDegree();
        }

        bool deleteNode(const int id) {
            // int idx = (id-1) % nodes.size();
            // std::cout << "deleteNode(" << idx << ")\n";
            if(id > nodes.size() || std::find(_emptyIdxs.begin(), _emptyIdxs.end(), id) != _emptyIdxs.end()) {
                // std::cout << "deleteNode() returning false\n";
                return false;
            }
            for(int i = 0; i < nodes.size(); i++) { // Delete all edges
                if(_isConnected(id, i)) {
                    _deleteEdge(id, i);
                }
            }
            _emptyIdxs.push_back(id);
            //std::cout << "deleteNode() returning true\n";
            return true;
        }

        bool deleteEdge(const int id1, const int id2) {
            // int idx1 = (id1 - 1) % nodes.size();
            // int idx2 = (id2 - 1) % nodes.size();
            return _deleteEdge(id1, id2);
        }

        void BFS(const int id, std::vector<std::string> & path) {
            const int V = nodes.size();
            int idx = (id-1) % V;    // Account for 1-indexing on BFS call
            
            // Mark all the vertices as not visited
            for(int i = 0; i < V; i++)
                nodes[i]._visited = false;

            std::list<int> queue;
            nodes[idx]._visited = true;   // Visit source node
            queue.push_back(idx);    // Push back source node

            while (!queue.empty()) {
                int currVertex = queue.front();         // Start at front
                path.push_back(nodes[currVertex].city); // Add front city
                queue.pop_front();                      // Pop front
                std::vector<int> curr_adj_ids;
                for(int i = 0; i < nodes[currVertex].getDegree(); i++) { // Push back all adjacent cities to front node if not visited
                    curr_adj_ids.push_back(nodes[currVertex]._paths[i].first->getID());
                }
                std::sort(curr_adj_ids.begin(), curr_adj_ids.end());
                // std::reverse(curr_adj_ids.begin(), curr_adj_ids.end());
                for(int i = 0; i < nodes[currVertex].getDegree(); i++) { // Push back all adjacent cities to front node if not visited
                    if(!nodes[curr_adj_ids[i]]._visited) {
                        nodes[curr_adj_ids[i]]._visited = true;    // Set as visited
                        queue.push_back(nodes[curr_adj_ids[i]].getID());    // Push back
                    }
                }
            }
        }
        /*
        void printAll() {
            for(int i = 0; i < nodes.size(); i++) {
                std::cout << i << ")\t" << nodes[i].city << "\n";
            }
        }
        */
        void DFS(const int id, std::vector<std::string> & path) {
            const int V = nodes.size();
            int idx = (id - 1) % V;
            for(int i = 0; i < V; i++)
                nodes[i]._visited = false;
            _DFS(idx, path);
        }

        int shortestPath(const int id1, const int id2, std::vector<std::string> & path) {
            const int idx1 = (id1-1) % nodes.size();
            const int idx2 = (id2-1) % nodes.size();
            
            if(!isReachable(id1, id2)) { // Needs to be a recursive check for connectivity
                return -1;
            }
            
            return dijkstra(idx1, idx2, path);
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

        void _DFS(const int id, std::vector<std::string> & path) {
            std::vector<int> S;
            S.push_back(nodes[id].getID()); // Initialize S to be a stack with one element s

            while(!S.empty()) { // While S is not empty
                int u = S.back();
                S.pop_back(); // Take a node u from S
                
                if(!nodes[u]._visited) { // If Explored[u] = false then
                    nodes[u]._visited = true; // Set Explored[u] = true
                    path.push_back(nodes[u].city); // Track explored cities in path
                    std::vector<int> u_adj_ids;
                    for(int i = 0; i < nodes[u].getDegree(); i++) { // Order each edge (u,v) incident to u
                        u_adj_ids.push_back(nodes[u]._paths[i].first->getID());
                    }
                    // Sort nodes adjacent to u
                    std::sort(u_adj_ids.begin(), u_adj_ids.end());
                    // Reverse sorted nodes so they can be visited in order out of S
                    std::reverse(u_adj_ids.begin(), u_adj_ids.end());
                    for(int i = 0; i < nodes[u].getDegree(); i++) { // For each edge (u,v) (ordered) incident to u
                        S.push_back(u_adj_ids[i]); // Add v to the stack S
                    }
                }
            }
        }

        int minDistance(std::pair<int,std::vector<std::string>> dist[], bool sptSet[]) {
            const int V = nodes.size();
            // Initialize min value
            int min = INT_MAX;
            int min_index;
            for (int v = 0; v < V; v++) {
                if (sptSet[v] == false && dist[v].first <= min) {
                    min = dist[v].first;
                    min_index = v;
                }
            }
        
            return min_index;
        }

        int dijkstra(const int id1, const int id2, std::vector<std::string> & path) {
            const int V = nodes.size();
            std::pair<int,std::vector<std::string>> dist[V]; // The output array.  dist[i] will hold the shortest distance from id1 to i
            bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
            // path tree or shortest distance from id1 to i is finalized
        
            // Initialize all distances as INFINITE and stpSet[] as false
            for (int i = 0; i < V; i++) {
                dist[i].first = INT_MAX, sptSet[i] = false;
                dist[i].second.push_back(nodes[i].city);
            }
        
            // Distance of source vertex from itself is always 0
            dist[id1].first = 0;
        
            // Find shortest path for all vertices
            for (int count = 0; count < V - 1; count++) {
                // Pick the minimum distance vertex from the set of vertices not
                // yet processed. u is always equal to id1 in the first iteration.
                int u = minDistance(dist, sptSet);
        
                // Mark the picked vertex as processed
                sptSet[u] = true;
        
                // Update dist value of the adjacent vertices of the picked vertex.
                for (int v = 0; v < V; v++) {
                    // Update dist[v] only if is not in sptSet, there is an edge from
                    // u to v, and total weight of path from id1 to  v through u is
                    // smaller than current value of dist[v]
                    if (!sptSet[v] && _isConnected(u, v) && dist[u].first != INT_MAX && dist[u].first + getEdge(u, v)._dist < dist[v].first) {
                        dist[v].first = dist[u].first + getEdge(u, v)._dist;
                        // Track new best path
                        dist[v].second.clear();
                        dist[v].second.push_back(nodes[v].city);
                        dist[v].second.insert(dist[v].second.end(), dist[u].second.begin(), dist[u].second.end()); // append path[u] to path[v]
                    }
                }
            }
            // print the constructed distance array
            // printSolution(dist);
            std::reverse(dist[id2].second.begin(), dist[id2].second.end());
            path = dist[id2].second;
            return dist[id2].first;   // Distance is calculated correctly
        }

        bool isReachable(int id1, int id2) {
            const int id = id1;
            const int V = nodes.size();
            // Base case
            if (id1 == id2) {
                return true;
            }
        
            int idx = (id-1) % V;    // Account for 1-indexing on BFS call
            
            // Complete BFS to determine if any path exists between id1 and id2 
        
            // Mark all the vertices as not visited
            for(int i = 0; i < V; i++)
                nodes[i]._visited = false;

            std::list<int> queue;
            nodes[idx]._visited = true;   // Visit source node
            queue.push_back(idx);    // Push back source node

            while (!queue.empty()) {
                int currVertex = queue.front();         // Start at front
                queue.pop_front();                      // Pop front
                std::vector<int> curr_adj_ids;
                for(int i = 0; i < nodes[currVertex].getDegree(); i++) { // Push back all adjacent cities to front node if not visited
                    curr_adj_ids.push_back(nodes[currVertex]._paths[i].first->getID());
                }
                std::sort(curr_adj_ids.begin(), curr_adj_ids.end());

                for(int i = 0; i < nodes[currVertex].getDegree(); i++) { // Push back all adjacent cities to front node if not visited
                    if(curr_adj_ids[i] == id2) {
                        return true;
                    }
                    if(!nodes[curr_adj_ids[i]]._visited) {
                        nodes[curr_adj_ids[i]]._visited = true;    // Set as visited
                        queue.push_back(nodes[curr_adj_ids[i]].getID());    // Push back
                    }
                }
            }
            return false; // id2 was not found during BFS
        }
};
#endif // MY_GRAPH