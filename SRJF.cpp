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


struct cmp {
    bool operator () (Process const& p1, Process const& p2)
    {
        return p1.remTime > p2.remTime;
    }
};

Process processArr[100];
vector<Process> processTime[100];
priority_queue<Process, vector<Process>, cmp > readyQ;
vector<int> ganttChart;
Process currCpuProcess;
bool cpuIsBusy = false;

int main(){

    int numOfProcess;
    cout<<"Enter number of process:"<<endl;
    cin>>numOfProcess;

    for(int i=1; i<=numOfProcess; i++){
        Process p;
        cout<<"Enter AT and BT of the process "<<i<<"  respectively:"<<endl;
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
            currCpuProcess = readyQ.top();
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
            }
            else{
                readyQ.push(currCpuProcess);
            }
            cpuIsBusy = false;
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
