Name: 
Id

SJF
	average waiting time = 23147.000000
	average turnaround time: 10.000000

SRTF
	average waiting time = 20126.000000
	average turnaround time: 43545.000000

SJF has a lower turnaround time while SRTF has a lower average time.
Comparing the two it’s evident that SRTF is faster since it has a lower waiting time.
This is because SRTF has a higher probability of having a process being processed due to it keeping waiting the processes with high process remaining time. These processes are processed when there are no other processes shorter waiting in line hence the speed.

In SJF, all processes waiting in the ready state queue are evaluated, and whichever is deemed to be the shortest moves to the front of the line. When the first job was recorded the system evaluates the first one no matter how big is the burst time. Once the first job has been completed the computer checks for any jobs in the queue waiting for evaluation. If there are no waiting jobs in the queue the system waits on the next job which is also treated as the first job. If there are other waiting processes in the queue the system loops through all the processes to check the ones with the smallest burst time. From the list the one with the smallest burst time is picked and evaluated till completion. Once completed the whole process of checking is repeated and the candidate process is picked for evaluation.

In the case of processes which have a tie in burst times the system picks the process which has a lower arrival time. Due to this logical algorithm the average turning time is lower than the SRTF which might keep the processes with high remaining time longer in the queue hence processes with high burst time end up waiting longer than expected.


In SRTF if a shorter process comes into the ready state queue than the one currently running, then the kernel will preempt the process that is running and run the shorter process first. The first process to arrive is processed first but its preempted if a process having a shorter remaining time enters the queue before its completion. The new process enters the queue and also can be preempted incase a new process enters the ready queue with a shorter remaining time.

From the program cpu_scheduler the SJF has a lower turning time compared to the SRTF. This is caused by processes being preempted before they are completed which makes processed being processed for more than expected time which makes it higher compared to SJF which takes exactly the expected burst time. 

On the other side the SRTF has a lower waiting time compared to the SJF. This happens because the processes with lowest remaining time are preempted first which reduces the queue faster and leaves the processes with higher remaining time to be processed. This increases the chance of having a job being evaluated at any time during the evaluation of the queue. This increases the chance of system being involved the entire time of processing the jobs hence little or no idle time.


