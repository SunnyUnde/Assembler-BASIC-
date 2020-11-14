Globally defined-structure pointer and variable

erroh - error linked list header pointer
defineh - defined symbol linked list header pointer
undefineh - undefined symbol linked list header pointer

char register8 -contains  8 bit registers
char register16 -contains 16 bit registers
char register32 -contains 32 bit registers

char instr0 -contains ins which takes 2 operands
char instr1 -contains ins which takes 1 operands

struct define->
	char name -character array to strore the defined symbol
	struct define* next -next pointer to struct define

struct undefine->
	char name - character array to store the undefined symbol
	int line - line where it was declared
	struct undefine* next-next pointer to struct undefine

struct error
	int line - line where error has declared
	char buf - character array to store error
	struct error* next -next pointer to struct error

cratedefine -function to create struct define

errorp -stores error in the linked list of error

printerror -function to print errors

bufzero1 -function to nullify the charcter array

power -function to get power of the integer

isdigit2 -function tells if the charctr array is digit

isdigit1 -converts character arrray to digit

addundefine -function adds the node to undef linked list

changetoerror -function to that creates undef symbol node

checkundefine -function checks for undefined symbols

checkdefine -function to check data section symbols validity

checkdef -function to check if symbol defined

checkSymbol -function to check validity of the symbol

checkins -function to check if instruction

checkreg -function to check if reg

checkit -function that check if character buffer is reg,defined symbol,digit

checkoprand -function to check what operand the chracter array is

check -function checks the line of the file

checkerror -function which checks the asm file line by line
