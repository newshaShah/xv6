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
    // set scheduling policy to MLQ algrotihm
    changePolicy(2);

   int numberOfProcesses = 10;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            junk_func(30);
            
            exit();
        }
        else
        {
            if (i == numberOfProcesses-1)
            {
                
                for (int j = 0; j < numberOfProcesses; j++)
                {
                    int creation_time = 0;
                    int running_time = 0;
                    int sleep_time = 0;
                    int waiting_time = 0;
                    int termination_time = 0;
                    int child_pid = waitForChild(&creation_time, &running_time, &sleep_time, &waiting_time, &termination_time);
                    printf(1, " proccess with pid = %d is done \n", child_pid);
                }
            }
        }
    }

    exit();
    return 0;
}