#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctype.h>
#include <Windows.h>
#include <time.h>
#include "myPrint.h"
#include "myFile.h"

/**
 * Files:    main.cpp
 *			 myFile.cpp
 *			 myPrint.cpp
 *			 myFile.h
 *			 myPrint.h
 *
 * Author:	 Adam Mitrenga (a_mitreng@utb.cz)
 * Date:     07/2020
 * Course:   Programming in C (700.016)
 *
 * Summary of Program:
 *
 *   These files contains code which should recreate simple UI in console for user.
 *	 The user interacts with te menu or can store the book in files and read them through the console
 *	 The menu include functions to input,delete,print,find books
 *	 Functioanality also include loading other files and storing them.
 *
 */

int main(int argc, char* argv[])
{
	FILE* f;
	char path[256];
	
	if (argc < 2)
	{
		printf("Path of File Not included You need to select your file\n");
		char path[256] = "C:\\TestFolder\\PersonalLibrary\\PersonalLibrary.txt";
		f = fopen(path, "a+");
		printf("File loaded from: %s\n", path);
		
	}
	else
	{
		 char* path = argv[1];
		 f = fopen(path, "a+");
		 printf("File loaded from: %s\n", path);
	}
	print_menu();
	//ChooseProgram(path); // ok for some reason it returns the shit in path and every fucking second char is 0 ???????


	// TODO also add loop to test if the path is corrcet
	
	while (1)
	{

		int c = getchar();
		while (c == 10)		// to get rid off the /n that printf leave
		{
			c = getchar();
		}
		switch (c)
		{
		case 'a':
			enter_new_book(f);
			printf("\n: ");
			break;
		case 'b':
			delete_book(f, path);
			printf("\n: ");
			break;
		case 'c':
			search_for_book(f);
			printf("\n: ");
			break;
		case 'd':
			print_all_books(f);
			printf("\n: ");
			break;
		case 'e':
			store_to_file(f);
			printf("\n: ");
			break;
		case 'f':
			printf("Enter path of File\n:");
			clean_stdin();
			char string[256];
			gets_s(string);
			f = fopen(string, "a+");
			printf("\n: ");
			break;
		case 'm':
			print_menu();
			break;
		case 'h':
			fclose(f);
			exit(0);
		default:
			printf("\n: ");
			break;
		}
	}
}
