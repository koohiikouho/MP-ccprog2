#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "eieimun.c"

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

/*	mainMenu displays main menu, scans, and returns the appropriate integer for the switch case in the main
	@return 1-3 depending on user input
*/
int
mainMenu()
{
	int nReturnVal = 1; //variable declaration
	
	do
	{
	if( !(nReturnVal >= 1 && nReturnVal <= 3) ) //guards against out of bounds inputs
		printf("\nENTER VALID VALUE\n");
	printf("Select Option:\n");
	printf("1. Game Menu\n2. Admin Menu\n3. Exit");
	printf("\nEnter your choice : ");
	fflush(stdin); //in case of string or char input
	scanf("%d", &nReturnVal);
	} while( !(nReturnVal >= 1 && nReturnVal <= 3) && nReturnVal != 816); //while loop to guard wrong inputs //816 easteregg
	
	return nReturnVal; // returns value from nReturnVal
}

/*	adminMenu displays admin menu, scans, and returns the appropriate integer for the switch case in the main
	@return 1-10 depending on user input
	Pre-condition: user selects 2 during mainMenu function
*/
int
adminMenu()
{	
	int rV = 1; //variable declaration
	do
	{
	if(!(rV >= 1 && rV <= 9) )
		printf("\nENTER VALID VALUE\n");
	printf("\nSelect Option:\n");
	printf("1. Add Word\n2. Add Trivia\n3. Modify Entry\n4. Delete Word\n5. Delete Clue\n6. View Words\n7. View Clues\n8. Export\n9. Import\n10. Back to Main Menu");
	printf("\nEnter your choice : ");
	fflush(stdin); //in case of string or char input
	scanf("%d", &rV);
	} while( !(rV >= 1 && rV <= 10) ); // while input to guard wrong inputs

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
	int i, bContinue = 0; 	//variable declaration / temp container declaration
	char strTemp1[16], strTemp2[31];
	
	while(strcmp(sHints[i].strRelation, "\0") != 0 && i < 10) //checks where the next unoccupied hint is
		i++;

	if(i < 10) 	//do while asks for inputs until nContinue is == 0 or i is equal to more than 10
	do
	{
	if(bContinue == 1)
		i++; 
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
	fflush(stdin);
	scanf("%d", &bContinue);
	}while( bContinue == 1 && i < 10);
	else
		printf("\nHint data already full! Delete to add more"); //gets printed if there are already 10 hints
	
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
	int i = 0, j = 0; //variable initializations
	bool bDupe = false, bRep = false;
	char strTemp[21];

	while(strcmp(gStruct[i].strWord, "\0") != 0) //counts how many words are in the struct, was made before the word counting function
		i++;
	do{
	if(bRep == true) //if the while function has already executed more than once
		printf("\nDUPLICATE WORD INPUTTED (current input and entry # %d are the same) Try inputting a different word!", i + 1);
	printf("\nEnter **WORD** to add (ALL CAPS): ");
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
	int i,j; //variable declaration
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
	int i, j = 0; //variable declarations
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
	
	strLength = strlen(string) - strlen(strTemp) - 3; //to get length for the right part of the hint
	k = 0;
	do
	{
	strTemp2[k] = string[i + 2];
	i++;
	k++;
	}while(k != strLength + 2); //if I'll be completely honest here, I don't know how it works but it works so I don't dare try to meddle with it
	strTemp2[k] = '\0'; //removes \n from relation value - this gave me a massive headache with strcmp

	strcpy(strOut1, strTemp);
	strcpy(strOut2, strTemp2); //copies it into the their respective containers 
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
	fgets(strTemp, 50, fp); //fgets because fscanf is a pain with newlines
	strTemp[ strlen(strTemp) -1] = '\0'; //newline gets replaced with null
	colonRemover(strTemp); 
	nOverWrite = false;
	nSkip = false;
		
	if(i != 0)
	{
		for(k = 0; k < *nWordCount; k++) //linear search to find duplicates
		{ 			
			if(strcmp(strTemp, sGameStruct[k].strWord) == false )
			{
				
				nSkip = true;
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
						splitterFunc(strTemp, sGameStruct[k].sHintPair[l].strRelation, sGameStruct[k].sHintPair[l].strRelationValue);//splits relation into two words
						
						fgets(strTemp, 50, fp); //fgets here to skip the newline
						l++;
					}while(strcmp(strTemp, "\n") != 0);	
				}
			};
		}
	}
	
	if(i != 0 && nSkip == false) //this is if there isn't a duplicate
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
	else if( i != 0 && nSkip == true) //if there is a duplicate but 0 is inputted, it'll be skipped
	{
		k = 0;
		fgets(strTemp, 50, fp); 
		do
		{
				fgets(strTemp, 50, fp);
				k++;
		}while(strcmp(strTemp, "\n") != 0);
	}
	}
	
	fclose(fp);
//end import
	printf("\nData imported from \"%s\"", fileName);
	}
	else
	printf("\nFile DOES NOT EXIST, please try again!\n");
}
/* 	viewWords displays words in the game struct alongside its hints and as per the specs
	it displays them one at a time
	@param wordStruct sGameStruct - array of structs where it will be read
	@param nWordCount - sets the range
*/
void viewWords(struct wordStruct sGameStruct[], 
			   int 	nWordCount)
{
	int i, j, min; //variable declarations
	char cSelect;
	struct wordStruct tempStruct[150];
	struct wordStruct tempStruct2;
	
	for(i = 0; i < nWordCount; i++) //copies current struct into a temporary struct
		tempStruct[i] = sGameStruct[i];
	
	for( i = 0; i < nWordCount - 1; i++ ) //selection sort :D
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
printf("\n%d words currently loaded\n", nWordCount); //prints how many words are currently loaded
i = 0;
do //prints the currently selected word until X
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
/* 	printAll prints every single 
	@param wordSturct sGameStruct - struct to print from
	@param nWordCount - how many times the for loop will run
	Pre-condition: executed for functions that require all words to be displayed
*/
void printAll(struct wordStruct sGameStruct[],
			  int nWordCount)
{
	int i; //variable declaration
	for(i = 0; i < nWordCount; i++)
		printf("%d. %s\n", i + 1, sGameStruct[i].strWord );
}

/* 	addTriviaComp reuses prexisting addTrivia function for option number 2, gets input (word) searches it and calls the addTrivia function
	@param wordStruct sGameStruct - struct to add trivia to
	@param nWordCount - for the for loop that will search the word that is inputted
*/
void addTriviaComp(struct wordStruct sGameStruct[],
				   int nWordCount)
{
	int indexTemp, i; //variable declaration
	char temp[21];
	printAll( sGameStruct, nWordCount );
	printf("\nEnter word to add trivia to: ");
	fflush(stdin);
	scanf("%[^\n]&*c", temp);
	toUpperString(temp);
	
	for(i = 0; i < nWordCount; i++)
		if(strcmp(sGameStruct[i].strWord, temp) == 0)
			indexTemp = i;
		
	addTrivia(sGameStruct[indexTemp].sHintPair);
}

/*	searchWord seraches for a word in a structure
	@param wordStruct sGameStruct - struct to search word in
	@param nWordCount - for linear searching purposes
	@return returns -1 if word is not found, index of the word if word is found
*/
int searchWord(struct wordStruct sGameStruct[] , int nWordCount)
{
	char temp[21]; //variable declarations
	int i;
	
	fflush(stdin);
	scanf("%[^\n]&*c", temp);
	toUpperString(temp);
	
	for( i = 0; i < nWordCount; i++)
		if(strcmp(sGameStruct[i].strWord, temp) == 0)
			return i;	//returns i when word is found, return -1 doesn't get executed
	
	return -1;
}

/*	displayAlpha displays words alphabetically
	@param wordStruct sGameStruct - struct to display alphabetically
	@param nWordCount - limits the for loop
*/
void displayAlpha(struct wordStruct sGameStruct[],
				  int nWordCount)
{
	char strTemp[150][21]; //variable declarations
	char strCont[21];
	int i, j, min;
	
	for(i = 0; i < nWordCount; i++) //copy to temproary container for alphabetical sorting
		strcpy(strTemp[i], sGameStruct[i].strWord);
	
	for( i = 0; i < nWordCount - 1; i++ ) //selection sort :D
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
void modifyWord(struct wordStruct sGameStruct[], 
				int nWordCount)
{
	int j, nTemp, nChoice, nSelect; //variable declaration
	
	displayAlpha(sGameStruct, nWordCount);

	do //everything below is pretty self explanatory due to the printfs
	{
	printf("Enter **WORD** to modify: ");
	nTemp = searchWord(sGameStruct, nWordCount);

		do
		{	
			printf("Modify 1 - Word or 2 - Hints?: ");
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
				printf("[%d.] %s: %s\n", j + 1, sGameStruct[nTemp].sHintPair[j].strRelation ,sGameStruct[nTemp].sHintPair[j].strRelationValue );
				j++;
				}while(strcmp(sGameStruct[nTemp].sHintPair[j].strRelation, "\0") != 0);
			
			do
			{
			printf("Enter number (1 - %d) of hint to edit: ", j);
			scanf("%d", &nSelect);
			
			printf("\nEnter hint to add (ex.Kind of, Part, Height): ");
			fflush(stdin);
			scanf("%[^\n]%*c", sGameStruct[nTemp].sHintPair[nSelect - 1].strRelation);
			
			printf("\nEnter hint value to add (ex.Furniture, Leg, Meter): ");
			fflush(stdin);
			scanf("%[^\n]%*c", sGameStruct[nTemp].sHintPair[nSelect - 1].strRelationValue);

			}while ( nSelect < 0 || nSelect >= j);
			
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
void deleteWord(struct wordStruct sGameStruct[], 
				int *nWordCount)
{
	int nIndex, i; //variable declarations
	
	displayAlpha(sGameStruct, *nWordCount);
	printf("Enter **WORD** of hint to DELETE (ex. Table): ");
	nIndex = searchWord(sGameStruct, *nWordCount);
	if(nIndex != -1)
	{
		for(i = nIndex; i < *nWordCount; i++)
		{	
			sGameStruct[i] = sGameStruct[i + 1]; //then it gets copied over
		}
		*nWordCount-=1;
		displayAlpha(sGameStruct, *nWordCount);
	}
	else printf("\nWord not found\n");
}

/*  deleteHint deletes a hint from the array, just like deleteWord but it only sets the chosen relation value to null and rearranges
	it to fill the void left, no need to set null 
	accepts input
	@param wordstruct sGameStruct - struct to delete relation value from
	@param nWordCount - limits for loop search for the word
*/
void deleteHint(struct wordStruct sGameStruct[],
				int nWordCount)
{
	int nIndex, i , j, nTemp;
	displayAlpha(sGameStruct, nWordCount);
	printf("Enter **WORD** of hint to DELETE: ");
	nIndex = searchWord(sGameStruct, nWordCount);
	
	j = 0;
	do
	{
	printf("[%d.] %s: %s\n", j + 1, sGameStruct[nIndex].sHintPair[j].strRelation ,sGameStruct[nIndex].sHintPair[j].strRelationValue );
	j++;
	}while(strcmp(sGameStruct[nIndex].sHintPair[j].strRelation, "\0") != 0);	
	
	printf("Enter **NUMBER** of hint to DELETE: ");
	scanf("%d", &nTemp);
	nTemp--;
	
	for(i = nTemp; i < j; i++)
	{	
		if(i != 9)
		{	strcpy(sGameStruct[nIndex].sHintPair[i].strRelation, sGameStruct[nIndex].sHintPair[i + 1].strRelation);
			strcpy(sGameStruct[nIndex].sHintPair[i].strRelationValue, sGameStruct[nIndex].sHintPair[i + 1].strRelationValue);
		}
		else //exists because it might grab from an upper value if i == 9 then it would be filled with garbage values
		{	strcpy(sGameStruct[nIndex].sHintPair[i].strRelation, "\0");
			strcpy(sGameStruct[nIndex].sHintPair[i].strRelationValue, "\0");
		}
	}	
}

/* 	viewHints views hints from the wordStruct, takes string as input, searches, then gives back the result
	@param sGameStruct - struct to view hints from
	@param nWordCount - for linear searching purposes
*/
void viewHints(struct wordStruct sGameStruct[],
			   int nWordCount)
{
	int nIndex, j; //variable declaration
	displayAlpha(sGameStruct, nWordCount);
	printf("Enter word of hints to view: ");
	nIndex = searchWord(sGameStruct, nWordCount);
	if(nIndex != -1)
	{
		printf("\nHints for %s:\n", sGameStruct[nIndex].strWord);
		j = 0;
		do
		{
		printf("%d. %s: %s\n", j + 1, sGameStruct[nIndex].sHintPair[j].strRelation ,sGameStruct[nIndex].sHintPair[j].strRelationValue );
		j++;
		}while(strcmp(sGameStruct[nIndex].sHintPair[j].strRelation, "\0") != 0);
	}
	else
		printf("\nWord not found\n");
}

/*	boardSize asks for input for width and height of the board and calculates how many spaces in the 10x10 board will be used
	@param xAxis - saves board width
	@param yAxis - saves board height
	@param product - how many spaces
*/
void boardSize(int *xAxis, int *yAxis, int *product)
{
	printf("\nInput width of board (Minimum - 3, Maximum - 10): ");
	do{ fflush(stdin); scanf("%d", xAxis);
	} while ( !(*xAxis > 2 && *xAxis <11));
		printf("\nInput length of board (Minimum - 3, Maximum - 10): ");
	do{ fflush(stdin); scanf("%d", yAxis);
	} while ( !(*yAxis > 2 && *yAxis <11));
	
 	*product = *yAxis * *xAxis;
}
/*	printBoard prints the board as a guide for the player, also shows what row the player is picking from
	@param wordStruct tempBoard - is used to display the first letters of each word
	@param nX - used to limit the printing of the x axis
	@param nY - used to imit the printing of the y axis
	@param nLevel - used to show the player where they currently are
*/
void
printBoard(struct wordStruct tempBoard[10][10], int nX, int nY,  int nLevel)
{
	int i , j;
	for(i = 0; i < nX; i++)
		printf("%d ", i + 1);
	printf("\t\tSTATUS");
	printf("\n");
	for(i = 0; i < nX; i++)
		printf("----------");
	printf("\n");
	for(i = 0; i < nY ; i++)
	{
		for(j = 0; j < nX; j++)
		{	printf("%c ", tempBoard[i][j].strWord[0]);
			
		}
		if(i < nLevel)
			printf("\t\tCLEAR");
		else if(i == nLevel)
			printf("\t\tYOU ARE HERE");
		printf("\n");
	}
}
/*	fillStructBoard fills board with randomized words based on the editable struct and stores it in the game's temp struct
	@param wordStruct sGameStruct - the editable struct, will be kept intact
	@param wordStruct sTempStruct - temp struct, will be edited, also a 2d array unlike sGameStruct
									It's width is 10x10 fixed but nX and nY determines what exists in the program's eyes
	@param nX - limits the board's width
	@param nY - limits the board's height
	@param nSize - limits the for loop to only look in values from 0 to nSize
*/
void
fillStructBoard(struct wordStruct sGameStruct[], struct wordStruct sTempStruct[10][10], int nX, int nY, int nWordCount, int nSize)
{
	int i, j, k = 0, nTemp, nFindNum = false, loopChecker = 0;
	int nArrDupeCheck[150];
	time_t randSeed;
	srand( (unsigned) time(&randSeed));
	rand(); rand(); rand();
	
	for(j = 0; j < nSize; j++)
	{	do
		{
		nTemp =  rand() % (nWordCount);
		nFindNum = false;
		loopChecker++;
		for(i = 0; i < nSize - 1; i++) // -1 just so it doesn't stuck in a loop
			if(nArrDupeCheck[i] == nTemp)
				nFindNum = true;
		
		} while (nFindNum == true);
		nArrDupeCheck[j] = nTemp;
	}

	for(i = 0; i < nY; i++)
	{
		for(j = 0; j < nX; j++)
		{
			sTempStruct[i][j] = sGameStruct[nArrDupeCheck[k]];
			k++;
		}
	}
	
}
/*	hintCounter counts hints and returns how many were found, used for the game
	hints sHintStruct - struct array to count hints from
*/
int
hintCounter(struct hints sHintStruct[])
{
	int i = 0;
	while(strcmp(sHintStruct[i].strRelation, "\0") != 0)
		i++;

	return i;
}

/*	wordPick is where the game mostly happens
	@param wordStruct sTempGameStruct - 
	@param nX - X input for board width sentinel code and game fail
	@param nY - X input for board width sentinel code AND game end
*/
void
wordPick(struct wordStruct sTempGameStruct[10][10], 
		 int nX, 
		 int nY)
{
	//variable initialization
	int nInput = 1, nLevel = 0, nRandHint, nRandHintLimit, nFailCount = 0;
	bool bLCount = false;
	char cInput[21];
	time_t randSeed; 
	srand( (unsigned) time(&randSeed)); //to randomize words, without it there will be a pattern
	
	do
	{
		printBoard(sTempGameStruct, nX, nY, nLevel);
		if(bLCount == false)
			printf("From left to right, enter a NUMBER: ");
		do
		{
		
			if(sTempGameStruct[nLevel][nInput].strWord[0] == '-')
				printf("\nYou can't select a word that you failed, choose another one\n");
			if(bLCount == true)
				printf("\nEnter value within range of the board (1 to %d): ", nX);
			bLCount = false;
			fflush(stdin);
			scanf("%d", &nInput);
			nInput--;
			bLCount = true;
		}while( !(nInput >= 0 && nInput <= nX) ||  sTempGameStruct[nLevel][nInput].strWord[0] == '-'  );
			
		printf("You picked %c\n", sTempGameStruct[nLevel][nInput].strWord[0]);
		nRandHintLimit = hintCounter(sTempGameStruct[nLevel][nInput].sHintPair);
		nRandHint = rand() % (nRandHintLimit);
		printf("\nHere is your hint: %s: %s", sTempGameStruct[nLevel][nInput].sHintPair[nRandHint].strRelation,
										sTempGameStruct[nLevel][nInput].sHintPair[nRandHint].strRelationValue );
		
		fflush(stdin);
		printf("\nEnter answer here (input in all caps): ");
		scanf("%[^\n]%*c", cInput);
		toUpperString(cInput);
		
		if(strcmp(cInput, sTempGameStruct[nLevel][nInput].strWord) == 0 && nLevel < nY)
			{	printf("\n**Correct Answer! Advance to the next level!**\n");
				sTempGameStruct[nLevel][nInput].strWord[0] = '*';
				nLevel++;
				nFailCount = 0;
				
			}	
		else
			{	printf("\n**Wrong answer\nCorrect Answer: %s\nPick another one from the same row**\n", sTempGameStruct[nLevel][nInput].strWord);
				nFailCount++;
				sTempGameStruct[nLevel][nInput].strWord[0] = '-';
			}	
	}
	while( (nLevel < nY) && (nFailCount < nX) );
	
	if(nLevel == nY)
		printf("\n**You win! I'm proud of you**\n");
	else if(nFailCount == nX)
		printf("\n**You lose! Better luck next time**\n");
	
	
}	
/*	gamePhase is mainly just there to input board size and execute 2 important fucntions, fillStructBoard and wordPick
	@param wordStruct sGameStruct - used for the game
	@param nWordCount - used for out of bounds board size
*/
void
gamePhase(struct wordStruct sGameStruct[], int nWordCount)
{
	struct wordStruct sTempGameStruct[10][10];
	int nXAxis, nYAxis, nSize = 0;
	do{
	if(nSize > nWordCount)
		printf("\nNot enough words in list to make board \n(Inputted size of board: %d) (Words in word list: %d)\n", nSize, nWordCount);
	boardSize(&nXAxis, &nYAxis, &nSize);
	} while (nSize > nWordCount); //if there's more spaces than words, it'll guard that from it
	
	fillStructBoard(sGameStruct, sTempGameStruct, nXAxis, nYAxis, nWordCount, nSize);	
	wordPick(sTempGameStruct, nXAxis, nYAxis);
	
	printf("\nGame Over\n");

}
	
/*	the main function's primary purpose is to be like a global variable holder but not really
*/
int
main()
{
//initialize variables
	int nMenuVal, nAdMenVal, nWordCount = 0;
//initialize array
	struct wordStruct sGameStruct[150]; initGameArr(sGameStruct);

//loop for the game
do
{
	nMenuVal = mainMenu();
	switch(nMenuVal)
	{
		case 1:
		if(nWordCount != 0)
			gamePhase(sGameStruct, nWordCount);
		else
		{	printf("No words loaded in yet!\n\n");}
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
				default:
					printf("\n");
					break;
			}
			}while(nAdMenVal != 10);
			break;
		case 816:
			matikanetannhauserfunc();
	}
}while(nMenuVal != 3);

}