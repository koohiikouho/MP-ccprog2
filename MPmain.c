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
	int i, k, l, arraySize, nOverWrite, nSkip;
	
	char strTemp[50];
	char fileName[31];
	FILE *fp;

	printf("Enter file name to import list (ex. exportedList.txt): ");
	fflush(stdin);
	scanf("%[^\n]%*c", fileName);
	
//	importing

	fp = fopen(fileName, "r");
	fscanf(fp, "%d", &arraySize);
	
	for( i = 0 ; i < arraySize + 1; i++)
	{
	strcpy(strTemp, "\0");
	nOverWrite = 0;
	nSkip = 0;

	fgets(strTemp, 50, fp);
	strTemp[ strlen(strTemp) -1] = '\0';	
	if(i != 0)
	{
		for(k = 0; k < *nWordCount; k++)
		{	  			
		
			if(strcmp(strTemp, sGameStruct[k].strWord) == 0 )
			{
				colonRemover(strTemp);
				nSkip = 1;
				printf("Duplicate found(%s)! Do you want to overwrite duplicate (1 - Yes, 0 - No)?: ", strTemp);
				fflush(stdin);
				scanf("%d", &nOverWrite);
			
				if(nOverWrite == 1)
				{	
					l = 0;
					fgets(strTemp, 50, fp);
					do
					{
						strTemp[ strlen(strTemp) - 1 ] = '\0';		
						splitterFunc(strTemp, sGameStruct[k].sHintPair[l].strRelation, sGameStruct[k].sHintPair[l].strRelationValue);
						fgets(strTemp, 50, fp);
						l++;
					;
					}while(strcmp(strTemp, "\n") != 0);	
				}
			
			};
		
		}
	}
	
	if(i != 0 && nSkip != 1)
		{      
			colonRemover(strTemp);	
			strcpy(sGameStruct[*nWordCount].strWord, strTemp);
			k = 0;
			fgets(strTemp, 50, fp);
			do
			{
				strTemp[ strlen(strTemp) - 1 ] = '\0';		
				splitterFunc(strTemp, sGameStruct[*nWordCount].sHintPair[k].strRelation, sGameStruct[*nWordCount].sHintPair[k].strRelationValue);
				fgets(strTemp, 50, fp);
				k++;
			}while(strcmp(strTemp, "\n") != 0);
			
			*nWordCount+=1;
		}
		
	}
	
	fclose(fp);
//end import
	printf("\nData imported from \"%s\"", fileName);
	
}

void viewWords(struct wordStruct sGameStruct[], int nWordCount)
{
	int i, j, min;
	char cSelect;
	struct wordStruct tempStruct[150];
	struct wordStruct tempStruct2;
	
	for(i = 0; i < nWordCount; i++)
		tempStruct[i] = sGameStruct[i];
	
	for( i = 0; i < nWordCount - 1; i++ )
	{
		min = i;
		
		for(j = i + 1; j < nWordCount; j++)
			if(strcmp(tempStruct[min].strWord, tempStruct[j].strWord) == 1)
				min = j;
	
		if(i != min)
		{
			tempStruct2 = tempStruct[i];
			tempStruct[i] = tempStruct[min];
			tempStruct[min] = tempStruct2;
		}	
	}

printf("\n%d words currently loaded\n", nWordCount);

i = 0;
do
{
	printf("%d. %s\n", i+1, tempStruct[i].strWord);
	fflush(stdin);
	j = 0;
	do
	{
	printf("%s: %s\n",tempStruct[i].sHintPair[j].strRelation,tempStruct[i].sHintPair[j].strRelationValue);
	j++;
	}while(strcmp(tempStruct[i].sHintPair[j].strRelation, "\0") != 0);
	
	printf("\npress 'N' for next, 'P' for previous, 'X' to end the display and go back to the menu: ");
	
	
	do
	{
	fflush(stdin);
	scanf("%c", &cSelect);	
	cSelect = toupper(cSelect);
		switch(cSelect)
		{
			case 'N':
			if(i != nWordCount -1)	
			{i++;}	
			else if ( i == nWordCount - 1)
			{ printf("REACHED END OF LIST\n"); }
				break;
			case 'P':
			if(i != 0)
			{	i--;}
			else if ( i == 0)
			{	printf("REACHED END OF LIST\n");}
				break;
			case 'X':
				break;
			default:
				printf("Invalid input\n");
				break;
		}
	} while(cSelect != 'X' && cSelect != 'P' && cSelect != 'N');
		
}while(cSelect != 'X');
}

void printAll(struct wordStruct sGameStruct[], int nWordCount)
{
	int i;
	for(i = 0; i < nWordCount; i++)
		printf("%d. %s\n", i + 1, sGameStruct[i].strWord );
}

void addTriviaComp(struct wordStruct sGameStruct[], int nWordCount)
{
	int indexTemp, i;
	char temp[21];
	printAll( sGameStruct, nWordCount );
	printf("\nEnter trivia to add: ");
	fflush(stdin);
	scanf("%[^\n]&*c", temp);
	toUpperString(temp);
	
	for(i = 0; i < nWordCount; i++)
		if(strcmp(sGameStruct[i].strWord, temp) == 0)
			indexTemp = i;
		
	addTrivia(sGameStruct[indexTemp].sHintPair);
}

int searchWord(struct wordStruct sGameStruct[] , int nWordCount)
{
	char temp[21];
	int i;
	
	fflush(stdin);
	scanf("%[^\n]&*c", temp);
	toUpperString(temp);
	
	for( i = 0; i < nWordCount; i++)
		if(strcmp(sGameStruct[i].strWord, temp) == 0)
			return i;	
	
	
	return -1;
}

void displayAlpha(struct wordStruct sGameStruct[], int nWordCount)
{
	char strTemp[150][21];
	char strCont[21];
	int i, j, min;
	
	for(i = 0; i < nWordCount; i++)
		strcpy(strTemp[i], sGameStruct[i].strWord);
	
	for( i = 0; i < nWordCount - 1; i++ )
	{
		min = i;
		
		for(j = i + 1; j < nWordCount; j++)
			if(strcmp(strTemp[min], strTemp[j]) == 1)
				min = j;
	
		if(i != min)
		{
			strcpy(strCont , strTemp[i]);
			strcpy(strTemp[i] , strTemp[min]);
			strcpy(strTemp[min], strCont);
		}	
	}

	for(i = 0; i < nWordCount; i++)
		printf("%d. %s\n", i + 1, strTemp[i]);

}

void modifyWord(struct wordStruct sGameStruct[] , int nWordCount)
{
	int j, nTemp, nChoice, nSelect;
	
	displayAlpha(sGameStruct, nWordCount);

	do
	{
	printf("Enter word to modify: ");
	nTemp = searchWord(sGameStruct, nWordCount);

	
		do
		{	

			printf("Modify 1 - Word or 2 - Hints?");
			fflush(stdin);
			scanf("%d", &nChoice);
			if(nChoice == 1)
			{
				printf("Enter new word: ");
				fflush(stdin);
				scanf("%[^\n]&*c", sGameStruct[nTemp].strWord);
				toUpperString(sGameStruct[nTemp].strWord);
			}
			else if(nChoice == 2)
			{
				j = 0;
				do
				{
				printf("%d. %s: %s\n", j + 1, sGameStruct[nTemp].sHintPair[j].strRelation ,sGameStruct[nTemp].sHintPair[j].strRelationValue );
				j++;
				}while(strcmp(sGameStruct[nTemp].sHintPair[j].strRelation, "\0") != 0);
			
			do
			{

			printf("Enter number of hint to edit: ");
			scanf("%d", &nSelect);
			
			printf("\nEnter hint to add (ex.Kind of, Part, Height): ");
			fflush(stdin);
			scanf("%[^\n]%*c", sGameStruct[nTemp].sHintPair[nSelect - 1].strRelation);
			
			printf("\nEnter hint value to add (ex.Furniture, Leg, Meter): ");
			fflush(stdin);
			scanf("%[^\n]%*c", sGameStruct[nTemp].sHintPair[nSelect - 1].strRelationValue);

			}while ( nSelect < 0 || nSelect > j);
			
			}
		
		} while(nChoice != 1 && nChoice != 2);

		nTemp = -1;
	}while( nTemp != -1);	
}

void deleteWord(struct wordStruct sGameStruct[] , int *nWordCount)
{
	int nIndex, i;
	
	displayAlpha(sGameStruct, *nWordCount);
	printf("Enter word of hint to DELETE: ");
	nIndex = searchWord(sGameStruct, *nWordCount);
	
	strcpy(sGameStruct[nIndex].strWord, "\0");
	for(i = 0; i < 10; i++)
	{ strcpy(sGameStruct[nIndex].sHintPair[i].strRelation, "\0");
	strcpy(sGameStruct[nIndex].sHintPair[i].strRelationValue, "\0");
		}

	for(i = nIndex; i < *nWordCount; i++)
	{	
			sGameStruct[i] = sGameStruct[i + 1];
	}

	*nWordCount-=1 ;
	displayAlpha(sGameStruct, *nWordCount);
}


void deleteHint(struct wordStruct sGameStruct[] , int nWordCount)
{
	int nIndex, i , j, nTemp;
	displayAlpha(sGameStruct, nWordCount);
	printf("Enter word of hint to DELETE: ");
	nIndex = searchWord(sGameStruct, nWordCount);
	
	
	j = 0;
	do
	{
	printf("%d. %s: %s\n", j + 1, sGameStruct[nIndex].sHintPair[j].strRelation ,sGameStruct[nIndex].sHintPair[j].strRelationValue );
	j++;
	}while(strcmp(sGameStruct[nIndex].sHintPair[j].strRelation, "\0") != 0);	
	
	printf("Enter number of hint to DELETE: ");
	scanf("%d", &nTemp);
	nTemp--;
	
	for(i = nTemp; i < j; i++)
	{	
			strcpy(sGameStruct[nIndex].sHintPair[i].strRelation, sGameStruct[nIndex].sHintPair[i + 1].strRelation);
			strcpy(sGameStruct[nIndex].sHintPair[i].strRelationValue, sGameStruct[nIndex].sHintPair[i + 1].strRelationValue);
	}	
	
}

void viewHints(struct wordStruct sGameStruct[] , int nWordCount)
{
	int nIndex, j;
	displayAlpha(sGameStruct, nWordCount);
	printf("Enter word of hints to view: ");
	nIndex = searchWord(sGameStruct, nWordCount);
	printf("\nHints for %s:\n", sGameStruct[nIndex].strWord);
	j = 0;
	do
	{
	printf("%d. %s: %s\n", j + 1, sGameStruct[nIndex].sHintPair[j].strRelation ,sGameStruct[nIndex].sHintPair[j].strRelationValue );
	j++;
	}while(strcmp(sGameStruct[nIndex].sHintPair[j].strRelation, "\0") != 0);
}

int main()
{
	int nMenuVal, nAdMenVal, nWordCount = 0;
//initialize array
	struct wordStruct sGameStruct[150]; initGameArr(sGameStruct);

//	char arrBoard[10][10];
do
{
	nMenuVal = mainMenu();
	switch(nMenuVal)
	{
		case 1:
			
			break;
		case 2:
			do
			{
			
			nAdMenVal = adminMenu();
			switch(nAdMenVal)
			{
				case 1:
					addWord(sGameStruct, &nWordCount);
					break;
				case 2:
					addTriviaComp(sGameStruct, nWordCount);
					break;
				case 3:
					modifyWord(sGameStruct, nWordCount);
					break;
				case 4:
					deleteWord(sGameStruct, &nWordCount);
					break;
				case 5:
					deleteHint(sGameStruct, nWordCount);
					break;
				case 6:
					viewWords(sGameStruct, nWordCount);
				case 7:
					viewHints(sGameStruct, nWordCount);
					break;					
				case 8:
					exportArray(sGameStruct, nWordCount);
					break;
				case 9:
					importArray(sGameStruct, &nWordCount);
					break;
			}
			}while(nAdMenVal != 10);
			break;

	}
}while(nMenuVal != 3);

}