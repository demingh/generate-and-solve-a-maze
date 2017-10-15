#include "NewMazeSolver.hpp"
#include <random> 
#include <ics46/factory/DynamicFactory.hpp> 

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, NewMazeSolver,"Deming's solution(REQUIRED)"); 

random_device device_solver; //create a random_device object outside the function to avoid open two many files for create_solution function


NewMazeSolver::NewMazeSolver(){} 
/*class NewMazeSolver default constructor */

void NewMazeSolver:: solveMaze(const Maze& maze, MazeSolution& mazeSolution)
/*this function called to start mark the maze and generate the solution*/
{	
	start_map(mazeSolution); 
	create_solution(mazeSolution.getStartingCell().first, mazeSolution.getStartingCell().second,maze,mazeSolution);
}

void NewMazeSolver::start_map(MazeSolution& mazeSolution) 
/*mark each unvisited cell as 0 in this 2D vector */
{	
	mazeSolution.restart(); 
	map.resize(mazeSolution.getWidth()); 
	for (int n=0; n<mazeSolution.getWidth(); n++) 
		{
			map[n].resize(mazeSolution.getHeight()); 
		}
	for (int i=0; i<mazeSolution.getWidth(); i++)
		{
			for(int j=0; j<mazeSolution.getHeight(); j++)
				{	
					map[i][j]=0; 
				}
		}
}

vector<Direction> NewMazeSolver::check_move(int x, int y, const Maze& maze, MazeSolution& mazeSolution)
/*check every position's possible moves and add those possible moves to a Vector<Direction> object*/
{
	vector<Direction> move; 
	if(y>=1)
	{
		if(!maze.wallExists(x, y, Direction::up)&&map[x][y-1]==0)
		{
			move.push_back(Direction::up); 
		}
	}
	if(y<=mazeSolution.getHeight()-2)
	{
		if(!maze.wallExists(x,y, Direction::down)&&map[x][y+1]==0)
		{
			move.push_back(Direction::down); 
		}
	}	
	if(x>=1)
	{
		if(!maze.wallExists(x,y, Direction::left)&&map[x-1][y]==0)
		{
			move.push_back(Direction::left); 
		}
	}
	if(x<=mazeSolution.getWidth()-2)
	{
		if(!maze.wallExists(x,y,Direction::right)&&map[x+1][y]==0)
		{
			move.push_back(Direction::right); 
		} 
	} 	
	return move; 
}

void NewMazeSolver:: create_solution(int x, int y, const Maze& maze,MazeSolution& mazeSolution)
/*using recursive function to generate the maze solution*/
{	
		map[x][y]=1; 
		vector<Direction> dir=check_move(x, y, maze, mazeSolution); 
		while(dir.size()!=0)
		{
			int n=dir.size()-1; 
			default_random_engine engine{device_solver()}; 
			uniform_int_distribution<int> dis{0,n}; 
			Direction new_dir=dir[dis(engine)]; 
			if(!maze.wallExists(x,y,new_dir))
			{	
				if(mazeSolution.isComplete())
				{
					return; 
				}
				mazeSolution.extend(new_dir);
				create_solution(mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second, maze, mazeSolution);
			}			
		}
		if(mazeSolution.isComplete())
		{
			return; 
		}	
		mazeSolution.backUp();
		create_solution(mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second, maze, mazeSolution);	
}

NewMazeSolver::~NewMazeSolver(){} //Clase destructor 

	

		 



	
	