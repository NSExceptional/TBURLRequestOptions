//
//  NSString+Encoding.h
//  TBURLRequestOptions
//
//  Created by Tanner Bennett on 1/7/16.
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
+ (NSString *)timestamp;
+ (NSString *)timestampInSeconds;
+ (NSString *)timestampFrom:(NSDate *)date;
@end


@interface NSString (Regex)
@property (nonatomic, readonly) NSString *textFromHTML;
- (NSString *)matchGroupAtIndex:(NSUInteger)idx forRegex:(NSString *)regex;
- (NSArray *)allMatchesForRegex:(NSString *)regex;
- (NSString *)stringByReplacingMatchesForRegex:(NSString *)regex withString:(NSString *)replacement;
@end


@interface NSString (Snapchat)
+ (NSString *)SCIdentifierWith:(NSString *)first and:(NSString *)second;
@end
