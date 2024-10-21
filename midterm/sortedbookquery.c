#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"
int main(int argc, char *argv[])
{
   int fd, id, num;
	char c; 
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }
      printf("\E0: list of all books, 1: list of available books ) ");
	  scabf("%d", &num);
      printf("id\t bookname\t author\t year\t numofborrow:\t borrow\n");
   do {
		if (num == 0){
         	lseek(fp, sizeof(record), SEEK_SET);
			if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.book_id != 0))
            printf("%8d\t %10s\t %10d\t %4d\t %10d\t %5s\n", record.book_id, record.name, record.author, record.year, record.num, record.yn);
		}
		if (num == 1){
			lseek(fp, sizeof(record), SEEK_SET);	
			if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.book_id != 0 && record.borrow == "True"))
            	printf("%8d\t %10s\t %10d\t %4d\t %10d\t %5s\n", record.book_id, record.name, record.author, record.year, record.num, record.yn);
		}
		else printf("Record %d Null\n", id);
      } else printf("Input Error");
      printf("Continue?(Y/N)");
      scanf(" %c", &c);
   } while (c=='Y');
   close(fd);
   exit(0);
}


