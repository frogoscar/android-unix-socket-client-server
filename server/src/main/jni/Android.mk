LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ServerJni
LOCAL_SRC_FILES := NDKServer.cpp
include $(BUILD_SHARED_LIBRARY)