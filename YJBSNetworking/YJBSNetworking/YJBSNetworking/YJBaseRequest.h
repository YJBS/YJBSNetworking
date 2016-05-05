//
//  YJBaseRequest.h
//  YJBSNetworking
//
//  Created by YJHou on 16/5/5.
//  Copyright © 2016年 ismonkey.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFNetworking.h"
#import "AFDownloadRequestOperation.h"

/** 请求方式 */
typedef NS_ENUM(NSInteger, YJRequestMethod){
    YJRequestMethodGET    = 0,
    YJRequestMethodPOST   = 1 << 0,
    YJRequestMethodPUT    = 1 << 1,
    YJRequestMethodDELETE = 1 << 2,
    YJRequestMethodHEAD   = 1 << 3,
    YJRequestMethodPATCH  = 1 << 4
};

/** 请求类型 */
typedef NS_ENUM(NSInteger, YJRequestSerializerType){
    YJRequestSerializerTypeHTTP = 0,
    YJRequestSerializerTypeJSON = 1 << 0
};

/** 优先级 */
typedef NS_ENUM (NSInteger, YJRequestPriority){
    YJRequestPriorityLOW     = -4L,
    YJRequestPriorityDefault = 0,
    YJRequestPriorityHIGH    = 4
};

@class YJBaseRequest;
/** 相关Block 区 */
typedef void(^YJRequestCompletionBlock)(__kindof YJBaseRequest *request);
typedef void (^AFConstructingBlock)(id<AFMultipartFormData> formData);
typedef void (^AFDownloadProgressBlock)(AFDownloadRequestOperation *operation, NSInteger bytesRead, long long totalBytesRead, long long totalBytesExpected, long long totalBytesReadForFile, long long totalBytesExpectedToReadForFile);

/** 代理方法 */
@protocol YJBaseRequestDelegate <NSObject>

@optional

- (void)requestFinished:(YJBaseRequest *)request;
- (void)requestFailed:(YJBaseRequest *)request;
- (void)clearRequest;

@end

@protocol YJBaseRequestAccessory <NSObject>

@optional

- (void)requestWillStart:(id)request;
- (void)requestWillStop:(id)request;
- (void)requestDidStop:(id)request;

@end

@interface YJBaseRequest : NSObject

/** 请求的标记Tag */
@property (nonatomic) NSInteger tag;

/** 用户信息 */
@property (nonatomic, strong) NSDictionary * userInfo;

/** AFN 请求操作 */
@property (nonatomic, strong) AFHTTPRequestOperation *requestOperation;

@property (nonatomic, weak) id<YJBaseRequestDelegate> delegate;

/** 请求头 */
@property (nonatomic, strong, readonly) NSDictionary * responseHeaders;

/** 返回状态码 */
@property (nonatomic, readonly) NSInteger responseStatusCode;

/** 返回NSData */
@property (nonatomic, strong, readonly) NSData * responseData;

/** 返回 JSONString */
@property (nonatomic, strong, readonly) NSString * responseString;

/** 返回 JSONObject */
@property (nonatomic, strong, readonly) id responseJSONObject;

/** 请求错误 */
@property (nonatomic, strong, readonly) NSError * requestOperationError;

@property (nonatomic, copy) YJRequestCompletionBlock successCompletionBlock;

@property (nonatomic, copy) YJRequestCompletionBlock failureCompletionBlock;

/** 请求附件参数 */
@property (nonatomic, strong) NSMutableArray * requestAccessories;

/** 请求的优先级 */
@property (nonatomic) YJRequestPriority requestPriority;

/** 返回请求的取消状态 */
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;

// ******************* 方法区 ************************

/** 开始 (添加到请求队列中去) */
- (void)start;

/** 停止请求 (从请求队列中移除) */
- (void)stop;

/** 返回正在执行 */
- (BOOL)isExecuting;


- (void)startWithCompletionBlockWithSuccess:(YJRequestCompletionBlock)success
                                    failure:(YJRequestCompletionBlock)failure;

- (void)setCompletionBlockWithSuccess:(YJRequestCompletionBlock)success
                              failure:(YJRequestCompletionBlock)failure;

/** 清除Block 避免循环引用 */
- (void)clearCompletionBlock;

/** 请求的开始和停止 */
- (void)addAccessory:(id<YJBaseRequestAccessory>)accessory;

// ******** 之类中实现 *************

/** 请求成功的回调 */
- (void)requestCompleteFilter;

/** 请求失败的回调 */
- (void)requestFailedFilter;

/** 请求的URL */
- (NSString *)requestUrl;

/** 请求的CdnURL */
- (NSString *)cdnUrl;

/** 请求的BaseURL */
- (NSString *)baseUrl;

/** 请求的连接超时时间，默认为60秒 */
- (NSTimeInterval)requestTimeoutInterval;

/** 请求的参数列表 */
- (id)requestArgument;

/** 用于在cache结果，计算cache文件名时，忽略掉一些指定的参数 */
- (id)cacheFileNameFilterForRequestArgument:(id)argument;

/** Http请求的方法 */
- (YJRequestMethod)requestMethod;

/** 请求的SerializerType */
- (YJRequestSerializerType)requestSerializerType;

/** 请求的Server用户名和密码 */
- (NSArray *)requestAuthorizationHeaderFieldArray;

/** 在HTTP报头添加的自定义参数 */
- (NSDictionary *)requestHeaderFieldValueDictionary;

/// 构建自定义的UrlRequest，
/// 若这个方法返回非nil对象，会忽略requestUrl, requestArgument, requestMethod, requestSerializerType
- (NSURLRequest *)buildCustomUrlRequest;

/** 是否使用CDN的host地址 */
- (BOOL)useCDN;

/** 用于检查JSON是否合法的对象 */
- (id)jsonValidator;

/** 用于检查Status Code是否正常的方法 */
- (BOOL)statusCodeValidator;

/** 当POST的内容带有文件等富文本时使用 */
- (AFConstructingBlock)constructingBodyBlock;

/** 当需要断点续传时，指定续传的地址 */
- (NSString *)resumableDownloadPath;

/** 当需要断点续传时，获得下载进度的回调 */
- (AFDownloadProgressBlock)resumableDownloadProgressBlock;

@end
