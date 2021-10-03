//
//  NSString+Encoding.h
//  TBURLRequestOptions
//
//  Created by Tanner Bennett on 1/7/16.
//  Copyright (c) 2015 Tanner Bennett. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSString (Encoding)

@property (nonatomic, readonly) NSString *tb_base64Encoded;
@property (nonatomic, readonly) NSString *tb_base64URLEncoded;
@property (nonatomic, readonly) NSString *tb_base64Decoded;
@property (nonatomic, readonly) NSData   *tb_base64DecodedData;

@property (nonatomic, readonly) NSString *tb_MD5Hash;
@property (nonatomic, readonly) NSString *tb_sha256Hash;
@property (nonatomic, readonly) NSData   *tb_sha256HashData;

+ (NSData *)tb_hashHMacSHA256:(NSString *)data key:(NSString *)key;
+ (NSString *)tb_hashHMac256ToString:(NSString *)data key:(NSString *)key;
+ (NSData *)tb_hashHMacSHA1:(NSString *)data key:(NSString *)key;

@end


@interface NSString (REST)
@property (nonatomic, readonly) NSString *tb_URLEncodedString;
+ (NSString *)tb_timestamp;
+ (NSString *)tb_timestampFrom:(NSDate *)date;
+ (NSString *)tb_queryStringWithParams:(NSDictionary *)params;
+ (NSString *)tb_queryStringWithParams:(NSDictionary *)params URLEscapeValues:(BOOL)escapeValues;
- (NSURL *)tb_URLByAppendingQueryStringWithParams:(NSDictionary *)params;

@end


@interface NSString (Regex)
@property (nonatomic, readonly) NSString *tb_textFromHTML;
- (NSString *)tb_matchGroupAtIndex:(NSUInteger)idx forRegex:(NSString *)regex;
- (NSArray *)tb_allMatchesForRegex:(NSString *)regex;
- (NSString *)tb_stringByReplacingMatchesForRegex:(NSString *)regex withString:(NSString *)replacement;
@end
