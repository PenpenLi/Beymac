package cn.pingames.beymac.pay;

import android.app.Activity;
import android.telephony.TelephonyManager;
import cn.pingames.beymac.MainActivity;
import cn.pingames.beymac.pay.strategy.MobilePay;
import cn.pingames.beymac.pay.strategy.TelecomPay;
import cn.pingames.beymac.pay.strategy.UnicomPay;

public class Payment {

	// 单例
	private static Payment payInstance;

	private Activity activity;

	// 策略
	PaymentStrategy absPay;

	public static void init(Activity activity) {
		if (activity != null) {
			payInstance = new Payment(activity);
		} else {
			System.out.println("activity is null");
		}
	}

	private Payment(Activity activity) {
		this.activity = activity;
		TelephonyManager tm = (TelephonyManager) activity
				.getSystemService(Activity.TELEPHONY_SERVICE);
		String sim = tm.getSimOperator();
		if (sim.equals("46000") || sim.equals("46002")) {
			// 移动
			this.absPay = new MobilePay();
		} else if (sim.equals("46001")) {
			// 联通
			this.absPay = new UnicomPay();
		} else if (sim.equals("46003")) {
			// 电信
			this.absPay = new TelecomPay();
		}
	}

	public static Payment getInstance() {
		if (payInstance == null) {
			System.out.println("Payment isn't init.");
		}
		return payInstance;
	}

	public void pay(int itemId, int delegateId) {

		absPay.pay(itemId, delegateId, activity, new PaymentCallback() {

			@Override
			public void payResult(int itemId, int delegateId, int result) {
				System.out.println("支付结果:" + itemId + "," + delegateId + ","
						+ result);
				// 回调给mainActivity
				MainActivity.paySucceed(result, itemId, delegateId);
			}
		});
	}

}
