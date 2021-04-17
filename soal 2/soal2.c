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
#include <wait.h>
#include <time.h>
#include <dirent.h>

int main(){
    pid_t child_id = fork();

    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"mkdir", "-p", "petshop", NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(NULL) != child_id);

    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"unzip", "-q", "pets.zip", "-d", "petshop", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while(wait(NULL) != child_id);

    child_id = fork();
    if (child_id == 0) {
    char *argv[] = {"find","petshop","-mindepth","1","-type","d","-name","*",
                    "-exec","rm","-r","{}","+",NULL};
    execv("/bin/find", argv);
    }
    while(wait(NULL) != child_id);

    
}
