#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int read_csv();
int read_data();
int add_data();
int update_data();
int main(int argc, char *argv[]);

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

int read_csv() {
  int counter;
  char *next;
  int bufferfile;
  struct stat s;
  int perrowsize = sizeof(struct pop_entry) * 5;
  int w = open("nyc_pop.csv",O_RDONLY);
  stat("nyc_pop.csv", &s);
  char *content = malloc(s.st_size);
  printf("reading nyc_pop.csv\n");
  read(w, content, s.st_size);
  close(w);
  char *buffer = content;
  int rowsneeded = 0;
  for (counter = 0; buffer[counter] != '\0'; counter++){
    if (buffer[counter] == '\n'){
      rowsneeded++;
    }
  }
  buffer = content;
  rowsneeded--;

  struct pop_entry *information = malloc(perrowsize * rowsneeded);
  counter = 0;
  next = 1 + strchr(buffer, '\n');
  int runs = 23;
  buffer = 1 + strchr(buffer, '\n');
  while(next != NULL && *next != '\0' && runs > 0) {
    char *other;
    other = next;
    next = strchr(other, '\n');
    *next = '\0';
    int year;

    sscanf(other,"%d,%d,%d,%d,%d,%d", &year, &(information[counter].population), &(information[counter+1].population), &(information[counter+2].population), &(information[counter+3].population), &(information[counter+4].population));
    for(int num = 0; num < 5; num++) {
      information[counter+num].year = year;
    }
    strcpy(information[counter].boro,"Manhattan");
    strcpy(information[counter+1].boro,"Brooklyn");
    strcpy(information[counter+2].boro,"Queens");
    strcpy(information[counter+3].boro,"Bronx");
    strcpy(information[counter+4].boro,"Staten Island");
    if(1 + strchr(other,'\n') != NULL) {
      *next = '\n';
      next++;
    }
    counter += 5;
    runs--;
  }
  // for(int a = 0; a < counter; a++) {
  //   printf("Year: %d, Boro: %s, Pop: %d\n",information[a].year,information[a].boro,information[a].population);
  // }
  bufferfile = open("nycpopdata.info", O_CREAT | O_TRUNC | O_WRONLY, 0644);
  write(bufferfile, information, (perrowsize * rowsneeded));
  free(content);
  free(information);
  printf("wrote %d bytes to nycpopdata.info\n", (perrowsize * rowsneeded));
  return 0;
}


int read_data() {
  int tempfile;
  tempfile = open("nycpopdata.info", O_RDONLY);
  if (tempfile == -1) {
    printf("%s\n",strerror(errno));
    return 0;
  }
  struct stat fsize;
  if (stat("nycpopdata.info", &fsize) == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }
  stat("nycpopdata.info", &fsize);
  struct pop_entry *information = malloc(fsize.st_size);
  read(tempfile, information, fsize.st_size);
  int counter;
  int fullsize = fsize.st_size / sizeof(struct pop_entry);
  for(counter = 0; counter < fullsize; counter++) {
    printf("[%d] year: %d boro: %s pop: %d\n",counter,information[counter].year,information[counter].boro,information[counter].population);
  }
  close(tempfile);
}

int add_data(){
  printf("Enter year boro pop: ");
  char input[100];
  fgets(input, sizeof(input), stdin);
  char *buffer;
  buffer = input;
  struct pop_entry n;
  char *temp;
  sscanf(buffer, "%d %s %d\n", &(n.year), temp, &(n.population));
  strcpy(n.boro, temp);
  int bufferfile = open("nycpopdata.info", O_WRONLY|O_APPEND);
  printf("Appended data to file: year: %d	boro: %s pop: %d\n", n.year, n.boro,n.population);
  write(bufferfile,&n, sizeof(struct pop_entry));
  return 0;
}

int update_data(){
  struct pop_entry n;
  char input[100];
  read_data();

  printf("Entry to update: ");
  int entry;
  fgets(input, sizeof(input), stdin);
  sscanf(input, "%d", &entry);

  printf("Enter year boro pop:\n");
  fgets(input, sizeof(input), stdin);
  sscanf(input,"%d %s %d", &n.year, n.boro, &n.population);

  int tempfile = open("nycpopdata.info", O_RDWR);
  if (tempfile == -1) {
    printf("%s\n",strerror(errno));
    return 0;
  }

  lseek(tempfile, entry*sizeof(struct pop_entry), SEEK_SET);
  int err = write(tempfile, &n, sizeof(n));
  if(err==-1){
      printf("Error:\n");
      return 0;
  }
  close(tempfile);
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("Include an argument -read_csv -read_data -add_data -update_data\n");
  } else {
    if(argc == 2){
      if (!strcmp(argv[1], "-read_csv")){
        read_csv();
      }else if(!strcmp(argv[1], "-read_data")){
        read_data();
      }else if(!strcmp(argv[1], "-add_data")){
        add_data();
      }else if(!strcmp(argv[1], "-update_data")){
        update_data();
      }else{
        printf("INVALID INPUT\n");
      }
    }
  }
  return 0;
}
