//
//  YJNetworkAgent.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YJBaseRequest.h"
#import "AFNetworking.h"

@interface YJNetworkAgent : NSObject

+ (YJNetworkAgent *)sharedInstance;

- (void)addRequest:(YJBaseRequest *)request;

- (void)cancelRequest:(YJBaseRequest *)request;

- (void)cancelAllRequests;

/// 根据request和networkConfig构建url
- (NSString *)buildRequestUrl:(YJBaseRequest *)request;


@end
