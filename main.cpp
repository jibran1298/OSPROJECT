
#include<iostream>
#include <stdlib.h> // For System
#include <queue>
using namespace std;
class Process
{
    public:
    int processID;
    int arrivalTime;
    int burstTime;
    int compTime;
    int wait;
    int remaining;
    int time;
    Process()
    {
        time=compTime=wait=remaining=0;
    }
    void setData(int process,int arrival,int burst,int rem)
    {
        processID = process;
        arrivalTime = arrival;
        burstTime = burst;
        remaining = rem;
    }
    int getProcess()
    {
        return processID;
    }
    int getArrivalTime()
    {
        return arrivalTime;
    }
    int getBurstTime()
    {
        return burstTime;
    }
};
void roundRobin()
{
    int num;
    int quantam;
    int count = 0;
    Process *obj;
    cout <<"Enter Number of Processes : ";
    cin >> num;
    obj = new Process[num];
    for(int i =0;i<num;i++)
    {
        int burst;
        int arrival;
        //cout <<"Enter Arrival Time For Process P" <<i+1<<" : ";
        //cin >> arrival;
        cout <<"Enter Burst Time For Process P" <<i+1<<" : " ;
        cin >> burst;
        obj[i].setData(i+1,count,burst,burst);
        count++;
    }
    cout <<"Enter Quantam Time : ";
    cin >> quantam;
    system("clear");
    int current =0;
    queue <Process> ready;
    queue <Process> gant;
    for(int i =0;i<num;i++)
    {
        ready.push(obj[i]);
    }
    while(!ready.empty())
    {
        Process temp = ready.front();
        ready.pop();
        if(temp.burstTime>0)
        {
            if(temp.burstTime>quantam)
            {
                temp.time = temp.time + quantam;
                temp.burstTime = temp.burstTime - quantam;
                current=current+quantam;
            }
            else
            {
                temp.time = temp.time + temp.burstTime;
                current = current+temp.burstTime;
                temp.burstTime = 0;
                temp.wait = current;
            }
        }
        if(temp.burstTime>0)
        {
            ready.push(temp);
        }
        gant.push(temp);
    }
    queue <Process> data = gant;
    cout << "Process\tBurst \tWaiting \tTurnaround \n";
   int totalWait=0;
   int  totalTurn=0;
    while(!data.empty())
    {
        Process temp = data.front();
        if(temp.wait!=0)
        {
            cout << "P" << temp.processID <<"\t"<< temp.remaining << "\t" << temp.wait-temp.remaining <<"\t\t" << temp.wait << endl;
            totalTurn+=temp.wait;
            totalWait+=temp.wait-temp.remaining;
        }
        data.pop();
    }
    cout << endl ;
    
    cout <<"Average Waiting Time : " << totalWait/num << endl;
    cout <<"Average TurnAround Time : " << totalTurn/num << endl<<endl;
    cout << "Gant Chart :  \n\n";
    while(!gant.empty())
    {
        Process temp = gant.front();
        cout << "[P" << temp.processID << "]\t";
        gant.pop();
    }
    cout << endl;

}
int main() {

    char ch='y';
    while(ch=='Y'|| ch=='y')
    {
        system("clear");
        cout<< "------------------Operating System Project ----------------"<<endl;
        int choice;
        cout <<"-Enter 1 For Round Robin Scheduling \n";
        cout <<"-Enter 2 For Segmentation \n";
        cout <<"-Enter Any other  to Exit\n";
        cin >> choice;
        
        if(choice==1)
        {
            //Round Robin Scheduling
            cout <<"Round Robin\n";
            roundRobin();
        }
        else if(choice ==2)
        {
            //Segmentation
            cout <<"Segmentation \n";
        }
        else
        {
            //Exit Program
            return 0;
        }
        cout <<"Do you want to continue ? (Y/N)";
        cin >> ch;
    }
    return 0;
}

