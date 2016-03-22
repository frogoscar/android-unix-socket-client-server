//
// Created by exe on 18/03/16.
//
#include "com_enmingx_socket_NDKClient1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

#define MY_SOCK_PATH "/data/data/com.enmingx.server/toto"

JNIEXPORT jstring JNICALL Java_com_enmingx_socket_NDKClient1_getMyString(JNIEnv *env, jobject) {
    return env->NewStringUTF("This is message from JNI Client1");
}

JNIEXPORT jstring JNICALL Java_com_enmingx_socket_NDKClient1_connectServer(JNIEnv *env, jobject) {
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
        char error_str [1024];
        sprintf(error_str, "connection to server error (%s)", strerror(errno));
        return env->NewStringUTF(error_str);
    }



    // keep communicating with server
    char helloMessage[] = "hello, i'm client1";
    // Send some data
    if (send(sock, helloMessage, strlen(helloMessage), 0) < 0) {
        char error_str [1024];
        sprintf(error_str, "Send error (%s)", strerror(errno));
        return env->NewStringUTF(error_str);
    }



    // Receive a reply from the server
    memset(server_reply, '\0', sizeof(server_reply));
    if (recv(sock, server_reply, BUF_SIZE, 0) < 0) {
        char error_str [1024];
        sprintf(error_str, "Recv error (%s)", strerror(errno));
        return env->NewStringUTF(error_str);
    }

    printf("Server reply : %s", server_reply);


    //close(sock);
    //printf("Connected\n");
    char server_reply_message [1024];
    sprintf(server_reply_message, "Successfully connected to server and send, receive message, Server sends back : %s", server_reply);
    return env->NewStringUTF(server_reply_message);
}

