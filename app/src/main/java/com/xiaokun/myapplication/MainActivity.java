package com.xiaokun.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.xiaokun.myplayer.Demo;
import com.xiaokun.myplayer.FOnPrepareListener;
import com.xiaokun.myplayer.Player;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    private Player mPlayer;

    private String source = "http://ws.stream.qqmusic.qq.com/M5000020VnHM0U9uNh.mp3?guid=659972215&vkey=208810730C71B5A11024D35EBCC467D4A4C5A35A1CE91D194D56FC37B865916DF36A55543C111DB8D4E19E46EA52EAA8D77D76E5F71A6A2E&uin=0&fromtag=66";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mPlayer = new Player();
        mPlayer.setSource(source);

        mPlayer.setFOnPrepareListener(new FOnPrepareListener() {
            @Override
            public void onPrepare() {
                Log.d(TAG, "[onPrepare] " + Thread.currentThread().getName());
                Log.d(TAG, "[onPrepare] 准备好了,开始解码");
                mPlayer.start();
            }
        });
    }

    public void begin(View view) {
        if (mPlayer != null) {
            mPlayer.prepared();
        }
    }
}
