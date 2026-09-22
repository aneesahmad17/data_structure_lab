#include <iostream>
using namespace std;

int main()
{
    const int ROWS = 4;
    const int COLS = 5;

    // 1. Create and initialize parking array (0 = Empty, 1 = Occupied)
    int parking[ROWS][COLS] = {
        {1, 0, 1, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1}
    };

    int occupied = 0, empty = 0;

    // 2. Display parking layout
    cout << "Parking Layout (0 = Empty, 1 = Occupied):" << endl;
    cout << "\t";
    for (int j = 0; j < COLS; j++)
        cout << "C" << j << "\t";
    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << "Row " << i << "\t";
        for (int j = 0; j < COLS; j++)
        {
            cout << parking[i][j] << "\t";
            // 3 & 4. Count occupied and empty spaces
            if (parking[i][j] == 1)
                occupied++;
            else
                empty++;
        }
        cout << endl;
    }

    cout << "\nTotal Occupied Spaces: " << occupied << endl;
    cout << "Total Empty Spaces: " << empty << endl;

    // 5 & 6. Check a specific space
    int r, c;
    cout << "\nEnter row number (0-" << ROWS - 1 << "): ";
    cin >> r;
    cout << "Enter column number (0-" << COLS - 1 << "): ";
    cin >> c;

    if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
    {
        if (parking[r][c] == 0)
            cout << "Parking space [" << r << "][" << c << "] is AVAILABLE." << endl;
        else
            cout << "Parking space [" << r << "][" << c << "] is OCCUPIED." << endl;
    }
    else
    {
        cout << "Invalid row or column number!" << endl;
    }

    // 7. Capacity and occupancy
    cout << "\nTotal Parking Capacity: " << ROWS * COLS << endl;
    cout << "Current Occupancy: " << occupied << " / " << ROWS * COLS
         << " (" << (occupied * 100.0) / (ROWS * COLS) << "%)" << endl;

    return 0;
}
