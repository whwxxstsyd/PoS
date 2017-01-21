#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;

  printf("This will display on the screen.\n");

  if((fp=freopen("OUT", "w" ,stdout))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  printf("This will be written to the file OUT.");

  fclose(fp);

  return 0;
}
