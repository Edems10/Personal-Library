#if !defined 
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "myPrint.h"

void enter_to_file_string(FILE* f)
{
	char string[64];
	fgets(string, 64, stdin);							//reads up to 64 characters and puts it into a file
	fputs(string, f);
}
void enter_to_file_year(FILE* f)
{
	int i = 0, x;
	char string[256];
	time_t now;
	time(&now);
	struct tm* local = localtime(&now);					//get the structure for local time

	do {												//checks if the string contains number and saves it
		fgets(string, 256, stdin);
		x = atoi(string);
	} while (x < -3100 && x < (local->tm_year + 1900));  //(3100 BC)and check for current year 1900 + because that's the date it started counting from 
	fputs(string, f);
}
void enter_to_file_stars(FILE* f)
{
	char string[256] = { '\0' };
	int x;

	do {												//checks if the string contains number and saves it
		fgets(string, 256, stdin);
		x = atoi(string);

	} while (x > 5 || x < 1);							//the number has to be between 1-5
	for (int j = 0; j < x; j++)
	{
		string[j] = '*';
	}
	string[x] = '\n';									//the way the file reader is designed enter is required at the end
	fputs(string, f);
}
void enter_new_book(FILE* f)
{
	printf("Title: ");
	clean_stdin();
	enter_to_file_string(f);
	printf("Author: ");
	enter_to_file_string(f);
	printf("Year of Publication: ");
	enter_to_file_year(f);
	printf("Have you finished the book: ");
	enter_to_file_string(f);
	printf("How was the Book (1-5): ");
	enter_to_file_stars(f);
}
void search_for_book(FILE* f)
{
	rewind(f);
	char line[100]{ NULL };
	int count = 0;
	int myBool = 0;
	int lineCounter = 0;
	char book[500]{ NULL };
	char string[256]{ NULL };
	int lengthOfUserString = 0;

	printf("Enter what are you looking for : ");
	clean_stdin();
	gets_s(string);
	print_book_spec();

	for (int i = 0; i < sizeof(string); i++)				//get length of entered string
	{
		if (string[i] > 0)
			lengthOfUserString++;
	}

	while (fgets(line, sizeof line, f) != NULL)
	{
		if (count % 5 == 0 && count != 0)					//if all 5 were search 
		{
			if (myBool == 1)								//if book with same name/author... found
			{
				printf(book);
				printf("\n");
				myBool = 0;									//reseting bool
			}

			memset(&book[0], NULL, sizeof(book));			//reseting values of book
			lineCounter = 0;								//reseting line counter
		}
		if ((((count % 5) == 0) || (((count - 1) % 5) == 0) || (((count - 2) % 5) == 0)) && (myBool == 0))  //this which cathegory are we searching first,second,third line of evry book
		{
			int sameNameCounter = 0;
			for (int i = 0; i < lengthOfUserString; i++)
			{
				if (line[i] == string[i])
				{
					sameNameCounter++;
				}
			}
			if (sameNameCounter == lengthOfUserString) myBool = 1;
		}
		int charCounterInLine = 0;
		for (int i = 0; i < sizeof(line); i++)
		{
			charCounterInLine++;
			if (line[i] == '\n')						// looking for \n
			{
				if (((count % 5) == 0))					//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((64 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[lineCounter++] = '\t';
					}
				}
				else if ((((count - 1) % 5) == 0))		//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((32 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[lineCounter++] = '\t';
					}
				}
				else
				{
					book[lineCounter++] = '\t';
				}
				break;									// no need to continue after finding \n it's the sign that te line is over
			}
			book[lineCounter++] = line[i];				//adding the char untill we find end of line that is marked by \n
		}

		count++;
	}
	if (myBool == 1)
		printf(book);
	print_line('_');
}
void delete_book(FILE* f, char path[])
{
	rewind(f);
	char line[100]{ NULL };
	int count = 0, counterSkiped = 0, amountOfDeletedFiles = 0;;
	int deleteFound = 0;
	char string[256]{ NULL };
	int lengthOfUserString = 0;
	FILE* temp_file;
	temp_file = fopen("replica.c", "w");					//creating temporary file

	printf("Enter Title of the book : ");					
	clean_stdin();		
	gets_s(string);											//title of book to delete


	for (int i = 0; i < sizeof(string); i++)
	{
		if (string[i] > 0)
			lengthOfUserString++;							//we get length of title
	}

	while (fgets(line, sizeof line, f) != NULL)				//read line by line the original file
	{
		if (count % 5 == 0)									//Checking evry 5th = only Titles
		{
			int counter = 0;
			for (int i = 0; i < lengthOfUserString; i++)	//Check whhether all charcters match
			{

				if (string[i] == line[i])
				{
					counter++;
				}
			}

			if (counter == lengthOfUserString)				
			{	
				deleteFound = 1;							//if yes we found our match
			}
		}
		if (deleteFound == 1)
		{
			counterSkiped++;								//we found the Title so we need to skip 5 lines for each cathegory
			if (counterSkiped == 5)
			{
				deleteFound = 0;
				counterSkiped = 0;
				amountOfDeletedFiles++;
			}
		}
		else
		{
			fputs(line, temp_file);							//if nothing is found we just copy the line
		}

		count++;
	}
	fclose(f);
	fclose(temp_file);
	remove(path);											//elete the original file
	rename("replica.c", path);								//change the temporary file to the original name
	f = fopen(path, "a+");
	
	if (amountOfDeletedFiles < 1)
	{
		printf("No Title with this name:{%s} was found\n",string);
	}
	else if(amountOfDeletedFiles==1) {
		printf("Title:{%s} was sucesfully deleted\n", string);
	}
	else
	{
		printf("Title:{%s} was sucesfully deleted multiple times: [%d]\n", string, amountOfDeletedFiles);
	}
}
void print_all_books(FILE* f)
{

	char line[100];										// line represents each cathegory
	int count = 0;
	int lineCounter = 0;
	char book[500]{ NULL };

	rewind(f);
	print_book_spec();
	while (fgets(line, sizeof line, f) != NULL)			// Reding the file line by line 
	{
		if (count % 5 == 0 && count != 0)				// the way its stored each book takes 5 lines in file so we read 5 lines then print 
		{
			printf(book);
			memset(&book[0], NULL, sizeof(book));		// reseting book
			printf("\n");
			lineCounter = 0;
		}
		int charCounterInLine = 0;
		for (int i = 0; i < sizeof(line); i++)
		{
			charCounterInLine++;
			if (line[i] == '\n')						// looking for \n
			{
				if (((count % 5) == 0))					//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((64 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[lineCounter++] = '\t';
					}
				}
				else if ((((count - 1) % 5) == 0))		//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((32 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[lineCounter++] = '\t';
					}
				}
				else
				{
					book[lineCounter++] = '\t';
				}					
				break;									// no need to continue after finding \n it's the sign that te line is over
			}
			book[lineCounter++] = line[i];				//adding the char untill we find end of line that is marked by \n
		}

		count++;
	}
	printf(book);
	print_line('_');
}
int store_to_file(FILE* f, char* target_file)
{
	rewind(f);
	char ch;
	FILE* target;

	if ((target = fopen(target_file, "w"))==NULL)					//if the path is incorrect or some other issue return 0 with error
	{
		perror("There was an issue try selecting another file");
		return 0;
	}
	while ((ch = fgetc(f)) != EOF)									//copy char by char to new file
	{
		fputc(ch, target);
	}

	printf("File saved successfully.\n");
	fclose(target);
	return 1;
}
int choose_file(char* point)
{
	OPENFILENAME open;												 // common dialog box structure
	char filename[256] = { 0 };										// buffer for file name

	ZeroMemory(&open, sizeof(open));								//inicialization
	open.lStructSize = sizeof(open);
	open.lpstrFile = (LPWSTR)filename;
	open.lpstrFile[0] = '\0';										// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	open.nMaxFile = 256;											// use the contents of szFile to initialize itself.
	open.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	open.lpstrTitle = L"Select/Create Your Personal Library";
	open.nFilterIndex = 1;
	open.lpstrFileTitle = NULL;
	open.nMaxFileTitle = 0;
	open.lpstrInitialDir = NULL;

	// Display the Open dialog box. 

	if (GetOpenFileName(&open))
	{
		for (int i = 0; i < 256; i++)								//save values from lpstrFile to array
		{
			point[i] = open.lpstrFile[i];
		}
		return 1;
	}
	return 0;
}