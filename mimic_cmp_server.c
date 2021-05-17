 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #define MAX_SIZE 200
 #include"mimic_cmp_server.h"


//The main section for comparing the files using different options
int MainMenu(){
 char n;
 printf(": : : : : : : : : : : : : : : : : Mimicing cmp Command : : : : : : : : : : : : : : : : : : :\n");
 printf("\n : : : : : : :1=>Compare files with -b option");
 printf("\n : : : : : : :2=>Compare files with -i option");
 printf("\n : : : : : : :3=>Compare files with -s option");
 printf("\n : : : : : : :4=>Compare files with -n option");
 printf("\n : : : : : : :5=>Exit");
 printf("\n\n Enter Your Choice : ");
 scanf("%c",&n);
 switch(n){
	case '1' : b_option();
		   break;
	case '2' : i_option();
		   break;
	case '3' : s_option();
                   break;
	case '4' : n_option();
		   break;
	case '5' : {
		    printf("Thank You!\n\n");
  		    //usleep(10000);
		    exit(0);
		   }
		}
}



//Comparing the files.
int isFileSame(  FILE *fp1, FILE *fp2,sMismatchingPos *psMismatchPos)
{
  int pos=0,line=1;
  char ch1,ch2;
  int isContentMatch=0;
  do
  {
    ch1=fgetc(fp1);
    ch2=fgetc(fp2);
    ++pos;
    if((ch1=='\n') && (ch2=='\n')) //starting the comparison from the line where the text starts.
    {
      ++line;
      pos=0;
    }
    psMismatchPos->pos=pos;
    psMismatchPos->line=line;
    psMismatchPos->ch1=ch1;
    psMismatchPos->ch2=ch2;
    if(ch1!=ch2)             // finding the first differing byte.
    {
      isContentMatch=1;
      break;
    }
  }
  while(ch1!=EOF && ch2!=EOF);
  return isContentMatch;
}



//function to report the differing byte or print "identical" if otherwise.
int b_option()          
{
  FILE *fp1=NULL;
  FILE *fp2=NULL;
  sMismatchingPos misMatchPos= {0};
  int isContentMatch=0;
  fp1=fopen("file1.txt","r");
  fp2=fopen("file2.txt","r");
  if(fp1==NULL || fp2==NULL)      //displays error if files are empty.
  {
    printf("error: files not open");
    exit(1);
  }
  isContentMatch=isFileSame(fp1,fp2,&misMatchPos);
  if(isContentMatch)
  {
    printf("file1 and file2 are different\n");
    printf("line number: %d\n",misMatchPos.line);
    printf("position (byte): %d\n",misMatchPos.pos);
    printf("byte in file 1: %d %c\n",misMatchPos.ch1,misMatchPos.ch1);
    printf("byte in file 2: %d %c\n",misMatchPos.ch2,misMatchPos.ch2);
  }
  else
  {
    printf("file1 and file2 are identical\n");
  }

  fclose(fp1);
  fclose(fp2);
  return 0;
}



//function to START comparison skipping the desired no. of bytes(according to user's preference).
int i_option()             
{
  FILE *fp1=NULL;
  FILE *fp2=NULL;
  sMismatchingPos misMatchPos= {0};
  int isContentMatch=0;
  int n1,n2;
  printf("enter the number of bytes you want to skip from file1 and file2 ( : ):");
  scanf("%d:%d",&n1,&n2);
  fp1=fopen("file1.txt","r");
  fseek(fp1,n1,SEEK_CUR);
  fp2=fopen("file2.txt","r");
  fseek(fp2,n2,SEEK_CUR);
  if(fp1==NULL || fp2==NULL)
  {
    printf("error: files not open");
    exit(1);
  }
  isContentMatch=isFileSame(fp1,fp2,&misMatchPos);
  if(isContentMatch)
  {
    printf("both files are different\n");
    printf("line number: %d\n",misMatchPos.line);
    printf("position: %d\n",misMatchPos.pos);
  }
  else
  {
    printf("both files are same\n");
  }
 
  fclose(fp1);
  fclose(fp2);
  return 0;
}



//function to compress the output.
int s_option()            
{
  FILE *fp1=NULL;
  FILE *fp2=NULL;
  sMismatchingPos misMatchPos= {0};
  int isContentMatch=0;
  fp1=fopen("file1.txt","r");
  fp2=fopen("file2.txt","r");
  if(fp1==NULL || fp2==NULL)
  {
    printf("error: files not open");
    exit(1);
  }
  isContentMatch=isFileSame(fp1,fp2,&misMatchPos);
  if(isContentMatch)
  {
    printf(" 1\n\n");
  }
  else
  {
    printf(" 0\n\n");
  }
 
  fclose(fp1);
  fclose(fp2);
  return 0;
}


//function to compare TILL  the desired no. of bytes.
int n_option()                  
{
  FILE *fp1=NULL;
  FILE *fp2=NULL;
  sMismatchingPos misMatchPos= {0};
  int isContentMatch=0;
  int n;
  printf("Till where you want to compare the files? (enter the no. of bytes): ");
  scanf("%d",&n);
  fp1=fopen("file1.txt","r");
  fp2=fopen("file2.txt","r");
  
  if(fp1==NULL || fp2==NULL)
  {
    printf("error: files not open");
    exit(1);
  }
  
  isContentMatch=isFileSame(fp1,fp2,&misMatchPos);
  
   if(isContentMatch && n>=misMatchPos.pos)
   {
     printf("both files are different\n");
     printf("line number: %d\n",misMatchPos.line);
     printf("position: %d\n",misMatchPos.pos);
   }
  
   else
    {
     printf("both files are same\n");
    }
 
  fclose(fp1);
  fclose(fp2);
  return 0;
}

