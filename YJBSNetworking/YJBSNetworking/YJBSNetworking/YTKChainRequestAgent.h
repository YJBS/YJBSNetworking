//
//  YTKChainRequestAgent.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "YTKChainRequest.h"

/// ChainRequestAgent is used for caching & keeping current request.
@interface YTKChainRequestAgent : NSObject

+ (YTKChainRequestAgent *)sharedInstance;

- (void)addChainRequest:(YTKChainRequest *)request;

- (void)removeChainRequest:(YTKChainRequest *)request;


@end
