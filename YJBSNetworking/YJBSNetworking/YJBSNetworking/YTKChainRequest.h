//
//  YTKChainRequest.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "YJBaseRequest.h"

@class YTKChainRequest;
@protocol YTKChainRequestDelegate <NSObject>

@optional

- (void)chainRequestFinished:(YTKChainRequest *)chainRequest;

- (void)chainRequestFailed:(YTKChainRequest *)chainRequest failedBaseRequest:(YJBaseRequest *)request;

@end

typedef void (^ChainCallback)(YTKChainRequest *chainRequest, YJBaseRequest *baseRequest);

@interface YTKChainRequest : NSObject

@property (weak, nonatomic) id<YTKChainRequestDelegate> delegate;

@property (nonatomic, strong) NSMutableArray *requestAccessories;

/// start chain request
- (void)start;

/// stop chain request
- (void)stop;

- (void)addRequest:(YJBaseRequest *)request callback:(ChainCallback)callback;

- (NSArray *)requestArray;

/// Request Accessory，可以hook Request的start和stop
- (void)addAccessory:(id<YJBaseRequestAccessory>)accessory;


@end
