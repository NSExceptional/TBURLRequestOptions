//
//  TBURLRequestBuilder.m
//  Pods
//
//  Created by Ernestine Goates on 6/30/16.
//
//

#import "TBURLRequestBuilder.h"
#import "NSArray+Networking.h"
#import "NSDictionary+Networking.h"
#import "NSString+Networking.h"

#define PropertyOptionIMP(type, name, code)- (TBURLRequestBuilder *(^)(type))name {\
    return ^(type name) { code\
        return self;\
    };\
}

#define PropertyOptionAutoIMP(type, name) PropertyOptionIMP(type, name, {\
    _##name = name;\
})

@interface TBURLRequestBuilder () {
    BOOL _background;
    NSString *_URL;
    NSString *_baseURL;
    NSString *_endpoint;
    NSDictionary *_headers;
    NSString *_contentTypeHeader;
    NSDictionary *_queries;
    NSData *_body;
    NSData *_multipartData;
    NSString *_boundary;
}
@end

@implementation TBURLRequestBuilder

- (TBURLRequestBuilder *)background {
    _background = YES;
    return self;
}

PropertyOptionIMP(NSString *, URL, {
    NSAssert(!_baseURL && !_endpoint, @"Cannot use a full URL and a base URL");
    _URL = URL;
})

PropertyOptionIMP(NSString *, baseURL, {
    NSAssert(!_URL, @"Cannot use a base URL and a full URL");
    _baseURL = _URL;
})

PropertyOptionIMP(NSString *, endpoint, {
    NSAssert(_baseURL, @"Must first use a baseURL");
    _endpoint = endpoint;
})

PropertyOptionAutoIMP(NSDictionary *, headers)
PropertyOptionAutoIMP(NSString *, contentTypeHeader)
PropertyOptionAutoIMP(NSDictionary *, queries)
PropertyOptionAutoIMP(NSData *, body)
PropertyOptionAutoIMP(NSData *, multipartData)
PropertyOptionAutoIMP(NSString *, boundary)

PropertyOptionIMP(NSString *, bodyString, {
    _body = [bodyString dataUsingEncoding:NSUTF8StringEncoding];
    _contentTypeHeader = nil;
})

PropertyOptionIMP(NSDictionary *, bodyJSON, {
    _body = [bodyJSON.JSONString dataUsingEncoding:NSUTF8StringEncoding];
    _contentTypeHeader = nil;
})

PropertyOptionIMP(NSString *, bodyFormString, {
    _body = [bodyFormString dataUsingEncoding:NSUTF8StringEncoding];
    _contentTypeHeader = nil;
})

PropertyOptionIMP(NSDictionary *, bodyJSONFormString, {
    _body = [bodyJSONFormString.queryString dataUsingEncoding:NSUTF8StringEncoding];
    _contentTypeHeader = nil;
})

@end
