#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

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

/*	mainMenu displays main menu, scans, and returns the appropriate integer for the switch case in the main
	@return 1-3 depending on user input
*/

int
mainMenu()
{
	//variable declaration
	int nReturnVal = 1;
	
	do
	{
	if( !(nReturnVal >= 1 && nReturnVal <= 3) )
		printf("\nENTER VALID VALUE\n");
	printf("Select Option:\n");
	printf("1. Game Menu\n2. Admin Menu\n3. Exit");
	printf("\nEnter your choice : ");
	fflush(stdin); //in case of string or char input
	scanf("%d", &nReturnVal);
	} while(!(nReturnVal >= 1 && nReturnVal <= 3)); //while loop to guard wrong inputs
	
	return nReturnVal; // returns value from nReturnVal
}

/*	adminMenu displays admin menu, scans, and returns the appropriate integer for the switch case in the main
	@return 1-10 depending on user input
	Pre-condition: user selects 2 during mainMenu function
*/
int
adminMenu()
{
	//variable declaration
	int rV = 1;
	do
	{
	if(!(rV >= 1 && rV <= 9) )
		printf("\nENTER VALID VALUE\n");
	printf("\nSelect Option:\n");
	printf("1. Add Word\n2. Add Trivia\n3. Modify Entry\n4. Delete Word\n5. Delete Clue\n6. View Words\n7. View Clues\n8. Export\n9. Import\n10. Back to Main Menu");
	printf("\nEnter your choice : ");
	fflush(stdin); //in case of string or char input
	scanf("%d", &rV);
	} while( !(rV >= 1 && rV <= 9) ); // while input to guard wrong inputs

	return rV; //returns value from rV
}

/* toUpperString converts all characters into upper case using the toupper function from ctype.h
	@param string[] - address of string to be converted
*/
void
toUpperString(char string[])
{
	int i;
	for(i = 0; i < strlen(string); i++)
		string[i] = toupper(string[i]); //toupper used here
}

/* addTrivia adds trivia to either a pre existing word or a new word
	@param string[] - address of string to be converted
*/
void addTrivia(struct hints sHints[])
{
	//variable declaration / temp container declaration
	int i;
	bool bContinue = false;
	char strTemp1[16], strTemp2[31];
	
	//checks where the next unoccupied hint is
	while(strcmp(sHints[i].strRelation, "\0") != 0 && i < 10)
		i++;
	//do while asks for inputs until nContinue is == 0 or i is equal to more than 10
	if(i < 10)
	do
	{
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
	scanf("%d", &bContinue);
	if(bContinue == false) i++; 
	}while( bContinue == true && i < 10);
	else
		printf("\nHint data already full! Delete to add more");
	
}

/* addWord adds a word and a minimum of 1 relation and relation value to the struct in the main menu
	@param wordStruct sGameStruct[] - gives access to the entire struct as it is needed for calling the addTrivia function
	@param nWordCount - increments by one every time a word is added
	Pre-condition: Add Word option in admin menu is selected
*/
void
addWord(struct	wordStruct gStruct[],
					int *nWordCount)
{
	int i = 0, j = 0;
	bool bDupe = false, bRep = false;
	char strTemp[21];

	while(strcmp(gStruct[i].strWord, "\0") != 0)
	
		i++;
	do{
	if(bRep == true)
		printf("\nDUPLICATE WORD INPUTTED (current input and entry # %d are the same) Try inputting a different word!", i + 1);
	printf("\nEnter word to add (ALL CAPS): ");
	fflush(stdin);
	scanf("%[^\n]%*c", strTemp);
	toUpperString(strTemp); // turns input into all caps just in case
	
	for(j = 0; j < *nWordCount; j++) //checks for duplicates
		if(strcmp(strTemp, gStruct[j].strWord) == 0)
			bDupe = true;
		else bDupe = false;
	
	if(bDupe == false)
		strcpy(gStruct[i].strWord, strTemp);
	bRep = true;
	}while(bDupe != false); //guards against duplicates
	
	addTrivia(gStruct[i].sHintPair); //a minimum of one trivia is needed per word
	
	(*nWordCount)++; //increments word count by one
}

/* initGameArr initializes sGameStruct and turns everything into null; is only executed once
	@param wordStruct sGameStruct[] - gives access to the struct to be initialized
	Pre-condition: program runs
*/
void
initGameArr(struct wordStruct sGameStruct[])
{
	int i,j;
	for(i=0;i<150;i++)strcpy(sGameStruct[i].strWord,"\0"); //sets words to null
	for(i=0;i<150;i++)
		for(j=0;j<10;j++) //sets strings to null
		{	strcpy(sGameStruct[i].sHintPair[j].strRelation,"\0");
			strcpy(sGameStruct[i].sHintPair[j].strRelationValue,"\0");}
			//this makes sure that no headaches will occur later on when it comes to string manipulation
}

/* exportArray exports the contents of the program into the txt file desired by the user
	@param wordStruct sGameStruct[] - gives access to the struct for printing
	@param nWordCount - count is added for the for loop, is also placed at the very top of the file
	Pre-condition: export option is selected
*/
void
exportArray(struct wordStruct sGameStruct[],
						int nWordCount)
{
	int i, j = 0;
	char fileName[31];
	FILE *fp;
	
	fflush(stdin);
	printf("Enter file name (ex. exportedList.txt): "); 
	scanf("%[^\n]%*c", fileName); //scans for user input, file name has a limit of 30 characters
	fp = fopen(fileName, "w");
	
	printf("\nSaving data...");
	fprintf(fp, "%d\n", nWordCount); //prints how many words are currently in the game's array
	for(i = 0; i < nWordCount; i++)
	{
	fprintf(fp, "Object: %s\n", sGameStruct[i].strWord); //prints the word with Object: as a prefix
	j = 0;
	do{
		fprintf(fp, "%s: ", sGameStruct[i].sHintPair[j].strRelation);
		fprintf(fp, "%s\n", sGameStruct[i].sHintPair[j].strRelationValue);
		j++; 
	}while(strcmp(sGameStruct[i].sHintPair[j].strRelation,"\0") != 0);
	fprintf(fp, "\n");
	}
	fclose(fp);
	printf(" Data saved as \"%s\"!\n", fileName); //shows what file you wrote to
	
}

/* colonRemover removes the colon from an imported word
	@param string[] - string to remove colon from
	Pre-condition: import function is called
*/
void
colonRemover(char string[])
{
	int i;
	for(i = 0; string[i] != ' ';i++); //finds the space as there is always a space before the colon
	i++;
	strcpy(string, string + i); //gives the string a colectomy and a spacectomy by strcpying onto itself 
}
/* splitterFunc splits relation and relation value from an imported word
	@param string[] - string to split
	@param stringOut1[] - string to store relation in
	@param StringOut2[] - string to store relation value in
	Pre-condition: import function is called
*/
void
splitterFunc(	char string[],
				char strOut1[],
				char strOut2[])
{
	char strTemp[50], strTemp2[50], strTemp3[50]; //strTemp3 isn't even needed, it's just there for redundancy
	int i, k, strLength;
	
	strcpy(strTemp2, string);
	strcpy(strTemp3, string);
	
	for(i = 0; string[i] != ':';i++);
	strTemp3[i] = '\0'; // replace colon with null byte then
	strcpy(strTemp, strTemp3); //strcpy to only copy the relation sans post null byte
	
	strLength = strlen(string) - strlen(strTemp) - 2 - 1;
	k = 0;
	do
	{
	strTemp2[k] = string[i + 2];
	i++;
	k++;
	}while(k != strLength + 2);
	strTemp2[k] = '\0'; //removes \n from relation value - this gave me a massive headache with strcmp

	strcpy(strOut1, strTemp);
	strcpy(strOut2, strTemp2);
}
/* importArray 	imports words from a text file and stores it in the currently running program's memory
				file is in plaintext so you can easily add or remove en masse
	@param wordStruct sGameStruct[] - struct to store in
	@param nWordCount - pointer variable for main
*/
void
importArray(struct wordStruct sGameStruct[],
			int *nWordCount)
{
	int i, k, l, arraySize, nOverWrite, nSkip;
	
	char strTemp[50];
	char fileName[31];
	FILE *fp;

	printf("Enter file name to import list (ex. exportedList.txt): ");
	fflush(stdin);
	scanf("%[^\n]%*c", fileName); //gets filename
	
//	importing part

	fp = fopen(fileName, "r"); //uses filename to open said file
	if(fp != NULL) //importing only functions if file actually exists, otherwise no dice
	{

	fscanf(fp, "%d", &arraySize);
	
	for( i = 0 ; i < arraySize + 1; i++)
	{
	strcpy(strTemp, "\0");
	nOverWrite = false;
	nSkip = false;

	fgets(strTemp, 50, fp); //fgets because fscanf is a pain with newlines
	strTemp[ strlen(strTemp) -1] = '\0';
	colonRemover(strTemp); 
		
	if(i != 0)
	{
		for(k = 0; k < *nWordCount; k++) //linear search to find duplicates
		{ 			
			if(strcmp(strTemp, sGameStruct[k].strWord) == false )
			{
				
				nSkip = 1;
				printf("Duplicate found(%s)! Do you want to overwrite duplicate (1 - Yes, 0 - No)?: ", strTemp); 
				fflush(stdin);
				scanf("%d", &nOverWrite);
			
				if(nOverWrite == true)
				{	
					l = 0;
					fgets(strTemp, 50, fp);
					do
					{
						strTemp[ strlen(strTemp) - 1 ] = '\0';		
						splitterFunc(strTemp, sGameStruct[k].sHintPair[l].strRelation, sGameStruct[k].sHintPair[l].strRelationValue);
						// ^^ splits relation into two words ^^
						fgets(strTemp, 50, fp); //fgets here to skip the newline
						l++;
					;
					}while(strcmp(strTemp, "\n") != 0);	
				}
			
			};
		
		}
	}
	
	if(i != 0 && nSkip != 1) //this is if 
		{      
		
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
	else
	printf("\nFile DOES NOT EXIST, please try again!\n");
}
/* viewWords displays words in the game struct alongside its hints and as per the specs
	it displays them one at a time
	@param wordStruct sGameStruct - array of structs where it will be read
	@param nWordCount - sets the range
*/
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
/* printAll prints every single 
	@param wordSturct sGameStruct - struct to print from
	@param nWordCount - how many times the for loop will run
	Pre-condition: executed for functions that require all words to be displayed
*/
void printAll(struct wordStruct sGameStruct[], int nWordCount)
{
	int i;
	for(i = 0; i < nWordCount; i++)
		printf("%d. %s\n", i + 1, sGameStruct[i].strWord );
}

/* addTriviaComp reuses prexisting addTrivia function for option number 2, gets input (word) searches it and calls the addTrivia function
	@param wordStruct sGameStruct - struct to add trivia to
	@param nWordCount - for the for loop that will search the word that is inputted
*/
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

/*	displayAlpha displays words alphabetically
	@param wordStruct sGameStruct - struct to display alphabetically
	@param nWordCount - limits the for loop
*/
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
/*	modifyWord modifies a word in the array of structs but keeps the struct for the relationship intact
	@param wordStruct sGameStruct - struct where the word is in
	@param nWordCount - limits for loop
*/
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

/*	deleteWord "deletes" a word from the array, in reality it just sets the word and its accompanying relation
	and relation values to null
	@param wordStruct sGameStruct - array struct to delete word from
	@param nWordCount - for loop limit
*/
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

/*  deleteHint deletes a hint from the array, just like deleteWord but it only sets the chosen relation value to null and rearranges
	it to fill the void left, no need to set null 
	accepts input
	@param wordstruct sGameStruct - struct to delete relation value from
	@param nWordCount - limits for loop search for the word
*/
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
		if(i != 9)
		{	strcpy(sGameStruct[nIndex].sHintPair[i].strRelation, sGameStruct[nIndex].sHintPair[i + 1].strRelation);
			strcpy(sGameStruct[nIndex].sHintPair[i].strRelationValue, sGameStruct[nIndex].sHintPair[i + 1].strRelationValue);
		}
		else strcpy(sGameStruct[nIndex].sHintPair[i].strRelation, "\0");
			strcpy(sGameStruct[nIndex].sHintPair[i].strRelationValue, "\0");
	}	

}

/* viewHints views hints from 

*/
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
					break;
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