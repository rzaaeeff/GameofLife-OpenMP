#include <iostream>
#include <fstream>
#include <omp.h>
#include <cstdlib>

/**
 * @author ACA Lab 14
 * Heydar Rzayev
 */

using namespace std;

int COLUMN, ROW;

char** currentGeneration;
char** newGeneration;

void initialize(string filename)
{
	ifstream f(filename);

	f >> COLUMN >> ROW;

	f.close();

    // for borders
	COLUMN = COLUMN + 2;
	ROW = ROW + 2;

    // initializing arrays
	currentGeneration = new char*[COLUMN];
	newGeneration = new char*[COLUMN];

	for(int i = 0; i < COLUMN; i++)
	{
		currentGeneration[i] = new char[ROW];
	}

	for(int i = 0; i < COLUMN; i++)
	{
		newGeneration[i] = new char[ROW];
	}
}

void readInitialGeneration(string filename)
{
	ifstream f(filename);

    // ignoring column and row count
	int dummy;

	f >> dummy >> dummy;

	for(int i = 1; i < COLUMN - 1; i++)
	{
		for(int j = 1; j < ROW - 1; j++)
		{
			f >> currentGeneration[i][j];
		}
	}

	f.close();
}

void addBorders()
{
    int i;

	// top row
	#pragma omp parallel for private(i)
	for (int i = 1; i < ROW - 1; i++)
	{
		currentGeneration[0][i] = '.';
	}

	// bottom row
	#pragma omp parallel for private(i)
	for (int i = 1; i < ROW - 1; i++)
	{
		currentGeneration[COLUMN - 1][i] = '.';
	}

	// left column	
	#pragma omp parallel for private(i)
	for (int i = 1; i < COLUMN - 1; i++)
	{
		currentGeneration[i][0] = '.';
	}

	// right column	
	#pragma omp parallel for private(i)
	for (int i = 1; i < COLUMN - 1; i++)
	{
		currentGeneration[i][ROW - 1] = '.';
	}

	// corners
	currentGeneration[0][0] = '.';                  // upper left
	currentGeneration[0][ROW - 1] = '.';            // upper right
	currentGeneration[COLUMN - 1][0] = '.';         // lower left
	currentGeneration[COLUMN - 1][ROW - 1] = '.';   // lower right
}

int countAliveNeighbours(int i, int j) {
    int aliveNeighbours = 0;

    if (currentGeneration[i - 1][j - 1] == 'X') { aliveNeighbours++; }    // top left
    if (currentGeneration[i - 1][j] == 'X') { aliveNeighbours++; }        // top
    if (currentGeneration[i - 1][j + 1] == 'X') { aliveNeighbours++; }    // top right
    if (currentGeneration[i][j + 1] == 'X') { aliveNeighbours++; }        // right
    if (currentGeneration[i + 1][j + 1] == 'X') { aliveNeighbours++; }    // bottom right
    if (currentGeneration[i + 1][j] == 'X') { aliveNeighbours++; }        // bottom
    if (currentGeneration[i + 1][j - 1] == 'X') { aliveNeighbours++; }    // bottom left
    if (currentGeneration[i][j - 1] == 'X') { aliveNeighbours++; }        // left

    return aliveNeighbours;
}

char analyzeCell(int i, int j)
{
    int aliveNeighbours = countAliveNeighbours(i, j);

    // under population
	if(aliveNeighbours < 2)
		return '.';

    // over crowding
	else if(aliveNeighbours > 3)
		return '.';

	else if(currentGeneration[i][j] == 'X' && (aliveNeighbours == 2 || aliveNeighbours == 3))
		return 'X';

    // reproduction
	else if(currentGeneration[i][j] == '.' && aliveNeighbours == 3)
		return 'X';
}

void applyAlgorithm()
{
	int i, j = 0;

	#pragma omp parallel for private(i, j)
	for (i = 1; i < COLUMN - 1; i++)
	{
		for (j = 1; j < ROW - 1; j++)
		{
			newGeneration[i][j] = analyzeCell(i, j);
		}
	}
}

void copyGeneration()
{
	int i, j = 0;

	#pragma omp parallel for private(i, j)
	for (i = 1; i < COLUMN - 1; i++)
	{
		for (j = 1; j < ROW - 1; j++)
		{
			currentGeneration[i][j] = newGeneration[i][j];
		}
	}
}

void writeFinalGeneration(string filename)
{
	ofstream f(filename);

	for (int i = 1; i< COLUMN - 1; i++)
	{
		for (int j = 1; j < ROW - 1; j++)
		{
			f << currentGeneration[i][j] << " ";
		}
		f << endl;
	}

	f.close();
}

int main()
{
	int iterations;
	string inputFilename;
	string outputFilename;

	cout << "Please, enter input file name: ";
	cin >> inputFilename;
	cout << "Please, enter iteration count: ";
	cin >> iterations;
	cout << "Please, enter output file name: ";
	cin >> outputFilename;

	double startTime = omp_get_wtime();

	initialize(inputFilename);

	readInitialGeneration(inputFilename);

	for (int i = 0; i < iterations; i++)
	{
		addBorders();
		applyAlgorithm();
		copyGeneration();
	}

	writeFinalGeneration(outputFilename);

	cout << "Execution time: " << omp_get_wtime() - startTime << "s" << endl;

	return 0;
}
