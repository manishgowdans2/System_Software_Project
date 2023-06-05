#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct estab
{
  char csname[10];
  char extsym[10];
  int address;
  int length;
}es[20];

struct exttable
{
  char csect[20], sname[20];
  int padd,plen;
}estab[20];
struct objectcode
{
 unsigned char code[15];
 int add;
}obcode[500];

void main()
{
    printf("Select : \n 1 -- For Pass 1 Linker Implementation \n 2 -- For Pass 2 Linker Implementation \n");
    int n;
    scanf("%d",&n);
    if(n==1)
    {
        char input[10],name[10],symbol[10],ch;  int count=0,progaddr,csaddr,add,len;
	FILE *fp1,*fp2;
	fp1=fopen("Object_Code_1.dat","r");
	fp2=fopen("ESTAB.dat","w");
	printf("\n\nEnter the address where the program has to be loaded : ");
	scanf("%x",&progaddr); // TAKING THE PROGRAM ADDRESS FROM THE USER,GENERALLY IT IS DONE BY THE OS
	csaddr=progaddr;
	fscanf(fp1,"%s",input);
	while(strcmp(input,"END")!=0)
	{
		if(strcmp(input,"H")==0)
		{
			fscanf(fp1,"%s",name);
			strcpy(es[count].csname,name);
			strcpy(es[count].extsym,"  ");
			fscanf(fp1,"%x",&add);
			es[count].address=add+csaddr;
			fscanf(fp1,"%x",&len);
			es[count].length=len;
			fprintf(fp2,"%s ** %x %x\n",es[count].csname,es[count].address,es[count].length);
			count++;
		}
		else if(strcmp(input,"D")==0)
		{
			fscanf(fp1,"%s",input);
			while(strcmp(input,"R")!=0)
			{
				strcpy(es[count].csname,"  ");
				strcpy(es[count].extsym,input);
				fscanf(fp1,"%x",&add);
				es[count].address=add+csaddr;
				es[count].length=0;
				fprintf(fp2,"** %s %x\n",es[count].extsym,es[count].address);
				count++;
				fscanf(fp1,"%s",input);
			}
			csaddr=csaddr+len;
		}
		else if(strcmp(input,"T")==0)
		{
			while(strcmp(input,"E")!=0)
			fscanf(fp1,"%s",input);
		}
		fscanf(fp1,"%s",input);
	}
  fclose(fp1);
  fclose(fp2);
  fp2=fopen("ESTAB.dat","r");
  ch=fgetc(fp2);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp2);
  }
  fclose(fp2);
    }

    else if(n==2)
    {
        FILE *fp1,*fp2,*fp3;
 int i,j,x,y,pstart,exeloc,start,textloc,loc,textlen,length,location,st,s;
 int n=0,num=0,inc=0,count=0,record=0,mloc[30],mlen[30];
 signed long int newadd;
 char operation,lbl[10],input[10],label[50][10],opr[30],ch,*add1,address[10];
 fp1=fopen("Object_Code_1.dat","r");
 fp2=fopen("ESTAB.dat","r");
 fp3=fopen("Executable_Code.dat","w");
 while(!feof(fp2))
 {
  fscanf(fp2,"%s %s %x %x", estab[num].csect, estab[num].sname, &estab[num].padd, 
                                            &estab[num].plen);
  num++;
 }
 exeloc=estab[0].padd;
 loc=exeloc;
 start=loc;
 st=start;
 while(!feof(fp1))
 {
  fscanf(fp1,"%s",input);
  if(strcmp(input,"H")==0)
  {
   fscanf(fp1,"%s",input);
   for(i=0;i<num;i++)
    if(strcmp(input,estab[i].csect)==0)
    {
     pstart=estab[i].padd;
     break;
    }
   while(strcmp(input,"T")!=0)
    fscanf(fp1,"%s",input);
  }
  do
  {
  if(strcmp(input,"T")==0)
  {
   fscanf(fp1,"%x",&textloc);
   textloc=textloc+pstart;
   for(i=0;i<(textloc-loc);i++)
   {
    strcpy(obcode[inc].code,"..");
    obcode[inc++].add=start++;
   }
   fscanf(fp1,"%x",&textlen);
   loc=textloc+textlen;
  }
  else if(strcmp(input,"M")==0)
  {
   fscanf(fp1,"%x",&mloc[record]);
   mloc[record]=mloc[record]+pstart;
   fscanf(fp1,"%x",&mlen[record]);
   fscanf(fp1,"%s",label[record++]);
  }
  else
  {
   length=strlen(input);
   x=0;
   for(i=0;i<length;i++)
   {
    obcode[inc].code[x++]=input[i];
    if(x>1)
    {
     obcode[inc++].add=start++;
     x=0;
    }
   }
   }
  fscanf(fp1,"%s",input);
 }while(strcmp(input,"E")!=0);
 if(strcmp(input,"E")==0)
   fscanf(fp1,"%s",input);
 }
 for(n=0;n<record;n++)
 {
  operation=label[n][0];
  length=strlen(label[n]);
  for(i=1;i<length;i++)
  {
   lbl[i-1]=label[n][i];
  }
  lbl[length-1]='\0';
  length=0;
  strcpy(address,"\0");
  location=mloc[n]-exeloc;
  loc=location;
  count=0;
  while(length<mlen[n])
  {
   strcat(address,obcode[location++].code);
   count++;
   length+=2;
  }
  for(i=0;i<num;i++)
  {
  if(strcmp(lbl,estab[i].csect)==0)
   break;
  if(strcmp(lbl,estab[i].sname)==0)
   break;
  }
  switch(operation)
  {
   case '+':
    newadd=strtol(address,&add1,16)+(long int)estab[i].padd;
    break;
   case '-':
    newadd=strtol(address,&add1,16)-(long int)estab[i].padd;
    break;
  }
  ltoa(newadd,address,16);
  x=0; y=0;
  while(count>0)
  {
   obcode[loc].code[x++]=address[y++];
   if(x>1)
   {
    x=0; loc++;
    count--;
   }
  }}
 count=0;
 n=0;
 s=st-16;
 fprintf(fp3,"%x\t",s);
 for(i=1;i<=16;i++)
 {
  fprintf(fp3,"xx");
  if(i==4||i==8||i==12)
  {
   fprintf(fp3,"\t");
  }
 }
 fprintf(fp3,"\n\n%x\t",obcode[0].add);
 for(i=0;i<inc;i++)
 {
  fprintf(fp3,"%s",obcode[i].code);
  n++;
  if(n>3)
  {
   fprintf(fp3,"\t");
   n=0;
   count++;
  }
  if(count>3)
  {
   fprintf(fp3,"\n\n%x\t",obcode[i+1].add);
   count=0;
  }}
fclose(fp1);
fclose(fp2);
fclose(fp3);
 printf("\n\t***** PASS TWO OF A DIRECT-LINKING LOADER *****\n");
 printf("\nThe contents of the output file, executable code:");
 printf("\n---------------------------------------------------------------");
 printf("\nAddress\t\t\t\tContents");
 printf("\n---------------------------------------------------------------\n");
 fp3=fopen("Executable_Code.dat","r");
 ch=fgetc(fp3);
 while(ch!=EOF)
 {
  printf("%c",ch);
  ch=fgetc(fp3);
 }
 fclose(fp3);
 getch();
    }
    else{
        printf("Invalid expression");
    }
}
