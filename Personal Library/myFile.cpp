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

	} while (x > 5 || x < 1);
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

	for (int i = 0; i < sizeof(string); i++)
	{
		if (string[i] > 0)
			lengthOfUserString++;
	}

	while (fgets(line, sizeof line, f) != NULL)
	{
		if (count % 5 == 0 && count != 0)
		{
			if (myBool == 1)
			{
				//printf("%d :", count + 1);
				printf(book);
				printf("\n");
				myBool = 0;
			}

			for (int i = 0; i < sizeof(book); i++)
			{
				book[i] = NULL;
			}


			lineCounter = 0;
		}
		if ((((count % 5) == 0) || (((count - 1) % 5) == 0) || (((count - 2) % 5) == 0)) && (myBool == 0))
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
			if (line[i] == '\n')					// looking for \n
			{
				if (((count % 5) == 0))			//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((64 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[lineCounter++] = '\t';
					}
				}
				else if ((((count - 1) % 5) == 0))			//the main reason behind this is to have somewhat allined output in the console
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
				break;								// no need to continue after finding \n it's the sign that te line is over
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
	int count = 0, counterSkiped = 0;
	int deleteFound = 0;
	char string[256]{ NULL };
	int lengthOfUserString = 0;
	FILE* fileptr2;
	fileptr2 = fopen("replica.c", "w");

	printf("Enter Title of the book : ");
	clean_stdin();
	gets_s(string);


	for (int i = 0; i < sizeof(string); i++)
	{
		if (string[i] > 0)
			lengthOfUserString++;
	}

	while (fgets(line, sizeof line, f) != NULL)
	{
		if (count % 5 == 0)
		{
			int counter = 0;
			for (int i = 0; i < lengthOfUserString; i++)
			{

				if (string[i] == line[i])
				{
					counter++;
				}
			}

			if (counter == lengthOfUserString)
			{
				deleteFound = 1;
			}
		}
		if (deleteFound == 1)
		{
			counterSkiped++;
			if (counterSkiped == 5)
			{
				deleteFound = 0;
			}
		}
		else
		{
			fputs(line, fileptr2);
		}

		count++;
	}
	fclose(f);
	fclose(fileptr2);
	remove(path);
	rename("replica.c", path);
	f = fopen(path, "a+");
}
void print_all_books(FILE* f)
{

	char line[100];									// line represents each cathegory
	int count = 0;
	int counter2 = 0;
	char book[500]{ NULL };

	rewind(f);
	print_book_spec();
	while (fgets(line, sizeof line, f) != NULL)
	{
		if (count % 5 == 0 && count != 0)			// the way its stored each book takes 5 lines in file so we read 5 lines then print 
		{
			printf(book);
			memset(&book[0], NULL, sizeof(book));	// reseting book
			printf("\n");
			counter2 = 0;
		}
		int charCounterInLine = 0;
		for (int i = 0; i < sizeof(line); i++)
		{
			charCounterInLine++;
			if (line[i] == '\n')					// looking for \n
			{
				if (((count % 5) == 0))			//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((64 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[counter2++] = '\t';
					}
				}
				else if ((((count - 1) % 5) == 0))			//the main reason behind this is to have somewhat allined output in the console
				{
					int amountOfSpaces = ((32 - charCounterInLine) / 8) + 1;
					for (int k = 0; k < amountOfSpaces; k++)
					{
						book[counter2++] = '\t';
					}
				}
				else
				{
					book[counter2++] = '\t';
				}

				//book[counter2++] = '\t';				// adding tab instead of \n						
				break;								// no need to continue after finding \n it's the sign that te line is over
			}
			book[counter2++] = line[i];				//adding the char untill we find end of line that is marked by \n
		}

		count++;
	}
	printf(book);
	print_line('_');
}
void store_to_file(FILE* f)					// can try with window.h file explorer
{
	rewind(f);
	char ch, target_file[100];
	FILE* target;

	clean_stdin();
	printf("Enter name of target file\n");
	gets_s(target_file);

	target = fopen(target_file, "w");
	if (!target)perror("fopen");

	while ((ch = fgetc(f)) != EOF)
		fputc(ch, target);

	printf("File saved successfully.\n");
	fclose(target);

}
int ChooseProgram(char* path)
{
	OPENFILENAME ofn;       // common dialog box structure
	//char szFile[260];       // buffer for file name
	HWND hwnd = NULL;              // owner window
	HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPWSTR)path;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn) == TRUE)
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
			0, (LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL);
		return 0;
	}
	return -1;
} //not working