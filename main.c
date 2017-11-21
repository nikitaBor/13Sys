#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int READ = 0;
    int WRITE = 1;

    int fds1[2];//parent to child
    int fds2[2];//child to parent
    pipe(fds1);
    pipe(fds2);

    if(!fork()){
        //child process
        close(fds1[WRITE]);
        int num;
        printf("Child receiving number from parent...\n");
        read(fds1[READ], &num, sizeof(int));
        int num2 = num*num;

        close(fds2[READ]);
        printf("Child sending %d squared (%d) to parent...\n",num,num2);
        write(fds2[WRITE], &num2, sizeof(num2));

        close(fds1[READ]); //closes left over fd's
        close(fds2[WRITE]);
    }
    else{
        //parent process
        close(fds1[READ]);
        int num = 15;
        printf("Parent sending %d to child...\n", num);
        write(fds1[WRITE], &num, sizeof(num));

        int *status;
        wait(status);

        close(fds2[WRITE]);
        int num2;
        printf("Parent receiving modified number from child...\n");
        read(fds2[READ], &num2, sizeof(int));
        printf("Parent received %d from child\n",num2);

        close(fds2[READ]); //closes left over fd's
        close(fds1[WRITE]);
    }
    return 0;
}