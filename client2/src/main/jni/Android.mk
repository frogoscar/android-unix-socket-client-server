LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Client2Jni
LOCAL_SRC_FILES := NDKClient2.cpp
include $(BUILD_SHARED_LIBRARY)