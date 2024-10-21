#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"
int main(int argc, char *argv[]){

   int fd;
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use: %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
      perror(argv[1]);
      exit(2);
   }

   printf("%-7s %-9s %-10s %-9s %-8s %-7s\n","book_id" "book_name", "book_author", "book_year", "book_num", "book_yn");
   
   while (scanf("%d %s %s %d %d %s", &record.book_id, &record.name, &record.author, &record.year, &record.num, &record.yn ) == 6) {
      lseek(fd, (record.book_id - START_ID) * sizeof(record), SEEK_SET);
      write(fd, (char *) &record, sizeof(record));
   };
   close(fd);
   exit(0);
}
