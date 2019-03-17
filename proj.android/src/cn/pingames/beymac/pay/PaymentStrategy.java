package cn.pingames.beymac.pay;

import android.app.Activity;

public interface PaymentStrategy {

	public void pay(int itemId, int delegateId,Activity activity,PaymentCallback callback);
	
}
