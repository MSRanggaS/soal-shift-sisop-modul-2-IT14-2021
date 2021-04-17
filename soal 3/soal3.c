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

void killer(char argc[]){
  if(strcmp(argc,"-z") == 0){
    FILE * fp;

    fp = fopen ("killer.sh", "w+");
    fprintf(fp, "pkill -9 new\nrm -r killer.sh");
    
    fclose(fp);
  }
  if(strcmp(argc,"-x") == 0 ){
    FILE * fp;

    fp = fopen ("killer.sh", "w+");
    fprintf(fp, "pkill -1 new\nrm -r killer.sh");
    
    fclose(fp);
  }

  if (fork() == 0) {
    char *argt[] = {"chmod", "777", "killer.sh", NULL};
    execv("/bin/chmod", argt);
  }

}

int main(int argc, char **argv) {
    
  pid_t pid, sid; 

  pid = fork(); 

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  // if ((chdir("/")) < 0) {
  //   exit(EXIT_FAILURE);
  // }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    
    if(argc != 2){
      printf("Tidak terdefinisi");
      exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-x") != 0 && strcmp(argv[1], "-z") != 0) {
      printf("Argumen kurang benar");
      return 1;
    }

    killer(argv[1]);
    
    pid_t child_id,child2,child3,child4;
    int status;

    char str[50], url[100], file[50], save[105];
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
        char *argg[] = {"mkdir", "-p", str, NULL};
	  	  execv("/bin/mkdir", argg);
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

          char nama_file[105];
          sprintf(nama_file, "%s.zip", str);
          char *argk[] = {"zip", "-r", nama_file, str, NULL};
          execv("/usr/bin/zip", argk);

        }

        wait(NULL);
        char *argb[] = {"rm", "-r", str, NULL};
        execv("/bin/rm", argb);
      }

    }
    
    sleep(40);
  }
}
