Input: Two file each contain symbol table and address of first asm file.
Output:symbol table are merge in third file.

Program:
1]struct symbol- store the symbol read from the file
char name -store the name of symbol
char newname -new name for the symbol if there is duplicate
char add -store the address of the symbol
char sec -store the section of the symbol
char value -store the value of the symbol
char size -store the size of the symbol
char def -store if the symbol is defined or not (D=defined U=undefined)
struct symbol* next -points the next symbol structure

2]printlist -function to print the linked list of the symbol

3]error -function to print the error and to exit from the code

4]checkfile -funtion to checks if the file pointer is NULL

5]power -function to get the power of the integers

6]isdigit1 -funnction to convert a character array into its equivalant integer
7]swap1	-function to swap 2 character pointer data

8]reverse -function to revese the charcter array in a given range

9]itoa -function to convert integer to ascii of given base

10]createnode -function to create a individual node of the struct symbol

11]list -function to create linked list of the symbol

12]changeadd -function to change address of the symbol

13]checkname -function to check if symbol with same name present


14]dupli-function to create a duplicate of given symbol address and adds int passed to it with it

15]mergesymbol-function to merge two linked list of struct symbol

16]writefile -function to write file with given linkedlist of struct symbol
