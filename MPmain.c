#include <stdio.h>
#include <string.h>
#include <stdbool.h>
typedef struct 
{
	
};

bool detectWin(int nArrWidth, int nRowCheck, char array[][nArrWidth])
{
	int i;
	bool bReturn = false;
	for(i = 0; i < nArrWidth; i++)
		if(array[nRowCheck][i] == '*')
			{i = nArrWidth;bReturn = true;}
			
return bReturn;				
}

bool detectLoss(int nArrWidth, int nRowCheck, char array[][nArrWidth])
{
	int i, nLossCount;
	bool bReturn;
	for(i = 0; i < nArrWidth; i++)
		if(array[nRowCheck][i] == '-')
			nLossCount++;

if(nLossCount == nArrWidth)
	return true;	
else
	return false;		
}

void fillArray(int nWidth, int nHeight, char array[][nWidth])
{
	int i, j;
	for(i = 0; i < nHeight; i++)
		for(j = 0; j < nWidth; j++)
			scanf(" %c", &array[i][j]);
	
}

void printArray(int nWidth, int nHeight, char array[][nWidth])
{
	int i, j;
	for(i = 0; i < nHeight; i++)
	{

		for(j = 0; j < nWidth; j++)
		 printf("%c ", array[i][j]);
		printf("\n");
	}
}

int main()
{
int nGameX = 5, nGameY = 5, nRCount;
/*
printf("Input game width (Max: 10): ");
	do
	{
		if(nRCount != 0 )
		printf("Input valid value!: ");
		scanf("%d", &nGameX);
		nRCount++;
	}while (nGameX < 0 || nGameX > 11);

	do
	{
		if(nRCount != 0 )
		printf("Input game height (Max: 10): ");
		scanf("%d", &nGameY);
		nRCount++;
	}while (nGameX < 0 || nGameX > 11);

char aGameBoard[nGameY][nGameX]; */


char aGameBoard[nGameY][nGameX];
printf("\nInitialized board containing %dx%d spaces.", nGameX, nGameY);
fillArray(nGameX, nGameY, aGameBoard);
printf("\n\n");
printArray(nGameX, nGameY, aGameBoard);



if(detectLoss(nGameX, 1, aGameBoard) == true)
	printf("YOU LOST");
else if(detectLoss(nGameX, 1, aGameBoard) == false)
	printf("KEEP PLAYING BOZO");

}