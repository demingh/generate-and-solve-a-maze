#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"


#ifndef NEWMAZESOLVER_HPP
#define NEWMAZESOLVER_HPP 

using namespace std; 

class NewMazeSolver: public MazeSolver
{
private:
	vector<vector<int>> map; 

public: 
	NewMazeSolver();	
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution); 
	vector<Direction> check_move(int x, int y, const Maze& maze, MazeSolution& mazeSolution);
	void create_solution(int x, int y, const Maze& maze,MazeSolution& mazeSolution);  
	void start_map(MazeSolution& mazeSolution); 
	~NewMazeSolver(); 
};



#endif
