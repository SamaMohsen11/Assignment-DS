#include<iostream>
#include<stack>
using namespace std;

class operations{
    private:   
    int n;
    int * arr;
    public:
      operations(int array[],int x){
        n=x;
        arr=new int[n];
        for(int i=0;i<n;i++){
            arr[i]=array[i];
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

     int array[]={1,2,1}; // 2 -1 2
     operations x(array,3);
     x.nextgreater();

 
    int arr[]={1,2,3,4,3}; // 2 3 4 -1 4
    operations y(arr,5);
    y.nextgreater();
  
   
    return 0;
}