#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PIPEREAD 0
#define PIPEWRITE 1

#define FILER "./geruest-aufgabe-09-03a.c"
#define NEWFILE "rot13output"

char getRot13(char c) {
    char start, limit;
    if('A'<=c && 'Z'>=c) {
        start='A';
        limit='Z';
    }
    else if ('a'<=c && 'z'>=c) {
        start='a';
        limit='z';
    }
    else {
        return c;
    }
    
    if( (c+13) <= limit ) {
        return c+13;
    }
    else
        return c-13;
}


int main(int argc, char* argv[])
{
    int ret, fd[2], fdrev[2], rfd;
    pid_t pid, wpid;
    ssize_t in_father, in_son;
    char buf_father, buf_son;
    
    ret = pipe(fd);
    if(ret == -1) {
        puts("cannt open pipe\n");
        exit(EXIT_FAILURE);
    }
    
    ret = pipe(fdrev);
    if(ret == -1) {
        puts("cannt open pipe\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid == -1) {
        puts("cannt create a fork\n");
        exit(EXIT_FAILURE);
    }


    if (pid == 0) { /* Son */

        /* *** Anfang Code des Sohnes ************************************ */
        
        close(fd[PIPEWRITE]); /* schließe unbenutzten (Schreib-)Deskriptor */
        close(fdrev[PIPEREAD]); /* schließe unbenutzten (Less-)Deskriptor */

        /* Schleife: Lesen aus der Pipe und Ausgabe nach stdout */
        in_son = read(fd[PIPEREAD], &buf_son, 1);
        if(in_son == -1) {
            puts("cannt read in_son\n");
            exit(EXIT_FAILURE);
        }
        buf_son = getRot13(buf_son);
        printf("sohn schreibt: %c\n", buf_son);
        write(fdrev[PIPEWRITE], &buf_son, 1);  

        while (in_son != 0) { 
            buf_son = getRot13(buf_son);
            write(fdrev[PIPEWRITE], &buf_son, 1); 
            in_son = read(fd[PIPEREAD], &buf_son, 1); /* Lies aus Pipe */
        }

        close(fd[PIPEREAD]); /* schließe benutzten Deskriptor */
        close(fdrev[PIPEWRITE]); /* schließe benutzte Deskriptoren */
        printf("Son exits.\n");
        exit(EXIT_SUCCESS); /* beendet den Sohn */
        /* *** Ende Code des Sohnes ************************************** */
    } 
    
    else {

        /* *** Anfang Code des Vaters ************************************ */

        rfd = open(FILER, O_RDONLY);  /* Öffne Datei zum Lesen */
        FILE *fr = fopen(NEWFILE, "w+");
        
        if(rfd == -1 || fr == NULL) {
            puts("cannt read from FILE\n");
            exit(EXIT_FAILURE);
        }

        close(fd[PIPEREAD]); /* schließe unbenutzten (Lese-)Deskriptor */
        close(fdrev[PIPEWRITE]); /* schließe unbenutzten (Schreib-)Deskriptor */

        /* Schleife: Lesen aus Datei und Schreiben in Pipe */
        in_father = read(rfd, &buf_father, 1);
        if(in_father == -1) {
            puts("cannt read in_father\n");
            exit(EXIT_FAILURE);
        }
        
        while (in_father != 0) {
            // read byte
            ret = write(fd[PIPEWRITE], &buf_father, 1);
            if(ret == -1) {
                puts("cannt write on to pipe\n");
                exit(EXIT_FAILURE);
            }
            // get rot13 from son
            in_father = read(fdrev[PIPEREAD], &buf_father, 1);
            if(in_father == -1) {
                puts("cannt read in_father1.1\n");
                exit(EXIT_FAILURE);
            }
            printf("%c",buf_father);
            fputc(buf_father,fr);
            // take next byte
            in_father = read(rfd, &buf_father, 1);
            if(in_father == -1) {
                puts("cannt read in_father1\n");
                exit(EXIT_FAILURE);
            }
        }
        
        close(fd[PIPEWRITE]); /* schließe benutzte Deskriptoren */
        close(fdrev[PIPEREAD]); /* schließe benutzten Deskriptor */
        close(rfd);

        wpid = wait(NULL); /* warte auf Ende des Sohnes */
        if(wpid == -1) {
            puts("error by waiting :in_father");
            exit(EXIT_FAILURE);
        }

        printf("Father exits.\n");
        exit(EXIT_SUCCESS);
        /* *** Ende Code des Vaters ************************************* */
    } 
}
