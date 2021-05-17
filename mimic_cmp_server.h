 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #define MAX_SIZE 200

typedef struct
{
  int pos;
  int line;
  char ch1;
  char ch2;
}sMismatchingPos;

int MainMenu();
int isFileSame(  FILE *fp1, FILE *fp2,sMismatchingPos *psMismatchPos);
int b_option();
int i_option();
int s_option();
int n_option();





