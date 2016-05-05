//
//  YJBatchRequestAgent.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "YTKBatchRequest.h"

@interface YJBatchRequestAgent : NSObject

+ (YJBatchRequestAgent *)sharedInstance;

- (void)addBatchRequest:(YTKBatchRequest *)request;

- (void)removeBatchRequest:(YTKBatchRequest *)request;


@end
