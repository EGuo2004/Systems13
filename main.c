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

int main(){
  read_csv();
}

int read_csv() {
  int w;
  w = open("nyc_pop.csv",O_RDONLY);
  struct stat s;
  stat("nyc_pop.csv", &s);
  char *content;
  content = malloc(s.st_size);
  read(w, content, s.st_size);
  close(w);
  
  printf("%s\n", content);
}

int read_data() {

}

int update_data() {

}



