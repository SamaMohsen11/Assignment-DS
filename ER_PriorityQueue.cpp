#include <iostream> 
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Patient {
    int id;
    string name; 
    int severity; 
    int arrivalTime;
};

struct Compare {

    bool operator()(Patient a, Patient b) {

        if (a.severity == b.severity) {
            return a.arrivalTime > b.arrivalTime;
        }
        else {
            return a.severity < b.severity;
        }
    }
};

int main() {
    priority_queue<Patient,vector<Patient>, Compare> pq;

    pq.push({1, "Ali", 7, 1});
    pq.push({2, "Sara", 9, 2});
    pq.push({3, "Omar", 5, 3});
    pq.push({4, "Mona", 8, 4});
    pq.push({5, "Khaled", 6, 5});
    pq.push({6, "Nour", 10, 6});
    pq.push({7, "Youssef", 4, 7});
    pq.push({8, "Laila", 7, 8});
    pq.push({9, "Hana", 9, 9});
    pq.push({10, "Adam", 3, 10});
    pq.push({11, "Salma", 8, 11});
    pq.push({12, "Tamer", 6, 12});
    pq.push({13, "Nada", 5, 13});
    pq.push({14, "Karim", 10, 14});
    pq.push({15, "Farah", 2, 15});
    pq.push({16, "Samir", 9, 16});
    pq.push({17, "Maged", 1, 17});
    pq.push({18, "Dina", 7, 18});
    pq.push({19, "Ramy", 8, 19});
    pq.push({20, "Mariam", 6, 20});

    // View Next Patient
    cout << "Current Top Patient: " << pq.top().name << endl;

    int targetID;
    int newSeverity;

    // Treating Patients
    cout << "Treating Patients:" << endl;
    priority_queue<Patient, vector<Patient>, Compare> tempPQ = pq;
    while (!tempPQ.empty()) {
        Patient current = tempPQ.top();
        cout << "ID: " << current.id << ", Name: " << current.name << ", Severity: " << current.severity << ", Arrival Time: " << current.arrivalTime << endl;
        tempPQ.pop();
    }

    // Update Severity
    cout << "Enter patient ID to update: " << endl;
    cin >> targetID;

    cout << "Enter new severity (1 - 10): ";
    cin >> newSeverity;

    while (newSeverity < 1 || newSeverity > 10) {

        cout << "Invalid severity! Enter value from 1 to 10: ";
        cin >> newSeverity;
    }

    vector<Patient> temp;

    bool found = false;

    while (!pq.empty()) {

        Patient current = pq.top();
        pq.pop();

        if (current.id == targetID) {
            current.severity = newSeverity;
            found = true;
        }

        temp.push_back(current);
    }

    if (!found) {

        cout << "Invalid ID! Patient not found." << endl;
    }
    else {

        cout << "Severity updated successfully." << endl;
    }

    for (Patient p : temp) {

        pq.push(p);
    }


    // Ptients after update
    cout << "Patients After Update:" << endl;
    priority_queue<Patient, vector<Patient>, Compare> updatedPQ = pq;
    while (!updatedPQ.empty()) {
        Patient current = updatedPQ.top();
        cout << "ID: " << current.id << ", Name: " << current.name << ", Severity: " << current.severity << ", Arrival Time: " << current.arrivalTime << endl;
        updatedPQ.pop();
    }

    cout << "Top Patient After Update: " << pq.top().name << " | Severity: " << pq.top().severity << endl;

    return 0;
}

