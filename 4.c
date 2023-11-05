#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Bubble_sort(int arr[], int size, int ascending)
{
	for(int step=0; step<size-1; step++)
	{
		for(int i = 0; i<size-step-1; i++ )
		{
			int condition = ascending ? (arr[i] > arr[i+1]) : (arr[i] < arr[i+1] );
			if(condition)
			{
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
		}
	}
}

int main()
{
	int pid,size;
	printf("enter no of elements to be sorted");
	scanf("%d", &size);
	
	int *arr = (int *)malloc(size * sizeof(int));
	printf("enter elements to be sorted");
	for(int i = 0 ; i<size ; i++)
	{
		scanf("%d",&arr[i]);
	}

	pid = fork();

	if(pid == 0)
	{
		clock_t start_time = clock();
		
		printf("child's pid %d ",getpid());
		printf(" parent's pid %d ", getppid());
		
		Bubble_sort(arr,size,1);
		for(int i=0;i<size; i++)
		{
			printf("%d",arr[i]);
		}
		clock_t end_time = clock();
		double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Sorting took %f seconds.\n", execution_time);
	}
	else if( pid > 0)
	{
		clock_t start_time = clock();
		int status;
		wait(&status);
		printf("child's pid %d ",pid);
		printf(" parent's pid %d ", getpid());
		printf(" parent's parent's pid %d ", getppid());
		
		Bubble_sort(arr,size,0);
		
		for(int i=0;i<size; i++)
		{
			printf("%d",arr[i]);
		}
		clock_t end_time = clock();
		double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Sorting took %f seconds.\n", execution_time);
	}
	else
	{
		printf("error in fork");
	}
	free(arr);
	return 0;
}
