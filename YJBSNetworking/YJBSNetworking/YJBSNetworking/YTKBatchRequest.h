//
//  YTKBatchRequest.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YJRequest.h"

@class YTKBatchRequest;
@protocol YTKBatchRequestDelegate <NSObject>

@optional

- (void)batchRequestFinished:(YTKBatchRequest *)batchRequest;

- (void)batchRequestFailed:(YTKBatchRequest *)batchRequest;

@end

@interface YTKBatchRequest : NSObject

@property (strong, nonatomic, readonly) NSArray *requestArray;

@property (weak, nonatomic) id<YTKBatchRequestDelegate> delegate;

@property (nonatomic, copy) void (^successCompletionBlock)(YTKBatchRequest *);

@property (nonatomic, copy) void (^failureCompletionBlock)(YTKBatchRequest *);

@property (nonatomic) NSInteger tag;

@property (nonatomic, strong) NSMutableArray *requestAccessories;

- (id)initWithRequestArray:(NSArray *)requestArray;

- (void)start;

- (void)stop;

/// block回调
- (void)startWithCompletionBlockWithSuccess:(void (^)(YTKBatchRequest *batchRequest))success
                                    failure:(void (^)(YTKBatchRequest *batchRequest))failure;

- (void)setCompletionBlockWithSuccess:(void (^)(YTKBatchRequest *batchRequest))success
                              failure:(void (^)(YTKBatchRequest *batchRequest))failure;

/// 把block置nil来打破循环引用
- (void)clearCompletionBlock;

/// Request Accessory，可以hook Request的start和stop
- (void)addAccessory:(id<YJBaseRequestAccessory>)accessory;

/// 是否当前的数据从缓存获得
- (BOOL)isDataFromCache;


@end
