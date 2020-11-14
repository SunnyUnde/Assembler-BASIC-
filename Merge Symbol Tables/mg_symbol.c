#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct symbol
{
	char name[20];
	char newname[25];
	char add[9];
	char sec[5];
	char type[7];
	char value[30];
	char size[4];
	char def;
	struct symbol* next;
};

void printlist(struct symbol* head)
{
	if(head==NULL)
		return;
	printf("\nName=%s\tNewName=%s\tAdd=%s\tsec=%s\ttype=%s\tvalue=%s\tsize=%s\tdef=%c\n",head->name,head->newname,head->add,head->sec,head->type,head->value,head->size,head->def);
	printlist(head->next);
}

void error(char* a)
{
	printf("\n%s\n",a);
	exit(0);
}

void checkfile(FILE *fp)
{
	if(fp==NULL)
	{
		error("FILE ERROR");
	}
}

int power(int a,int b)
{
	if(b==0)
		return 1;
	return a*power(a,(b-1));
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
			error("Invalid ENTRY\n");
		}
		i++;
	}
	ans=ans*sign;
	return ans;
}

void swap1(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

char* reverse(char *buf, int i, int j)
{
	while (i < j)
		swap1(&buf[i++], &buf[j--]);

	return buf;
}

char* itoa(int value, char* buf, int base)
{
	// invalid input
	if (base < 2 || base > 32)
		return buf;

	// consider absolute value of number
	int n = abs(value);

	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) 
			buf[i++] = 65 + (r - 10);
		else
			buf[i++] = 48 + r;

		n = n / base;
	}

	// if number is 0
	if (i == 0)
		buf[i++] = '0';

	if (value < 0 && base == 10)
		buf[i++] = '-';

	buf[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(buf, 0, i - 1);
}

struct symbol* createnode(char ** buf)
{
	struct symbol* node=(struct symbol*)malloc(sizeof(struct symbol));
	strcpy(node->name,buf[0]);
	strcpy(node->add,buf[1]);
	strcpy(node->sec,buf[2]);
	strcpy(node->type,buf[3]);
	strcpy(node->value,buf[4]);
	strcpy(node->size,buf[5]);
	node->def=buf[6][0];
	strcpy(node->newname,"");
	node->next=NULL;
	return node;
}

struct symbol* list(FILE *fp)
{
	struct symbol* head=NULL;
	struct symbol* temp=NULL;
	char** buf=(char **)malloc(sizeof(char*)*8);
	int i=0,j=0,c;
	for(i=0;i<8;i++)
	{
		buf[i]=(char*)malloc(sizeof(char)*20);
	}
	c=fgetc(fp);
	i=0;
	while(c!=EOF)
	{
		while(c!='\n' && c!=EOF)
		{
			j=0;
			while(c!='\t' && c!=EOF && c!='\n')
			{
				buf[i][j]=c;
				j++;
				c=fgetc(fp);
			}
			buf[i][j]='\0';
			i++;
			if(c=='\n' || c==EOF)
				break;
			c=fgetc(fp);
		}
		buf[7]="";
		struct symbol* node=createnode(buf);
		if(head==NULL)
		{
			head=temp=node;
		}
		else
		{
			temp->next=node;
			temp=temp->next;
		}
		if(c==EOF)
			break;
		c=fgetc(fp);
		i=0;
	}
	return head;
}

void changeadd(struct symbol* head,struct symbol *tmp)
{
	int add=isdigit1(tmp->add)+isdigit1(tmp->size);
	itoa(add,head->add,10);
}

void checkname(struct symbol* head,struct symbol* tmp)
{
	while(strcmp(head->sec,tmp->sec)==0 && head!=tmp)
	{
		if(strcmp(head->name,tmp->name)==0)
		{
			strcpy(head->newname,head->name);
			strcat(head->newname,"_new");
			break;
		}
		tmp=tmp->next;
		if(tmp==NULL)
			break;
	}
}

struct symbol* dupli(struct symbol* head,int add)
{
	struct symbol* node=(struct symbol*)malloc(sizeof(struct symbol));
	itoa((isdigit1(head->add)+add),node->add,10);
	return node;
}
struct symbol* mergesymbol(struct symbol* head1,struct symbol* head2)
{
	struct symbol* head=NULL;
	struct symbol* tmp=NULL;
	struct symbol* tmp2=NULL;
	int flag=0,count=0;  //0=no change 1=change
	char buf[5]="data";
	if(head1==NULL)
		return head2;
	if(head2==NULL)
		return head1;
	while(head1!=NULL && head2!=NULL)
	{
		flag=0;
		if(strcmp(head1->sec,buf)==0)
		{
			if(head==NULL)
				head=tmp=head1;
			else
				tmp->next=head1;
			tmp2=head1;
			while(strcmp(head1->sec,buf)==0)
			{
				tmp=head1;
				head1=head1->next;
				if(head1==NULL)
					break;
			}
			flag=1;
		}
		if(strcmp(head2->sec,buf)==0)
		{
			if(flag==0)
			{
				if(head==NULL)
					head=tmp=head2;
				else
					tmp->next=head2;
				while(strcmp(head2->sec,buf)==0)
				{
					tmp=head2;
					head2=head2->next;
					if(head2==NULL)
						break;
				}
			}
			else
			{
				tmp->next=head2;
				if(strcmp(tmp->sec,"text")==0)
				{
					int n=40;
					printf("\nEnter the add at which the first symbol table asm ends\t");
					scanf("%d",&n);
					tmp=dupli(tmp,n);
				}
				while(strcmp(head2->sec,buf)==0)
				{
					changeadd(head2,tmp);
					checkname(head2,tmp2);
					tmp=head2;
					head2=head2->next;
					if(head2==NULL)
						break;
				}
			}
		}
		tmp2=NULL;
		count++;
		if(count==1)
			strcpy(buf,"bss");
		else
			strcpy(buf,"text");
	}
	if(head1!=NULL)
		tmp->next=head1;
	if(head2!=NULL)
		tmp->next=head2;
	return head;
}

void writefile(FILE *fw,struct symbol *head)
{
	fprintf(fw,"Name\tNewName\tADDRESS\tSECTION\tTYPE\tSIZE\tDEF\tVALUE\n");
	while(head!=NULL)
	{
		fprintf(fw,"\n%s\t%s\t%s\t%s\t%s\t%s\t%c\t%s\n",head->name,head->newname,head->add,head->sec,head->type,head->size,head->def,head->value);	
		head=head->next;
	}
}

void main()
{
	FILE *fr,*fr1,*fw;
	fr=fopen("mg_symbol.txt","r");
	fr1=fopen("mg_symbol1.txt","r");
	fw=fopen("mg_mergesymbol.txt","w");
	checkfile(fr);
	checkfile(fr1);
	checkfile(fw);
	struct symbol* head1=list(fr);
	struct symbol* head2=list(fr1);
	printf("\nfirst\n");
	printlist(head1);
	printf("\nsecond\n");
	printlist(head2);
	struct symbol*head=mergesymbol(head1,head2);
	printf("\nThird\n");
	printlist(head);
	writefile(fw,head);
	fclose(fr);
	fclose(fr1);
	fclose(fw);
}
