package com.enmingx.server;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.IOException;

public class Server extends AppCompatActivity {

    private Button btnStartServer;
    private static final String TAG = Server.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_server);

        btnStartServer = (Button)findViewById(R.id.start_server_button);

        NDKServer mNDKServer = new NDKServer();

        Log.i(TAG, mNDKServer.getMyString());

        String current = "";
        try {
            current = new java.io.File( "." ).getCanonicalPath();
        } catch (IOException e) {
            e.printStackTrace();
        }

        Log.i(TAG, "Current Path : " + current);

        btnStartServer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Server.this, ServerService.class);
                Server.this.startService(intent);
                Log.i(TAG, "Button clicked, started Server");
            }
        });
    }
}
