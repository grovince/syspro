#include <stdio.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
   char c;
   char a;
   FILE *fp1, *fp2;
   if (argc !=4) {
      fprintf(stderr,  "How to use: %s File1 File2\n", argv[0]);
      return 1;
   }

   fp1 = fopen(argv[1], "r");

   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
   }

	if (argv[1] == 0){
		fp2 = fopen(argv[2], "w");
		while ((c = fgetc(fp1)) != EOF)
			fputc(c, fp2);
	}

	if (argv[1] == 1){
		fp2 = fopen(argv[2], "w");
		while((c = fgetc(fp1))!= EOF)
			a = tolower(c);
			fputc(a, fp2);
	}

	if (argv[1] == 2){
	   fp2 = fopen(argv[2], "w");
	   while ((c = fgetc(fp1)) != EOF){
		a = toupper(c);
	   	fputc(a, fp2);
	  
		}
	}

   fclose(fp1);
   fclose(fp2);
   return 0;
}


