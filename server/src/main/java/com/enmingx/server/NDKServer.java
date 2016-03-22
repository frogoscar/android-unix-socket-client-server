package com.enmingx.server;

/**
 * Created by exe on 22/03/16.
 */
public class NDKServer {

    static {
        System.loadLibrary("ServerJni");
    }

    public native String getMyString();

    public native String startServer();
}
