package com.enmingx.server;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

/**
 * Created by exe on 22/03/16.
 */
public class ServerService extends Service {

    private static final String TAG = ServerService.class.getName();

    // ==================== Binder ================
    public class ServerServiceBinder extends Binder {
        public ServerService getService() {
            return ServerService.this;
        }
    }

    private final ServerServiceBinder mBinder = new ServerServiceBinder();

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    // ==================== Service Lifecycle ================
    @Override
    public void onCreate() {
        super.onCreate();

        NDKServer mNDKServer = new NDKServer();

        Log.i(TAG, "ServerService started");

        Log.i(TAG, mNDKServer.startServer());
    }
}
