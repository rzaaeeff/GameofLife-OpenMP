#include <iostream>
#include <fstream>
#include <cstdlib>

/**
 * @author ACA Lab 14
 * Heydar Rzayev
 */

using namespace std;

int main() {
    int column, row;
    string filename;

    cout << "This program will create input file\n"
            "Please enter details." << endl;
    cout << "Please, enter input file name: ";
    cin >> filename;
    cout << "Please, enter column count: ";
    cin >> column;
    cout << "Please, enter row count: ";
    cin >> row;

    int array[column][row];

    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            array[i][j] = rand() % 2;
        }
    }

    ofstream f(filename);
    f << row << " " << column << endl;

    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            if (array[i][j] == 1) f << "X";
            else f << ".";
            f << " ";
        }

        f << endl;
    }

    f.close();

    return 0;
}