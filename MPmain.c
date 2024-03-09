#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//	struct for hints
struct hints
{
	char 	strRelation[16],
			strRelationValue[31];
};

//	struct for the word itself, contains the struct for hints
struct wordStruct
{
	char 	strWord[21];
	struct 	hints sHintPair[10];
};

//
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

int mainMenu()
{
	int nReturnVal = 0, nLoopCount = 0;
	do
	{
	if(nLoopCount != 0)
		printf("\nENTER VALID VALUE\n");
	printf("Select Option:\n");
	printf("1. Game Menu\n2. Admin Menu\n3. Exit");
	printf("\nEnter your choice : ");
	scanf("%d", &nReturnVal);
	nLoopCount++;
	} while(nReturnVal < 1 && nReturnVal > 3);
	
	return nReturnVal;
}

int adminMenu()
{
	int rV = 0, loopCount = 0;
	do
	{
	if(loopCount != 0)
		printf("\nENTER VALID VALUE\n");
	printf("\nSelect Option:\n");
	printf("1. Add Word\n2. Add Trivia\n3. Modify Entry\n4. Delete Word\n5. Delete Clue\n6. View Words\n7. View Clues\n8. Export\n9. Import\n10. Back to Main Menu");
	printf("\nEnter your choice : ");
	scanf("%d", &rV);
	loopCount++;
	} while(rV < 1 && rV > 9);
	
	return rV;
}

void toUpperString(char string[])
{
	int i;
	for(i = 0; i < strlen(string); i++)
		string[i] = toupper(string[i]);
}

void addTrivia(struct hints sHints[])
{
	int i, nContinue = 0;
	char strTemp1[16], strTemp2[31];
	
	while(strcmp(sHints[i].strRelation, "\0") != 0)
		i++;
	
	do
	{
	if(nContinue == 1) i++;
	printf("\nEnter hint to add (ex.Kind of, Part, Height): ");
	fflush(stdin);
	scanf("%[^\n]%*c", strTemp1);
	printf("\nEnter hint value to add (ex.Furniture, Leg, Meter): ");
	fflush(stdin);
	scanf("%[^\n]%*c", strTemp2);
	strcpy(sHints[i].strRelation, strTemp1);
	strcpy(sHints[i].strRelationValue, strTemp2);
	strcpy(strTemp1, "\0");
	strcpy(strTemp2, "\0");
	printf("\nAdd more hints (1 to continue, 0 to stop)? ");
	scanf("%d", &nContinue);
	}while( nContinue == 1 && i < 10);
	
}

void addWord(struct wordStruct gStruct[], int *nWordCount)
{
	int i = 0, j = 0, nDupeCount = 0, nRepCount = 0;
	char strTemp[21];

	while(strcmp(gStruct[i].strWord, "\0") != 0)
	
		i++;
	do{
	if(nRepCount != 0)
		printf("\nDUPLICATE WORD INPUTTED (current input and entry # %d are the same) Try inputting a different word!", i + 1);
	printf("\nEnter word to add (ALL CAPS): ");
	fflush(stdin);
	scanf("%[^\n]%*c", strTemp);
	toUpperString(strTemp);
	
	for(j = 0; j < *nWordCount; j++)
		if(strcmp(strTemp, gStruct[j].strWord) == 0)
			nDupeCount++;
	
	if(nDupeCount==0)
		strcpy(gStruct[i].strWord, strTemp);
	nRepCount++;
	}while(nDupeCount != 0);
	
	addTrivia(gStruct[i].sHintPair);
	
	*nWordCount+=1;
}

void initGameArr(struct wordStruct sGameStruct[])
{
	int i,j;
	for(i=0;i<150;i++)strcpy(sGameStruct[i].strWord,"\0");
	for(i=0;i<150;i++)
		for(j=0;j<10;j++)
		{	strcpy(sGameStruct[i].sHintPair[j].strRelation,"\0");
			strcpy(sGameStruct[i].sHintPair[j].strRelationValue,"\0");}
}

void exportArray(struct wordStruct sGameStruct[], int nWordCount)
{
	int i, j = 0;
	char fileName[31];
	FILE *fp;
	
	fflush(stdin);
	printf("Enter file name (ex. exportedList.txt): ");
	scanf("%[^\n]%*c", fileName);
	fp = fopen(fileName, "w");
	
	printf("\nSaving data...");
	fprintf(fp, "%d\n", nWordCount);
	for(i = 0; i < nWordCount; i++)
	{
	fprintf(fp, "Object: %s\n", sGameStruct[i].strWord);
	j = 0;
	do{
		fprintf(fp, "%s: ", sGameStruct[i].sHintPair[j].strRelation);
		fprintf(fp, "%s\n", sGameStruct[i].sHintPair[j].strRelationValue);
		j++; 
	}while(strcmp(sGameStruct[i].sHintPair[j].strRelation,"\0") != 0);
	fprintf(fp, "\n");
	}
	fclose(fp);
	printf(" Data saved as \"%s\"!\n", fileName);
	
}

void colonRemover(char string[])
{
	int i;
	for(i = 0; string[i] != ' ';i++);
	i++;
	strcpy(string, string + i);
}

void splitterFunc(char string[], char stringOut1[], char stringOut2[])
{
	char tempstring2[50];
	char tempstring3[50];
	char tempstring4[50];
	int i, k, strLength;
	
	strcpy(tempstring3, string);
	
	strcpy(tempstring4, string);
	
	for(i = 0; string[i] != ':';i++);
	tempstring4[i] = '\0';
	strcpy(tempstring2, tempstring4);
	
	strLength = strlen(string) - strlen(tempstring2) - 2 - 1;
	k = 0;
	do
	{
	tempstring3[k] = string[i + 2];
	i++;
	k++;
	}while(k != strLength + 2);
	tempstring3[k] = '\0';

	strcpy(stringOut1, tempstring2);
	strcpy(stringOut2, tempstring3);
	
}

void importArray(struct wordStruct sGameStruct[], int *nWordCount)
{
	int i, j = 0;
	char fileName[31];
	char strWordTemp[29];
	FILE *fp;
	
	printf("Enter file name to import list (ex. exportedList.txt): ");
	fflush(stdin);
	scanf("%[^\n]%*c", fileName);
	
	fp = fopen(fileName, "r");
	
	
	
	
	
	fclose(fp);
	printf("\nData imported from \"%s\"", fileName);
	
	
}

int main()
{
	int nMenuVal, nAdMenVal, i, nWordCount = 0;
//initialize array

	struct wordStruct sGameStruct[150]; initGameArr(sGameStruct);

//	char arrBoard[10][10];
	
	nMenuVal = mainMenu();
	switch(nMenuVal)
	{
		case 2:
			do
			{
			
			nAdMenVal = adminMenu();
			switch(nAdMenVal)
			{
				case 1:
					addWord(sGameStruct, &nWordCount);
					break;
					
				case 8:
					exportArray(sGameStruct, nWordCount);
					break;
				case 9:
					importArray(sGameStruct, &nWordCount);
					break;
				case 6:
				//	viewWords(sGameStruct);
					break;
			}
			}while(nAdMenVal != 10);
			break;
			
	}
	

}