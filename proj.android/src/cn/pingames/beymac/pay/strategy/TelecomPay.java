package cn.pingames.beymac.pay.strategy;

import android.app.Activity;
import cn.pingames.beymac.pay.PaymentStrategy;
import cn.pingames.beymac.pay.PaymentCallback;

public class TelecomPay implements PaymentStrategy{

	@Override
	public void pay(int itemId, int delegateId, Activity activity,
			PaymentCallback callback) {

		System.out.println("电信支付结果:");
		
		callback.payResult(itemId, delegateId, 1);
		
	}

}
