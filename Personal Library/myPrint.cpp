#if !defined 
#define _CRT_SECURE_NO_WARNINGS
#endif
#if !defined 
#include <stdio.h>
#endif

void clean_stdin()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
void print_line(char c)
{
	printf("\n");
	for (int i = 0; i < (8 * 15) - 3; i++)
	{
		printf("%c",c);
	}
	printf("\n");
}
void print_menu()
{
	print_line('#');
	printf("(a)\tEnter book\n");
	printf("(b)\tRemove book\n");
	printf("(c)\tSearch for book\n");
	printf("(d)\tPrint book list\n");
	printf("(e)\tStore library to a file\n");
	printf("(f)\tRead library from a file\n");
	printf("(m)\tPrint Menu\n");
	printf("(h)\tExit Personal Library");
	print_line('#');
}
void print_book_spec()
{
	printf("\nTitle");
	for (int i = 0; i < 8; i++)
	{
		printf("\t");
	}
	printf("Author");
	for (int i = 0; i < 4; i++)
	{
		printf("\t");
	}
	printf("Year\t");
	printf("Read\t");
	printf("Grade");
	print_line('_');
}