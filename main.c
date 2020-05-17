#include <linux/kernel.h>
#include <sys/syscalls.h>
#include <asm/uaccess.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
    // Args check
    //
    if (argc != 2)
    {
        printf("ERROR:  Invalid input. Input must be only one Process ID.");
        return 0;
    }
    else if (-1 == is_number(argv[1]))
    {
        printf("ERROR:  Invalid Process ID %s. PID should be positive integer.", argv[1]);
        return 0;
    }
    //
    /// Call new system call
    //
    long ret_status = syscall(548, atoi(argv[1]));
    printf(0 == ret_status ? "Sys call was done successfuly." : "Sys call failed.");
    //
    return 0;
}

//
/// Check if the total string is a number
//
int is_number(char* pNum)
{
	char* pTmp = pNum;
	if (!pNum) return -1;

	for (; *pTmp ; ++pTmp)
    {
		if (!isdigit(*pTmp))
			return -1;
	}
	return atoi(pNum);
}