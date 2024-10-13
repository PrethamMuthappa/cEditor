#include <unistd.h>
#include <stdio.h>
#include <termios.h>

void enables(){

  struct termios raw; 
  tcgetattr(STDIN_FILENO,&raw);
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

int main(){
  enables();
  char c;
  while (read(STDIN_FILENO,&c,1)==1 && c!='q'); 
  printf("  %c\n", c);
  return 0;
}
