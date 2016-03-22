package com.enmingx.client2;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class Client2 extends AppCompatActivity {

    private Button btnConnectServer;

    private static final String TAG = Client2.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_client2);

        btnConnectServer = (Button)findViewById(R.id.connect_server_button);

        final NDKClient2 mNDKClient2 = new NDKClient2();

        Log.i(TAG, mNDKClient2.getMyString());

        btnConnectServer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i(TAG, "Button clicked");
                Log.i(TAG, mNDKClient2.connectServer());
            }
        });
    }
}
