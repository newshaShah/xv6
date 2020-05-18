#include "types.h"
#include "stat.h"
#include "user.h"



int junk_func(int n) 
{ 
    if (n == 0) 
        return 1; 
    else if(n==1)
        return n + junk_func(n-1);

    return n + junk_func(n-1)+junk_func(n-2); 
} 

int main(void)
{
    // set scheduling policy to default scheduling 
    changePolicy(0);
    int numberOfProccesses = 12;
    for (int i = 0; i < numberOfProccesses; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            // just doing some actions to take time
            junk_func(35);
            
            exit();
        }
        else if (i == (numberOfProccesses - 1))
        {
                int sum = 0;
                for (int j = 0; j < numberOfProccesses; j++)
                {
                    int creation_time = 0;
                    int running_time = 0;
                    int sleep_time = 0;
                    int waiting_time = 0;
                    int termination_time = 0;
                    waitForChild(&creation_time, &running_time, &sleep_time, &waiting_time, &termination_time);
                    sum += waiting_time;
                }
                int avg = sum / numberOfProccesses;
                printf(1, "waiting time of proccesses is:  %d \n", avg);
            
        }
    }

    exit();
    return 0;
}

//waitingTime=1556, for quantum = 1
//waitingTime=1478, for quantum = 5
//waitingTime=1387, for quantum = 10
//waitingTime=1300, for quantum = 100
//waitingTime=805, for quantum = 500
//waitingTime=789, for quantum = 1000
//waitingTime=804, for quantum = 1500
//waitingTime=807, for quantum = 2000
