/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
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

#import <UIKit/UIKit.h>
//#import "GDTMobBannerView.h"
//#import "GDTMobInterstitial.h"
#import "TencentOpenAPI/QQApiInterface.h"
#import <TencentOpenAPI/TencentOAuth.h>

#define AD_APPID @"1104491098"
#define AD_BAR @"2010700215264654"
#define AD_INTERSTITIAL @"9050509225660685"

#define APP_URL @"http://www.pingames.cn/share/index.html"
#define APP_TITLE @"水滴物语,打发休闲时间的神器"

#define TCSafeRelease(__tcObj) { [__tcObj release]; __tcObj = nil; }

@interface RootViewController : UIViewController<QQApiInterfaceDelegate,TencentSessionDelegate> { //GDTMobInterstitialDelegate, GDTMobBannerViewDelegate
    
}

//@property(nonatomic, retain) GDTMobBannerView *bannerView;//声明⼀一个GDTMobBannerView的实例
//@property(nonatomic, retain) GDTMobInterstitial *interstitialObj;

+ (RootViewController*) shareRootViewController;

- (BOOL) prefersStatusBarHidden;

- (void) showAdBar;
- (void) hidenAdBar;

- (void) loadAdInterstitial;
- (void) showAdInterstitial;

- (void) sendNewsMessageWithNetworkImage;


@end
