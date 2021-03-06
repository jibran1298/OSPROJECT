#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<iostream>
#include <stdlib.h> // For System
#include <queue>
#include <signal.h>
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

int getPro()
{
    pid_t cpid;
    pid_t ppid;
    

    if ((cpid = fork()) == 0)
    {
        int x = getpid();
       
        ppid = getpid();
        kill(ppid, SIGUSR1);
        return x;
    }
}
void roundRobin()
{
    int num;
    int dat;
    int quantam;
    int count = 0;
    Process *obj;
    cout <<"Enter Number of Processes : ";
    cin >> num;
    obj = new Process[num];
    dat = getPro();
    for(int i =0;i<num;i++)
    {
        int burst;
        burst = (rand() % 16)+3;
        obj[i].setData(dat,0,burst,burst);
        count++;
        dat+=3;
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
    cout << "\nProcess\tBurst \tWaiting \tTurnaround \n";
   float totalWait=0;
   float  totalTurn=0;
    while(!data.empty())
    {
        Process temp = data.front();
        if(temp.wait!=0)
        {
            cout << "P" << temp.processID <<"\t"<< temp.remaining << "\t" << temp.wait-temp.remaining <<"\t\t" << temp.wait << endl;
            totalTurn+=temp.wait;
            totalWait=totalWait + (temp.wait-temp.remaining);
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
        cout << "[P" << temp.processID << "] - ";
        gant.pop();
    }
    cout << endl;

}



void segmentation()
{
    int numOfSegments, baseAddress[20], limitRegister[20], logicalAddress, sizeOfSegment[20], memoryUnit = 5000, physicalAddress, segmentNumber;
    char ch = 'y';
	cout << "Enter the Number of Segments: ";
	cin >> numOfSegments;
	cout << endl << endl;
	for (int i = 0; i < numOfSegments; i++)
	{
                system("clear");
		cout << "Enter Base Address for Segment " << i + 1 << ": ";
		cin >> baseAddress[i];
		cout << "Enter Limit Register for Segment " << i + 1 << ": ";
		cin >> limitRegister[i];
	}
        
	
	while(ch=='y'||ch=='Y')
        {
            system("clear");
            cout << "\nEnter the Logical Address: ";
            cin >> logicalAddress;
            cout << "\n---------------Segment Table ------------------\n";
            cout << "Segment # " <<"\t"<<"Base Address" <<"\tLimit Register\n";
            for(int i =0;i<numOfSegments;i++)
            {
                cout << i+1 <<"\t\t" << baseAddress[i] <<"\t\t" << limitRegister[i] << endl;
            }
            cout << "\nEnter Segment No: ";
            cin >> segmentNumber;
            if (baseAddress[segmentNumber - 1] > memoryUnit)
            {
                cout << " Invalid Memory Limit.\n";
            }
            else
            {
                if (logicalAddress < limitRegister[segmentNumber - 1])
                    {
                        physicalAddress = logicalAddress + baseAddress[segmentNumber - 1];
                        cout << "\nSegment No \tBase Address \tPhysical Address\n";
                        cout  << segmentNumber;
                        cout << "\t\t" << baseAddress[segmentNumber - 1];
                        cout << "\t\t" << physicalAddress << endl;
                    }
                        
                else if (segmentNumber > numOfSegments)
                    cout << "Invalid Segment Number. Does not Exist.\n";
                else
                    {
                        cout << "Error :  Invalid Logical Address. Size exceeded.\n";
                    }
            }
            
            cout <<"\n\nContinue ? (Y/N)";
            cin >> ch;
        }		
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
            segmentation();
        }
        else
        {
            //Exit Program
            return 0;
        }
        cout <<"\n\nDo you want to continue ? (Y/N)";
        cin >> ch;
    }
    return 0;
}

