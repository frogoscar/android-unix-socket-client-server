package com.ercom.socket;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class Client1 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_client1);

        NDKClient1 mNDKClient1 = new NDKClient1();
        Log.i("MyTag", mNDKClient1.getMyString());
    }
}
