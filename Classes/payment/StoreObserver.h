//
//  StoreObserver.h
//  HelloStore
//
//  Created by guoke on 13-8-4.
//  Copyright (c) 2013年 guoke. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StoreKit/StoreKit.h>
#import <StoreKit/SKPaymentTransaction.h>

class StoreDelegate {
public :
    virtual void payResult(bool result) = 0;
};


@interface StoreObserver : NSObject <SKPaymentTransactionObserver, SKProductsRequestDelegate>
{
    int buyType;
    NSString *ProductID;
}

@property (nonatomic) StoreDelegate* delegate;

-(void)Create;
-(void)Destroy;

-(void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
-(void)PurchasedTransaction: (SKPaymentTransaction *)transaction;
-(void)completeTransaction: (SKPaymentTransaction *)transaction;
-(void)failedTransaction: (SKPaymentTransaction *)transaction;
-(void)paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;
-(void)paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;

-(void)Buy:(int)type;
-(bool)CanMakePay;
-(void)RequestProductData;
-(void)restoreTransaction: (SKPaymentTransaction *)transaction;



@end