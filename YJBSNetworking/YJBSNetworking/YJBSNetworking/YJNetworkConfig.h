//
//  YJNetworkConfig.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFNetworking.h"


@class YJBaseRequest;
@protocol YTKUrlFilterProtocol <NSObject>
- (NSString *)filterUrl:(NSString *)originUrl withRequest:(YJBaseRequest *)request;
@end

@protocol YTKCacheDirPathFilterProtocol <NSObject>
- (NSString *)filterCacheDirPath:(NSString *)originPath withRequest:(YJBaseRequest *)request;
@end


@interface YJNetworkConfig : NSObject

+ (YJNetworkConfig *)sharedInstance;

@property (strong, nonatomic) NSString *baseUrl;
@property (strong, nonatomic) NSString *cdnUrl;
@property (strong, nonatomic, readonly) NSArray *urlFilters;
@property (strong, nonatomic, readonly) NSArray *cacheDirPathFilters;
@property (strong, nonatomic) AFSecurityPolicy *securityPolicy;

- (void)addUrlFilter:(id<YTKUrlFilterProtocol>)filter;
- (void)addCacheDirPathFilter:(id <YTKCacheDirPathFilterProtocol>)filter;



@end
