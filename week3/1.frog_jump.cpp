/*

Frog Jumping

(INOI 2005)

The latest hit on TV is a jumping game played on a giant rectangular chessboard. Each participant dresses up in a green frog suit and starts at the top left corner of the board. On every square there is a spring-loaded launcher that can propel the person either to the right or down.

Each launcher has two quantities R and D associated with it. The launcher can propel the person upto R squares to the right and upto D squares down. The participant can set the direction of the launcher to Right or Down and set the number of squares to jump to any number between 1 and R squares when jumping right, or between 1 and D squares when jumping down. The winner is the one who can reach bottom right corner of the chessboard in the smallest number of jumps.

For instance, suppose you have 3 × 4 chessboard as follows. In each square, the pair of numbers indicates the quantities (R,D) for the launcher on that square.

(1,2)	(1,2)	(1,2)	(2,1)
(3,1)	(1,1)	(1,2)	(1,2)
(1,1)	(1,1)	(1,2)	(2,2)
Here, one way to reach the bottom right corner is to first jump 1 square right, then jump 2 squares down to the bottom row, then jump right two times, one square a time, for a total of 4 jumps. Another way is to first jump 1 square down, then jump 3 squares right to the last column and finally jump one square down to the bottom right corner, for a total of 3 jumps. On this board, it is not possible to reach the bottom right corner in fewer than 3 jumps.

Your task is to write a program to calculate the smallest number of jumps needed to go from the top left corner to the bottom right corner, given the layout of the launchers on the board.

*/

#include <iostream>
#include <queue>
void BFS(int start,bool **a,int nodes,int *distance)
{
	std::queue <int>q;
	distance[start] = 0;
	q.push(start);

	bool flag = false;
	while(!q.empty())
	{
		int curr = q.front();
		q.pop();
		for(int j = 0;j < nodes; j++)
		{
			if(a[curr][j] == true && distance[j] == -1)
			{
				distance[j] = 1 + distance[curr];
				if(j == nodes - 1)
				{
					flag = true;
					break;
				}
				q.push(j);
			}
		}
		if(flag)
			break;
	}
}

int roofValue(int x, int y)
{
	if(x % y == 0)
		return x/y;
	else
		return (x/y + 1);
}

bool** dynamic2DString(int row,int column)
{
	bool** array = new bool*[row];
	int i;
	for(i = 0;i < row;i++)
		array[i] = new bool[column];
	return array;
}

int main()
{
	int m,n;
	std::cin >> m >> n;
	
	//	adjacency matrix formation
	int v = m * n;

	bool **adj = dynamic2DString(v,v);

	//	initially no connections
	for(int i = 0;i < v; i++)
		for(int j = 0;j < v; j++)
			adj[i][j] = 0;

	//	connections made
	int x;
	for(int i = 0;i < v; i++)
	{
		std::cin >> x;
		for(int j = 1;j <= x; j++)
		{
			if(i + 1 + j <= roofValue(i+1, n) * n)
				adj[i][i+j] = 1;
			else
				break;
		}
	}
	for(int i = 0;i < v; i++)
	{
		std::cin >> x;
		for(int j = 1;j <= x; j++)
			if(i + (n*j) < v)
				adj[i][i + (n*j)] = 1;
	}

	//	distance array formed(visited)
	int distance[v];

	for(int i = 0;i < v; i++)
		distance[i] = -1;
	BFS(0, adj, v, distance);
	std::cout<<distance[v-1]<<std::endl;
	return 0;
}