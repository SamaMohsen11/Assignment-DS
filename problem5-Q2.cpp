#include<iostream>
#include<stack>
using namespace std;

class operations{
    private:   
    int n;
    int * arr;
    public:
        operations(int x){
        n=x;
        arr=new int[n];
}
    void getarray(){
        for(int i=0;i<n;i++){
            cout<<"Enter ELement:"<<(i+1)<<endl;
            cin>>arr[i];
        }
    }

    void nextgreater(){
        stack<int>s;
    int * res=new int[n];
    for(int i=0;i<n;i++){
        res[i]=-1;
    }
 

for(int i=0;i<2*n;i++){ //to make  circular array
// current >elements in stack and stack is not empty
while(!s.empty()&& arr[i%n]>arr[s.top()]){
    res[s.top()]=arr[i%n];
    s.pop();
}

// condition to prevent dublicates
if(i<n){
// push current element if stack is empty or current < elements in stack
s.push(i%n);
}
    }
 // final result
    for(int i=0;i<n;i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;

    delete[]res;
    }

~operations(){
    delete[] arr;
}

};

int main(){
// test input 1 2 1
 operations x(3);
 x.getarray(); 
x.nextgreater();  

// test input 1 2 3 4 3
operations y(5);
y.getarray();
y.nextgreater();
   
    return 0;
}