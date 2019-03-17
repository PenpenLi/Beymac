/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package cn.pingames.beymac;

import org.cocos2dx.lib.Cocos2dxActivity;

import cn.pingames.beymac.pay.Payment;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.telephony.TelephonyManager;

public class MainActivity extends Cocos2dxActivity {
	static MainActivity thisActivity;

	static String imei;

	// public static int number = 1;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		thisActivity = this;

		// imei
		TelephonyManager tm = (TelephonyManager) this
				.getSystemService(TELEPHONY_SERVICE);
		imei = tm.getDeviceId();
		System.out.println("tm:" + imei);

		// 初始化支付模块
		Payment.init(this);
	}

	public static int isNetworkConnected() {
		System.out.println("检查网络 in android");
		Context context = thisActivity;
		if (context != null) {
			ConnectivityManager connManager = (ConnectivityManager) context
					.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo netInfo = connManager.getActiveNetworkInfo();
			if (netInfo != null) {
				if (netInfo.isAvailable()) {
					return 1;
				} else {
					return 0;
				}
			}
		}
		return 0;
	}

	// 支付
	public static void pay(int itemId, int delegateId) {
		Payment.getInstance().pay(itemId, delegateId);

		// if(number==1){
		// System.out.println("调用移动支付");
		// }else if (number==2) {
		// System.out.println("调用联通支付");
		// }else if (number==3) {
		// System.out.println("调用电信支付");
		// }
	}

	native public static void paySucceed(int succeed, int itemId, int delegateId);

	public static void onCocosPause() {
		System.out.println("cocos call to pause");
	}

	public static void onCocosExit() {
		System.out.println("cocos call to exit");
		// System.exit(0);
	}

	private static String getIMEI() {
		System.out.println("getting imei in android.");
		return imei;
	}

	public static void sendNewsMessageWithNetworkImage() {
		System.out.println("QQ分享");
		TencentShare.share(thisActivity);
	}
}
