#include <stdio.h>
#include <string.h>

int main ()
{
  FILE * fp;
  int i,n;
  char str[20];
  fp = fopen ("autoCodeSetup.c","w"); 
  strcpy(str, "void ladder(void){");
  fputs(str, fp);
  fputs("\n", fp);

  strcpy(str, " STPLC_setoneDO(channel_ name)");
  fputs(str, fp);
  fputs("\n", fp);

  strcpy(str, "}");
  fputs(str, fp);
  fputs("\n", fp);

 
  fclose (fp);
  return 0;
}