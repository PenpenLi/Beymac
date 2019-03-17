package cn.pingames.beymac;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class LoadActivity extends Activity {

	static final int DELAY_TIME = 1500;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_load);
		
		new Handler().postDelayed(new Runnable() {
			@Override
			public void run() {
				gotoMainActivity();
			}
		}, DELAY_TIME);

	}

	private void gotoMainActivity() {

		Intent intent = new Intent(LoadActivity.this, MainActivity.class);
		intent.setFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
		LoadActivity.this.startActivity(intent);
	}



}
