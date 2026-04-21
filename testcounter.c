#include "types.h"
#include "stat.h"
#include "user.h"

extern void ucounter_set(int);
extern int ucounter_get(void);
int main()
{
	int ret;
	int i;
	
	ucounter_set(0);
	
	ret = fork();
	if(ret==0)//child, change the counter to 5
	{		
		ucounter_set(5);
		printf(1,"Child: set counter to 5\n");
		exit();
	}else{//parent, wait and read the counter
		wait();//wait until child exits
		i=ucounter_get();
		printf(1,"Parent: the value of counter is %d\n",i);
		exit();
	}	
}

