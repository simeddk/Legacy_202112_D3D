#include <stdio.h>
#include <string>
#include <Windows.h>

#define MAX 1024
#define INIT -1

#define START 'S'
#define GOAL 'G'
#define WAY ' '
#define WALL '#'
#define MARKED '+'
#define BACK 'X'

enum class Direction { Up, Down, Right, Left };

struct Vector
{
	int X, Y;
};

struct MazeDesc
{
	int Rows;
	int Cols;

	char** Data;
};

void ReadFile(const char* path, MazeDesc* maze)
{
	FILE* fp = nullptr;
	fopen_s(&fp, path, "r");

	int rows = 0, cols = INIT;
	char buffer[MAX];

	while (fgets(buffer, MAX, fp) != nullptr)
	{
		rows++;

		if (cols == INIT)
			cols = (int)strlen(buffer) - 1;
	}

	maze->Rows = rows;
	maze->Cols = cols;

	maze->Data = new char* [rows];
	for (int i = 0; i < rows; i++)
		maze->Data[i] = new char[cols];

	rewind(fp);

	for (int i = 0; i < rows; i++)
	{
		fgets(buffer, MAX, fp);

		for (int j = 0; j < cols; j++)
			maze->Data[i][j] = buffer[j];
	}

	fclose(fp);
}

bool GetNextStep(MazeDesc* maze, Vector* curr, Direction direction, Vector* next)
{
	switch (direction)
	{
		case Direction::Up:
		{
			next->X = curr->X;
			next->Y = curr->Y - 1;

			if (next->Y == -1)
				return false;
		}
		break;

		case Direction::Down:
		{
			next->X = curr->X;
			next->Y = curr->Y + 1;

			if (next->Y == maze->Rows)
				return false;
		}
		break;

		case Direction::Right:
		{
			next->X = curr->X + 1;
			next->Y = curr->Y;

			if (next->X == maze->Cols)
				return false;
		}
		break;

		case Direction::Left:
		{
			next->X = curr->X - 1;
			next->Y = curr->Y;

			if (next->X == -1)
				return false;
		}
		break;
	}

	if (maze->Data[next->Y][next->X] == WALL) return false;
	if (maze->Data[next->Y][next->X] == MARKED) return false;

	return true;
}

bool MoveTo(MazeDesc* maze, Vector* curr, Direction direction)
{
	Vector next;

	if (maze->Data[curr->Y][curr->X] == GOAL)
		return true;

	maze->Data[curr->Y][curr->X] = MARKED;

	for (int i = 0; i < 4; i++)
	{
		if (GetNextStep(maze, curr, (Direction)i, &next) == false)
			continue;

		if (MoveTo(maze, &next, Direction::Up))
			return true;
	}

	maze->Data[curr->Y][curr->X] = BACK;

	return false;
}

bool Solve(MazeDesc* maze)
{
	bool bStartBound = false;
	bool result = false;

	Vector start;
	for (int y = 0; y < maze->Rows; y++)
	{
		for (int x = 0; x < maze->Cols; x++)
		{
			if (maze->Data[y][x] == START)
			{
				bStartBound = true;
				start.X = x;
				start.Y = y;

				break;
			}
		}
	}

	if (bStartBound == false)
	{
		printf("출발지점이 없음\n");
		return false;
	}

	result = MoveTo(maze, &start, Direction::Up);

	maze->Data[start.Y][start.X] = START;

	return result;
}

int main()
{
	const char* path = (char*)"Maze2.txt";

	MazeDesc maze;
	ReadFile(path, &maze);

	if (Solve(&maze) == false)
		return -1;


	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD cyan = FOREGROUND_GREEN | FOREGROUND_BLUE;
	WORD red = FOREGROUND_RED;
	WORD gray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	for (int y = 0; y < maze.Rows; y++)
	{
		for (int x = 0; x < maze.Cols; x++)
		{
			if (maze.Data[y][x] == MARKED)
				SetConsoleTextAttribute(h, cyan);
			else if(maze.Data[y][x] == BACK)
				SetConsoleTextAttribute(h, red);
			else
				SetConsoleTextAttribute(h, gray);

			printf("%c", maze.Data[y][x]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}