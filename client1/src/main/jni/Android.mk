LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Client1Jni
LOCAL_SRC_FILES := NDKClient1.cpp
include $(BUILD_SHARED_LIBRARY)