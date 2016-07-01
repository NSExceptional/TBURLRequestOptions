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

- (NSData *)base64DecodedData {
    return [[NSData alloc] initWithBase64EncodedString:self options:0];
}

- (NSString *)base64Encoded {
    NSData *stringData = [self dataUsingEncoding:NSUTF8StringEncoding];
    return [stringData base64EncodedStringWithOptions:0];
}

- (NSString *)base64URLEncoded {
    return [[self dataUsingEncoding:NSUTF8StringEncoding] base64URLEncodedString];
}

- (NSString *)base64Decoded {
    return [[NSString alloc] initWithData:self.base64DecodedData encoding:NSUTF8StringEncoding];
}

- (NSString *)sha256Hash {
    return [[self dataUsingEncoding:NSUTF8StringEncoding] sha256Hash];
}

- (NSData *)sha256HashData {
    NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
    
    unsigned char result[CC_SHA256_DIGEST_LENGTH];
    CC_SHA256(data.bytes, (unsigned int)data.length, result);
    
    data = [[NSData alloc] initWithBytes:result length:CC_SHA256_DIGEST_LENGTH];
    
    return data;
}

+ (NSString *)hashSCString:(NSString *)first and:(NSString *)second {
    return [NSString hashSC:[first dataUsingEncoding:NSUTF8StringEncoding] and:[second dataUsingEncoding:NSUTF8StringEncoding]];
}

+ (NSString *)hashSC:(NSData *)a and:(NSData *)b {
    NSData *secretData = [SKConsts.secret dataUsingEncoding:NSUTF8StringEncoding];
    
    NSMutableData *firstData  = secretData.mutableCopy;
    NSMutableData *secondData = b.mutableCopy;
    
    // Append secret to values
    [firstData appendData:a];
    [secondData appendData:secretData];
    
    // SHA256 hash data
    NSString *first  = [firstData sha256Hash];
    NSString *second = [secondData sha256Hash];
    
    // SC hash
    NSMutableString *hash = [NSMutableString string];
    for (int i = 0; i < SKConsts.hashPattern.length; i++) {
        if ([SKConsts.hashPattern characterAtIndex:i] == '0')
            [hash appendFormat:@"%C", [first characterAtIndex:i]];
        else
            [hash appendFormat:@"%C", [second characterAtIndex:i]];
    }
    
    return hash;
}

+ (NSString *)hashHMacToString:(NSString *)data key:(NSString *)key {
    return [[self hashHMac:data key:key] base64EncodedStringWithOptions:0];
}

+ (NSData *)hashHMac:(NSString *)data key:(NSString *)key {
    const char *cKey  = [key cStringUsingEncoding:NSUTF8StringEncoding];
    const char *cData = [data cStringUsingEncoding:NSUTF8StringEncoding];
    unsigned char cHMAC[CC_SHA256_DIGEST_LENGTH];
    
    CCHmac(kCCHmacAlgSHA256, cKey, strlen(cKey), cData, strlen(cData), cHMAC);
    return [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
}

- (NSString *)MD5Hash {
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

+ (NSString *)timestamp {
    return [self timestampFrom:[NSDate date]];
}

+ (NSString *)timestampInSeconds {
    return [NSString stringWithFormat:@"%llu", (unsigned long long)[NSDate date].timeIntervalSince1970];
}

+ (NSString *)timestampFrom:(NSDate *)date {
    NSTimeInterval time = date.timeIntervalSince1970;
    return [NSString stringWithFormat:@"%llu", (unsigned long long)round(time *1000.0)];
}

- (NSString *)URLEncodedString {
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

@end


@implementation NSString (Regex)

- (NSString *)matchGroupAtIndex:(NSUInteger)idx forRegex:(NSString *)regex {
    NSArray *matches = [self matchesForRegex:regex];
    if (matches.count == 0) return nil;
    NSTextCheckingResult *match = matches[0];
    if (idx >= match.numberOfRanges) return nil;
    
    return [self substringWithRange:[match rangeAtIndex:idx]];
}

- (NSArray *)matchesForRegex:(NSString *)pattern {
    NSError *error = nil;
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:pattern options:NSRegularExpressionCaseInsensitive error:&error];
    if (error)
        return nil;
    NSArray *matches = [regex matchesInString:self options:0 range:NSMakeRange(0, self.length)];
    if (matches.count == 0)
        return nil;
    
    return matches;
}

- (NSArray *)allMatchesForRegex:(NSString *)regex {
    NSArray *matches = [self matchesForRegex:regex];
    if (matches.count == 0) return @[];
    
    NSMutableArray *strings = [NSMutableArray new];
    for (NSTextCheckingResult *result in matches)
        [strings addObject:[self substringWithRange:[result rangeAtIndex:1]]];
    
    return strings;
}

- (NSString *)textFromHTML {
    if (!self.length)
        return @"";
    
    NSArray *strings = [self allMatchesForRegex:@"<title>(.*)<[^>]*>"];
    NSMutableString *text = [NSMutableString string];
    
    for (NSString *s in strings)
        if (s.length)
            [text appendFormat:@"%@—", s];
    [text deleteCharactersInRange:NSMakeRange(text.length-1, 1)];
    
    return text;
}

- (NSString *)stringByReplacingMatchesForRegex:(NSString *)pattern withString:(NSString *)replacement {
    return [self stringByReplacingOccurrencesOfString:pattern withString:replacement options:NSRegularExpressionSearch range:NSMakeRange(0, self.length)];
}

@end
