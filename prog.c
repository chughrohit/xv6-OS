#include "types.h"
#include "stat.h"
#include "user.h"

int LotteryScheduler(void){
	int pid;

    assignTicket(1, 60);
    for (int i = 0; i < 3; i++){
        pid = fork();
        if (pid){
            continue;
        }
        else if (!pid){
            assignTicket(1, 30 - 10 * i);
            for (int j = 0; j < 30000; j++)
			{
				asm("nop");
                for (int k = 0; k < 30000; k++)
				{
                    asm("nop");
                }
            }
            printf(1, "\n  child# %d with %d tickets has finished!  \n", getpid(), 30 - 10 * i, assignTicket(0, 10));
            exit();
        }
        else{
            printf(2, "  \n  Error  \n ");
        }
    }

    if (pid){
        for (int i = 0; i < 3; i++){
            wait();
        }
    }
    exit();
    return 0;
}

int main(int argc, char *argv[])
{
    LotteryScheduler();
    return 0;
}


