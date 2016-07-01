//
//  NSString+YakKit.h
//  YakKit
//
//  Created by Tanner on 5/5/15.
//  Copyright (c) 2015 Tanner Bennett. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSString (Encoding)

@property (nonatomic, readonly) NSString *base64Encoded;
@property (nonatomic, readonly) NSString *base64URLEncoded;
@property (nonatomic, readonly) NSString *base64Decoded;
@property (nonatomic, readonly) NSData   *base64DecodedData;

@property (nonatomic, readonly) NSString *MD5Hash;
@property (nonatomic, readonly) NSString *sha256Hash;
@property (nonatomic, readonly) NSData   *sha256HashData;

+ (NSData *)hashHMac:(NSString *)data key:(NSString *)key;
+ (NSString *)hashHMacToString:(NSString *)data key:(NSString *)key;

@end


@interface NSString (REST)
@property (nonatomic, readonly) NSString *URLEncodedString;
+ (NSString *)timestamp;
+ (NSString *)timestampFrom:(NSDate *)date;
+ (NSString *)queryStringWithParams:(NSDictionary *)params;
+ (NSString *)queryStringWithParams:(NSDictionary *)params URLEscapeValues:(BOOL)escapeValues;
- (NSURL *)URLByAppendingQueryStringWithParams:(NSDictionary *)params;

@end


@interface NSString (Regex)
- (NSString *)matchGroupAtIndex:(NSUInteger)idx forRegex:(NSString *)regex;
- (NSArray *)allMatchesForRegex:(NSString *)regex;
- (NSString *)textFromHTML;
- (NSString *)stringByReplacingMatchesForRegex:(NSString *)regex withString:(NSString *)replacement;
@end
