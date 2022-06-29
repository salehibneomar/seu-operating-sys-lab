#include <bits/stdc++.h>
using namespace std;

struct Process{
    int id;
    vector <int> allocation;
    vector <int> maxNeed;
    vector <int> need;
    bool isExecuted;

    void printNeedMatrix(){
        for(int i=0; i<need.size(); i++){
            cout<<need.at(i)<<" ";
        }
        cout<<endl;
    }
};

vector <int> available;
vector <Process> process;
vector <int> executionOrder;

int main(){

    int numOfProcess, numOfResources;

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    //cout<<"Enter number of Process and Resources respectively: ";
    cin>>numOfProcess>>numOfResources;

    for(int i=1; i<=numOfProcess; i++){
        Process p;
        p.id = i;
        p.isExecuted = false;

        int r;
        //cout<<"Enter allocation of process "<<i<<endl;
        for(int j=1; j<=numOfResources; j++){
            cin>>r;
            p.allocation.push_back(r);
        }

        int m;
        //cout<<"Enter max need of process "<<i<<endl;
        for(int j=1; j<=numOfResources; j++){
            cin>>m;
            p.maxNeed.push_back(m);
        }

        process.push_back(p);
    }

    int a;
    //cout<<"Enter initial available"<<endl;
    for(int i=1; i<=numOfResources; i++){
        cin>>a;
        available.push_back(a);
    }

    //Need calculation
    for(int i=0; i<numOfProcess; i++){
        for(int j=0; j<numOfResources; j++){
            process.at(i).need.push_back(process.at(i).maxNeed.at(j) - process.at(i).allocation.at(j));
        }
    }

    //cout<<endl;
    for(int i=0; i<numOfProcess; i++){
        process.at(i).printNeedMatrix();
    }

    int processExecutionCount = 0;

    while(processExecutionCount<numOfProcess){

        for(int i=0; i<numOfProcess; i++){

            if(!process.at(i).isExecuted){

                int safe = true;
                for(int j=0; j<numOfResources; j++){
                    if(process.at(i).need.at(j) > available.at(j)){
                        safe= false;
                        break;
                    }
                }

                if(safe){

                    cout<<"Process P"<<process.at(i).id<<" will be executed"<<endl;
                    for(int j=0; j<numOfResources; j++){
                        available.at(j) = available.at(j) + process.at(i).need.at(j);
                    }

                    processExecutionCount++;
                    process.at(i).isExecuted = true;
                    executionOrder.push_back(process.at(i).id);
                }
                else{
                    cout<<"Process P"<<process.at(i).id<<" needs to wait"<<endl;
                }
            }
        }
    }

    return 0;
}

/*

Input

5 3
0 1 0 7 5 3
2 0 0 3 2 2
3 0 2 9 0 2
2 1 1 2 2 2
0 0 2 4 3 3
3 3 2

*/
