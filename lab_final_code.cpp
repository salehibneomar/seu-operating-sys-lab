#include <bits/stdc++.h>
using namespace std;

float TOTAL_TAT_RR = 0.0;
float TOTAL_WT_RR  = 0.0;
float TOTAL_TAT_PS = 0.0;
float TOTAL_WT_PS  = 0.0;
int timeQuantum = 3;

struct Process{
    int ID,AT,BT,WT,CT,TAT,priority,remTime;

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
        return p1.priority < p2.priority;
    }
};

Process processArr[1000];
vector<Process> processTime[1000];
queue<Process> readyQRR;
priority_queue<Process, vector<Process>, cmp > readyQPS;
Process currCpuProcessRR;
Process currCpuProcessPS;
bool cpuIsBusyRR = false;
bool cpuIsBusyPS = false;

int main(){

    int numOfProcess;
    int TQ = timeQuantum;
    int countRR = 0, countPS = 0;

    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    cin>>numOfProcess;

        for(int i=1; i<=numOfProcess; i++){
        Process p;
        cin>>p.AT>>p.BT>>p.priority;

        p.ID      = i;
        p.remTime = p.BT;

        processArr[i] = p;
        processTime[p.AT].push_back(processArr[i]);
    }


    for(int i=0, ct=1; i<1000; i++, ct++){

        if(processTime[i].size()!=0){
            for(int j=0; j<processTime[i].size(); j++){
                if(processTime[i][j].priority == 1){
                    readyQRR.push(processTime[i][j]);
                    countRR++;
                }
                else if(processTime[i][j].priority>1){
                    readyQPS.push(processTime[i][j]);
                    countPS++;
                }
            }
        }

        if(!readyQRR.empty() && !cpuIsBusyRR){
            currCpuProcessRR = readyQRR.front();
            readyQRR.pop();
            cpuIsBusyRR = true;
            TQ = timeQuantum;
        }

        if(cpuIsBusyRR){
            currCpuProcessRR.remTime--;
            TQ--;

            if(TQ==0 && currCpuProcessRR.remTime!=0){
                readyQRR.push(currCpuProcessRR);
                cpuIsBusyRR = false;
            }

            if(currCpuProcessRR.remTime==0){
                currCpuProcessRR.CT  = ct;
                currCpuProcessRR.TAT = currCpuProcessRR.CT  - currCpuProcessRR.AT;
                currCpuProcessRR.WT  = currCpuProcessRR.TAT - currCpuProcessRR.BT;
                processArr[currCpuProcessRR.ID] = currCpuProcessRR;
                TOTAL_TAT_RR+=currCpuProcessRR.TAT;
                TOTAL_WT_RR+=currCpuProcessRR.WT;
                cpuIsBusyRR = false;
            }
        }

        if(!readyQPS.empty() && !cpuIsBusyPS){
            currCpuProcessPS = readyQPS.top();
            readyQPS.pop();
            cpuIsBusyPS = true;
        }

        if(cpuIsBusyPS){
            currCpuProcessPS.remTime--;

            if(currCpuProcessPS.remTime==0){
                currCpuProcessPS.CT  = ct;
                currCpuProcessPS.TAT = currCpuProcessPS.CT  - currCpuProcessPS.AT;
                currCpuProcessPS.WT  = currCpuProcessPS.TAT - currCpuProcessPS.BT;
                processArr[currCpuProcessPS.ID] = currCpuProcessPS;
                TOTAL_TAT_PS+=currCpuProcessPS.TAT;
                TOTAL_WT_PS+=currCpuProcessPS.WT;
                cpuIsBusyPS = false;
            }
        }

    }


    cout<<"\nRR details: "<<endl;
    for(int i=1; i<=numOfProcess; i++){
        if(processArr[i].priority == 1){
            processArr[i].printDetails();
        }
    }

    cout<<"ATAT = "<<setprecision(2)<<fixed<<(TOTAL_TAT_RR/countRR)<<endl;
    cout<<"AWT  = "<<setprecision(2)<<fixed<<(TOTAL_WT_RR/countRR)<<endl;

    cout<<"\n\nPS details: "<<endl;
    for(int i=1; i<=numOfProcess; i++){
        if(processArr[i].priority > 1){
            processArr[i].printDetails();
        }
    }

    cout<<"ATAT = "<<setprecision(2)<<fixed<<(TOTAL_TAT_PS/countPS)<<endl;
    cout<<"AWT  = "<<setprecision(2)<<fixed<<(TOTAL_WT_PS/countPS)<<endl;

    return 0;

}
