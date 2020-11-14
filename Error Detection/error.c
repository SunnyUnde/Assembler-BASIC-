#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct error *errorh=NULL;
struct define* defineh=NULL;
struct undefine* undefineh=NULL;
char register8[8][3]={"al","cl","dl","bl","ah","ch","dh","bh"};
char register16[8][3]={"ax","cx","dx","bx","sp","bp","si","di"};
char register32[8][4]={"eax","ecx","edx","ebx","esp","ebp","esi","edi"};
char instr0[8][4]={"mov","add","sub","cmp","xor","adc","or","and"};
char instr1[8][5]={"loop","jmp","not","div","inc","dec","pop","push"};
int Label=-1,Flag=0;
struct define
{
	char name[20];
	struct define* next;
};

struct undefine
{
	char name[20];
	int line;
	struct undefine* next;
};

struct error
{
	int line;
	char buffer[1000];
	struct error* next;
};

struct define* createdefine(char *buffer)
{
	struct define* node=(struct define*)malloc(sizeof(struct define));
	strcpy(node->name,buffer);
	node->next=NULL;
	return node;
}

void errorp(char *a,int line)
{
	struct error* node=(struct error*)malloc(sizeof(struct error));
	strcpy(node->buffer,a);
	node->line=line;
	node->next=NULL;
	if(errorh==NULL)
	{
		errorh=node;
		return;
	}
	struct error* temp=errorh;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=node;
}

void printerror()
{
	struct error* temp=errorh;
	if(temp==NULL)
	{
		printf("List is Empty");
	}
	while(temp!=NULL)
	{
		printf("%d:%s\n",temp->line,temp->buffer);
		temp=temp->next;
	}
}

void bufzero1(char *a,int n)
{
	for(int i=0;i<n;i++)
		a[i]='\0';
}

unsigned long int power(unsigned long int a,int b)
{
	if(b==0)
		return 1;
	return a*power(a,(b-1));
}

int isdigit2(char *a)
{
	int i=0,sign=1;
	if(a[0]=='-')
	{
		i++;
	}
	if(a[0]=='+')
	{
		i++;
	}
	if(a[i]=='\0')
		return -1;
	while(a[i]!='\0')
	{
		if(isdigit(a[i])!=0)
			i++;
		else
			return -1;
	}
	return 1;
}

unsigned long int isdigit1(char* a)
{
	int m,i=0,n=strlen(a),sign=1;
	unsigned long int ans=0;
	n--;
	if(a[0]=='-')
	{
		sign=-1;
		i++;
		n--;
	}
	if(a[0]=='+')
	{
		sign=1;
		i++;
	}
	while(a[i]!='\0')
	{
		if(a[i]<=57 && a[i]>=48)
		{
			if(a[i]==48)
				m=0;
			else 
				if(a[i]==49)
				m=1;
				else
					if(a[i]==50)
						m=2;
					else
						if(a[i]==51)
							m=3;
						else
							if(a[i]==52)
								m=4;
							else
								if(a[i]==53)
									m=5;
								else
									if(a[i]==54)
										m=6;
									else
										if(a[i]==55)
											m=7;
										else
											if(a[i]==56)
												m=8;
											else
												if(a[i]==57)
													m=9;
			ans=ans+power(10,n)*m;
			n--;
		}
		i++;
	}
	ans=ans*sign;
	return ans;
}

void addundefine(char *buffer,int line)
{
	struct undefine* node=(struct undefine*)malloc(sizeof(struct undefine));
	strcpy(node->name,buffer);
	node->line=line;
	node->next=NULL;
	if(undefineh==NULL)
	{
		undefineh=node;
		return;
	}
	struct undefine* temp=undefineh;
	struct undefine*temp1=NULL;
	while(temp!=NULL)
	{
		temp1=temp;
		if(strcmp(temp->name,node->name)==0)
		{
			free(node);
			return;
		}
		temp=temp->next;
	}
	temp1->next=node;
}

struct error* changetoerror(int line)
{
	struct error* node=(struct error*)malloc(sizeof(struct error));
	strcpy(node->buffer,"Symbol Undefined Encountered");
	node->line=line;
	node->next=NULL;
	return node;
}

void checkundefine()
{
	if(undefineh==NULL)
		return;
	struct undefine* temp=undefineh;
	struct undefine* temp1=NULL;
	struct define* deftemp=defineh;
	if(defineh!=NULL)
	{
		while(temp!=NULL && deftemp!=NULL)
		{
			if(strcmp(temp->name,deftemp->name)==0)
			{
				if(temp==undefineh)
				{
					undefineh=undefineh->next;
					free(temp);
					temp=undefineh;
				}
				else
				{
					temp1->next=temp->next;
					free(temp);
					temp=temp1->next;
				}
			}
			else
			{
				temp1=temp;
				temp=temp->next;
			}
			deftemp=deftemp->next;
		}
	}
	if(undefineh==NULL)
	{
		return;
	}
	temp=undefineh;
	struct error* temp2=errorh;
	struct error* temp3;
	char buffer[1000];
	while(temp!=NULL)
	{
		temp3=NULL;
		temp2=errorh;
		while(temp2!=NULL)
		{
			if(temp2->line>temp->line)
			{
				struct error* node=changetoerror(temp->line);
				if(temp2==errorh)
				{
					node->next=temp2;
					errorh=node;
				}
				else
				{
					node->next=temp3->next;
					temp3->next=node;
				}
				break;
			}
			temp3=temp2;
			temp2=temp2->next;
		}
		temp=temp->next;
	}
	while(undefineh!=NULL)
	{
		struct error* node=changetoerror(undefineh->line);
		temp3->next=node;
		temp3=node;
		temp=undefineh;
		undefineh=undefineh->next;
		free(temp);
	}
}

void checkdefine(char *buffer,int type,int line)
{
	int n=strlen(buffer);
	if(n==0)
	{
		errorp("Need a operand, can't be empty",line);
		return;
	}
	if(n==1)
	{
		if(isalpha(buffer[0]!=0))
		return;//check if its a character
	}
	//check if int is then in its data limit
	//else if array which one character or int no mix allowed
	//else if string should end with 0 or 10,0
	if(isdigit2(buffer)==1)
	{
		unsigned long int num=isdigit1(buffer);
		if(type==1 && num>256)
			errorp("Byte Data exceeds bound",line);
		else
			if(type==2 && num>65536)
				errorp("Word Data exceeds bound",line);
			else
				if(type==4 && num >4294967295)
					errorp("Double Data exceeds bound",line);
		return;
	}
	else
	{
		if(buffer[0]==39)
		{
			for(int i=1;buffer[i]!='\0';)
			{
				if(isalpha(buffer[i])==0 && isdigit(buffer[i])==0)
				{
					errorp("Unacceptable Charcter array declaration",line);
					return;
				}
				if(buffer[i+1]==39) 
					if(buffer[i+2]==',' && buffer[i+3]==39)
						i+=4;
					else
						if(buffer[i+2]=='\0')
							break;
						else
						{
							errorp("Unaccptable declaration of character array",line);
							return;
						}
			}
			return;
			//character array;
			//check it can just have numbers or alphabeth;
		}
		else
		{
			if(buffer[0]=='"')
			{
				//string which ends with 10,0 or 0
				int i=1;
				while(buffer[i]!='"')
				{
					if(buffer[i]==92)
					{
						if(buffer[i+1]=='"')
						i+=2;
					}
					else
						if(buffer[i]=='\0')
						{
							errorp("Invalid string declaration",line);
							return;
						}
						else
							i++;
				}
				i++;
				if(buffer[i]==',')
				{
					i++;
					if((buffer[i]=='0' && buffer[i]=='\0') || (buffer[i]=='1' && buffer[i+1]=='0' && buffer[i+2]==',' && buffer[i+3]=='0'&& buffer[i+4]=='\0'))
					{
						return;
					}
				}
				errorp("Invalid string End",line);
				return;
			}
			else
			{
				int i=0,j;
				long int ans=0;
				char inta[11];
				while(buffer[i]!='\0')
				{
					j=0;
					while(buffer[i]!=',' && buffer[i]!='\0')
					{
						inta[j]=buffer[i];
						i++;
						j++;
					}
					i++;
					inta[j]='\0';
					if(isdigit2(inta)==-1)
					{
						errorp("Invalid declaration of int array",line);
						return;
					}
					else
					{
						ans=isdigit1(inta);
						if(type==1 && ans>256)
						{
							errorp("Byte data exceeds",line);
							return;
						}
						else
						{
							if(type==2 && ans>65536)
							{
								errorp("word data exceeds",line);
								return;
							}
							else
							{
								if(type==4 && ans>4294967295)
								{
									errorp("Double data exceeds",line);
									return;
								}
							}
						}
					}
					//check if int array.
				}
			}
		}
	}
}

int checkdef(char *buffer)
{
	if(defineh==NULL)
		return 1;
	struct define* temp=defineh;
	while(temp!=NULL)
	{
		if(strcmp(buffer,temp->name)==0)
		{
			return 0;
		}
		temp=temp->next;
	}
	return 1;
}

int checkSymbol(char* buffer,int sec,int line,int op)//op==1 checking for symbol op==0 checking for Label when sec==2;
{
	int i;
	if(isdigit(buffer[0])!=0)
	{
		errorp("Integer can't be at start of symbol",line);
		return 1;
	}
	for(i=0;i<8;i++)
	{
		if(strcmp(buffer,register8[i])==0 || strcmp(buffer,register16[i])==0 || strcmp(buffer,register32[i])==0)
		{
			errorp("Symbol can't be Register",line);
			return 1;
		}
		if(strcmp(buffer,instr0[i])==0 || strcmp(buffer,instr1[i])==0)
		{
			errorp("Symbol can't be Instruction",line);
			return 1;
		}
	}
	if(strlen(buffer)>4)
	{
		if(buffer[0]=='d' && buffer[1]=='w' && buffer[2]=='o' && buffer[3]=='r' && buffer[4]=='d')
		{
			if(buffer[5]=='[' || buffer[5]=='\0')
			{
				errorp("Symbol can't be dword",line);
			}
		}
	}
	if(defineh==NULL && (sec==0 || sec==1))
	{
		defineh=createdefine(buffer);
		return 0;
	}
	struct define* temp=defineh;
	struct define*temp2=NULL;
	if(sec==0 || sec==1 || (sec==2 && op==1 ))
	{
		while(temp!=NULL)
		{
			temp2=temp;
			if(strcmp(temp->name,buffer)==0)
			{
				if(sec==0 || sec==1)
				{
					errorp("Redfined Symbol",line);
					return 1;
				}
				return 0;
			}
			temp=temp->next;
		}
		if(sec==2)
		{
			addundefine(buffer,line);
			return -1;
		}
		temp2->next=createdefine(buffer);
		return 0;
	}
	if(sec==2)
	{
		if(defineh==NULL)
		{
			defineh=createdefine(buffer);
			return 0;
		}
		struct define* temp1=defineh;
		struct define* temp3=NULL;
		while(temp1!=NULL)
		{
			temp3=temp1;
			if(strcmp(temp1->name,buffer)==0)
			{
				errorp("Label Redfined",line);
				return 1;
			}
			temp1=temp1->next;
		}
		temp3->next=createdefine(buffer);
		return 0;
	}
	return 0;
}

int checkins(char *buffer)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(strcmp(buffer,instr0[i])==0)
		{
			return 2;//if it takes 2 operands
		}
		if(strcmp(buffer,instr1[i])==0)
		{
			if(i==0)
				return 0;//loop
			return 1;//it it takes 1 operands
		}
	}
	return -1;
}

int checkreg(char * buffer)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(strcmp(buffer,register8[i])==0)
		{
			return 8;
		}
		if(strcmp(buffer,register16[i])==0)
		{
			return 16;
		}
		if(strcmp(buffer,register32[i])==0)
		{
			return 32;
		}
	}
	return -1;
}

int checkit(char *buffer)
{
	int i=checkreg(buffer);
	if(i!=-1)
		return i;
	i=checkdef(buffer);
	if(i==0)
		return 1;
	i=isdigit2(buffer);
	if(i==1)
	{
		return 2;
	}
	return -1;
}

int checkoprand(char* buffer)
{
	int i,n;
	char temp[50];
	char *a;
	n=strlen(buffer);
	i=checkreg(buffer);
	if(i!=-1)
	{
		return i;//its a reg 8,16,32
	}
	i=isdigit2(buffer);
	if(i!=-1)
	{
		return 0;//its a imm;
	}
	i=checkdef(buffer);
	if(i==0)
	{
		return 3;// its a imm and symbol
	}
	if(buffer[0]=='[')//return 1 is for memory;
	{
		if(buffer[n-1]==']')
		{
			strcpy(temp,buffer);
			a=&temp[1];
			temp[n-1]='\0';
			strcpy(temp,a);
			i=checkdef(temp);
			if(i==0)
			{
				return 1;
			}
			i=checkreg(temp);
			if(i==8)
				return -1;
			if(i!=-1)
			{
				return 1;
			}
		}
		return -1;
	}
	if(buffer[0]=='d' && buffer[1]=='w' && buffer[2]=='o' && buffer[3]=='r' && buffer[4]=='d' && buffer[5]=='[' && buffer[n-1]==']')
	{
		strcpy(temp,buffer);
		a=&temp[6];
		temp[n-1]='\0';
		strcpy(temp,a);
		if(strlen(temp)==0)
			return -1;
		i=checkreg(temp);
		if(i==8)
			return -1;
		if(i!=-1)
			return 2;
		i=checkdef(temp);
		if(i==0)
			return 2;
		char array[3][50];
		int add=-1,mul=-1,j=0,k=0;
		i=0;
		while(temp[i]!='\0')
		{
			j=0;
			while(temp[i]!='+' && temp[i]!='*' && temp[i]!='\0')
			{
				array[k][j]=temp[i];
				i++;
				j++;
			}
			array[k][j]='\0';
			if(temp[i]=='+')
				add=i;
			if(temp[i]=='*')
				mul=i;
			if(temp[i]!='\0')
				i++;
			k++;
		}
		if(add!=-1 && mul!=-1 && strlen(array[2])==0)
		{
			return -1;
		}
		int a1=-1,a2=-2,a3=-1;
		a1=checkit(array[0]);//8,16,32=reg //1 symbol //2 digit //-1 for none
		a2=checkit(array[1]);
		a3=checkit(array[2]);
		if(a1==-1 || a2==-1 || a3==-1 || a1==8 || a2==8 || a3==8)
			return -1;
		if(add<mul)
		{
			if(a1==2 && a2==2)
				return -1;
			if(a1==1 && a2==1)
				return -1;
			if(mul!=-1)
			{
				if(a2!=2 && a3!=2)
				{
					return -1;
				}
				if(a2==1 || a3==1)
					return -1;
				if(a3==2)
				{
					a3==isdigit1(buffer);
					if(a3>9 && a3<0)
						return -1;
				}
				if(a3!=2)
				{
					a2=isdigit1(buffer);
					if(a2>9 && a2<0)
						return -1;
				}
			}
		}
		if(mul<add)
		{
			if(a1!=2 && a2!=2)
				return -1;
			if(a1==1 || a2==1)
			{
				return -1;
			}
			if(a1==2)
			{
				a1=isdigit1(buffer);
				if(a1>9 && a1<0)
					return -1;
			}
			if(a1!=2)
			{
				a2=isdigit1(buffer);
				if(a2>9 && a2<0)
					return -1;

			}
			if(add!=-1)
			{
				if(a3==2)
					return -1;
			}
		}
		return 2;
	}
	return -1;
}

void check(char **buffer,int j,int line)
{
	static int sec=-1;
	if(sec>2)
	{
		printf("\nFATAL ERROR\n");
		exit(0);
	}
	if(strcmp(buffer[0],"global")==0)
	{
		if(strcmp(buffer[1],"main")==0)
		{
			if(strlen(buffer[2])==0)
			{
				return;
			}
		}
		errorp("Not a instruction",line);
		return;
	}
	if(strcmp(buffer[0],"section")==0)
	{
		if(strcmp(buffer[1],".data")==0)
		{
			if(sec!=-1)
			{
				errorp("Inapproiate declaration of data section",line);
			}
			else
				sec=0;
		}
		else
		{
			if(strcmp(buffer[1],".bss")==0)
			{
				if(sec!=0 && sec!=-1)
				{
					errorp("Inapproriate declaration of bss section",line);
				}
				else
					sec=1;
			}
			else
			{
				if(strcmp(buffer[1],".text")==0)
				{
					if(sec!=1 && sec!=-1)
					{
						errorp("Inapprrotiate declaration of text section",line);
					}
					else
						sec=2;
					Flag=1;
				}
			}
		}
		if(j>2)
		{
			errorp("Unknown section attribute",line);
		}
		return;
	}
	if(sec==-1)
	{
		errorp("No section declared",line);
	}
	Label=-1;
	int n=strlen(buffer[0]);
	if(buffer[0][n-1]==':')
	{
		Label=1;
		buffer[0][n-1]='\0';
	}
	if(sec==0 || sec==1)
	{
		if(Label==1)
		{
			errorp("Label must be decalred only in text section",line);
			return;
		}
		if(j>3)
		{
			errorp("comma expected after operand1",line);
		}
		else
		{

			if(checkSymbol(buffer[0],sec,line,0)==1)
				return;
			if(sec==0)
			{
				if(strcmp(buffer[1],"dd")==0)
				{
					checkdefine(buffer[2],4,line);
				}
				else
				{
					if(strcmp(buffer[1],"dw")==0 )
					{
						checkdefine(buffer[2],2,line);
					}
					else
					{
						if(strcmp(buffer[1],"db")==0)
						{
							checkdefine(buffer[2],1,line);
						}
						else
						{
							errorp("Wrong declaration of data type",line);
							return;
						}
					}
				}	
			}
			if(sec==1)
			{
				if(strcmp(buffer[1],"resd")==0 || strcmp(buffer[1],"resb")==0 || strcmp(buffer[1],"resw")==0)
				{
					if(isdigit2(buffer[2])==-1)
					{
						errorp("Error attempt to reserve non-constant value at BSS space",line);
						return;
					}
				}
				else
					errorp("Wrong declaration of data type",line);
				return;
			}
		}
		return;
	}
	if(sec==2)
	{
		int ins=-1,op1=-1,op2=-1;
		char ains[50],aop1[50],aop2[50];
		if(Label==1)
		{
			if(checkSymbol(buffer[0],sec,line,0)==1)
				return;
			strcpy(ains,buffer[1]);
			strcpy(aop1,buffer[2]);
			strcpy(aop2,buffer[3]);
		}
		else
		{
			strcpy(ains,buffer[0]);
			strcpy(aop1,buffer[1]);
			strcpy(aop2,buffer[2]);
		}
		ins=checkins(ains);
		if(ins==-1)
		{
			errorp("Undefined ins",line);
			return;
		}
		if(strlen(aop1)==0)
		{
			errorp("Operand1 required",line);
			return;
		}
		op1=checkoprand(aop1);
		if(op1==-1)
		{
			if(ins==1 || ins==1)
			{
				//undefine
				addundefine(aop1,line);
				return;
			}
			errorp("Operand 1 entered is unrecognizable",line);
			return ;
		}
		if(op1==0 || (op1==3 && ins==2))//op1 can't be imm nor it can be symbol if its from ins==2;
		{
			errorp("Invalid combination of opcode and operands",line);
		}
		if(ins==0 && op1!=3)
		{
			errorp("Invalid combination of opcode and operands",line);
			return;
		}
		if(ins==1 && op1==0)
		{
			errorp("Can't have immediate",line);
			return;
		}
		if(ins==2)
		{
			if(strlen(aop2)==0)
			{
				errorp("Operand2 is required",line);
				return;
			}
			op2=checkoprand(aop2);
			if(op2==-1)
			{
				addundefine(aop2,line);
				return;
			}
			else
			{
				if(op1==8 &&(op2==16 || op2==32))
				{
					errorp("Mismatch in register found",line);
					return;
				}
				if(op1==16 &&(op2==8 || op2==32))
				{
					errorp("Mismatch in register found",line);
					return;
				}
				if(op1==32 && (op2==8 || op2==16))
				{
					errorp("Mismatch in register found",line);
					return;
				}
				if(op1==8 && op2==8)
					return;
				if(op1==16 && op2==16)
					return;
				if(op1==32 && op2==32)
					return;
				if((op1==8 || op1==16) && op2==2 )
				{
					errorp("Invalid combination of operands",line);
					return;
				}
				if(op1==op2)
				{
					errorp("Invalid combination of operads",line);
				}
				if(op2==0)
				{
					long long int ans=isdigit1(aop2);
					if(op1==8 && ans>255)
					{

						errorp("Invalid size of operands",line);
						return;
					}
					if(op1==16 && ans>65535)
					{
						errorp("Invalid size of operands",line);
						return;
					}
					if(op1==32 && ans>4294967295)
					{
						errorp("Invalid size of operands",line);
						return;
					}
				}
				//check other compability of op1 and op2;
			}
		}
	}
	//text section reamining
}

void checkerror(FILE* fr)
{
	int c,i,j,line=0;
	char **buffer=(char**)malloc(sizeof(char*)*4);
	for(i=0;i<5;i++)
		buffer[i]=(char*)malloc(sizeof(char)*50);
	c=fgetc(fr);
	while(c!=EOF)
	{
		for(i=0;i<5;i++)
			bufzero1(buffer[i],50);
		j=0;
		line++;
		Label=0;
		while(c!='\n' && c!=EOF)
		{
			i=0;
			while(c=='\t')
				c=fgetc(fr);
			while(c!='\t' && c!=' ' && c!='\n' && c!=EOF)
			{
				if(c==',' && Flag==1)
				{
					c=fgetc(fr);
					break;
				}
				if(c==';')
				{
					while(c!='\n' && c!=EOF)
					{
						c=fgetc(fr);
					}
					break;
				}
				buffer[j][i]=c;
				i++;
				c=fgetc(fr);
				if(i==50)
				{
					errorp("BUFFER OVERFLOW",line);
					break;
				}
			}
			buffer[j][i]='\0';
			j++;
label1:			if(c=='\t' || c==' ')
				c=fgetc(fr);
			while(c==';')
			{
				c=fgetc(fr);
			}
			if(c==' ' || c=='\t')
				goto label1;
			if(j==5 && c!='\n' && c!=EOF)
			{
				errorp("BUFFER OVERFLOW ",line);
				break;
			}

		}
		if(strlen(buffer[0])==0)
		{
			c=fgetc(fr);
			continue;
		}
		check(buffer,j,line);
		printf("\n%s\t%s\t%s\t%s",buffer[0],buffer[1],buffer[2],buffer[3]);
		if(c=='\n')
			c=fgetc(fr);
	}
	//Do undefine check
	checkundefine();
}

void main()
{
	FILE *fr;
	fr=fopen("error_ref.asm","r");
	checkerror(fr);
	printf("\nError Printing\n");
	printerror();
	fclose(fr);
}

/*	
 1 .section in order of 1.data 2.bss 3.text
 2.section word followed by one of the following=
 -symbol name can't be started with integer
 3.data section= 
 -data section must have 1 op as dd/dw/db and the op followed by it must be in the         range of it
 -can have 2 op as character array,int array,string,character,int mix is not allowed
 -string will end with 0 it may have 10 before it other than that nothing is allowed
 4.bss section 
 -must have 1 op as resb/resd/resw and the op followed by it must be a int
 -symbols should not be redefined 
 5.text section
 -ins should have there possible combination nothing other than that
 -no undefined symbols use
 -oprand1 can never be imm
 */
