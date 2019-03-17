package cn.pingames.beymac;

import android.app.Activity;
import android.os.Bundle;

import com.tencent.connect.share.QQShare;
import com.tencent.tauth.IUiListener;
import com.tencent.tauth.Tencent;
import com.tencent.tauth.UiError;

public class TencentShare {

	private static final String APP_ID = "1104668952";
	private static final String APP_KEY = "ofyqCzUSzYkWlj2g";
	private static final String APP_URL = "http://www.pingames.cn/waterwar/share/index.html";
	private static final String shareTitle = "超能力战队";
	private static final String shareContent = "超能力战士坎坷曲折的大冒险~";

	private static Tencent tx;

	public static void share(Activity act) {
		System.out.println("share sendNewsMessageWithNetworkImage");
		final Bundle params = new Bundle();
		params.putString(QQShare.SHARE_TO_QQ_TITLE, shareTitle);
		params.putString(QQShare.SHARE_TO_QQ_TARGET_URL, APP_URL);
		params.putString(QQShare.SHARE_TO_QQ_SUMMARY, shareContent);
		params.putString(QQShare.SHARE_TO_QQ_IMAGE_URL,
				"http://pingames.oss-cn-qingdao.aliyuncs.com/WaterWarIcon.png");
		// share
		tx=Tencent.createInstance(APP_ID, act.getApplicationContext());
		tx.shareToQQ(act, params, qqShareListener);
	}

	private static IUiListener qqShareListener = new IUiListener() {
		@Override
		public void onCancel() {
			System.out.println("share cancel");
		}

		@Override
		public void onComplete(Object arg0) {
			System.out.println("share complete");
		}

		@Override
		public void onError(UiError arg0) {
			System.out.println("share error");
		}
	};
}
