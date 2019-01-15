#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
	int pid;
	int ar;
	int bur;
	int start;
	int end;
};

bool function(Process a, Process b){return (a.ar < b.ar);}
void *cal_st_end(Process p[], int n);
void *sort_opt(Process p[], int n);
void *cal_time(Process p[], int n);

int main(){
	int burst, arrival, n;
	cout << "Type the number of processes ";
	cin >> n;
	Process p[n];
	//**[1]** Get values from the user
	for(int i = 1; i < n+1; i++){
		cout << "What is P"<<i<<" arrival time? ";
		cin >> arrival;
		cout << "What is P"<<i<<" burst time? ";
		cin >> burst;
		p[i-1] = { i, arrival, burst};
	}
	//**[2]** Solve the problem as FCFS:
    	//[a] Sort the processes based on the arrival time
	sort(p, p+n, function);
  	//[b] Calculate the start and end time for each process */
	cal_st_end(p, n);
	/* 
	**[3]** Re-sort the processes based on the following condition:
		[if the arrival time for the next process is less than or equal the start time for the current process 
		(AND) the burst time for the next process is less than the burst time for the current process -> SWAP] 
	**[4]** Re-calculate the start and end time for each process */
	sort_opt(p, n);
	//**[5]** Calculate response, waiting, turnaround times for each process
	//**[6]** Display the results
	cal_time(p, n);

	return 0;
}


void * cal_st_end(Process p[], int n){

	for(int i = 0; i < n; i++){
		if ((p[i].ar > p[i-1].end) || (p[i].pid == p[0].pid)) {
			p[i].start = p[i].ar;
			p[i].end = p[i].start + p[i].bur;
		}
		else {
			p[i].start = p[i-1].end;
			p[i].end = p[i].start + p[i].bur;
		} 
	}
}

void * sort_opt(Process p[], int n){
	for(int i = 0; i < n-1; i++){
		if((p[i+1].ar <= p[i].start) && (p[i+1].bur < p[i].bur))
			swap(p[i],p[i+1]);
		cal_st_end(p, n);
	}
}

void * cal_time(Process p[], int n){
	int response, waiting, turnaround;
	for(int i = 0; i < n; i++){
		response = p[i].start-p[i].ar;
		waiting = p[i].start-p[i].ar;
		turnaround = p[i].end-p[i].ar;
		cout << "P" << p[i].pid << "\nresponse time = " << response << ", waiting time = " << waiting << ", turnaround time = " << turnaround << endl;
	}
}
