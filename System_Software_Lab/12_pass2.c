/*
                                                                           Program.No:12
                                                                  PASS TWO OF TWO PASS ASSEMBLER
                                                                  ==============================
*/
#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
   char a[10],label[10],opcode[10],operand[10],symbol[10],ch;
   int c=0;
   int sa,st,diff,diffl=0,i,address,add,len,actual_len,finaddr,prevaddr,j=0;
   char mnemonic[15][15]={"LDA","STA","LDCH","STCH"};
   char code[15][15]={"33","44","53","57"};
   FILE *fp1,*fp2,*fp3,*fp4;
   fp1=fopen("assmlist.dat","w");
   fp2=fopen("symtab.dat","r");
   fp3=fopen("inter.dat","r");
   fp4=fopen("objcode.dat","w");
   fscanf(fp3,"%s%s%s",label,opcode,operand);
   while(strcmp(opcode,"END")!=0)
   {
      if(strcmp(opcode,"START")==0)
         sa=atoi(operand);
      if(strcmp(opcode,"RESW")==0)
      {
         c=3*atoi(operand);
         diffl+=c;
      }
      if(strcmp(opcode,"RESB")==0)
      {
         c=atoi(operand);
         diffl+=c;
      }
      prevaddr=address;
      fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
   }
   finaddr=address-sa;
   diff=finaddr-diffl;
   fclose(fp3);
   fp3=fopen("inter.dat","r");
   fscanf(fp3,"%s%s%s",label,opcode,operand);
   if(strcmp(opcode,"START")==0)
   {
      fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);fprintf(fp4,"H^%s^00%s^0000%d\n",label,operand,finaddr);
      fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
      st=address;
      fprintf(fp4,"T^00%d^%d",address,diff);
   }
   while(strcmp(opcode,"END")!=0)
   {
      if(strcmp(opcode,"BYTE")==0)
      {
         fprintf(fp1,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
         len=strlen(operand);
         actual_len=len-3;
         fprintf(fp4,"^");
         for(i=2;i<(actual_len+2);i++)
         {
            fprintf(fp1,"%x",operand[i]);
            fprintf(fp4,"%x",operand[i]);
         }
         fprintf(fp1,"\n");
      }
      else if(strcmp(opcode,"WORD")==0)
      {
         len=strlen(operand);
         fprintf(fp1,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,operand);
         fprintf(fp4,"^00000%s",operand);
      }
      else if(strcmp(opcode,"RESB")==0||(strcmp(opcode,"RESW")==0))
      {
         fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
      }
      else
      {
          while(strcmp(opcode,mnemonic[j])!=0)
          {
             j++;
          }
          if(strcmp(operand,"COPY")==0)
          {
              fprintf(fp1,"%d\t%s\t%s\t%s\t%s0000\n",address,label,opcode,operand,code[j]);
          }
          else
          {
              rewind(fp2);
              fscanf(fp2,"%s%d",symbol,&add);
              while(strcmp(operand,symbol)!=0)
              {
                  fscanf(fp2,"%s%d",symbol,&add);
              }
              printf("\nj=%d",j);
              fprintf(fp1,"%d\t%s\t%s\t%s\t%s\t%d\n",address,label,opcode,operand,code[j],add);
              fprintf(fp4,"^%s%d",code[j],add);
          }
      }
      fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
   }
   fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
   fprintf(fp4,"\nE^00%d",st);
   printf("\nIntermediate file is converted into object code");
   fcloseall();
   printf("\n\nThe contents of intermediate file:\n\n\t");
   fp3=fopen("inter.dat","r");
   ch=fgetc(fp3);
   while(ch!=EOF)
   {
      printf("%c",ch);
      ch=fgetc(fp3);
   }
   printf("\n\nThe contents of symbol table:\n\n");
   fp2=fopen("symtab.dat","r");
   ch=fgetc(fp2);
   while(ch!=EOF)
   {
      printf("%c",ch);
      ch=fgetc(fp2);
   }
   printf("\n\nThe contents of output file:\n\n");
   fp1=fopen("assmlist.dat","r");
   ch=fgetc(fp1);
   while(ch!=EOF)
   {
      printf("%c",ch);
      ch=fgetc(fp1);
   }
   printf("\n\nThe contents of object code file:\n\n");
   fp4=fopen("objcode.dat","r");
   ch=fgetc(fp4);
   while(ch!=EOF)
   {
      printf("%c",ch);
      ch=fgetc(fp4);
   }
   printf("\n");
   fcloseall();
}
/*
 OUTPUT
 ======
j=0
j=1
j=2
j=3
Intermediate file is converted into object code

The contents of intermediate file:

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


The contents of symbol table:

ALPHA	2012
FIVE	2015
CHARZ	2018
C1	2019


The contents of output file:

	COPY	START	2000
2000	**	LDA	FIVE	33	2015
2003	**	STA	ALPHA	44	2012
2006	**	LDCH	CHARZ	53	2018
2009	**	STCH	C1	57	2019
2012	ALPHA	RESW	1
2015	FIVE	WORD	5	000005
2018	CHARZ	BYTE	C'E'	45
2019	C1	RESB	1
2020	**	END	**


The contents of object code file:

H^COPY^002000^000020
T^002000^16^332015^442012^532018^572019^000005^45
E^002000
*/
