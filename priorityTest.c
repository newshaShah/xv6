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
    // set scheduling policy to priority
    changePolicy(1);
    int numberOfProcess = 5;

    for (int i = 0; i < numberOfProcess; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            // change priority of each process process. later the process is made larger priority it has
            int priority;
            priority = (i+1)*2;
            setPriority(priority);
            
            junk_func(30);
            
            exit();
        }
        else
        {
            if (i == numberOfProcess-1)
            {
                // print Termination Time of the child proccess to check which one finished earlier
                for (int j = 0; j < numberOfProcess; j++)
                {
                     int creation_time = 0;
                    int running_time = 0;
                    int sleep_time = 0;
                    int waiting_time = 0;
                    int termination_time = 0;
                    int p = waitForChild(&creation_time, &running_time, &sleep_time, &waiting_time, &termination_time);
                   
                    printf(1, "proccess with pid = %d  is done with %d termination_time \n",p,termination_time);
                }
            }
        }
    }

    exit();
    return 0;
}