/*
	A program that will fucntion through a command prompt and will have a parameter that allows the user to enter a file name
	When the file name is entered,  the program will check for the MP3 tag, if successfull, the program will use a fucntion
	to read all the MP3 files properties. If any property if unknown, the sting Unknown will be printed
--Author: Robert Vaughan
--Date: 07/04/2016
--Complier: GCC
--Environment: Bloodshell - DEV C++
--
*/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Macros
#define TAG 4
#define THRITY 31
#define FOUR 5
#define END 128
#define NC '\0'
#define TMAC "TAG"
#define ASCII 0
#define SIZE 20

//Struct Template
struct mp
{
	//Struct Members
	char tag[TAG];
	char title[THRITY];
	char artist[THRITY];
	char album[THRITY];
	char year[FOUR];
	char comment[THRITY];
	char genre;
};

//Prototypes
void getDetails(struct mp, FILE*);
int genreSearch(int, struct mp);
void nullCheck(char[]);

int main(int argc, char *argv[])
{
	//Declarations
	FILE *fp;
	struct mp music;
	int size;
	int i;
	
	fp = fopen(argv[argc - 1], "r+b");
	
	if (fp == NULL)
	{
		printf("Failed to open file entered.\n");
		exit(1);
	}//end if
	
	//Prints out file name user entered
	printf("\n%s\n", argv[argc - 1]);
	
	//Searches for TAG
	fseek(fp, -1 * END, SEEK_END);
	fread(music.tag, TAG - 1, 1, fp);
	music.tag[TAG - 1] = NC;
	
	//Check if TAG is valid
	if (strcmp(music.tag, TMAC) == 0)
	{
		printf("MP3 Tag Found!");
		getDetails(music, fp);
	}//end if
	else
	{
		printf("Tag Not Found!");
	}//end else
}//end main

/*
	A function that will scan through each property of the file and will search for information
	in relation to the MP3 file, such as the name of the song and the name of the artist.
*/

void getDetails(struct mp data, FILE* fp)
{
	//Declarations
	int key;
	char genre;
	
	fread(data.title, THRITY - 1, 1, fp);
	data.title[THRITY - 1] = NC;
	printf("\n\nSong Title: ");
	
	//Check if there is information
	nullCheck(data.title);
	
	fread(data.artist, THRITY - 1, 1, fp);
	data.artist[THRITY - 1] = NC;
	printf("Artist: ");
	
	//Check if there is information
	nullCheck(data.artist);
	
	fread(data.album, THRITY - 1, 1, fp);
	data.album[THRITY - 1] = NC;
	printf("Album: ");
	
	//Check if there is information
	nullCheck(data.album);
	
	fread(data.year, FOUR - 1, 1, fp);
	data.album[FOUR - 1] = NC;
	printf("Year: ");
	
	//Check if there is information
	nullCheck(data.year);
	
	//Points file pointer to genre information
	fseek(fp, -1, SEEK_END);
	
	//Reads in genre
	fread(&data.genre, 1, 1, fp);
	printf("Genre: ");
	
	//Gains the value of genre (ASCII)
	key = (int)data.genre;
	
	//Check for Unknown
	if (key < 0 || key > 125)
	{
		printf("Unknown\n");
	}
	else
	{
		//A call to check the genre binary file
		genreSearch(key, data);
	}//end else
}//end getDetails()

/*
	A function that checks if the genre code in the file is valid and find the name associated with said code
*/

int genreSearch(int key, struct mp song)
{
	//Declarations
	FILE *genrefp;
	int size;
	char string[SIZE];
	int count = 0;
	
	//File pointer to genre file
	genrefp = fopen("genre.txt", "r");
	
	//File pointer check
	if (genrefp == NULL)
	{
		printf("Could not open genre file\n");
		return (-1);
	}//end fail
	
	fseek(genrefp, 0, SEEK_SET);
	
	//While loop goes through entire file until it finds the genre
	while (count != key + 1)
	{
		fscanf(genrefp, "%s", string);
		
		if (count == key)
		{
			printf("%s\n", string);
			break;
		}//end if
		
		count++;
	}//end while
	
}//end genreSearch()

/*
	A function to check if information is contained within a certain aspect of a files properties
*/

void nullCheck(char value[])
{
	//Check if array contains ASCII 0
	if (value[0] == 0)
	{
		printf("Unknown\n");
	}//end if
	else
	{
		printf("%s\n", value);
	}//end else
}//end nullCheck()
