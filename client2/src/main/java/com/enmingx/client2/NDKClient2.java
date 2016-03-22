package com.enmingx.client2;

/**
 * Created by exe on 22/03/16.
 */
public class NDKClient2 {

    static {
        System.loadLibrary("Client2Jni");
    }

    public native String connectServer();

    public native String getMyString();
}
