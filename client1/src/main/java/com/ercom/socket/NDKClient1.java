package com.ercom.socket;

/**
 * Created by exe on 18/03/16.
 */
public class NDKClient1 {

    static {
        System.loadLibrary("Client1Jni");
    }

    public native String connectServer();

    public native String getMyString();
}
