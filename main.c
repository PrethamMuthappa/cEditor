#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


#define CTRL_KEY(k) ((k) & 0x1f)
struct termios orignal_attrs;

void die(const char *s){
 perror(s);
  exit(1);
}


/* To disable raw mode in terminal
 */
void disablerawmode(){
  
 if( tcsetattr(STDIN_FILENO,TCSAFLUSH,&orignal_attrs)==-1 ){
    die("tcsetattr");
  }
}

/*
 * To enable raw mode (raw mode where something typed in the terminal is invisible for example , Entering pass in terminal)
 */
void enables(){
  if(tcgetattr(STDIN_FILENO,&orignal_attrs) == -1){
    die("tcgetattr");
  }
   atexit(disablerawmode); 
   struct termios raw = orignal_attrs;
  /* Icanon to caninonal mode one or off */
   raw.c_iflag &= ~(BRKINT |IXON | ICRNL | INPCK | ISTRIP);
   raw.c_lflag &= ~( ECHO | ICANON | ISIG | IEXTEN);
   raw.c_oflag &= ~(OPOST);
   raw.c_cflag  |=(CS8);
   raw.c_cc[VMIN] = 0;
   raw.c_cc[VTIME]=1;
   if( tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw)==-1) die("tcsetattr");
}

/*create a key to read input from keyboard */

char editorkey(){

  int nread;
  char c;
  while ((nread==read(STDIN_FILENO,&c,1))!= 1) {
  if(nread==-1 && errno!=EAGAIN) die("read");
  }
  return c;
}

/*procees this input  */

void editorprocess(){
  char c=editorkey();
  switch (c) {
    case CTRL_KEY('q'):
    exit(0);
    break;
  }
}

/* MAIN FUNCTION */
int main(){
  enables();

  while (1)
  {
    editorprocess();
    /* onlt this should go 
     */

    printf("hellow");
    
  }
  return 0;
}
