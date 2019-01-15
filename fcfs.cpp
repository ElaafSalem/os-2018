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
void *cal_time(Process p[], int n);

//**[1]** Get values from the user
int main(){
	int burst, arrival, n;
	cout << "Type the number of processes ";
	cin >> n;
	Process p[n];
	for(int i = 1; i < n+1; i++){
		cout << "What is P"<<i<<" arrival time? ";
		cin >> arrival;
		cout << "What is P"<<i<<" burst time? ";
		cin >> burst;
		p[i-1] = { i, arrival, burst};
	}
	// **[2]** Sort the processes based on the arrival time 
	sort(p, p+n, function);
	// **[3]** Calculate the start and end time for each process
	cal_st_end(p, n);
	//**[4]** Calculate response, waiting, turnaround times for each process
	cal_time(p, n);

	return 0;
}

void * cal_st_end(Process p[]){

	for(int i = 0; i < n; i++){
		if ((p[i].ar > p[i-1].end) || (p[i].pid == p[0].pid)) {
			p[i].start = p[i].ar;
			p[i].end = p[i].start + p[i].bur;
		}
		else {
			p[i].start = p[i-1].end;
			p[i].end = p[i].start + p[i].bur;
		} 
		cout << "P" << p[i].pid << " start time " << p[i].start << " end time " << p[i].end << endl;
	}
}


void * cal_time(Process p[]){
	int response, waiting, turnaround;
	for(int i = 0; i < n; i++){
		response = p[i].start-p[i].ar;
		waiting = p[i].start-p[i].ar;
		turnaround = p[i].end-p[i].ar;
		

		cout << "P" << p[i].pid << "\nresponse time = " << response << ", waiting time = " << waiting << ", turnaround time = " << turnaround << endl;
	}
}
