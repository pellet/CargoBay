// CargoBay.h
//
// Copyright (c) 2012 Mattt Thompson (http://mattt.me/)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

//@class AFHTTPClient;

typedef void (^CargoBayPaymentQueueProductSuccessBlock)(NSArray *products, NSArray *invalidIdentifiers);
typedef void (^CargoBayPaymentQueueProductFailureBlock)(NSError *error);
typedef void (^CargoBayPaymentQueueTransactionsBlock)(SKPaymentQueue *queue, NSArray *transactions);
typedef void (^CargoBayPaymentQueueRestoreSuccessBlock)(SKPaymentQueue *queue);
typedef void (^CargoBayPaymentQueueRestoreFailureBlock)(SKPaymentQueue *queue, NSError *error);

@interface CargoBay : NSObject <SKPaymentTransactionObserver> {
@private
//    AFHTTPClient *_receiptVerificationClient;
    
    CargoBayPaymentQueueTransactionsBlock _paymentQueueTransactionsUpdated;
    CargoBayPaymentQueueTransactionsBlock _paymentQueueTransactionsRemoved;
    CargoBayPaymentQueueRestoreSuccessBlock _paymentQueueRestoreSuccessBlock;
    CargoBayPaymentQueueRestoreFailureBlock _paymentQueueRestoreFailureBlock;
}

//@property (nonatomic) AFHTTPClient *productsHTTPClient;

+ (CargoBay *)sharedManager;

///---------------------
/// @name Product Lookup
///---------------------

- (void)productsWithIdentifiers:(NSSet *)identifiers
                        success:(void (^)(NSArray *products, NSArray *invalidIdentifiers))success
                        failure:(void (^)(NSError *error))failure;

//- (void)productsWithRequest:(NSURLRequest *)request
//                    success:(void (^)(NSArray *products, NSArray *invalidIdentifiers))success
//                    failure:(void (^)(NSError *error))failure;

///-------------------------------
/// @name Product Purchase
///-------------------------------

- (BOOL)purchaseProduct:(SKProduct *)product;

- (void)finishTransaction:(SKPaymentTransaction *)transaction;

///-------------------------------
/// @name Transaction Verification
///-------------------------------

//- (void)verifyTransaction:(SKPaymentTransaction *)transaction
//                  success:(void (^)(NSDictionary *receipt))success
//                  failure:(void (^)(NSError *error))failure;

///--------------------------------------------------
/// @name Transaction Queue Observer Delegate Methods
///--------------------------------------------------

- (void)setPaymentQueueUpdatedTransactionsBlock:(void (^)(SKPaymentQueue *queue, NSArray *transactions))block;

- (void)setPaymentQueueRemovedTransactionsBlock:(void (^)(SKPaymentQueue *queue, NSArray *transactions))block;

- (void)setPaymentQueueRestoreCompletedTransactionsWithSuccess:(void (^)(SKPaymentQueue *queue))success
                                                       failure:(void (^)(SKPaymentQueue *queue, NSError *error))failure;

@end

///----------------
/// @name Constants
///----------------

extern NSString * const CargoBarErrorDomain;
