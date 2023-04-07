#include<stdio.h>
#include<unistd.h>
#include <variant>
#include <string>
int main() {
  char* buffer;
  if ((buffer = getcwd (NULL, 0)) == NULL) {
    perror ("getcwd error");
  } else {
    printf ("%s\n", buffer);
  }
}
