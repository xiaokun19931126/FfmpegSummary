package com.xiaokun.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.xiaokun.myplayer.Demo;

public class MainActivity extends AppCompatActivity {

    private Demo demo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        demo = new Demo();

        demo.testFFmpeg();

        TextView tv = findViewById(R.id.sample_text);
        //tv.setText(demo.stringFromJNI());
    }


}
