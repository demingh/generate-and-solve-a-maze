#include "NewMazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, NewMazeGenerator, "Deming's Algorithm(REQUIRED)"); 

random_device device; //create a random_device object outside the function to avoid open two many files for create_maze function

NewMazeGenerator::NewMazeGenerator(){}
/*default NewMazeZGenerator constructor */

void NewMazeGenerator::generateMaze(Maze& maze) 
/*this function generate maze from a random spot in the maze*/
{ 
    start_map(maze);
   	random_device _x,_y,_direction; 
	default_random_engine e_x{_x()},e_y{_y()};
	int height=maze.getHeight()-1; 
	int width=maze.getWidth()-1;
	uniform_int_distribution<int> dis_x{0,width};
	uniform_int_distribution<int> dis_y{0,height};
	int x=dis_x(e_x); 
	int y=dis_y(e_y); 
 	create_maze(x,y,maze); 
}

void NewMazeGenerator::start_map(Maze& maze) 
/*start a maze as 2D vector with all walls and set every cell 0 as not visited*/
{	
	maze.addAllWalls();
	map.resize(maze.getWidth()); 
	for (int n=0; n<maze.getWidth(); n++) 
		{
			map[n].resize(maze.getHeight()); 
		}
	for (int i=0; i<maze.getWidth(); i++)
		{
			for(int j=0; j<maze.getHeight(); j++)
				{	
					map[i][j]=0; 
				}
		}
}

void NewMazeGenerator::make_move(int& x, int& y, Direction direction) 
/*make a move to change the cell base on the direction in 2D vector */
{
	if(direction==Direction::up)
	{
  		y--; 
  	} 
  	if (direction==Direction::down)
  	{
  	 	y++; 
  	}
  	if (direction==Direction::left)
  	{
  		x--; 
  	}
  	if (direction==Direction::right)
  	{
  		x++; 
  	} 	
}

vector<Direction> NewMazeGenerator::check_move(int x, int y, Maze& maze)
/*check every position's possible moves and add those possible moves to a Vector<Direction> object*/
{		
	vector<Direction> move; 
	
	if(y>=1)
	{
		if(map[x][y-1]==0)
		{
			move.push_back(Direction::up);
		}
	}
	if(y<=maze.getHeight()-2)
	{
		if(map[x][y+1]==0)
		{
			move.push_back(Direction::down);
		}
	}
	if(x>=1)
	{
		if(map[x-1][y]==0)
		{
			move.push_back(Direction::left); 
		}
	}
	if(x<=maze.getWidth()-2)
	{
		if(map[x+1][y]==0)
		{
			move.push_back(Direction::right); 
		}
	}
	return move; 
}


void NewMazeGenerator::create_maze(int x, int y, Maze& maze)
/*create maze by mark any visited cell 1 and remove wall between cells*/
{
	map[x][y]=1; 
	vector<Direction> dir=check_move(x,y,maze);

	while(dir.size()!=0)
	{	
		int n=dir.size()-1; 
		default_random_engine engine{device()}; 
		uniform_int_distribution<int> dis{0, n}; 
		Direction new_dir=dir[dis(engine)];  
		int new_X=x; 
		int new_Y=y; 
		make_move(new_X, new_Y, new_dir); 
		if(map[new_X][new_Y]==0)
		{	
			maze.removeWall(x,y,new_dir);
			create_maze(new_X, new_Y, maze);
		} 
		dir=check_move(x,y,maze); 
	}
	
}

NewMazeGenerator::~NewMazeGenerator(){}
/*Class NewMazeGerator's destructor */
		
	