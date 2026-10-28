
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int P = 5;
const int R = 3;

// Resources currently allocated to each process
int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Maximum resource demand of each process
int maxNeed[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Initially available resources: A, B, C
int available[R] = {3, 3, 2};

// Calculate Need = Max - Allocation
void calculateNeed(int need[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

// Check whether the system is in a safe state
bool isSafe(const int avail[R], int sequence[P]) {
    int need[P][R];
    calculateNeed(need);

    int work[R];
    bool finish[P] = {false};

    for (int j = 0; j < R; j++) {
        work[j] = avail[j];
    }

    int count = 0;

    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (finish[i]) {
                continue;
            }

            bool canFinish = true;

            for (int j = 0; j < R; j++) {
                if (need[i][j] > work[j]) {
                    canFinish = false;
                    break;
                }
            }

            if (canFinish) {
                for (int j = 0; j < R; j++) {
                    work[j] += allocation[i][j];
                }

                sequence[count++] = i;
                finish[i] = true;
                found = true;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

// Display available resources and safety result
void displayResult(const int avail[R]) {
    int sequence[P];

    cout << "\nAvailable (A B C): ";
    for (int j = 0; j < R; j++) {
        cout << avail[j] << " ";
    }
    cout << endl;

    if (isSafe(avail, sequence)) {
        cout << "System is in a SAFE state.\n";
        cout << "Safe sequence: ";

        for (int i = 0; i < P; i++) {
            cout << "P" << sequence[i];
            if (i < P - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "System is in an UNSAFE state.\n";
        cout << "No complete safe sequence exists.\n";
    }
}

// Add resource instances
void addResources() {
    int added[R];

    cout << "Enter resources to add (A B C): ";

    for (int j = 0; j < R; j++) {
        if (!(cin >> added[j])) {
            cout << "Invalid input.\n";
            return;
        }

        if (added[j] < 0) {
            cout << "Resource addition cannot be negative.\n";
            return;
        }
    }

    int updated[R];

    for (int j = 0; j < R; j++) {
        updated[j] = available[j] + added[j];
    }

    cout << "\nChecking state after resource addition...\n";
    displayResult(updated);

    // Apply the addition only if the resulting state is safe
    int sequence[P];

    if (isSafe(updated, sequence)) {
        for (int j = 0; j < R; j++) {
            available[j] = updated[j];
        }

        cout << "Resource addition applied.\n";
        displayResult(available);
    } else {
        cout << "Resource addition rejected: resulting state is unsafe.\n";
        cout << "Available resources remain unchanged.\n";
    }
}

// Permanently remove available resource instances
void removeResources() {
    int removed[R];

    cout << "Enter resources to remove (A B C): ";

    for (int j = 0; j < R; j++) {
        if (!(cin >> removed[j])) {
            cout << "Invalid input.\n";
            return;
        }

        if (removed[j] < 0) {
            cout << "Resource removal cannot be negative.\n";
            return;
        }
    }

    // Ensure enough resources are available for removal
    for (int j = 0; j < R; j++) {
        if (removed[j] > available[j]) {
            cout << "Removal rejected: insufficient available "
                 << "resources of type " << char('A' + j) << ".\n";
            cout << "Available resources remain unchanged.\n";
            return;
        }
    }

    int updated[R];

    for (int j = 0; j < R; j++) {
        updated[j] = available[j] - removed[j];
    }

    cout << "\nChecking state after proposed removal...\n";
    displayResult(updated);

    int sequence[P];

    if (isSafe(updated, sequence)) {
        for (int j = 0; j < R; j++) {
            available[j] = updated[j];
        }

        cout << "Resource removal accepted.\n";
        displayResult(available);
    } else {
        cout << "Resource removal rejected: it would leave "
             << "the system in an unsafe state.\n";
        cout << "Available resources remain unchanged.\n";
    }
}

int main() {
    int choice;

    cout << "BANKER'S ALGORITHM - DEADLOCK AVOIDANCE\n";
    cout << "Resources: A, B, C\n";
    cout << "Processes: P0, P1, P2, P3, P4\n";

    cout << "\nInitial system state:\n";
    displayResult(available);

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Check current system state\n";
        cout << "2. Add resources\n";
        cout << "3. Permanently remove resources\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a menu number.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                displayResult(available);
                break;

            case 2:
                addResources();
                break;

            case 3:
                removeResources();
                break;

            case 4:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
