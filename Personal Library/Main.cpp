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
 * These files contains code which should recreate simple UI in console for user.
 * The user interacts with te menu or can store the book in files and read them through the console
 * The menu include functions to input,delete,print,find books
 * Functioanality also include loading other files and storing them.
 */

int main(int argc, char* argv[])
{
	FILE* f;
	char path[256];

	if (argc < 2)
	{
		printf("Path of File Not included You need to select your file\n");
		while (choose_file(path) != 1) 
		{ 
			printf("Something went wrong try again.\n"); 
		}
		while ((f = fopen(path, "a+")) == NULL)
		{
			while (choose_file(path) != 1)
			{
				printf("Something went wrong try again.\n");
			}
		}
		
	}
	else
	{
		char* path = argv[1];
		while ((f = fopen(path, "a+")) == NULL)
		{
			while (choose_file(path) != 1)
			{
				printf("Something went wrong try again.\n");
			}
		}
		
	}
	printf("File loaded from: %s\n", path);
	print_menu();

	while (1)
	{
		int c = getchar();
		while (c == 10)		// to get rid off the /n
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
			char target_file[256];
			while (choose_file(target_file) != 1)				//get path to save files to
			{
				printf("Something went wrong try again.\n");
			}
			store_to_file(f, target_file);
			printf("\n: ");
			break;
		case 'f':
			while (choose_file(path) != 1)						//get new path to load from
			{
				printf("Something went wrong try again.\n");
			}
			f = fopen(path, "a+");
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
