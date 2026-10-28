
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


void calculateNeed(int need[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

void displayNeed(int need[P][R]) {
    cout << "\nNeed Matrix (A B C):\n";

    for (int i = 0; i < P; i++) {
        cout << "P" << i << ": ";

        for (int j = 0; j < R; j++) {
            cout << need[i][j] << " ";
        }

        cout << endl;
    }
}


int main() {
    cout << "BANKER'S ALGORITHM - DEADLOCK AVOIDANCE" << endl;
    cout << "Number of processes: " << P << endl;
    cout << "Number of resource types: " << R << endl;

    cout << "Available resources (A B C): ";
    for (int j = 0; j < R; j++) {
        cout << available[j] << " ";
    }
    cout << endl;
    int need[P][R];

    calculateNeed(need);
    displayNeed(need);

    return 0;
}
