#include <stdio.h>
#include <string.h>
/*
Notes:
Admin Phase
	In the Admin Phase, this serves as the interface and features that will allow the Admin or game master
	manage the collection of words and the trivia/clues that will be used in the game. It is important to note that each
	word (the answer) can be at most 20 letters. And there can be at most 10 trivia per word. The trivia/clue is
	represented by a relation and the relation value pair. The relation and relation value can each
	be a phrase and each can have at most 30 characters. For example, for the word Table, the following can be
	some trivia information:

Game Phase
	If the user chooses Game Phase from the Main menu, the program then asks the user what dimension
	the board (of letters) will be. Proceed by loading the text file of words and trivia (ask the user for the filename).
	From this, generate the letters to appear in the board. Make sure you have enough entries in the database for
	the grid. Meaning, if you only have 12 entries in the database, then you can have at most a 3x4, 4x3, 5x2, 2x5,
	6x2, or 2x6 board, since the answers in the grid should be unique words. Note also that in a row, the letters
	should be unique. Once the board is initialized, the user can start to play.
*/
void
MainMenu()
{
	char MenuOptions[100] = "1. Game\n2. Admin\n3. Exit\nPlease choose an option: ";
	char MenuChoice[20];
	
	do{
	printf("%s", MenuOptions);
	scanf("%s", MenuChoice);
	printf("\nYou chose %s\n", MenuChoice);
	} while(strcmp(MenuChoice, "Game") != 0 && strcmp(MenuChoice, "Admin") != 0 && strcmp(MenuChoice, "Exit") != 0 && strcmp(MenuChoice, "1") != 0 && strcmp(MenuChoice, "2") != 0 && strcmp(MenuChoice, "3") != 0);
	
	if(strcmp(MenuChoice, "Game") == 0)
	{
		//placeholder...
	}
	else if(MenuChoice, "Admin") == 0)
	{
		AdminMenu();
	}
	else if(MenuChoice, "Exit") == 0)
	{
		
	}
	else if(MenuChoice, "1") == 0)
	{
		
	}
	else if(MenuChoice, "2") == 0)
	{
		
	}
	else
	{
		
	}
}


/* Note that there can be at most 150 entries or words(serving as the answers in the game), but a word can have
at most 10 trivia/clues.*/
void
AdminMenu()
{
	char Answer[21];
	char Relation[31];
	char RelationValue[31];
	
	
}

//pangtest ko lang tong main
int main()
{
	
	MainMenu();
	
	
	return 0;
}