#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<assert.h>
#include<unistd.h>

#define MAXBUFLEN 1024



int main() {

        int sockfd;
        struct hostend *he;
        char* host = "127.0.0.1";
        int port = 1206;
        int numbytes;
        char* buf[MAXBUFLEN];
        int id;
        int length;

        char* rq[16];

        char* uname = "watermelon";
        char* upass = "weedsalt";
        int attr;
        char* secret = "our secret";
        int count;
        int sizeReq, sizeName, sizePass;

        printf("host: %s, port: %d, filename: %s\n", host, port, "love");

        //memsetting buffer null
        memset(buf, "", 1024);
        puts(buf);

        //creating 16bytes worth of random hex numbers for rq
        int random;
        for(int i = 0; i < 16; i++){
                random = rand() % 255;
                sprintf(rq+i, "%.2x", random);
        }

        // if ((he = gethostbyname(host))==NULL){
        //         perror("Error getting gethostbyname\n");
        //         exit(1);
        // }

        // sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        // if(sockfd < 0)
        // {
        //   perror("Error initializing client socket\n");
        // }

        // struct sockaddr_in serv_addr;

        // serv_addr.sin_family = AF_INET;
        // serv_addr.sin_port = htons(port);
        // serv_addr.sin_addr = *((struct in_addr*)he->h_addr);
        // memset(&(serv_addr.sin_zero), '\0', 8);

        //setting up ACC-RQQ PACKET
        //sizes
        sizePass = 2 + strlen(upass);
        sizeName = 2 + strlen(uname);
        sizeReq = 16 + sizeName + sizePass;
        //add opcode
        sprintf(buf, "%.2x", 0x01);
        //add id
        sprintf(buf+1, "%.2x", 0x01);
        //add length NOT DONE
        //size of it all bb
        //finally adding length overal
        if(sizeReq <= 255){
            sprintf(&buf[3], "%.2x", sizeReq);
            //sprintf(&buf[2], "%.2d", 0x00);
        }
        puts(buf);
        //add 16 bytes of rqauth
        for(int i = 8; count < (4 + 8 + 16); i++){
                buf[i] = rq[count];
                count++;
        }
        //not done yet, attribute time

        //User-Name~ tacking it on
        //finding size of addition
        sizeName = 2 + strlen(uname);
        //add typecode
        sprintf(buf+24, "%.2x", 0x01);
        //add length from addition NOT DONE
        sprintf(buf+26, "%.2x", sizeName);
        //add string username
        for(int i = 0; i < strlen(uname); i++){
                sprintf(buf+28+i, "%.2x", uname[i]);
        }
        //User-Password~
        //find nearest NULL, then tack on password
        count = 0;
        for(int i = 0; i < strlen(buf); i++){
                if(buf[i] != ""){
                        count++;
                }else { break; }
        }
        //typecode
        sprintf(buf+count, "%.2x", 0x02);
        //length NOT DONE
        sprintf(buf+count+2, "%.2x", sizePass);
        //message
        for(int i = 0; i < strlen(upass); i++){
                sprintf(buf+count+4+i, "%.2x", upass[i]);
        }

        printf("On god i hope this works, ish: \n");
        for(int i = 0; i < sizeReq; i++){
            printf("%i: %s\n", i, &buf[i]);
        }

        // if ((numbytes = sendto(sockfd, buf, strlen(*buf), 0, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) ) < 0 ){
        //         perror("Error sending Access-Request Packet\n");
        //         exit(1);
        // }


        return 0 ;
}
