#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

enum class priorityLevel {
    Critical,
    Industrial,
    Residential
};

struct area {
    int id;
    string name;
    int currentLoad;
    priorityLevel priority;
    bool isPowerOn = true;
};

class powerGridSystem {
private:
    vector<area> areas;
    const int maxCapacity;
    int totalCurrentLoad = 0;

public:
    // explicit to avoid accidental implicit conversions
    explicit powerGridSystem(int capacity) : maxCapacity(capacity) {} // Constructor to initialize maxCapacity

    // Register a new area with its load and priority
    void registerArea(int id, const string& name, int load, priorityLevel priority) {
        areas.push_back({id, name, load, priority, true});
        totalCurrentLoad += load;
    }

    // Optimize the grid by turning off power to lower priority areas if the total load exceeds max capacity
    void optimizeGrid() {
        if(totalCurrentLoad <= maxCapacity) {
            return;
        }

        cout << "[ALERT] Grid Overload Detected! " << totalCurrentLoad << " MW exceeds max capacity of " << maxCapacity << " MW.\n"<< "Optimizing power distribution...\n";

        // Sort areas by priority i.e., critical areas move to the front, residential areas move to the back
        sort(areas.begin(), areas.end(),[](const area& a, const area& b) {
            if (a.priority != b.priority) {
                return a.priority < b.priority;
            }
            // If priorities are the same, sort by current load (lower load first)
            return a.currentLoad < b.currentLoad; 
        });

        // Turn off power to lower priority areas until the total load is within the max capacity
        for(auto it = areas.rbegin(); it != areas.rend(); ++it) {
            if(totalCurrentLoad <= maxCapacity) {
                break;
            }

            if(it->isPowerOn) {
                it->isPowerOn = false;
                totalCurrentLoad -= it->currentLoad;
                cout << "[ACTION] Power turned OFF for area: " << it->name << " (ID: " << it->id << ", Load: " << it->currentLoad << " MW)\n";
            }
        }
    }


    void displayGridStatus() const {
        cout << "Max Capacity: " << maxCapacity << " MW\n";
        cout << "Total Current Load: " << totalCurrentLoad << " MW\n";
        cout << "Areas:\n";

        for(const auto& a : areas) {
            cout << "ID: " << a.id 
                 << ", Name: " << a.name 
                 << ", Load: " << a.currentLoad 
                 << " MW, Priority: " 
                 << (a.priority == priorityLevel::Critical ? "Critical" : (a.priority == priorityLevel::Industrial ? "Industrial" : "Residential")) 
                 << ", Power Status: " 
                 << (a.isPowerOn ? "ON" : "OFF") 
                 << '\n';
        }
    }
};

int main () {
    powerGridSystem grid(1000); // Initialize grid with max capacity of 1000 MW

    grid.registerArea(1001, "Government Hospital", 300, priorityLevel::Critical);
    grid.registerArea(1002, "cement Factory", 400, priorityLevel::Industrial);
    grid.registerArea(1003, "Residential district Khordha", 200, priorityLevel::Residential);
    grid.registerArea(1004, "Residential district Anantapur", 150, priorityLevel::Residential);
    grid.registerArea(1005, "Data Center", 250, priorityLevel::Critical);
    grid.registerArea(1006, "Chemical Processing Plant", 300, priorityLevel::Industrial);

    cout << "Initial Grid Status:\n";
    grid.displayGridStatus();

    grid.optimizeGrid();
    
    cout <<"\nPost-Optimization Grid Status:\n";
    grid.displayGridStatus();

    return 0;
}
