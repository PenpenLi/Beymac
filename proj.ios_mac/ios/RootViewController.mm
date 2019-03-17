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

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"


@implementation RootViewController






static RootViewController* rootViewController = nil;
//static NSString *INTERSTITIAL_STATE_TEXT = @"插屏状态";

/**/
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    NSLog(@"initWithNibName");
    
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
//        /*
//         * 创建Banner⼲⼴广告View
//         * "appkey" 指在 http://e.qq.com/dev/ 能看到的app唯⼀一字符串
//         * "placementId" 指在 http://e.qq.com/dev/ ⽣生成的数字串,⼲⼴广告位id *
//         * banner条的宽度开发者可以进⾏行⼿手动设置,⽤用以满⾜足开发场景需求或是适配最新版本的iphone
//         * banner条的⾼高度⼲⼴广点通侧强烈建议开发者采⽤用推荐的⾼高度,否则显⽰示效果会有影响
//         * ⼲⼴广点通提供3种尺⼨寸供开发者在不同设别上使⽤用,这⾥里以320*50为例 */
//        _bannerView = [[GDTMobBannerView alloc]
//                       initWithFrame:CGRectMake(0, 0,
//                                                GDTMOB_AD_SUGGEST_SIZE_320x50.width,
//                                                GDTMOB_AD_SUGGEST_SIZE_320x50.height) appkey:AD_APPID
//                       placementId:AD_BAR];
//        
//        _bannerView.delegate = self;
//        // 设置Delegate
//        _bannerView.currentViewController = self; //设置当前的ViewController
//        _bannerView.interval = 30;                  //【可选】设置刷新频率;默认30秒
//        _bannerView.isGpsOn = NO;                   //【可选】开启GPS定位;默认关闭
//        _bannerView.showCloseBtn = YES;
//        //【可选】展⽰示关闭按钮;默认显⽰示
//        _bannerView.isAnimationOn = YES;
//        
//        [_bannerView setFrame:CGRectMake(0,  ([[UIScreen mainScreen] bounds].size.height-GDTMOB_AD_SUGGEST_SIZE_320x50.height), GDTMOB_AD_SUGGEST_SIZE_320x50.width, GDTMOB_AD_SUGGEST_SIZE_320x50.height)];
//        //【可选】开启banner轮播和展现时的动画效果;默认开启
////        [self.view addSubview:_bannerView]; //添加到当前的view中
//        
//        [_bannerView loadAdAndShow];
        
//        [self loadAdInterstitial];
        
//        [[self.view superview] addSubview:_bannerView];

        NSDictionary *infoDictionary =[[NSBundle mainBundle]infoDictionary];
        NSLog(@"%@",[infoDictionary objectForKey:@"CFBundleIdentifier"]);
        if ([[infoDictionary objectForKey:@"CFBundleIdentifier"] isEqual:@"cn.pingames.water"]) {
            NSLog(@"info true");
        } else {
            NSLog(@"info false");
        }
//        [[ addSubview:_bannerView];
        //加载⼲⼴广告并展⽰示
        [self initQQOAuth];
    }
    
    if (!rootViewController) {
        rootViewController = self;
    }
    
    return self;
}


// 请求广告条数据成功后调用
//
// 详解:当接收服务器返回的广告数据成功后调用该函数
- (void)bannerViewDidReceived
{
    NSLog(@"%s",__FUNCTION__);
}

/*
 Implement loadView to create a view hierarchy programmatically, without using a nib.
*/
- (void)loadView {
    NSLog(@"loadView");
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    NSLog(@"viewDidLoad");
    
}


// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
//    _bannerView.delegate = nil;
//    _bannerView.currentViewController = nil;
//    _bannerView = nil;
}

- (void) showAdBar {
//    UIWindow *window =  [UIApplication sharedApplication].keyWindow;
//    if (!window) {
//        window = [[UIApplication sharedApplication].windows objectAtIndex:0];
//    }
//    
//    [window addSubview:_bannerView];

}

- (void) hidenAdBar {
    NSLog(@"隐藏广告条");
//    [_bannerView removeFromSuperview];
}



+ (RootViewController*) shareRootViewController
{
    return rootViewController;
}


///**
// *  广告预加载成功回调
// *  详解:当接收服务器返回的广告数据成功后调用该函数
// */
//- (void)interstitialSuccessToLoadAd:(GDTMobInterstitial *)interstitial
//{
//    NSLog(@"%@:%@",INTERSTITIAL_STATE_TEXT,@"Success Loaded.");
//}
//
//
/**
 * 在适当的时候,初始化并调⽤用loadAd⽅方法进⾏行预加载 */
- (void)loadAdInterstitial {
    NSLog(@"预加载");
//    _interstitialObj = [[GDTMobInterstitial alloc] initWithAppkey:AD_APPID placementId:AD_INTERSTITIAL];
//    _interstitialObj.delegate = self; //设置委托
//    _interstitialObj.isGpsOn = NO; //【可选】设置GPS开关
//    //预加载广告
//    [_interstitialObj loadAd];
}

- (void) showAdInterstitial {
//    UIViewController *vc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
//    [_interstitialObj presentFromRootViewController:vc];
}

/*
 * QQ分享相关
 *
 */

- (void) sendNewsMessageWithNetworkImage
{
    NSLog(@"sendNewsMessageWithNetworkImage");
    
    NSURL *previewURL = [NSURL URLWithString:@"http://pingames.oss-cn-qingdao.aliyuncs.com/WaterWarIcon.png"];
    NSURL* url = [NSURL URLWithString:@"http://www.pingames.cn/waterwar/share/index.html"];
    
    QQApiNewsObject* img = [QQApiNewsObject objectWithURL:url title:@"水滴物语~快来帮我回家吧~" description:@"小水滴回家路上坎坷曲折的大冒险~" previewImageURL:previewURL];
    SendMessageToQQReq* req = [SendMessageToQQReq reqWithContent:img];
    
    QQApiSendResultCode sent = [QQApiInterface sendReq:req];
    [self handleSendResult:sent];
}

- (void) initQQOAuth
{
    [[TencentOAuth alloc] initWithAppId:@"1104440271" andDelegate:self];
}




- (void)handleSendResult:(QQApiSendResultCode)sendResult
{
    switch (sendResult)
    {
        case EQQAPIAPPNOTREGISTED:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"App未注册" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
            [msgbox release];
            
            break;
        }
        case EQQAPIMESSAGECONTENTINVALID:
        case EQQAPIMESSAGECONTENTNULL:
        case EQQAPIMESSAGETYPEINVALID:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"发送参数错误" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
            [msgbox release];
            
            break;
        }
        case EQQAPIQQNOTINSTALLED:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"未安装手Q" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
            [msgbox release];
            
            break;
        }
        case EQQAPIQQNOTSUPPORTAPI:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"API接口不支持" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
            [msgbox release];
            
            break;
        }
        case EQQAPISENDFAILD:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"发送失败" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
            [msgbox release];
            
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 * 登录成功后的回调
 */
- (void)tencentDidLogin {
    
}

/**
 * 登录失败后的回调
 * \param cancelled 代表用户是否主动退出登录
 */
- (void)tencentDidNotLogin:(BOOL)cancelled {
    
}

/**
 * 登录时网络有问题的回调
 */
- (void)tencentDidNotNetWork {
    
}

/**
 处理来至QQ的请求
 */
- (void)onReq:(QQBaseReq *)req {
    switch (req.type)
    {
        case EGETMESSAGEFROMQQREQTYPE:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 处理来至QQ的响应
 */
- (void)onResp:(QQBaseResp *)resp {
    switch (resp.type)
    {
        case ESENDMESSAGETOQQRESPTYPE:
        {
            SendMessageToQQResp* sendResp = (SendMessageToQQResp*)resp;
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:sendResp.result message:sendResp.errorDescription delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 处理QQ在线状态的回调
 */
- (void)isOnlineResponse:(NSDictionary *)response {
    
}

@end
