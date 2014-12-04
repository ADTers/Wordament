#include <signal.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

volatile unsigned int variable = 0;
volatile unsigned int print_variable = 0;

void alarm_handler(int signum)
{
    variable++;
    print_variable = 1;
    alarm(2);
}

int main()
{        
    signal(SIGALRM, alarm_handler);
    alarm(2);
    for (;;)
    {
        select(0, NULL, NULL, NULL, NULL);
        if (print_variable)
        {
            printf("Timer = %u\n", variable);
	sleep(1);
	system("clear");
        }
	
    }
}
