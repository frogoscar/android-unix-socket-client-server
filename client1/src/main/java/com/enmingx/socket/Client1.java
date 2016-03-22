package com.enmingx.socket;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class Client1 extends AppCompatActivity {

    private Button btnConnectServer;
    private static final String TAG = Client1.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_client1);

        btnConnectServer = (Button)findViewById(R.id.connect_server_button);

        final NDKClient1 mNDKClient1 = new NDKClient1();

        Log.i(TAG, mNDKClient1.getMyString());

        btnConnectServer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i(TAG, "Button clicked");
                Log.i(TAG, mNDKClient1.connectServer());
            }
        });
    }
}
