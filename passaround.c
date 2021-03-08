/*
** name: passaround.c
**
** author: Alexandros Ali Khan
** date: 2/19/2020
** last modified:
**
** from template created 31 jan 2015 by bjr
**
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<assert.h>

#include "passaround.h"

#define LOCALHOST "localhost"
#define MAXMSGLEN 2048
#define N_REPEAT_DEFAULT 1

#define USAGE_MESSAGE "usage: passaround [-v] [-n num] [-m message] port"

int g_verbose = 0 ;

int main(int argc, char * argv[]) {
int ch ;
int the_port = 0 ;
int loop = 1 ;
int n_repeat = N_REPEAT_DEFAULT ;
char * msg = NULL ;
int is_forever = 0 ;

char * next_msg ;
int sockfd ;
struct sockaddr_in my_addr;
struct sockaddr_in their_addr ;
int index = 0 ;
        struct hostent *he ;
int numbytes ;

assert(sizeof(short)==2) ;

while ((ch = getopt(argc, argv, "vm:n:")) != -1) {
switch(ch) {
case 'n':
n_repeat = atoi(optarg) ;
break ;
case 'v':
g_verbose = 1 ;
break ;
case 'm':
msg = strdup(optarg) ;
break ;
case '?':
default:
printf(USAGE_MESSAGE) ;
return 0 ;
}
}
argc -= optind;
argv += optind;

if ( argc!= 1 ) {
fprintf(stderr,"%s\n",USAGE_MESSAGE) ;
exit(0) ;
}

the_port = atoi(*argv) ;
assert(the_port) ;

is_forever = (n_repeat == 0) ;

if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 ) {
                perror("socket") ;
exit(1) ;
}

my_addr.sin_family = AF_INET ;
my_addr.sin_port = htons((short)the_port) ;
my_addr.sin_addr.s_addr = INADDR_ANY ;
memset(&(my_addr.sin_zero),'\0',8) ;

if (bind(sockfd, (struct sockaddr *)&my_addr,
                sizeof(struct sockaddr)) == -1 ) {
                perror("bind") ;
        exit(1) ;
        }


their_addr.sin_family = AF_INET ;
        their_addr.sin_port = htons((short)the_port) ;
memset(&(their_addr.sin_zero), '\0', 8 ) ;

if ( msg ) {

// parse and send

while(msg[index] != ':' && msg[index] != '\0') {
index++ ;
}
char dest[index] ;
strncpy(dest, msg, index) ;
dest[index] = '\0' ;
(msg[index] == '\0') ? (next_msg = msg + index) : (next_msg = msg + index + 1) ;

if ((he=gethostbyname(dest))==NULL) {
perror("gethostbyname") ;
exit(1) ;
}

their_addr.sin_addr = *((struct in_addr *)he->h_addr) ;

if ((numbytes=sendto(sockfd, next_msg, strlen(next_msg),0,
(struct sockaddr *)&their_addr, sizeof(struct sockaddr)) ) == -1 ) {
perror("sendto") ;
exit(1) ;
}

printf("S: %s:%d |%s|\n", inet_ntoa(their_addr.sin_addr),
                                ntohs(their_addr.sin_port), next_msg) ;

free(msg) ;
n_repeat-- ; // a packet sent
}

while( is_forever || n_repeat ) {

// listen for a packet
// print R: host:port |message|

unsigned int addr_len ;
char buf[MAXMSGLEN];

addr_len = sizeof(struct sockaddr_in) ;
if ((numbytes=recvfrom(sockfd, buf, MAXMSGLEN-1,0,
(struct sockaddr *)&their_addr, &addr_len)) == -1 ) {
perror("recvfrom") ;
exit(1) ;
}

buf[numbytes] = '\0' ;

printf("R: %s:%d |%s|\n", inet_ntoa(their_addr.sin_addr),
ntohs(their_addr.sin_port), buf) ;

// if something to send, {
//    parse and send
//    and print S: host:port |message|
// }

if (numbytes) {
while(buf[index] != ':' && buf[index] != '\0')
                        index++ ;
                char dest[index] ;
strncpy(dest, buf, index) ;
                dest[index] = '\0' ;
(buf[index] == '\0') ? (next_msg = buf + index) : (next_msg = buf + index + 1) ;
                if ((he=gethostbyname(dest))==NULL) {
                        perror("gethostbyname") ;
                        exit(1) ;
                }

                their_addr.sin_addr = *((struct in_addr *)he->h_addr) ;

                if ((numbytes=sendto(sockfd, next_msg, strlen(next_msg),0,
                        (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) ) == -1 ) {
                        perror("sendto") ;
                        exit(1) ;
                }

printf("S: %s:%d |%s|\n", inet_ntoa(their_addr.sin_addr),
                                ntohs(their_addr.sin_port), next_msg) ;
}

n_repeat-- ;
}
close(sockfd) ;
return 0 ;
}
