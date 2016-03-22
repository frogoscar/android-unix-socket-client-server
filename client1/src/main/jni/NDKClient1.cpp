//
// Created by exe on 18/03/16.
//
#include "com_ercom_socket_NDKClient1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

JNIEXPORT jstring JNICALL Java_com_ercom_socket_NDKClient1_getMyString(JNIEnv *env, jobject) {
    return env->NewStringUTF("This is message from JNI Client1");
}

JNIEXPORT jstring JNICALL Java_com_ercom_socket_NDKClient1_connectServer(JNIEnv *env, jobject) {

}

