#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>

using namespace std; 

#ifndef NEWMAZEGENERATOR_HPP
#define NEWMAZEGENERATOR_HPP

class NewMazeGenerator: public MazeGenerator
{

private: 
        vector<vector<int>> map; 

public:
        NewMazeGenerator(); 
        virtual void generateMaze(Maze& maze);
        void start_map(Maze& maze);
        void create_maze(int x, int y, Maze& maze); 
        vector<Direction> check_move(int x, int y, Maze& maze); 
		void make_move(int& x, int& y, Direction direction);
		~NewMazeGenerator(); 
};

#endif 
