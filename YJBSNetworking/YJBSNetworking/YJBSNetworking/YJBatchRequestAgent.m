//
//  YJBatchRequestAgent.m
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import "YJBatchRequestAgent.h"

@interface YJBatchRequestAgent()

@property (strong, nonatomic) NSMutableArray *requestArray;

@end

@implementation YJBatchRequestAgent

+ (YJBatchRequestAgent *)sharedInstance {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}


- (id)init {
    self = [super init];
    if (self) {
        _requestArray = [NSMutableArray array];
    }
    return self;
}

- (void)addBatchRequest:(YTKBatchRequest *)request {
    @synchronized(self) {
        [_requestArray addObject:request];
    }
}

- (void)removeBatchRequest:(YTKBatchRequest *)request {
    @synchronized(self) {
        [_requestArray removeObject:request];
    }
}


@end
