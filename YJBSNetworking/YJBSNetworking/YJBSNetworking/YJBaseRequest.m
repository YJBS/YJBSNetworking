//
//  YJBaseRequest.m
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import "YJBaseRequest.h"
#import "YJNetworkPrivate.h"
#import "YJNetworkAgent.h"

@implementation YJBaseRequest

#pragma mark - 子类重写方法
- (void)requestCompleteFilter {
}

- (void)requestFailedFilter {
}

- (NSString *)requestUrl {
    return @"";
}

- (NSString *)cdnUrl {
    return @"";
}

- (NSString *)baseUrl {
    return @"";
}

- (NSTimeInterval)requestTimeoutInterval {
    return 60;
}

- (id)requestArgument {
    return nil;
}

- (id)cacheFileNameFilterForRequestArgument:(id)argument {
    return argument;
}

- (YJRequestMethod)requestMethod {
    return YJRequestMethodGET;
}

- (YJRequestSerializerType)requestSerializerType {
    return YJRequestSerializerTypeHTTP;
}

- (NSArray *)requestAuthorizationHeaderFieldArray {
    return nil;
}

- (NSDictionary *)requestHeaderFieldValueDictionary {
    return nil;
}

- (NSURLRequest *)buildCustomUrlRequest {
    return nil;
}

- (BOOL)useCDN {
    return NO;
}

- (id)jsonValidator {
    return nil;
}

- (BOOL)statusCodeValidator {
    NSInteger statusCode = [self responseStatusCode];
    if (statusCode >= 200 && statusCode <= 299) {
        return YES;
    } else {
        return NO;
    }
}

- (AFConstructingBlock)constructingBodyBlock {
    return nil;
}

- (NSString *)resumableDownloadPath {
    return nil;
}

- (AFDownloadProgressBlock)resumableDownloadProgressBlock {
    return nil;
}

/**
 *  请求开始
 */
- (void)start {
    [self toggleAccessoriesWillStartCallBack];
    [[YJNetworkAgent sharedInstance] addRequest:self];
}

- (void)stop {
    [self toggleAccessoriesWillStopCallBack];
    self.delegate = nil;
    [[YJNetworkAgent sharedInstance] cancelRequest:self];
    [self toggleAccessoriesDidStopCallBack];
}

- (BOOL)isCancelled {
    return self.requestOperation.isCancelled;
}

- (BOOL)isExecuting {
    return self.requestOperation.isExecuting;
}

- (void)startWithCompletionBlockWithSuccess:(YJRequestCompletionBlock)success
                                    failure:(YJRequestCompletionBlock)failure {
    [self setCompletionBlockWithSuccess:success failure:failure];
    [self start];
}

- (void)setCompletionBlockWithSuccess:(YJRequestCompletionBlock)success
                              failure:(YJRequestCompletionBlock)failure {
    self.successCompletionBlock = success;
    self.failureCompletionBlock = failure;
}

- (void)clearCompletionBlock {
    // nil out to break the retain cycle.
    self.successCompletionBlock = nil;
    self.failureCompletionBlock = nil;
}

- (id)responseJSONObject {
    return self.requestOperation.responseObject;
}

- (NSData *)responseData {
    return self.requestOperation.responseData;
}

- (NSString *)responseString {
    return self.requestOperation.responseString;
}

- (NSInteger)responseStatusCode {
    return self.requestOperation.response.statusCode;
}


- (NSDictionary *)responseHeaders {
    return self.requestOperation.response.allHeaderFields;
}

- (NSError *)requestOperationError {
    return self.requestOperation.error;
}

#pragma mark - Request Accessories

- (void)addAccessory:(id<YJBaseRequestAccessory>)accessory {
    if (!self.requestAccessories) {
        self.requestAccessories = [NSMutableArray array];
    }
    [self.requestAccessories addObject:accessory];
}

@end
