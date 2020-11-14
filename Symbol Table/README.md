

1]struct elesymbol has been defined for defining the structure for symbol , Its contents are
a)char pointer for name(char * name).
b)char array for - address(add[9]),section( sec[5] ),type(type[6]),value(value[50]).
c)int value are for - size of symbol(size), defined/undefined(def -1 for undefined and 1 being for defined).
d)structure pointer for next node.

2]struct eleliteral has been defined for defining the structure for literal , Its contents are
a)char array for- value(value[50]), address(add[9]), section(sec[5]).
b)structure pointer for the next node.

3]printsymbollist function
input:takes a structure pointer of ele.
use:to print the linked list of ele.

4]printliterallist function
input:takes a structure pointer of eleL
use:to print the linked list of eleL.

5]error function
input:char pointer (pointer to a string).
use:to print the string and exit(0) from the code.

6]lower function
input:char pointer (pointer to a string).
use:to change the upppercase char to lowercase char.

7]bufferzero1 function
input:char pointer(pointer to a char array) ,int (size of the array).
use:to put '\0' in the array.

8]stringbreak funtion
input:char  pointer(pointer to a char array (buf)),char double pointer(pointer to array of string(tok)),int (for knowing which section it is(s)),int pointer(pass by ref for label flag(label)).
use:tokenizing the character array(buf) ,storing it(tok).

9]datasection function
input:character pointer(pointer to char array(bufer)),int (value telling which sec 0=data and 1=bss).
use:return the value of data(1=byte ,2=word ,4=double).

10]stringcounter function
input:charcter array(it should be string ending with 0 and or/and 10 before it).
use:return number of element in the char array ( {" , } not being considered in the count).

11]charactercount
input:char pointer(assuming that the char array is array of char).
use:return number of char int the array.

12]sizeD
input:char pointer,int((type) signifying whether it is byte,word,double).
use:return the size of data section symbol.

13]power
input:int((a)int whose power is to be known),int((b)int value of power).
use:return a^b.

14]isdigit2
input: char pointer(to array of char).
use:return 1 (char array contains all digit) -1(char array contains atleast one char which is not a digit).

15]isdigit1
input:char pointer(assuming that it is char array with all char as digit).
use:return converting the char to digit.

16]sizeB
input:char pointer(char array containg the value of bss section symbol),int(signifying the type of symbol 1=byte, 2=word, 4=double).
use:return the value of size of bss secction symbol.

17]hexCon
input:char
use:return (-1 if its not a HEX) or value in decimal of HEX

18]zerAdd
input:char pointer(pointer to char array),int(size of the array).
use:to zero the address array.

19]swap1
input:char pointer(pass by refrence of the char),char pointer(pass by refrence of the char).
use:swaps the characters.

20]reverse
input:char pointer(to char array),int(pos of swap),int(pos of swap).
use:reverse the char according to postion.

21]itoa
input:int(value to converted),char pointer(char array to store the converted value),int(value of base).
use:integer to ascii conversion.

22]addCall
input:int(digit to be converted),int pointer(pass by refrence of carry to store carry).
use:returns HEX converted char of the digit and stores carry genrated.

23]addCal
input:char pointer(char array of the address),int(size to be addded into the address array).
use:adds the size to the address.

24]registercheck
input:char pointer(char array).
use:returns -1(if array is not a reg) or regid+pos in the array(int).

25]dwordcheck
input:char pointer(char array).
use:return 0(if its SIB) or 1(if its dword[reg] and sets sf(special flag)=1 if its any of the special reg(esp,ebp,sp,bp)) or 2 (if its dword[symbol]) or -1(if its none of the above).

26]check
input:struct ele pointer(to the linked list head),char pointer(to check if it is present in the linked list).
use:return -1(linked list is empty) or 1(char array is from text section) or 0(char array is from bss or data section).

27]sizeCal
input:int(op1 value of 1st operand),int(op2 value of 2nd operand),int(flag),int(immf immediate flag)
description:
	op1 or op2 =>7 <40 (reg 8 or 16 or 32 bit) =-1 (symbol) =2 (dword[symbol]) =0 (dword[SIB]) =1 (dword[reg]) op2<-1 (ins of one operand.
	flag=1 (ins is of mov) >1 (ins is which takes just one operand).
	immf=0 (imm<128) =1(imm>127) =-2(ins is of the one operand).
use:calculates value according to the value of op1,op2,flag,immf.

28]setter
input:char pointer(char array of instruction),char pointer(char array of the operand1),char pointer(char array of the operand2),int poiter(pass by refernce of the op1 flag),int pointer(pass by reference of the op2 flag),int pointer(pass by reference of the flag),int pointer(pass by references of the immediate flag).
use:sets all the flag.

29]newnodesymbol
input:char pointer(char array of name),char pointer(char array of address),int(value of sec =0(data) or =1(bss) or =2(text)),int(value of type =1(byte) or =2(word) or =4(double)),char pointer(char array of the value),int(size of the symbol),int(=1 symbol defined =-1 undefined).
use:return node of symbol according to input.

30]newnodeliteral2
input:char pointer(char array of value),char pointer(char array of address),int(value defining the section =0(data) =1(bss) =2(text)).
use:return node of literal according to input.

31]element
input:char pointer(char array of buffer),struct ele pointer(head pointer of linked list of symbol),struct eleL pointer(head pointer of linked list of literal),char pointer(char array of address),int(value of section).
use:creates element of symbol and literal according to input.

32]table
input:FILE pointer(of the reading file),struct ele pointer(of linked list of symbol),struct eleL pointer(of linked list of literal).
use:created linked list of symbol and literal.

33]writeFile
input:FILE pointer(of the writing file),struct ele pointer(head pointer of linked list of symbol),struct eleL pointer(head pointer of linked list of literal).
use:to write the file according to linked list of symbol and literal.
