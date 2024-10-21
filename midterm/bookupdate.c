#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
int main(int argc, char *argv[])
{
   int fd, id;
   char c;
   int num;
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDWR)) == -1) {
      perror(argv[1]);
      exit(2);
   }

      printf("0 bookId: borrow book, 1 bookId: return book ) ");
      do {
      if (scanf("%d %d",&num, &id) == 1) {
		  if (num  == 0){
			  printf("You've got bellow book..\n)");
	         lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
         	if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0) && &record.yn == "True") {
            printf("id:%8d\t bookname:%10s\t author:%10d\t year:%4d\t numofborrow:%10d\t borrow:%5s\n",
                    record.book_id, record.name, record.author, record.year, record.num, record.yn);}
			
         	if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0) && &record.yn == "False") {
				printf("can't borrow");
		  }

		  if (num == 1){
	  		    printf("You've returned bellow book..");
	            lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
            	write(fd, record.borrow = 0, sizeof(record));
	            printf("id:%8d\t bookname:%10s\t author:%10d\t year:%4d\t numofborrow:%10d\t borrow:%5s\n",
         } else printf("Record %d Null\n", id);
      } else printf("Insert Error\n");
      printf("Continue?(Y/N)");
      scanf(" %c",&c);
   } while (c == 'Y');
   close(fd);
   exit(0);
}


