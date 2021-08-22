#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>
#include <string.h>

int wprintcentered(char * string, int height, int width){
      int strl = sizeof(string) / sizeof(char);
      strl = strlen(string);
      mvprintw(height, width-(strl/2), string);
      refresh();
      return 1;
}

int calclifepos(int birthyear, int expectancy, int minwidth, int maxwidth){
      float oneperc = (float)expectancy/100;
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      int age = (tm.tm_year + 1900) - birthyear;
      float lifeprog = oneperc * age;

      int barlen = maxwidth - minwidth;
      float baroneperc = (float)barlen / 100;
      int barprog = baroneperc * lifeprog;
      return barprog;
}


int main(int argc, char *argv[]){

      if(argc == 1){
            printf("Missing parameter!\nUsage: ./memmori [99-99-9999]");
            return -1;
      }

      char byear[4];
      int i;
      for(i = 0; i < 5; i++){
            byear[i] = argv[1][6+i];
      }

      char * p;
      long birthl = strtol(byear, &p, 10);
      int birth;
      if(*p != '\0' || birthl > 4000 || birthl < 0){
            printf("Invalid date given!");
            return -1;
      }
      else {
            birth = birthl;
      }

      WINDOW * w;
      int eHeight, eWidth;

      char * locale;
      locale = setlocale(LC_ALL,"");

      // ncurses start
      initscr();
      refresh();
      noecho();
      curs_set(FALSE);
      box(stdscr, 0, 0);
      refresh();
      int pathpos = 5;

      getmaxyx(stdscr, eHeight, eWidth);
      wprintcentered("\u2020 Memento mori \u2020", 4, eWidth/2);
      wprintcentered("\u205C--------------\u205C", 5, eWidth/2);
      wprintcentered(byear, eHeight/2-3, pathpos);
      char buf[8];
      sprintf(buf, "%d", birth+75);
      wprintcentered(buf, eHeight/2-3, eWidth-5);
      refresh();

      int maxlen = eWidth - 5;
      int put = 0;
      int curr = calclifepos(birth, 75, 5, eWidth-5);
      while(put < curr){
            getmaxyx(stdscr, eHeight, eWidth);
            mvprintw(eHeight/2, pathpos, "\u2593");
            pathpos += 1;
            put += 1;
      }

      refresh();
      getch();
      endwin();
      // ncurses end
      return 0;
}
