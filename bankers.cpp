
#include <iostream>
using namespace std;

const int P = 5;  // Number of processes
const int R = 3;  // Number of resource types

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maxNeed[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int available[R] = {3, 3, 2};

int main() {
    cout << "BANKER'S ALGORITHM - DEADLOCK AVOIDANCE" << endl;
    cout << "Number of processes: " << P << endl;
    cout << "Number of resource types: " << R << endl;

    cout << "Available resources (A B C): ";
    for (int j = 0; j < R; j++) {
        cout << available[j] << " ";
    }
    cout << endl;

    return 0;
}
