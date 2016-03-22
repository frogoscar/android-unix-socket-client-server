//
// Created by exe on 22/03/16.
//
#include "com_ercom_server_NDKServer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

JNIEXPORT jstring JNICALL Java_com_ercom_server_NDKServer_getMyString(JNIEnv *env, jobject) {
    return env->NewStringUTF("This is message from JNI Server");
}

JNIEXPORT void JNICALL Java_com_ercom_server_NDKServer_startServer(JNIEnv *env, jobject){
    const int MYPORT = 1314;          // the port users will be connecting to
    const int BACKLOG = 5;            // how many pending connections queue will hold
    const int BUF_SIZE = 64;
    int fd_A[5] = {0,0,0,0,0};              // accepted connection fd
    int sock_fd, new_fd;            // listen on sock_fd, new connection on new_fd
    struct sockaddr_in server_addr; // server address information
    struct sockaddr_in client_addr; // connector's address information
    socklen_t sin_size;
    int yes = 1;
    char buf[BUF_SIZE];
    int ret;
    int i;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    server_addr.sin_family = AF_INET;         // host byte order
    server_addr.sin_port = htons(MYPORT);     // short, network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
        -1) {
        perror("bind");
        exit(1);
    }
    if (listen(sock_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    printf("listen port %d\n", MYPORT);
    fd_set fdsr;
    int maxsock;
    struct timeval tv;
    int conn_amount = 0; // current connection amount
    sin_size = sizeof(client_addr);
    maxsock = sock_fd;
    while (1) {
        // initialize file descriptor set
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr); // add fd
        // timeout setting
        tv.tv_sec = 60;
        tv.tv_usec = 0;
        // add active connection to fd set
        for (i = 0; i < BACKLOG; i++) {
            if (fd_A[i] != 0) {
                FD_SET(fd_A[i], &fdsr);
            }
        }
        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
        if (ret < 0) { // error
            perror("select");
            break;
        } else if (ret == 0) { // time out
            printf("timeout\n");
            continue;
        }
        // check every fd in the set
        for (i = 0; i < conn_amount; i++) {
            if (FD_ISSET(fd_A[i], &fdsr)) // check which fd is ready
            {
                ret = recv(fd_A[i], buf, sizeof(buf), 0);
                if (ret <= 0) { // client close
                    printf("ret : %d and client[%d] close\n", ret, i);
                    close(fd_A[i]);
                    FD_CLR(fd_A[i], &fdsr); // delete fd
                    fd_A[i] = 0;
                    conn_amount--;
                } else { // receive data
                    if (ret < BUF_SIZE)
                        memset(&buf[ret], '\0', 1); // add NULL('\0')
                    printf("client[%d] send : %s\n", i, buf);
                    // Turn all the character in buffer to UPCASE
                    for (int j = 0; j < sizeof(buf); j++) {
                        buf[j] = toupper(buf[j]);
                    }
                    if (send(fd_A[i], buf, sizeof(buf), 0) < 0) {
                        perror("send to client");
                    }
                }
            }
        }
        // check whether a new connection comes
        if (FD_ISSET(sock_fd, &fdsr)) // accept new connection
        {
            new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
            if (new_fd <= 0) {
                perror("accept");
                continue;
            }
            // add to fd queue
            if (conn_amount < BACKLOG) {
                fd_A[conn_amount++] = new_fd;
                printf("new connection client[%d] %s:%d\n", conn_amount,
                       inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                if (new_fd > maxsock) // update the maxsock fd for select function
                    maxsock = new_fd;
            } else {
                printf("max connections arrive, exit\n");
                send(new_fd, "bye", 4, 0);
                close(new_fd);
                break;
            }
        }
        // showclient();

        printf("client amount: %d\n", conn_amount);
        for (i = 0; i < BACKLOG; i++) {
            printf("[%d]:%d  ", i, fd_A[i]);
        }
        printf("\n\n");
    }
    // close other connections
    for (i = 0; i < BACKLOG; i++) {
        if (fd_A[i] != 0) {
            close(fd_A[i]);
            printf("Closed File Descriptor %d\n", i);
        }
    }
    exit(0);
}
