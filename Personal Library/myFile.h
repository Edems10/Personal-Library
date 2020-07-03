#pragma once
#if !defined 
#define _CRT_SECURE_NO_WARNINGS
#endif
#if !defined 
#include <stdio.h>
#endif
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * This function saves string enterd by the user to the file
  */
void enter_to_file_string(FILE* f);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * This function saves specific year ranged from -3000 to current year enterd by the user to the file
  *	otherwise stays in loop untill waiting for correct input
  */
void enter_to_file_year(FILE* f);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * This function asks user for intiger input ranging from 1-5
  * Conversts this number to stars and prints it in to the file
  */
void enter_to_file_stars(FILE* f);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * This function serves as an menu that combines other functions
  * At the end user will enter book with 5 categories to the file
  */
void enter_new_book(FILE* f);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- 
  * Description:
  * User inputs string and then
  * This function browses through file checking the first 3 categories (Author,Year,Title)
  * If any matches it will print them out in readable static format
  */
void search_for_book(FILE* f);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * char: containg path to the file
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * User inputs string then
  * This function deletes book if it matches the Title of any book 
  * Inseretd by the user string
  * The Function delets the book by deleting all 5 cathegories
  * The delete is done by creatig tempoary file without the book
  * Then writing it to the original file
  */
void delete_book(FILE* f, char path[]);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * This function prints all books from file in readable format 
  * -- Note: the format is static
  */
void print_all_books(FILE* f);
/**
  * Parameters:
  * FILE: cointaining file to write to
  * Return Value:
  * Nothing -- Note: Modifies the file.
  * Description:
  * This function saves the loaded file to the new enterd file by the user
  */
void store_to_file(FILE* f);

int ChooseProgram(char* path);