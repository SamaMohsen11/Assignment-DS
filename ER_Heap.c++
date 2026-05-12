#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name; 
    int severity; 
    int arrivalTime;
};

void heapify(Patient arr[], int size, int i) {
    int left = (2 * i) + 1;
    int right = left + 1;
    int largest = i;

    if(left < size && ((arr[left].severity > arr[largest].severity) || (arr[left].severity == arr[largest].severity && arr[left].arrivalTime < arr[largest].arrivalTime))) {
        largest = left;
}

    if(right < size && ((arr[right].severity > arr[largest].severity) || (arr[right].severity == arr[largest].severity && arr[right].arrivalTime < arr[largest].arrivalTime))) {
        largest = right;
}

    if(largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

void buildMaxHeap(Patient arr[], int size) {
    for(int i = (size / 2) - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }
}

void insert(Patient arr[], int& size, Patient element) {
    arr[size] = element;
    size ++;

    int i = size - 1;
    int parent = (i - 1) / 2;
    while(i > 0 && (arr[i].severity > arr[parent].severity || (arr[i].severity == arr[parent].severity && arr[i].arrivalTime < arr[parent].arrivalTime))){
        swap(arr[parent], arr[i]);
        i = parent;
        parent = (i - 1) / 2; 
    }
}

Patient extractMax(Patient arr[], int& size) {
    Patient largest = arr[0];
    arr[0] = arr[size - 1];
    size --;
    heapify(arr, size, 0);

    return largest;
}

void heapifyUp(Patient arr[], int i) {
    int parent = (i - 1) / 2;

    while(i > 0 &&(arr[i].severity > arr[parent].severity ||(arr[i].severity == arr[parent].severity && arr[i].arrivalTime < arr[parent].arrivalTime))) {

        swap(arr[i], arr[parent]);

        i = parent;
        parent = (i - 1) / 2;
    }
}

Patient viewNextPatient(Patient arr[], int size) {
    return arr[0];
}

void displayAllPatients(Patient arr[], int size) {
    for(int i = 0; i < size; ++i) {
        cout << "Patient's ID is: "<< arr[i].id << endl;
        cout << "Patient's name is: "<< arr[i].name << endl;
        cout << "Patient's severity is: "<< arr[i].severity << endl;
        cout << "Patient's arrival time is: "<< arr[i].arrivalTime << endl;
        cout << "==========================================================================================\n";
    }
}



void updateSeverity(Patient arr[], int size, int ID, int newSeverity) {
    for(int i = 0; i < size; ++i) {
        if(arr[i].id == ID) {
            int oldSeverity = arr[i].severity;
            arr[i].severity = newSeverity;

            if(newSeverity > oldSeverity) {
                heapifyUp(arr, i);
            } else {
                heapify(arr, size, i);
            }
            break;
        }
    }
}

int main() {
    Patient patients[100] = {
    {1, "Ali", 7, 1},
    {2, "Sara", 9, 2},
    {3, "Omar", 5, 3},
    {4, "Mona", 8, 4},
    {5, "Khaled", 6, 5},
    {6, "Nour", 10, 6},
    {7, "Youssef", 4, 7},
    {8, "Laila", 7, 8},
    {9, "Hana", 9, 9},
    {10, "Adam", 3, 10},
    {11, "Salma", 8, 11},
    {12, "Tamer", 6, 12},
    {13, "Nada", 5, 13},
    {14, "Karim", 10, 14},
    {15, "Farah", 2, 15},
    {16, "Samir", 9, 16},
    {17, "Maged", 1, 17},
    {18, "Dina", 7, 18},
    {19, "Ramy", 8, 19},
    {20, "Mariam", 6, 20}
    };

    int size = 20;

    //Make this array max heap
    buildMaxHeap(patients, size);

    //Printing the whole array
    // displayAllPatients(patients, size);


    //Inserting a new patient, then printing the array

//     insert(patients, size, {21, "Sama", 8, 21});
//     displayAllPatients(patients, size);

    //Treat next patient
    // Patient nextP = extractMax(patients, size);
    // cout << "Next patient is: " << nextP.name << endl;
    // cout << "================================\n";
    // displayAllPatients(patients, size);

    //View next patient 
    // Patient nextP = viewNextPatient(patients, size);
    // cout << "Next patient is: " << nextP.name << endl;

    //Update severity
    // displayAllPatients(patients, size);
    // cout << "############################################################################################\n";
    // updateSeverity(patients, size, 6, 8);
    // displayAllPatients(patients, size);
}