#include <bits/stdc++.h>
using namespace std;

struct Process{
    int ID,AT,BT,WT,CT,TAT,remTime;

    void printDetails(){
        cout<<"PID  = "<<ID
            <<", AT  = "<<AT
            <<", BT  = "<<BT
            <<", WT  = "<<WT
            <<", CT  = "<<CT
            <<", TAT = "<<TAT<<endl;
    }
};

Process processArr[100];
vector<Process> processTime[100];
vector<int> ganttChart;
queue<Process> readyQ;
Process currCpuProcess;
bool cpuIsBusy = false;

int main(){

    int numOfProcess;

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    cin>>numOfProcess;

    for(int i=1; i<=numOfProcess; i++){
        Process p;
        cin>>p.AT>>p.BT;

        p.ID      = i;
        p.remTime = p.BT;

        processArr[i] = p;
        processTime[p.AT].push_back(processArr[i]);
    }

    for(int i=0, ct=1; i<100; i++, ct++){

        if(processTime[i].size()!=0){
            for(int j=0; j<processTime[i].size(); j++){
                readyQ.push(processTime[i][j]);
            }
        }

        if(!readyQ.empty() && !cpuIsBusy){
            currCpuProcess = readyQ.front();
            readyQ.pop();
            cpuIsBusy = true;
        }

        if(cpuIsBusy){
            currCpuProcess.remTime-=1;
            ganttChart.push_back(currCpuProcess.ID);
            if(currCpuProcess.remTime==0){
                currCpuProcess.CT  = ct;
                currCpuProcess.TAT = currCpuProcess.CT  - currCpuProcess.AT;
                currCpuProcess.WT  = currCpuProcess.TAT - currCpuProcess.BT;
                processArr[currCpuProcess.ID] = currCpuProcess;
                cpuIsBusy = false;
            }
        }
    }

    cout<<endl;
    for(int i=1; i<=numOfProcess; i++){
        processArr[i].printDetails();
    }

    cout<<endl;
    for(int i=0; i<ganttChart.size(); i++){
        printf("P%d | ", ganttChart.at(i));
    }
    cout<<endl;

return 0;

}
