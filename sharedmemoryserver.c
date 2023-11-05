#include<sys/shm.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#define SIZE 400
#define data_not_filled -1
#define data_filled 0
#define data_read_client 1
typedef struct data
{
	int status;
	char buff[100];
}data1;

int main()
{
	printf("\n # ASSIGNMENT NO.- 2 [PART B] ");
   	printf("\n # Name - Nikhil Bare.");
   	printf("\n # Roll No.- 307A013.\n");
   		
	int key=0,shmid,i=0;
	key=ftok(".",'A');
	printf("key=%d",key);
	char ch;
	data1 *shm_ptr;
	shmid=shmget(key,SIZE,IPC_CREAT|0666);
	if(shmid<0)
	{
		printf("\nShared memory id not created");
		exit(-1);
	}
	else
	{
		printf("\nShared memory id created");
		printf("\nShared memory id = %d",shmid);
	}
	shm_ptr=(data1*)shmat(shmid,NULL,0);
	if(shm_ptr>=0)
		printf("\nShared memory is attached");
	else
	{
		printf("\nShared memory is  not attached");
		exit(-1);
	}

	shm_ptr->status=data_not_filled;
	if(shm_ptr->status == data_not_filled)
	{
		printf("\ndata is not filled");
		printf("\nenter the text ending with #\n");
		ch=getchar();
		while(ch!='#')
		{
		shm_ptr->buff[i]=ch;
		ch=getchar();
		i++;
		}
		shm_ptr->buff[i]='\0';
		shm_ptr->status=data_filled;
		
	}
	
	return 0;
}

