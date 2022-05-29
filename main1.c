/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "AO.h"

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold


// define active objects and their respective queues.
queue* _first_q;
queue* _second_q;
queue* _third_q;
active_object* _first_ao;
active_object* _second_ao;
active_object* _third_ao;


struct arg_struct {
    int arg1;
};


/**
 * @brief first and second functions.
 */

void* ceasar_chiper(void* args){
    /**
     * @brief this method apply the Ceasar chiper on args.
     * e.g. helLO -> ifmMP
     */
    
    char* str_input = (char*) args;
    printf("%s", str_input);
    while(*str_input != '\n'){

        if(*str_input == 90 || *str_input == 122){
            (*str_input) -= 25;
        }
        else{
            (*str_input)++;
        }
        str_input++;
    }
}

void* upper_lower(void* args){

    char* str_input = (char*) args;
    printf("%s", str_input);
    while(*str_input != '\n'){

        if (*str_input >= 65 && *str_input <= 90)
        {
            // lower case - upper case
            (*str_input) += 32;
        }
        else{
            // upper case -> lower case
            (*str_input) -= 32;
        }
        str_input++;
    }
    printf("%s", (char*)args);
}


void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void *handle_client(void *args)
{
   
    struct arg_struct *argss = (struct arg_struct *)args;
    int new_fd = argss->arg1;
    
    sleep(5);
    char buffer[1024] = {0};
    for(;;){
        read(new_fd, buffer, 1024);
        // do something
        ceasar_chiper(buffer);
        upper_lower(buffer);
        bzero(buffer, 1024);
    }
    
    close(new_fd);
    return NULL;

}

int main(void)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo *servinfo, *p;
    struct addrinfo hints;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        pthread_t thread_id;
        
        struct arg_struct args;
        args.arg1 = new_fd;
        pthread_create(&thread_id, NULL, handle_client, (void*)&args);
        
    }

    return 0;
}