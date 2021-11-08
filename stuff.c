#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int read_csv();
int read_data();
int update_data();
int main();

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

int read_csv() {
  int w;
  int perrowsize = sizeof(struct pop_entry) * 5;
  w = open("nyc_pop.csv",O_RDONLY);
  struct stat s;
  stat("nyc_pop.csv", &s);
  char *content;
  content = malloc(s.st_size);
  read(w, content, s.st_size);
  close(w);
  char *buffer = content;
  printf("%s\n",buffer);
  int rowsneeded;
  rowsneeded = 0;
  int counter;
  for (counter = 0; content[counter] != NULL; counter++){
  if (content[counter] == '\n'){
    rowsneeded++;
  }
  rowsneeded--;
  struct pop_entry *information = malloc(perrowsize * rowsneeded);

}

int read_data() {

}

int update_data() {

}



