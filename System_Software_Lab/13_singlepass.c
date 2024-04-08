/*
                                                                           Program.No:13
                                                                      SINGLE PASS ASSEMBLER
                                                                      =====================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int fcloseall(void);
int findInSYMTAB(char findLabel[])
{
   FILE *SYMTAB;
   char label[30],addr[30];
   SYMTAB=fopen("symtab.dat","r");
   fscanf(SYMTAB,"%s%s",label,addr);
   while(1)
   {
      if(feof(SYMTAB))
      {
         fclose(SYMTAB);
         break;
      }
      if(strcmp(findLabel,label)==0)
      {
         fclose(SYMTAB);
         return atoi(addr);
      }
      fscanf(SYMTAB,"%s%s",label,addr);
   }
}
int getMnemonicCode(char mnemonic[])
{
   if(strcmp(mnemonic,"LDA")==0)
      return 33;
   else if(strcmp(mnemonic,"STA")==0)
      return 44;
   else if(strcmp(mnemonic,"LDCH")==0)
      return 53;
   else if(strcmp(mnemonic,"STCH")==0)
      return 57;
   else
      return -1;
}
void main()
{
   FILE *INPUT,*OUTPUT,*SYMTAB,*INTERMEDIATE,*FINAL,*OBJ;
   char mnemonic[10][10]={"START","LDA","STA","LDCH","STCH","END"};
   int LOCCTR,start=0,j=0,i,length,Tlength,count=0,finalAddress,startAddr;
   char label[20],opcode[20],operand[20],address[20];INPUT=fopen("input.dat","r");
   OUTPUT=fopen("output.dat","w+");
   SYMTAB=fopen("symtab.dat","w+");
   fscanf(INPUT,"%s%s%s",label,opcode,operand);
   if(strcmp(opcode,"START")==0)
   {
      start=atoi(operand);
      LOCCTR=start;
      fprintf(OUTPUT,"\t%s\t\%s\t%s\n",label,opcode,operand);      
      fscanf(INPUT,"%s%s%s",label,opcode,operand);
   }
   else
      LOCCTR=0;
   while(strcmp(opcode,"END")!=0)
   {
      j=0;
      fprintf(OUTPUT,"%d",LOCCTR);
      if(strcmp(label,"**")!=0)
         fprintf(SYMTAB,"\t%s\t%d\n",label,LOCCTR);
      while(strcmp(mnemonic[j],"END")!=0)
      {
          if(strcmp(mnemonic[j],opcode)==0)
          {
             LOCCTR+=3;
          }
          j++;
      }
      if(strcmp(opcode,"WORD")==0)
         LOCCTR+=3;
      else if(strcmp(opcode,"RESW")==0)
      {
         LOCCTR=LOCCTR+(3* atoi(operand));
         count+=(3* atoi(operand));
      }
      else if (strcmp(opcode,"RESB")==0)
      {
         LOCCTR=LOCCTR+atoi(operand);
         count+=atoi(operand);
      }
      else if(strcmp(opcode,"BYTE")==0)
      {
          LOCCTR=LOCCTR+(strlen(operand)-3);
      }
      else
      {
         printf(" ");
      }
      fprintf(OUTPUT,"\t%s\t%s\t%s\n",label,opcode,operand);fscanf(INPUT,"%s%s%s",label,opcode,operand);
   }
   fprintf(OUTPUT,"%d",LOCCTR);
   fprintf(OUTPUT,"\t%s\t%s\t%s\n",label,opcode,operand);
   printf("\n\n THE LENGTH OF THE PROGRAM IS %d",LOCCTR-start);
   length=LOCCTR-start;
   finalAddress=LOCCTR;
   Tlength=length-count;
   fcloseall();
   
   INTERMEDIATE=fopen("output.dat","r");
   OBJ=fopen("obj.dat","w");
   FINAL=fopen("final.dat","w");
   fscanf(INTERMEDIATE,"%s%s%s",label,opcode,operand);
   startAddr=atoi(operand);
   if( strcmp(opcode,"START")==0)
   {
      fprintf(FINAL,"%s\t%s\t%s\t\n",label,opcode,operand);
      fprintf(OBJ,"H^%s^00%s^00%d\n",label,operand,length);
      fscanf(INTERMEDIATE,"%s%s%s%s",address,label,opcode,operand);
      fprintf(OBJ,"T^%06d^%d^",atoi(address),Tlength);
   }
   while(strcmp(opcode,"END")!=0)
   {
      if(strcmp(label,"**")==0 )
      {
         fprintf(OBJ,"%d%d^",getMnemonicCode(opcode),findInSYMTAB(operand));
         fprintf(FINAL,"%s\t%s\t%s\t%s\t%d%d\n",address,label,opcode,operand,getMnemonicCode(opcode),findInSYMTAB(operand));
         fscanf(INTERMEDIATE,"%s%s%s%s",address,label,opcode,operand);
      }
      else if(strcmp(opcode,"BYTE")==0)
      {
         fprintf(FINAL,"%s\t%s\t%s\t%s",address,label,opcode,operand);
         for(i=2;i<(strlen(operand)-1);i++)
         {
            fprintf(OBJ,"%x",operand[i]);
            fprintf(FINAL,"%x",operand[i]);      
         }
         fprintf(FINAL,"\n");
         fscanf(INTERMEDIATE,"%s%s%s%s",address,label,opcode,operand);
      }
      else if(strcmp(opcode,"WORD")==0)
      {
          fprintf(OBJ,"%06x^",atoi(operand));
          fprintf(FINAL,"%s\t%s\t%s\t%s\t%06x\n",address,label,opcode,operand,atoi(operand));
          fscanf(INTERMEDIATE,"%s%s%s%s",address,label,opcode,operand);
      }
      else
      {
         fscanf(INTERMEDIATE,"%s%s%s%s",address,label,opcode,operand);
      }
   }
   fprintf(FINAL,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
   fprintf(OBJ,"\nE^%06d\n",startAddr);
   fcloseall();
}
/*
OUTPUT
======
THE LENGTH OF THE PROGRAM IS 20

CONTENTS OF INPUT FILE(input.dat)
*********************************
COPY START 2000
** LDA FIVE
** STA ALPHA
** LDCH CHARZ
** STCH C1
ALPHA RESW 1
 FIVE WORD 5
 CHARZ BYTE C'E'
C1 RESB 1
** END **

CONTENTS OF SYMBOL TABLE(symtab.dat)
************************************
	ALPHA	2012
	FIVE	2015
	CHARZ	2018
	C1	2019

CONTENTS OF OUTPUT FILE(output.dat)
***********************************
	COPY	START	2000
2000	**	LDA	FIVE
2003	**	STA	ALPHA
2006	**	LDCH	CHARZ
2009	**	STCH	C1
2012	ALPHA	RESW	1
2015	FIVE	WORD	5
2018	CHARZ	BYTE	C'E'
2019	C1	RESB	1
2020	**	END	**

CONTENTS OF FINAL FILE(final.dat)
*********************************
COPY	START	2000	
2000	**	LDA	FIVE	332015
2003	**	STA	ALPHA	442012
2006	**	LDCH	CHARZ	532018
2009	**	STCH	C1	572019
2015	FIVE	WORD	5	000005
2018	CHARZ	BYTE	C'E'45
2020	**	END	**

CONTENTS OF OBJECT FILE(obj.dat)
********************************
H^COPY^002000^000020
T^002000^16^332015^442012^532018^572019^000005^45
E^002000
*/
