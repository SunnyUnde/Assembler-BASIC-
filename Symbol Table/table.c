#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int specialflag=-1; //special flag for si,bp,esp,ebp
struct elesymbol
{
	char* name;
	char add[9];
	int size;
	char sec[5];
	char type[7];
	char value[50];
	int def;
	struct elesymbol* next;
};

struct eleliteral
{
	char value[50];
	char add[9];
	char sec[5];
	struct eleliteral *next;
};

void printsymbollist(struct elesymbol* head)
{
	if(head==NULL)
		return;
	printf("\nNAME=%s\tADD=%s\tsec=%s\ttype=%s\tvalu=%s\tsize=%d\tdef=%d",head->name,head->add,head->sec,head->type,head->value,head->size,head->def);
	printsymbollist(head->next);
}

void printliteralist(struct eleliteral* head)
{
	if(head==NULL)
		return;
	printf("\nVALUE=%s\tADD=%s\tsection=%s",head->value,head->add,head->sec);
	printliteralist(head->next);
}

void error(char *a)
{
	printf("%s",a);
	exit(0);
}
void lower(char *b)
{
	for(int i=0;b[i]!='\0';i++)
		if(b[i]>=65 && b[i]<=90)
			b[i]=b[i]+32;
}

void bufferzero1(char *a,int n)
{
	for(int i=0;i<n;i++)
		a[i]='\0';
}

void stringbreak(char *buffer,char **tok,int s,int* label)
{
	int i=0,count=0,j=0,flag=0;
	while(buffer[i]!='\0')
	{
                 flag=0;
		while(buffer[i]!=' '&& buffer[i]!='\t' && buffer[i]!='\0' && ( s<1 ||  buffer[i]!=',')||flag==1)
		{
                   if(buffer[i]=='"')
                    {
                      if(flag==0)
				flag=1;
                       else
                                 flag=0;
                     }
			if(buffer[i]==':')
			{
				*label=1;
				break;
			}
			tok[count][j]=buffer[i];
			j++;
			i++;
		}
		j=0;
		i++;
		count++;
		if(count==5)
			break;
		while((buffer[i]==' ' || buffer[i]=='\t')&& buffer[i]!='\0')
		{
			i++;
		}
	}
}

	//char valid[][6]={"mov","jmp","or","sub","and","xor","add","inc","not","cld","div","loop","pop","jmp","push","cmp","al","cl","dl","bl","ah","ch","dh","bh","ax","cx","dx","bx","sp","bp","si","di","eax","ecx","edx","ebx","esp","ebp","esi","edi",}
	
int datasection(char * buffer,int j)
{
	int i;
	if(j==0)
	{
		if(buffer[0]!='d')
		{
			error("INVALID ENTRY IN DATA SECTION");
		}
		i=1;
	}
	else
	{
		if(buffer[0]!='r' && buffer[1]!='e' && buffer[2]!='s')
			error("INVALID ENTRY IN BSS SECTION");
		i=3;
	}
	if(buffer[i]=='d')
		return 4;
	else
		if(buffer[i]=='w')
			return 2;
		else
			if(buffer[i]=='b')
				return 1;
			else
				error("INVALID ENTRY DURING DEFINIG");
}

int stringcounter(char *buffer)
{
	int count=0,i=1,flag=1;
	while(buffer[i]!='\0')
	{
		if(buffer[i]==92)
		{
			i++;
			if(buffer[i]=='"')
			{
				count++;
				i++;
				continue;
			}
		}
                if(buffer[i]=='"')
			flag--;                
		i++;
                if(flag==0)
                break;		
		count++;
	}
	if(flag!=0)
		error("INVALID STRING");
	i++;
	if(buffer[i]=='1' && buffer[i+1]=='0')
	{
		count++;
		i=i+2;
		if(buffer[i]==',')
		{
			i++;
		}
		else
			error("Invalid string\n");
	}
	if(buffer[i]=='0' && buffer[i+1]=='\0')
	{
		count++;
		return count;
	}
	else
		error("INVALID ENTRY IN STRING\n");
}

int charactercount(char* buffer)
{
	int i,count=0,n=strlen(buffer);
	for(i=1;i<n;i+=4)
		count++;
	return count;
}

int sizeD(char *buffer,int type)
{
	int count=1,i=0;
	if(buffer[0]=='"')
		return stringcounter(buffer)*type;
	if(buffer[0]==39)
		return charactercount(buffer)*type;
	else
	{
		while(buffer[i]!='\0')
		{
			if(buffer[i]==',')
				count++;
			i++;
		}
	}
	return count*type;
}

int power(int a,int b)
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

int isdigit1(char* a)
{
	int m,i=0,ans=0,n=strlen(a),sign=1;
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
		else
		{
			error("INVALID ENTRY IN NUMBER\n");
		}
		i++;
	}
	ans=ans*sign;
	return ans;
}

int sizebuf(char *buffer,int type)
{
	return isdigit1(buffer)*type;
}

int hexconver(char a)
{
	char hex[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i=0;i<16;i++)
	{
		if(a==hex[i])
			return i;
	}
	return -1;
}

void addzero(char *add,int n)
{
	for(int i=0;i<n;i++)
	{
		add[i]='0';
	}
}
void swap1(char *x, char *y) 
{
	char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap1(&buffer[i++], &buffer[j--]);

	return buffer;
}

char* itoa(int value, char* buffer, int base)
{
	// invalid input
	if (base < 2 || base > 32)
		return buffer;

	// consider absolute value of number
	int n = abs(value);

	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	// if number is 0
	if (i == 0)
		buffer[i++] = '0';

	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0'; // null terminate string

	// reverse the whole string and return it
	return reverse(buffer, 0, i - 1);
}

char addCall(int a,int* c)
{
	int q=a/16;
	int r=a-q*16;
	char cha[2];
	itoa(r,cha,16);
	*c=q;
	return cha[0];
}

void addCal(char *ad,int size)
{
	int i,j,a,b,carry=0;
	char buffer[9];
	itoa(size,buffer,16);
	for(i=strlen(ad)-1,j=strlen(buffer)-1;i>=0;i--,j--)
	{
		if(carry==0 && j<0)
			break;
		if(j<0)
		{
			b=0;
		}
		else
		{
			b=hexconver(buffer[j]);
		}
		a=hexconver(ad[i]);
		ad[i]=addCall((a+b+carry),&carry);
	}
}
int registercheck(char *buffer)
{
	char register8[8][3]={"al","cl","dl","bl","ah","ch","dh","bh"};
        char register16[8][3]={"ax","cx","dx","bx","sp","bp","si","di"};
        char register32[8][4]={"eax","ecx","edx","ebx","esp","ebp","esi","edi"};
	int i,j=-1;
	for(i=0;i<8;i++)
	{
		j=strcmp(buffer,register8[i]);
		if(j==0)
		{
			return 8+i;
		}
		j=strcmp(buffer,register16[i]);
		if(j==0)
			return 16+i;
		j=strcmp(buffer,register32[i]);
		if(j==0)
			return 32+i;
	}
	return -1;
}

int dwordCheck(char* buffer)
{
	int i;
	char *p=strstr(buffer,"dword[");
	char buff[10];
	char *q;
	if(p!=NULL)
	{
		i=strlen("dword[");
		while(i>0)
		{
			p++;
			i--;
		}
		if(strlen(p)>4)
		{
			q=strstr(p,"+");
			if(q)
				return 0;
			q=strstr(p,"-");
			if(q)
				return 0;
			q=strstr(p,"*");
			if(q)
				return 0;
			return 2;
		}
		else
		{
			p[3]='\0';
			i=registercheck(p);
			if(i!=-1)
			{
				if(i==20 || i==21 || i==36 || i==37)
					specialflag=1;
				return 1;
			}
			else
				return 2;
		}
	}
	if(buffer[0]=='[')
		return 2;
	return -1;
}

int check (struct elesymbol* head,char *buffer)
{
	if(head==NULL)
		return -1;
	while(head!=NULL)
	{
		if(strcmp(head->name,buffer)==0)
		{
			if(strcmp(head->sec,"text")==0)
					return 1;
			return 0;
		}
		head=head->next;
	}
	return -2;
}

int sizeCal(int operand1,int operand2,int flag,int immf)
{
	if(operand2<-1 && immf==-2)
	{
		if(flag==2)
		{
			return 2;
		}
		else
		{
			if(2<flag && flag<6)
			{
				if((7<operand1 && operand1<16) ||( 31<operand1 && operand1<40))
					return 2;
				else
					if(15<operand1 && operand1<24)
						return 3;
					else
						if(operand1==2)
							return 6;
						else
							if(operand1==1)
								if(specialflag==1)
									return 3;
								else
									return 2;
							else
								if(flag==3)
									if(operand2==-3 && operand1!=0)
										return 2;
									else
										if(operand1==0)
											return 3;
										else
											return 5;
								else
									if(operand1==-1)
										return 5;
									else
										return 3;
			}
			else
			{
				if((7<operand1 && operand1<16)||(31<operand1 && operand1<40))
					return 1;
				else
					if(15<operand1 && operand1<24)
						return 2;
					else
						if(operand1==2)
							return 6;
						else
							if(operand1==1)
								if(specialflag==1)
									return 3;
								else
									return 2;
							else
								if(operand1==-1)
									return 5;
								else
									return 3;
			}
		}
	}
	if((7<operand1&& operand1<16)||(15<operand1 && operand1<24)||(31<operand1&& operand1<40))
	{
		if(7<operand2 && operand2<40 && immf==-1)
		{
			if(15<operand2 && operand2<24)
				return 3;
			else
				return 2;
		}
		else
		{
			if(operand2==2 && immf==-1)
			{
				if(((operand1==8)||(operand1==16)||(operand1==32))&&flag==1)
					return 5;
				else
					return 6;
			}
			if(operand2==1 && immf==-1)
				if(specialflag==1)
					return 3;
				else
					return 2;
			if(operand2==0 && immf==-1)
				return 3;
			if(immf!=-1)
			{
				if(flag==1)
				{
					if(7<operand1 && operand1<16)
						return 2;
					if(15<operand1 && operand1<24)
						return 4;
					if(31<operand1 && operand1<40)
						return 5;
				}
				if(immf==0)
					if(15<operand1 && operand1<24)
						return 4;
					else
						return 3;
				else
					if(15<operand1 && operand1<24)
						return 7;
					else
						return 6;
			}
			if((operand1==8)||(operand1==16)||(operand1==32))
				return 5;
			if(flag==1 && operand2==-1)
				if(operand1== 8|| operand1==16|| operand1== 32)
					return 6;
				else
					return 5;
			return 6;
		}
	}
	else
	{
		if(operand1==2)
		{
			if(7<operand2 && operand2<40 && immf==-1)
			{
				if(flag==1)
				{
					if(operand2==8 || operand2==16 || operand2==32)
					{
						return 5;
					}
				}
				return 6;
			}
			else
			{
				if(flag==1 || immf==1)
					return 10;
				else
					return 7;
			}
		}
		else
		{
			if(operand1==1)
			{
				if((31<operand2 && operand2<40)&& immf==-1)
				{
					if(specialflag==1)
						return 3;
					else
						return 2;
				}
				if(immf==1 || flag==1)
					if(specialflag==1)
						return 7;
					else
						return 6;
				else
					if(specialflag==1)
						return 4;
					else
						return 3;
			}
			else
			{
				if(31<operand2 && operand2<40 && immf==-1)
				{
					return 3;
				}
				if(immf==1 || flag==1 || operand2==-1)
					return 7;
				else
					return 4;
			}
		}
	}
}

void setter(char *ins,char* operand1,char *cop2,int *op1f,int* op2f,int *flag,int *immf)
{
	specialflag=-1;
	char operand2[20];
	strcpy(operand2,cop2);
	char ins0[8][4]={"mov","add","sub","cmp","xor","adc","or","and"};
	char ins1[8][5]={"loop","jmp","not","div","inc","dec","pop","push"};
	//flag=1 mov  =i+1 for ins1
	//immf=-1 if no imm  =0 <128 =1>127
	//operand1 & operand2=regid+i for reg dword[m]=0 dword[r]=regid+i dword[SIB]=2
	int i,j=-1;
	for(i=0;i<8;i++)
	{
		j=strcmp(ins,ins0[i]);
		if(j==0)
		{
			*flag=-2;
			break;
		}
	}
	if(i==0)
		*flag=1;
	if(j!=0)
	{
		for(i=0;i<8;i++)
		{
			j=strcmp(ins,ins1[i]);
			if(j==0)
			{
				*flag=i+2;
				break;
			}
		}
	}
	if(*flag==-1)
		return;
	//check that ins1 can only have 1 op
	*op1f=registercheck(operand1);
	if(*op1f==-1)
	{
		*op1f=dwordCheck(operand1);
	}
	if(*flag>1)
		return;
	*op2f=registercheck(operand2);
	if(*op2f==-1)
	{
		*op2f=dwordCheck(operand2);
		if(*op2f==-1)
		{
			if(isdigit2(operand2)==1)
			{
				*op2f=isdigit1(operand2);
				if(*op2f<128)
					*immf=0;
				else
					*immf=1;
			}
			*operand2=-1;
		}
	}
}

struct elesymbol* newnodesymbol(char *name,char *add,int sec,int type,char *value,int size,int def)
{
	struct elesymbol* node=(struct elesymbol*)malloc(sizeof(struct elesymbol));
	node->name=name;
	strcpy(node->add,add);
	node->add[8]='\0';
	node->add[9]='\0';
	if(sec==0)
		strcpy(node->sec,"data");
	else
		if(sec==1)
			strcpy(node->sec,"bss");
		else
			strcpy(node->sec,"text");
	if(type==1)
		strcpy(node->type,"byte");
	else
		if(type==2)
			strcpy(node->type,"word");
		else
			if(type==4)
				strcpy(node->type,"double");
			else
				strcpy(node->type,"label");
	strcpy(node->value,value);
	node->size=size;
	node->def=def;
	node->next=NULL;
	return node;
}

struct eleliteral* newnodeliteral(char *value,char* add,int sec)
{
	struct eleliteral* node=(struct eleliteral*)malloc(sizeof(struct eleliteral));
	strcpy(node->value,value);
	strcpy(node->add,add);
	node->add[8]='\0';
	node->add[9]='\0';
	if(sec==0)
		strcpy(node->sec,"data");
	else
		strcpy(node->sec,"text");
	node->next=NULL;
	return node;
}

struct elesymbol* element(char *buffer,struct elesymbol* head,struct eleliteral** headL,char *ad,int j)
{
	static int count=-1;
	struct eleliteral* tempL=*headL;
	struct eleliteral* node=NULL;
	if(tempL!=NULL)
	{
		while(tempL->next!=NULL)
			tempL=tempL->next;
	}
	char *add=ad;
	if(count<j)
	{
		addzero(&add[0],8);
		count=j;
	}
	struct elesymbol* temp=head;
	if(temp!=NULL)
	{
		while(temp->next!=NULL)
			temp=temp->next;
	}
	struct elesymbol *temp2=NULL,*temp3=NULL;
	int i=0,type=-1,size=0,def=-1;
	int operand1=-1,operand2=-1,flag=-1,immf=-1;
	int labelf=-1,label=0;
	char **tok=(char **)malloc(sizeof(char*)*4);
	for(int i=0;i<4;i++)
	{
		tok[i]=(char *)malloc(sizeof(char)*100);
		bufferzero1(tok[i],20);
	}
																																																																												stringbreak(buffer,tok,j,&label);
	//printf("\ntok0=%s\ttok1=%s\ttok2=%s\ttok3=%s\tj=%d",tok[0],tok[1],tok[2],tok[3],j);
	//j==0 section .data
	//j==1 sectiom .bss
	//j==2 section .text
	if(j==0 || j==1)
	{
		def=1;
		type=datasection(tok[1],j);
		if(j==0)
		{
			size=sizeD(tok[2],type);
			node=newnodeliteral(tok[2],add,j);
		}
		if(j==1)
		{
			size=sizebuf(tok[2],type);
		}
		temp2=newnodesymbol(tok[0],add,j,type,tok[2],size,def);
	}
	i=-3;
	if(j==2)
	{
		if(label==1)
		{
			def=1;
			i=check(head,tok[0]);
//label present in tok[0]==name and it may be present in instruction	//type==-1 for label //section j==3 == text //value ==NULL
////size== 0 for node for ins it should be there	//Defined if found in tok[0] first Undefined if found in ins
			if(i==-2)
				temp2=newnodesymbol(tok[0],add,j,type,"NULL",size,def);
			labelf=1;
			i=-3;
		}
//check for label in instruction
		if(labelf==1)
		{
		single:	setter(tok[1],tok[2],tok[3],&operand1,&operand2,&flag,&immf);
		}
		else
		{
			setter(tok[0],tok[1],tok[2],&operand1,&operand2,&flag,&immf);
			if(flag==-1)
			{
				goto single;
			}
		}
		if(flag>1)
		{
			if(flag==2 || flag==3)
			{
				if(labelf==1)
					i=check(head,tok[2]);
				else
					i=check(head,tok[1]);
				if(i==-2 && operand1==-1)
				{
					def=-1;
					if(labelf==1)
						temp3=newnodesymbol(tok[2],add,j,type,"NULL",size,def);
					else
						temp3=newnodesymbol(tok[1],add,j,type,"NULL",size,def);
				}
			}
			operand2=-2;
			if(i==-2 || i==1)
				operand2=-3;
			immf=-2;
		}
		if(immf==0 || immf==1)
		{
			if(label==1)
			{
				node=newnodeliteral(tok[3],add,j);
			}
			else
			{
				node=newnodeliteral(tok[2],add,j);
			}
		}
		size=sizeCal(operand1,operand2,flag,immf);
	}
	addCal(&add[0],size);
	if(temp==NULL)
	{
		head=temp2;
	}
	if(temp!=NULL)
	{
		if(temp2!=NULL)
			temp2->next=temp3;
		temp->next=temp2;
	}
	if(tempL==NULL)
	{
		*headL=node;
	}
	else
		tempL->next=node;
	return head;
}

struct elesymbol* table(FILE *fr,struct elesymbol* head,struct eleliteral** headL)
{
	struct eleliteral* temp=*headL;
	int c,count=0;
	char *add=(char *)malloc(sizeof(char)*9);
	add[8]='\0';
	char *p=NULL;
	char buffer[100];
	int i=0,j=0,flag=0;
	c=fgetc(fr);
	while(c!=EOF)
	{
		bufferzero1(&buffer[0],40);
		while(c!='\n' && c!=EOF)
		{
			if(c=='\t')
			{
				c=fgetc(fr);
				continue;
			}
			if(c==';')
				flag=1;
			else
			{
			//	printf("%c",c);
				if(flag==0)
				{
					buffer[i]=c;
					i++;
				}
			}
			c=fgetc(fr);
		}
		buffer[i]='\0';
		if(strlen(buffer)==0)
		{
			goto label1;
		}
		lower(&buffer[0]);
		p=strstr(buffer,"section .data");
		if(p!=NULL && count==0)
		{
			count=1;
			j=0;
			goto label1;
		}
		p=strstr(buffer,"section .bss");
		if(p!=NULL && count<2)
		{
			count=2;
			j=1;
			goto label1;
		}
		p=strstr(buffer,"section .text");
		if(p!=NULL && count<3)
		{	
		//	lower(&buffer[0]);
			count=3;
			j=2;
			goto label1;
		}
		p=strstr(buffer,"global main");
		if(p!=NULL && count==3)
		{
			goto label1;
		}
		head=element(buffer,head,&temp,&add[0],j);
	label1:
	//	bufferzero1(&buffer[0],40);
		flag=0;
		c=fgetc(fr);
		i=0;
	}
	*headL=temp;
	return head;
}

void writefile(FILE *fw,struct elesymbol *head,struct eleliteral* headL)
{
	if(head!=NULL)
	{
		fprintf(fw,"\nSYMBOL TABEL:\n\nName\tADDRESS\t\tSECTION\tTYPE\tSIZE\tDEFINED\tVALUE");
		while(head!=NULL)
		{
			fprintf(fw,"\n%s\t%s\t%s\t%s\t%d\t%d\t%s",head->name,head->add,head->sec,head->type,head->size,head->def,head->value)
;
			head=head->next;
		}
	}
	if(headL!=NULL)
	{
		fprintf(fw,"\n\nLITREAL TABEL:\n\nADDRESS\t\tSEC\tVALUE");
		while(headL!=NULL)
		{
			fprintf(fw,"\n%s\t%s\t%s",headL->add,headL->sec,headL->value);
			headL=headL->next;
		}
	}
}

void main()
{
	FILE *fr,*fw;
	struct elesymbol* head=NULL;
	struct eleliteral* headL=NULL;
	fr=fopen("table_ref.asm","r");
	fw=fopen("table_test.txt","w");
	if(fr==NULL || fw==NULL)
	{
		error("\nFile opening failed\n");
	}
	head=table(fr,head,&headL);
	writefile(fw,head,headL);
	fclose(fr);
	fclose(fw);
}
