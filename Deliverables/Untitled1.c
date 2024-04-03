#include <stdio.h>
#include <string.h>

int main()
{
	int	wow[100] = {68,11,36,4,8,1,18,49,10,13,65,22,63,96,98,51,89,97,53,25,77,50,61,21,33,91,74,27,55,35,30,85,5,7,45,28,79,38,42,32,78,31,41,37,62,90,82,17,100,20};
	int temp, i, j, min;
	
	
	for( i = 0; i < 100 - 1; i++ ) //selection sort :D
	{
		min = i;
		
		for(j = i + 1; j < 100; j++)
			if( wow[i] > wow[j])
				min = j;
	
		if(i != min)
		{
			temp = wow[i];
			wow[i] = wow[min];
			wow[min] = temp;
		}			
	}
	
	for(i = 0; i < 50; i++)
	{	if(i % 2 == 0 && wow[i] != 0)	
		printf("\n");
		if(wow[i] % 2 == 1 && wow[i] != 0)
			printf("%d ", wow[i]);
		else if(wow[i] % 2 == 0  && wow[i] != 0)
			{printf("%d ", wow[i]);
			}
	}
}
