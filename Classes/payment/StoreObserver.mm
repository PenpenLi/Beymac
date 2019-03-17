//
//  StoreObserver.m
//  HelloStore
//
//  Created by guoke on 13-8-4.
//  Copyright (c) 2013年 guoke. All rights reserved.
//
#import "StoreObserver.h"

//#define ProductID @"cn.pingames.waterwars.6"	// 产品ID，对应iTunes Connect中设置的产品ID

@implementation StoreObserver

-(void)Create
{
    //---------------------
    //----监听购买结果
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
}

-(void)Destroy
{
    //解除监听
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
}

-(void)Buy:(int)type
{
    NSLog(@"--- buy ---");
    buyType = type;
    ProductID = @"cn.pingames.beymac.";
    
    //1 crystal1   cn.pingames.beymac.crystal1
    //2 crystal2   cn.pingames.beymac.crystal2
    //3 crystal3   cn.pingames.beymac.crystal3
    //4 gift   cn.pingames.beymac.gift
    //5 mysteryshop1   cn.pingame…ymac.mysteryshop1
    //6 mysteryshop2   cn.pingame…ymac.mysteryshop2
    //7 phoenix   cn.pingames.phoenix
    //8 power1   cn.pingames.beymac.power1
    //9 power2   cn.pingames.beymac.power2
    //10 power3   cn.pingames.beymac.power3
    //11 rolefulllevel   cn.pingame…mac.rolefulllevel
    //12 skillfulllevel   cn.pingame…ac.skillfulllevel
    //13 unlocklevel   cn.pingame…eymac.unlocklevel
    //14 unlockrole   cn.pingame…beymac.unlockrole
    //15 unlockskill   cn.pingame…eymac.unlockskill
    
    switch (type) {
        case 1:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"crystal1"];
            break;
        case 2:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"crystal2"];
            break;
        case 3:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"crystal3"];
            break;
        case 4:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"gift"];
            break;
        case 5:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"mysteryshop1"];
            break;
        case 6:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"mysteryshop2"];
            break;
        case 7:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"phoenix"];
            break;
        case 8:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"power1"];
            break;
        case 9:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"power2"];
            break;
        case 10:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"power3"];
            break;
        case 11:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"rolefulllevel"];
            break;
        case 12:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"skillfulllevel"];
            break;
        case 13:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"unlocklevel"];
            break;
        case 14:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"unlockrole"];
            break;
        case 15:
            ProductID = [NSString stringWithFormat:@"%@%@",ProductID,@"unlockskill"];
            break;
        default:
            break;
    }
    
    
    
    if ([self CanMakePay])
    {
        NSLog(@"允许程序内付费购买");
        [self RequestProductData];
    }
    else
    {
        NSLog(@"不允许程序内付费购买");        
    }
//    _delegate->payResult(true);
}

-(bool)CanMakePay
{
    return [SKPaymentQueue canMakePayments];
}

-(void)RequestProductData
{
    NSLog(@"---------请求对应的产品信息------------");
    NSArray *product = nil;

    // 这时可以根据buyType不同选择不同的商品，这个只是测试，只用了一种
    product=[[NSArray alloc] initWithObjects:ProductID,nil];

    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate=self;
    [request start];
}

//<SKProductsRequestDelegate> 请求协议
//收到的产品信息
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    
    NSLog(@"-----------收到产品反馈信息--------------");
    NSArray *myProduct = response.products;
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    NSLog(@"产品付费数量: %lu", (unsigned long)[myProduct count]);
    // populate UI
    for(SKProduct *product in myProduct){
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
        SKPayment *payment = nil;
        //    payment  = [SKPayment paymentWithProductIdentifier:ProductID];
        payment = [SKPayment paymentWithProduct:product];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
    
    NSLog(@"---------发送购买请求------------");
}
- (void)requestProUpgradeProductData
{
    NSLog(@"------请求升级数据---------");
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.productid"];
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
    
}
//弹出错误信息
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    NSLog(@"-------弹出错误信息----------");
}

-(void) requestDidFinish:(SKRequest *)request
{
    NSLog(@"----------反馈信息结束--------------");
//    _delegate->payResult(false);
}

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@"-----PurchasedTransaction----");
    NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
    [self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
}

//<SKPaymentTransactionObserver> 千万不要忘记绑定，代码如下：
//----监听购买结果
//[[SKPaymentQueue defaultQueue] addTransactionObserver:self];

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果
{
    NSLog(@"-----paymentQueue--------");
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://交易完成
                [self completeTransaction:transaction];
                NSLog(@"-----交易完成 --------");
                break;
            case SKPaymentTransactionStateFailed://交易失败
                [self failedTransaction:transaction];
                NSLog(@"-----交易失败 --------");
                _delegate->payResult(false);
                [self Destroy];
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                [self restoreTransaction:transaction];
                NSLog(@"-----已经购买过该商品 --------");
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表
                NSLog(@"-----商品添加进列表 --------");
                break;
            default:
                break;
        }
    }
}
- (void) completeTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@"-----completeTransaction--------");

    // 接受到的App Store验证字符串，这里需要经过JSON编码
    NSString* jsonObjectString = [self encode:(uint8_t *)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];

    // 以下为测试POST到itunes上验证，正常来说，装jsonObjectString发给服务器，由服务器来完成验证
    NSString* sendString = [[NSString alloc] initWithFormat:@"{\"receipt-data\":\"%@\"}",jsonObjectString];
    NSURL *sandboxStoreURL = [[NSURL alloc] initWithString: @"https://sandbox.itunes.apple.com/verifyReceipt"];
	NSData *postData = [NSData dataWithBytes:[sendString UTF8String] length:[sendString length]];
	NSMutableURLRequest *connectionRequest = [NSMutableURLRequest requestWithURL:sandboxStoreURL];
	[connectionRequest setHTTPMethod:@"POST"];
	[connectionRequest setTimeoutInterval:120.0];
	[connectionRequest setCachePolicy:NSURLRequestUseProtocolCachePolicy];
	[connectionRequest setHTTPBody:postData];
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
	
	
    [[NSURLConnection alloc] initWithRequest:connectionRequest delegate:self];
    
    // Your application should implement these two methods.
    NSString *product = transaction.payment.productIdentifier;
    if ([product length] > 0)
    {
        NSArray *tt = [product componentsSeparatedByString:@"."];
        NSString *bookid = [tt lastObject];
        if([bookid length] > 0)
        {
            NSLog(@"bookid:%@",bookid);
        }
    }
    
    // Remove the transaction from the payment queue.
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@"失败");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
    }
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
}
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction
{
    
}

- (void) restoreTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@" 交易恢复处理");
    
}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
    NSLog(@"-------paymentQueue----");
}

// JSON编码
- (NSString *)encode:(const uint8_t *)input length:(NSInteger)length
{
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData *data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t *output = (uint8_t *)data.mutableBytes;
    
    for (NSInteger i = 0; i < length; i += 3) {
        NSInteger value = 0;
        for (NSInteger j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger index = (i / 3) * 4;
        output[index + 0] =                    table[(value >> 18) & 0x3F];
        output[index + 1] =                    table[(value >> 12) & 0x3F];
        output[index + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[index + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
}

// 以下是HTTP协议的监听，若由服务器验证，可不用这段代码
#pragma mark connection delegate
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    NSLog(@"回调: %@",  [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
    NSDictionary *dict=[NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableLeaves error:nil];
    NSLog(@"status : %@",[dict objectForKey:@"status"]);
    
    //0是成功
    if (_delegate) {
        if ([[NSString stringWithFormat:@"%@",[dict objectForKey:@"status"]] isEqual:@"0"]) {
            _delegate->payResult(true);
        } else {
            _delegate->payResult(false);
        }
        
    }
    [self Destroy];
    
}
- (void)connectionDidFinishLoading:(NSURLConnection *)connection{
    
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response{
    switch([(NSHTTPURLResponse *)response statusCode]) {
        case 200:
        case 206:
            break;
        case 304:
            break;
        case 400:
            break;
        case 404:
            break;
        case 416:
            break;
        case 403:
            break;
        case 401:
        case 500:
            break;
        default:
            break;
    }
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    NSLog(@"test");
}

@end