#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>


struct termios orignal_attrs;

/* To disable raw mode in terminal
 */
void disablerawmode(){

tcsetattr(STDIN_FILENO,TCSAFLUSH,&orignal_attrs);
}

/*
 * To enable raw mode (raw mode where someting typed in the terminal is invisible for example , Entering pass in terminal)
 */

void enables(){
   tcgetattr(STDIN_FILENO,&orignal_attrs);
   atexit(disablerawmode); 
   struct termios raw = orignal_attrs; 
   raw.c_lflag &= ~(ECHO);
   tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

int main(){
  enables();
  char c;
  while (read(STDIN_FILENO,&c,1)==1 && c!='q');
  return 0;
}
