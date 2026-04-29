#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time = 0;
    int turnaround_time = 0;
    int waiting_time = 0;

    process(int x, int y, int z) {
        id = x;
        arrival_time = y;
        burst_time = z;
        remaining_time = z; 
    }
};

class roundrobinscheduler {
private:
    vector<process> p;// vector  to add all processes
    queue<int> q; // queue to add index of all process
    int timequantum;
    int current_time = 0;

public:
    roundrobinscheduler(int t) {
        timequantum = t;
    }

    // adding process
    void addProcess(int id, int at, int bt) {
        p.push_back(process(id, at, bt));
    }

// print queue
    void printQueue() {
        queue<int> temp = q;

        cout << "[ ";
        if (temp.empty()) {
            cout << "Empty";
        }
         else {
            while (!temp.empty()) {
                cout << "P" << p[temp.front()].id << " ";
                temp.pop();
            }
        }
        cout << "]\n";
    }

    void run() {
        int n = p.size();
        vector<bool> added(n, false);
        int done = 0;

        cout << "\nQueue updates:\n";

        while (done < n) { 

            // add arrived processes
            for (int i = 0; i < n; i++) {
                if (!added[i] && p[i].arrival_time<=current_time) { // check condition 
                    q.push(i);
                    added[i] = true;
                }
            }

            if (q.empty()) {
                current_time++;
                continue;
            } 
    
            printQueue();

        
            int i = q.front();
            q.pop();   

            int exec = min(timequantum, p[i].remaining_time);  
            current_time += exec;  
            p[i].remaining_time -= exec;  

            if (p[i].remaining_time == 0) {   
                p[i].completion_time = current_time;
                done++;
            } 

            else {
                q.push(i);
            }

        }
// after run ->[Empty] 
        printQueue();

        //calculations
        float total = 0;

        cout << "\nP  CT  TAT  WT\n";

        for (int i = 0; i < n; i++) {
            p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time; 
            total += p[i].waiting_time; 

            cout << "P" << p[i].id << " "
                 << p[i].completion_time << " "
                 << p[i].turnaround_time << " "
                 << p[i].waiting_time << "\n";
        }

        cout << "Average WT = " << total / n << endl;
    }
};

int main() {
    int n, tq;
    cout<<"Enter Number of Process\n";
    cin >>n;
    cout<<"Enter  Time Quantum:\n";
     cin>>tq;

    roundrobinscheduler s(tq);

    for (int i = 0; i < n; i++) {
        int at, bt;
        cout<<"Enter Arival Time of Process "<<i+1<<endl;
        cin >> at;
        cout<<"Enter Brust Time "<<i+1<<endl;
        cin>>bt;
        s.addProcess(i + 1, at, bt);
    }

    s.run();
    return 0;
}