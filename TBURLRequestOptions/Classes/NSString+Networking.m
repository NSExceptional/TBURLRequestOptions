//
//  NSString+Encoding.m
//  TBURLRequestOptions
//
//  Created by Tanner Bennett on 1/7/16.
//  Copyright (c) 2015 Tanner Bennett. All rights reserved.
//

#import "NSString+Networking.h"
#import "NSData+Networking.h"
#import <CommonCrypto/CommonHMAC.h>


@implementation NSString (Encoding)

- (NSData *)tb_base64DecodedData {
    return [[NSData alloc] initWithBase64EncodedString:self options:0];
}

- (NSString *)tb_base64Encoded {
    NSData *stringData = [self dataUsingEncoding:NSUTF8StringEncoding];
    return [stringData base64EncodedStringWithOptions:0];
}

- (NSString *)tb_base64URLEncoded {
    return [[self dataUsingEncoding:NSUTF8StringEncoding] tb_base64URLEncodedString];
}

- (NSString *)tb_base64Decoded {
    return [[NSString alloc] initWithData:self.tb_base64DecodedData encoding:NSUTF8StringEncoding];
}

- (NSString *)tb_sha256Hash {
    return [[self dataUsingEncoding:NSUTF8StringEncoding] tb_sha256Hash];
}

- (NSData *)tb_sha256HashData {
    NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
    
    unsigned char result[CC_SHA256_DIGEST_LENGTH];
    CC_SHA256(data.bytes, (unsigned int)data.length, result);
    
    data = [[NSData alloc] initWithBytes:result length:CC_SHA256_DIGEST_LENGTH];
    
    return data;
}

+ (NSString *)tb_hashHMac256ToString:(NSString *)data key:(NSString *)key {
    return [[self tb_hashHMacSHA256:data key:key] base64EncodedStringWithOptions:0];
}

+ (NSData *)tb_hashHMacSHA256:(NSString *)data key:(NSString *)key {
    const char *cKey  = [key cStringUsingEncoding:NSUTF8StringEncoding];
    const char *cData = [data cStringUsingEncoding:NSUTF8StringEncoding];
    unsigned char cHMAC[CC_SHA256_DIGEST_LENGTH];
    
    CCHmac(kCCHmacAlgSHA256, cKey, strlen(cKey), cData, strlen(cData), cHMAC);
    return [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
}

+ (NSData *)tb_hashHMacSHA1:(NSString *)data key:(NSString *)key {
    const char *cKey  = [key cStringUsingEncoding:NSUTF8StringEncoding];
    const char *cData = [data cStringUsingEncoding:NSUTF8StringEncoding];
    unsigned char cHMAC[CC_SHA1_DIGEST_LENGTH];
    
    CCHmac(kCCHmacAlgSHA1, cKey, strlen(cKey), cData, strlen(cData), cHMAC);
    return [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
}

- (NSString *)tb_MD5Hash {
    const char *cStr = [self UTF8String];
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    CC_MD5( cStr, (CC_LONG)strlen(cStr), result );
    return [NSString stringWithFormat: @"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            result[0], result[1], result[2], result[3],
            result[4], result[5], result[6], result[7],
            result[8], result[9], result[10], result[11],
            result[12], result[13], result[14], result[15]
            ];
}

@end


@implementation NSString (REST)

+ (NSString *)tb_timestamp {
    return [self tb_timestampFrom:[NSDate date]];
}

+ (NSString *)tb_timestampFrom:(NSDate *)date {
    NSTimeInterval time = date.timeIntervalSince1970;
    return [NSString stringWithFormat:@"%llu", (unsigned long long)round(time)];
}

+ (NSString *)tb_queryStringWithParams:(NSDictionary *)params {
    return [NSString tb_queryStringWithParams:params URLEscapeValues:NO];
}

+ (NSString *)tb_queryStringWithParams:(NSDictionary *)params URLEscapeValues:(BOOL)escapeValues {
    if (params.allKeys.count == 0) return @"";
    
    NSMutableString *q = [NSMutableString string];
    [params enumerateKeysAndObjectsUsingBlock:^(NSString *key, NSString *value, BOOL *stop) {
        if ([value isKindOfClass:[NSString class]]) {
            if (escapeValues) {
                value = [value tb_URLEncodedString];
            } else {
                value = [value stringByReplacingOccurrencesOfString:@" " withString:@"+"];
            }
        }
        [q appendFormat:@"%@=%@&", key, value];
    }];
    
    [q deleteCharactersInRange:NSMakeRange(q.length-1, 1)];
    
    return q;
}

- (NSString *)tb_URLEncodedString {
    NSMutableString *encoded    = [NSMutableString string];
    const unsigned char *source = (const unsigned char *)self.UTF8String;
    NSInteger sourceLen         = (NSInteger)strlen((const char *)source);
    
    for (NSInteger i = 0; i < sourceLen; i++) {
        const unsigned char c = source[i];
        if (c == ' '){
            [encoded appendString:@"+"];
        } else if (c == '.' || c == '-' || c == '_' || c == '~' ||
                   (c >= 'a' && c <= 'z') ||
                   (c >= 'A' && c <= 'Z') ||
                   (c >= '0' && c <= '9')) {
            [encoded appendFormat:@"%c", c];
        } else {
            [encoded appendFormat:@"%%%02X", c];
        }
    }
    
    return encoded;
}

- (NSURL *)tb_URLByAppendingQueryStringWithParams:(NSDictionary *)params {
    if (!params.allKeys.count) return [NSURL URLWithString:self];
    
    NSMutableString *url = self.mutableCopy;
    if ([self characterAtIndex:self.length-1] == '/')
        [url deleteCharactersInRange:NSMakeRange(self.length-1, 1)];
    
    [url appendFormat:@"?%@", [NSString tb_queryStringWithParams:params]];
    return [NSURL URLWithString:url];
}

@end


@implementation NSString (Regex)

- (NSString *)tb_matchGroupAtIndex:(NSUInteger)idx forRegex:(NSString *)regex {
    NSArray *matches = [self tb_matchesForRegex:regex];
    if (matches.count == 0) return nil;
    NSTextCheckingResult *match = matches[0];
    if (idx >= match.numberOfRanges) return nil;
    
    return [self substringWithRange:[match rangeAtIndex:idx]];
}

- (NSArray *)tb_matchesForRegex:(NSString *)pattern {
    NSError *error = nil;
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:pattern options:NSRegularExpressionCaseInsensitive error:&error];
    if (error)
        return nil;
    NSArray *matches = [regex matchesInString:self options:0 range:NSMakeRange(0, self.length)];
    if (matches.count == 0)
        return nil;
    
    return matches;
}

- (NSArray *)tb_allMatchesForRegex:(NSString *)regex {
    NSArray *matches = [self tb_matchesForRegex:regex];
    if (matches.count == 0) return @[];
    
    NSMutableArray *strings = [NSMutableArray new];
    for (NSTextCheckingResult *result in matches)
        [strings addObject:[self substringWithRange:[result rangeAtIndex:1]]];
    
    return strings;
}

- (NSString *)tb_textFromHTML {
    if (!self.length)
        return @"";
    
    NSArray *strings = [self tb_allMatchesForRegex:@"<title>(.*)<[^>]*>"];
    NSMutableString *text = [NSMutableString string];
    
    for (NSString *s in strings)
        if (s.length)
            [text appendFormat:@"%@—", s];
    [text deleteCharactersInRange:NSMakeRange(text.length-1, 1)];
    
    return text;
}

- (NSString *)tb_stringByReplacingMatchesForRegex:(NSString *)pattern withString:(NSString *)replacement {
    return [self stringByReplacingOccurrencesOfString:pattern withString:replacement options:NSRegularExpressionSearch range:NSMakeRange(0, self.length)];
}

@end
