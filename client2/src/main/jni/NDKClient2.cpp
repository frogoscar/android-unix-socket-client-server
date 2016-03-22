//
// Created by exe on 22/03/16.
//
#include "com_enmingx_client2_NDKClient2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

#define MY_SOCK_PATH "/data/data/com.enmingx.server/toto"

JNIEXPORT jstring JNICALL Java_com_enmingx_client2_NDKClient2_getMyString(JNIEnv *env, jobject) {
    return env->NewStringUTF("This is message from JNI Client2");
}

JNIEXPORT jstring JNICALL Java_com_enmingx_client2_NDKClient2_connectServer(JNIEnv *env, jobject) {
    int sock;
    const int BUF_SIZE = 64;
    struct sockaddr_un server;
    char message[BUF_SIZE], server_reply[BUF_SIZE];

    // Create socket
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1) {
        //printf("cound not create socket\n");
        return env->NewStringUTF("could not create socket");
    }
    //printf("Socket created\n");

    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, MY_SOCK_PATH);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        //printf("connection error\n");
        char error_str [1024];
        sprintf(error_str, "Bind error (%s)", strerror(errno));
        return env->NewStringUTF(error_str);
        //exit(1);
    }

    //printf("Connected\n");
    return env->NewStringUTF("Successfully connected to server");

//    // keep communicating with server
//    while (1) {
//        printf("write your message : ");
//        if (fgets(message, BUF_SIZE, stdin) != NULL) {
//            // Send some data
//            if (send(sock, message, strlen(message), 0) < 0) {
//                printf("send error\n");
//                //exit(1);
//            }
//        }
//
//        // Receive a reply from the server
//        memset(server_reply, '\0', sizeof(server_reply));
//        if (recv(sock, server_reply, BUF_SIZE, 0) < 0) {
//            printf("recv failed\n");
//            break;
//        }
//
//        printf("Server reply : %s", server_reply);
//    }
//
//    close(sock);
}
