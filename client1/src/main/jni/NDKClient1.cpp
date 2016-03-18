//
// Created by exe on 18/03/16.
//
#include "com_ercom_socket_NDKClient1.h"

JNIEXPORT jstring JNICALL Java_com_ercom_socket_NDKClient1_getMyString(JNIEnv *env, jobject) {
    return env->NewStringUTF("This is message from JNI Client1");
}

