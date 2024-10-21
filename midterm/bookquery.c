#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"
int main(int argc, char *argv[])
{
   int fd, id;
   int num;
	char c; 
   struct book record;
   if (argc < 3) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }

   do {
      printf("\E0: list of all books, 1: list of available books");
	if (scanf("%d", &num) == 1){
		   // available books
		if(num == 1){}
	  if (scanf("%d", &id) == 1) {
         lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
          if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.book_id != 0))
       printf("id:%d\t bookname:%s\t author:%s\t year:%d\t numofborrow:%d\t borrow:%s\n", record.book_id, record.name, record.author, record.year, record.num, record.yn);
		  if(num == 0){ // all books
			lseek(fd, SEEK_SET);
	          if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.book_id != 0))
       			printf("id:%d\t bookname:%s\t author:%s\t year:%d\t numofborrow:%d\t borrow:%s\n", record.book_id, record.name, record.author, record.year, record.num, record.yn);
		  }
      } else printf("Input Error");
      printf("Continue?(Y/N)");
      scanf(" %c", &c);
   } while (c=='Y');
   }
   close(fd);
   exit(0);
}

