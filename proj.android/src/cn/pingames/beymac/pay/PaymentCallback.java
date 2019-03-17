package cn.pingames.beymac.pay;

public interface PaymentCallback {

	void payResult(int itemId, int delegateId,int result);
	
	
}
