#include <string>
#include <vector>
#include <utility> 
#include "myDisjointSets_c699k482.h"
#include <iostream>
#include <fstream>
#include "myMaze_c699k482.h"
using namespace std;


int main(int argc, char* argv[])
{
      if (argc != 2)
      {
            std::cout << "You have to provide one test data file and output file name to run the MainTest!\n";
            return 0;
      }
      
      ifstream inFile;
      inFile.open(argv[1]);
      vector<int> tmp;
      if (inFile.is_open())
      {
            int str;
            while(!inFile.eof())
            {
                inFile >> str;
                tmp.push_back(str);
            }
            // myDisjointSets* mds = new myDisjointSets(tmp[0]);
            // int number_of_pairs = int((tmp.size()-1)/2);
            // for(int i = 0; i < int(number_of_pairs/2); i++)
            // {
            //     mds->unionSets( mds->find(tmp[2*i+1]), mds->find(tmp[2*i+2]));
            // }
            // for(int i = 0; i < tmp.size(); i++)
            // {
            //     std::cout << mds->getSetSize(i) << " ";
            // }
            // cout<<endl;
            //test myMaze
            int col = tmp[1]%10;
            int squ = col*(col+1);
            myMaze m1(col,col+1);
            vector<pair<int, int> > broken_walls;
            vector<int> path;
            m1.buildMaze(broken_walls);
            m1.solveMaze(path);
            int num_breakwalls = squ - 1;
            if (broken_walls.size() == num_breakwalls)
            {
                cout<<"1"<<endl;
            }else
            {
                cout<<"0"<<endl;
            }   
            vector<pair<int, int> >::iterator it;
            pair<int,int> tmp_pair;
            // cout << "maze size: " << squ << endl;
            // cout << "path size: " << path.size() << endl;
            // cout << "walls:\n";
            for(int i = 0; i < broken_walls.size(); i++) {
                // cout << broken_walls[i].first << " " << broken_walls[i].second << "\n";
            }
            for (size_t i = 0; i < path.size(); i++)
            {
                if(i+1<path.size())
                {
                    if( path[i]< path[i+1])
                    {
                        tmp_pair = make_pair(path[i],path[i+1]);
                    }
                    else
                    {
                        tmp_pair = make_pair(path[i+1],path[i]);
                    }
                    it = find (broken_walls.begin(), broken_walls.end(), tmp_pair);
                    if(it != broken_walls.end())
                    {
                            cout<<"1"<<endl;
                    } 
                    else
                    {
                            cout<<"0"<<endl;
                    }
                }
            }  
            //delete mds;         
      }
      else
      {
            cout << "The data file cannot be opened";
      }
      inFile.close();
    
    return 1;
}

