#include<stdio.h>
#include<string.h>
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


void importArray2(struct hints hint[])
{
	int i, j = 0;
	char fileName[31];
	char strWordTemp[29];
	FILE *fp;
	
	fp = fopen("exportedList.txt", "r");
	
	fscanf(fp, "%d", &j);
	printf("%d", j);
	for(i = 0; i < j; i++)
	{
	fgets(strWordTemp, 29, fp);
	printf("%s", strWordTemp);
		do
		{
		fgets(strWordTemp, 29, fp);
		printf("%s", strWordTemp);
			
		}while(strcmp(strWordTemp, "\n") != 0 );
	
	}
	
	
	fclose(fp);
	printf("\nData imported from \"%s\"", fileName);
	
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
	int i, j = 0, k, arraySize;
	char fileName[31];
	char strTemp[50];
	FILE *fp;
//	
//	printf("Enter file name to import list (ex. exportedList.txt): ");
//	fflush(stdin);
//	scanf("%[^\n]%*c", fileName);
	
//	importing



	fp = fopen("lovelive.txt", "r");
	fscanf(fp, "%d", &arraySize);
	
	for( i = 0 ; i < arraySize + 1; i++)
	{
			
		fgets(strTemp, 50, fp);
		if(i != 0)
		{
			colonRemover(strTemp);
			strcpy(sGameStruct[j].strWord, strTemp);
			k = 0;
			fgets(strTemp, 50, fp);
			do
			{
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
//	printf("\nData imported from \"%s\"", fileName);
	
	
}

int main()
{
	struct wordStruct sGameStruct[150];
	
	int nWordCount = 0;
	int i;
	char string[29];
	
//	strcpy(string, "Object: RIKO SAKURAUCHI");
	importArray(sGameStruct, &nWordCount);
	
	printf("%s", sGameStruct[1].strWord);
//splitterFunc("kind of: cute girl");

	printf("\n%s", sGameStruct[1].sHintPair[0].strRelation);
	printf("\n%s", sGameStruct[1].sHintPair[0].strRelationValue);
	printf("\n%s", sGameStruct[1].sHintPair[1].strRelation);
	printf("\n%s", sGameStruct[1].sHintPair[1].strRelationValue);
//	colonRemover(string);
//		printf("%s", string);

}