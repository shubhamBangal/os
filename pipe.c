#include <fcntl.h>

#include <sys/stat.h>

#include <unistd.h>

#include <stdio.h>



#define MAX_BUFFER 1024



int main() {

  int fd, fd1, wr;

  int words = 1, len = 0, i = 0, line = 1, c = 0;

  

  const char *avfifo = "avfifo";

  const char *avfifo1 = "avfifo1";



  char buff[MAX_BUFFER], str[MAX_BUFFER];

  

  FILE *fp;



  /* Create the FIFO (named pipe) */

  mkfifo(avfifo1, 0666);

  mkfifo(avfifo, 0666);



  /* Open, read, and display the message from the FIFO */

  fd = open(avfifo, O_RDWR);



  printf("\n\nEnter a sentence ending with 0:\n");



  while ((str[i] = getchar()) != '0') {

    i++;

  }

  str[i] = '\0';



  write(fd, str, sizeof(str));



  i = 0;



  read(fd, buff, MAX_BUFFER);



  printf("\nFirst Message received: %s \n", buff);



  while (buff[i] != '\0') {

    if (buff[i] == ' ' || buff[i] == '\n') {

      words++;

      if (buff[i] == '\n') {

        line++;

      }

    } else {

      c++;

    }

    i++;

  }



  fp = fopen("test.txt", "w+");

  if (fp != NULL) {

    fprintf(fp, "\nTotal characters = %d\n", c);

    fprintf(fp, "\nTotal words = %d\n", words);

    fprintf(fp, "\nTotal lines = %d\n", line);

    fclose(fp);

  } else {

    printf("Error opening 'test.txt' for writing.\n");

  }



  close(fd);



  fd1 = open(avfifo1, O_RDWR);

  wr = write(fd1, &c, sizeof(c));

  wr = write(fd1, &words, sizeof(words));

  wr = write(fd1, &line, sizeof(line));

  

  printf("\nTotal characters = %d\n", c);

  printf("\nTotal words = %d\n", words);

  printf("\nTotal lines = %d\n", line);

  if (wr == -1) {

    printf("\nError writing in the second pipe..!\n");

    return 1;

  } else {

    printf("\nSuccessful writing in the second pipe..!\n");

  }

  close(fd1);



  return 0;

}

