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

    private String source = "http://m7.music.126.net/20191210173138/469d91f29f12dd65fa2eb1b148549183/ymusic/0152/055a/5308/681ef6f50f20971ac5bddb07161fc6b5.mp3";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mPlayer = new Player();
        mPlayer.setSource("http://mpge.5nd.com/2015/2015-11-26/69708/1.mp3");
        //mPlayer.setSource(source);

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
