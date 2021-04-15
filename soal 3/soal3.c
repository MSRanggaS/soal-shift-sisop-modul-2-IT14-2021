#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

int main() {
    pid_t child_id,child2,child3,child4;
    int status;

    char str[50], url[100], file[100], save[100];
    int a;
    time_t t, w;
    t = time(NULL);
    struct tm *tm, *wm;
    tm = localtime(&t);
    strftime(str, 50, "%Y-%m-%d_%H:%M:%S", tm);
    char now[80];
    strftime(now, 80, "%Y-%m-%d_%H:%M:%S", tm);
  
    child_id = fork();
  
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }

    if (child_id == 0)
    {
        char *argv[] = {"mkdir", "-p", str, NULL};
	  	  execv("/bin/mkdir", argv);
    }
    else{
      wait(NULL);
      
      child2 = fork();

      if (child2 < 0){
          exit(EXIT_FAILURE);
      }

      if (child2 == 0){

          for (int i = 0; i < 10; i++) {

          child3 = fork();

          if (child3 < 0){
          exit(EXIT_FAILURE);
          }

          if (child3 == 0) {

            w = time(NULL);
            wm = localtime(&w);
            a = (w%1000)+50;
            sprintf (url, "https://picsum.photos/%d", a);
            strftime(file, 50, "%Y-%m-%d_%H:%M:%S", wm);
            sprintf (save, "%s/%s", str, file);
            char *args[] = {"wget","--no-check-certificate", "-q", "-O", save, url, NULL};

            execv("/usr/bin/wget", args);

          }
          else{
            wait(NULL);
          }

          sleep(5);

        }

        chdir(str);
        char message[100]="Download Success", ch;
        int i, key=5;
        
        for(i = 0; message[i] != '\0'; ++i){
          ch = message[i];
          
          if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            
            if(ch > 'z'){
              ch = ch - 'z' + 'a' - 1;
            }
            
            message[i] = ch;
          }
          else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            
            if(ch > 'Z'){
              ch = ch - 'Z' + 'A' - 1;
            }
            
            message[i] = ch;
          }
        }
        
        FILE * fp;
        fp = fopen("status.txt", "w+");
        fputs(message, fp);
        fclose(fp);

        chdir("../");

        while(wait(NULL) > 0);
        child4 = fork();
        if (child4 == 0) {

          char nama_file[80];
          sprintf(nama_file, "%s.zip", str);
          char *argv[] = {"zip", "-r", nama_file, str, NULL};
          execv("/usr/bin/zip", argv);

        }

        wait(NULL);
        char *argv[] = {"rm", "-r", str, NULL};
        execv("/bin/rm", argv);
      }
    
    exit(0);

    }
