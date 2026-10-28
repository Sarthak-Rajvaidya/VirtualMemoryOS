
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

void FIFO(vector<int> pages, int capacity) {
    stack<int> memory;
    stack<int> temp;

    int pageFaults = 0;
    int pageHits = 0;

    for (int page : pages) {
        bool found = false;

        // Check whether the page is already in memory
        temp = memory;

        while (!temp.empty()) {
            if (temp.top() == page) {
                found = true;
                break;
            }
            temp.pop();
        }

        if (found) {
            pageHits++;
            cout << "Page " << page << " -> Hit" << endl;
        } else {
            pageFaults++;

            if (memory.size() == capacity) {
                // Remove the oldest page using two stacks
                while (!memory.empty()) {
                    temp.push(memory.top());
                    memory.pop();
                }

                temp.pop(); // Remove the oldest page

                while (!temp.empty()) {
                    memory.push(temp.top());
                    temp.pop();
                }
            }

            memory.push(page);
            cout << "Page " << page << " -> Fault" << endl;
        }

        cout << "Frames: ";
        temp = memory;

        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << pageHits << endl;
}


void LRU(vector<int> pages, int capacity) {
    list<int> memory;
    int pageFaults = 0;
    int pageHits = 0;

    for (int page : pages) {
        auto it = find(memory.begin(), memory.end(), page);

        if (it != memory.end()) {
            // Page is already present: update its recent usage
            pageHits++;
            memory.erase(it);
            memory.push_back(page);

            cout << "Page " << page << " -> Hit" << endl;
        } else {
            // Page is absent: page fault occurs
            pageFaults++;

            if (memory.size() == capacity) {
                memory.pop_front(); // Remove least recently used page
            }

            memory.push_back(page);
            cout << "Page " << page << " -> Fault" << endl;
        }

        cout << "Frames (LRU -> MRU): ";
        for (int p : memory) {
            cout << p << " ";
        }
        cout << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << pageHits << endl;
}


int main() {
    int n, capacity;

    cout << "Enter number of page references: ";
    cin >> n;

    vector<int> pages(n);

    cout << "Enter the page reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> capacity;

    cout << "\n--- FIFO Page Replacement ---\n";
    FIFO(pages, capacity);

    return 0;
}
