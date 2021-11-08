// Author: Caden Kroonenberg
// Date: November 5, 2021

#ifndef MY_MAZE
#define MY_MAZE
#include <utility>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include "myDisjointSets.h"

class myMaze {
    public:
    myMaze(const int m, const int n) : size(m*n), r(m), c(n){
        djs = new myDisjointSets(size);
        std::srand(std::time(0));
    }
    ~myMaze() {
        delete djs;
    }

    void buildMaze(std::vector<std::pair<int,int>> & broken_walls) {
        while(djs->getSetSize(0)!=size) {
            int a = rand() % size;          // Randomly select a
            int b = findValidNeighbor(a);   // Find valid neighbor b (if no valid neighbor, b = a)
            if(a!=b) {                      // Check if b is valid
                djs->unionSets(djs->find(a), djs->find(b));
                std::pair<int,int> pair;
                if (a < b) {
                    pair = std::make_pair(a, b);
                } else {
                    pair = std::make_pair(b, a);
                }
                broken_walls.push_back(pair);
            }
        }
        brkn_walls = broken_walls;
    }

    void solveMaze(std::vector<int> & path) {
        path = std::vector<int>(0);
        _solveMaze(path, 0);
        // std::cout << "Path: ";
        for(int i = 0; i < path.size(); i++) {
            // std::cout << path[i] << " ";
        }
        // std::cout << "\n";

    }

    private:
    myDisjointSets* djs;
    std::vector<std::pair<int,int>> brkn_walls;
    const int size;
    const int r;
    const int c;

    bool _solveMaze(std::vector<int> & path, int step) {
        // if(!path.empty() && path[path.size()-1] == size-1) // if done
        if(!hasBeenVisited(step, path)) {
            path.push_back(step);
        }
        if(!path.empty()) {
            if(path.back() == size - 1) {
                return(true);
            }
        }

        if(top_valid(step) && isValidPath(step, top_neighbor(step)) && !hasBeenVisited(top_neighbor(step), path)) {
            // std::cout << "top_valid(" << step << "): " << top_valid(step) << "\t" << "top_neighbor(" << step << "): " << top_neighbor(step) << "\n";
            if(_solveMaze(path, top_neighbor(step))) {
                // path.push_back(top_neighbor(step));
                return(true);
            }
        }
        
        if(right_valid(step) && isValidPath(step, right_neighbor(step)) && !hasBeenVisited(right_neighbor(step), path)) {
            // std::cout << "right_valid(" << step << "): " << right_valid(step) << "\t" << "right_neighbor(" << step << "): " << right_neighbor(step) << "\n";
            if(_solveMaze(path, right_neighbor(step))) {
                // path.push_back(right_neighbor(step));
                return(true);
            }
        }

        if(bottom_valid(step) && isValidPath(step, bottom_neighbor(step))  && !hasBeenVisited(bottom_neighbor(step), path)) {
            // std::cout << "bottom_valid(" << step << "): " << bottom_valid(step) << "\t" << "bottom_neighbor(" << step << "): " << bottom_neighbor(step) << "\n";
            if(_solveMaze(path, bottom_neighbor(step))){
                // path.push_back(bottom_neighbor(step));
                return(true);
            }
            
        }

        if(left_valid(step) && isValidPath(step, left_neighbor(step)) && !hasBeenVisited(left_neighbor(step), path)) {
            // std::cout << "left_valid(" << step << "): " << left_valid(step) << "\t" << "left_neighbor(" << step << "): " << left_neighbor(step) << "\n";

            if(_solveMaze(path, left_neighbor(step))) {
                // path.push_back(left_neighbor(step));
                return(true);
            }
        }
        //path.erase(std::remove(path.begin(), path.end(), step), path.end());
        path.pop_back();
        // std::cout << "returning false\n";
        // remove step from path
        return(false);
    }

    bool isValidPath(int a, int b) {
        std::pair<int, int> x;
        if(a < b) {
            x = std::make_pair(a, b);
        } else {
            x = std::make_pair(b, a);
        }
        if(std::find(brkn_walls.begin(), brkn_walls.end(), x) != brkn_walls.end()) {
            // std::cout << "pair " << x.first << " " << x.second << " is valid\n";
            return true;
        } else {
            // std::cout << "pair " << x.first << " " << x.second << " is invalid\n";
            return false;
        }
    }

    bool hasBeenVisited(int a, std::vector<int> path) {
        return std::find(path.begin(), path.end(), a) != path.end();
    }

    int findValidNeighbor(int i) {
        std::vector<int> vec;
        int i_c = djs->find(i);
        if(top_valid(i) && i_c != djs->find(i-c)) {         // Check if top neighbor is valid
            vec.push_back(top_neighbor(i));
        }
        if(right_valid(i) && i_c != djs->find(i+1)) {     // Check if right neighbor is valid
            vec.push_back(right_neighbor(i));
        }
        if(bottom_valid(i) && i_c != djs->find(i+c)) {    // Check if bottom neighbor is valid
            vec.push_back(bottom_neighbor(i));
        }
        if(left_valid(i) && i_c != djs->find(i-1)) {                     // Check if left neighbor is valid
            vec.push_back(left_neighbor(i));
        }
        if(vec.size() != 0) {                                       // Choose random (valid) neighbor
            int idx = rand() % vec.size();
            return vec[idx];
        } else {
            return i;
        }
    }

    int top_neighbor(int i) {
        return (i - c);
    }

    int right_neighbor(int i) {
        return (i + 1);
    }

    int bottom_neighbor(int i) {
        return (i + c);
    }

    int left_neighbor(int i) {
        return (i - 1);
    }

    bool top_valid(int i) {
        return (top_neighbor(i) >= 0);
    }

    bool right_valid(int i) {
        return (right_neighbor(i)%c != 0);
    }

    bool bottom_valid(int i) {
        return (bottom_neighbor(i) < size);
    }

    bool left_valid(int i) {
        return (i%c != 0);
    }
};
#endif // MY_MAZE