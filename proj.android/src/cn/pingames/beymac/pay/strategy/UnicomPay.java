package cn.pingames.beymac.pay.strategy;

import android.app.Activity;
import cn.pingames.beymac.pay.PaymentStrategy;
import cn.pingames.beymac.pay.PaymentCallback;

public class UnicomPay implements PaymentStrategy {

	@Override
	public void pay(int itemId, int delegateId, Activity activity,
			PaymentCallback callback) {
		
		System.out.println("联通支付结果:");
		
		callback.payResult(itemId, delegateId, 1);
		
	}

}
