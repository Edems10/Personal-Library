#pragma once
#if !defined 
#define _CRT_SECURE_NO_WARNINGS
#endif
#if !defined 
#include <stdio.h>
#endif
/**
 * This function saves string enterd by the user to the file
 * Parameters:
 * FILE: cointaining file to write to
 * Return Value:
 * Nothing -- Note: Modifies the file.
 * Description:
 */
void enter_to_file_string(FILE* f);
/**
 * This function saves specific year ranged from -3000 up to current year entered by the user to the file
 * otherwise stays in loop waiting for correct year
 * @param f cointaining file to write to
 * @note Modifies the file.
 */
void enter_to_file_year(FILE* f);
/**
 * This function asks user for intiger input ranging from 1-5
 * Conversts this number to stars and prints it in to the file
 * @param f Cointaining file to write to
 * @note Modifies the file.
 */
void enter_to_file_stars(FILE* f);
/**
 * This function serves as an menu that combines other functions
 * At the end user will enter book with 5 categories to the file
 * @param f Cointaining file to write to
 * @note: Modifies the file.
 */
void enter_new_book(FILE* f);
/**
 * This function browses through file checking the first 3 categories (Author,Year,Title)
 * If any matches it will print them out in readable static format
 * FILE: cointaining file to write to
 * @param f Cointaining file to write to
 * @note: Modifies the file.
 */
void search_for_book(FILE* f);
/**
 * User inputs string then
 * This function deletes book if it matches the Title of any book
 * Inseretd by the user string
 * The Function delets the book by deleting all 5 cathegories
 * The delete is done by creatig tempoary file without the book
 * Then writing it to the original file
 * @param f Cointaining file to write to
 * @param path: containg path to the file
 * @note: Modifies the file.
 */
void delete_book(FILE* f, char path[]);
/**
 * This function prints all books from file in readable format
 * @param f Cointaining file to write to
 * @note: Modifies the file.
 * 		  The format is static
 */
void print_all_books(FILE* f);
/**
 * This function saves the loaded file to the new file
 * @param f Cointaining file to write to
 * @param target_file*: array that contains the path to file that will be copied to or created
 * @return  0 - Fail
 * 			1 - Succes
 */
int store_to_file(FILE* f, char* target_file);
/**
 * This function prompts user to select file from windows explorer
 * @param *p: array[256] path of file will be stored here
 * @return  0 - User failed to select File
 *			1 - File selected Correctly
 */
int choose_file(char* p);