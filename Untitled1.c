#include <string.h>
#include <stdio.h>
typedef char str20[21];
typedef char str25[26];

struct skillDef
{
	str20 skillType;
	int Level; 
};

struct attr
{
	int intel;
	int agi;
	int str;
	int dex;
};
struct player
{
	str20 charName;
	str20 charClass;
	int skillHave;
	struct attr charAttr;	
	struct skillDef skillDesc[10];

};

void getCharacter(struct player *pC)
{	int i;
	scanf("%s", pC->charName);
	scanf("%s", pC->charClass);
	//attributes
	scanf("%d", &pC->charAttr.intel);
	scanf("%d", &pC->charAttr.agi);
}

typedef struct network
{
	str25 monitorMake;
	str25 keyboardMake;
	str25 mouseMake;
	int hardDriveCap[12];
	struct ram 
	{
		int capacity;
	} memoryChip[4];	
	str25 cDriveMake;
	str25 floppyMake;
	str25 psuMake;	
} model[10]; 


int main()
{

//struct player RagChar;

model p;
//strcpy(RagChar.skillDesc[1].skillType,"Heal");
//printf("%s", RagChar.skillDesc[1].skillType);

p[10].hardDrive[5].capacity = 5;
printf("%d", p[10].hardDrive[5].capacity);



}
