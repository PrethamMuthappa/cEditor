#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>


struct termios orignal_attrs;

/* To disable raw mode in terminal
 */
void disablerawmode(){
tcsetattr(STDIN_FILENO,TCSAFLUSH,&orignal_attrs);
}
/*
 * To enable raw mode (raw mode where something typed in the terminal is invisible for example , Entering pass in terminal)
 */
void enables(){
   tcgetattr(STDIN_FILENO,&orignal_attrs);
   atexit(disablerawmode); 
   struct termios raw = orignal_attrs;
  /* Icanon to caninonal mode one or off */
   raw.c_lflag &= ~(IXON | ICRNL);
   raw.c_lflag &= ~( ECHO | ICANON | ISIG | IEXTEN);
   raw.c_lflag &= ~(OPOST);
   tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

int main(){
  enables();
  char c;
  while (read(STDIN_FILENO,&c,1)==1 && c!='q'){
   
    if(iscntrl(c)){
      printf("%d\r\n",c);
    }
    else{
      printf("%d ('%c')\r\n",c,c);
    }
    
  }
  return 0;
}
