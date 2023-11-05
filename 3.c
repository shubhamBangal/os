#include <stdio.h>
#include <stdlib.h>

    int main()
{
    int n, head, seektime = 0;
	
	
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int sequence[n];

    printf("Enter the disk request sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &sequence[i]);
    }

    printf("Enter the initial position of the R/W head: ");
    scanf("%d", &head);

	int arr[n],min, i, pos;

	for(i=0; i<n; i++)
	{
		arr[i] = 0;
	}
	printf("Sequnce is");

	while(1)
	{
		min = 999;
		for(i=0; i<n; i++)
		{
			if(arr[i] == 0)
			{
				if(min > abs(head - sequence[i]))
				{
					min = abs(head - sequence[i]);
					pos = i;
				}
			}
		}
		if(min == 999)
			break;
		arr[pos] = 1;
		seektime += min;
		head = sequence[pos];
		printf(" > %d", sequence[pos]);
	}
	printf("\n\n Seek Time of SSTF = %d", seektime);
	return 0;
}

    


