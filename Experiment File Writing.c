#include<stdio.h>
#include<string.h>
#include<stdbool.h>

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
	int i, j = 0, k, l, arraySize, nOverWrite, nSkip;
	
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
	
	if(i != 0)
	{
		for(k = 0; k < *nWordCount; k++)
		{
		
			if(k == 0)	
			{ strTemp[ strlen(strTemp) -1] = '\0'; colonRemover(strTemp); };			
		
			if(strcmp(strTemp, sGameStruct[k].strWord) == 0 )
			{
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
			strcpy(sGameStruct[j].strWord, strTemp);
						
			k = 0;
			fgets(strTemp, 50, fp);
			do
			{
				strTemp[ strlen(strTemp) - 1 ] = '\0';		
				splitterFunc(strTemp, sGameStruct[j].sHintPair[k].strRelation, sGameStruct[j].sHintPair[k].strRelationValue);
				fgets(strTemp, 50, fp);
				k++;
			}while(strcmp(strTemp, "\n") != 0);
			
			j++;
			*nWordCount+=1;
		}
		
	}
	
	fclose(fp);
//end import
	printf("\nData imported from \"%s\"", fileName);
	
}

int main()
{
	struct wordStruct sGameStruct[150];
	
	int nWordCount = 1;
	int i;
	char string[29];
	
//	strcpy(string, "Object: RIKO SAKURAUCHI");

	importArray(sGameStruct, &nWordCount);
	
;
//splitterFunc("kind of: cute girl");
	printf("%s", sGameStruct[0].strWord);
	printf("\n%s", sGameStruct[0].sHintPair[0].strRelation);
	printf(" %s", sGameStruct[0].sHintPair[0].strRelationValue);
	printf("\n%s", sGameStruct[0].sHintPair[1].strRelation);
	printf(" %s", sGameStruct[0].sHintPair[1].strRelationValue);
	printf("\n%s", sGameStruct[0].sHintPair[2].strRelation);
	printf(" %s", sGameStruct[0].sHintPair[2].strRelationValue);
//	colonRemover(string);
//		printf("%s", string);

}