//
//  TBResponseParser.h
//  Pods
//
//  Created by Tanner on 7/2/16.
//
//

#import <Foundation/Foundation.h>


typedef void (^TBResponseBlock)(NSDictionary *json, NSData *data, NSError *error, NSInteger code);

@interface TBResponseParser : NSObject

+ (void)parseResponseData:(NSData *)data response:(NSHTTPURLResponse *)response error:(NSError *)error callback:(TBResponseBlock)callback;

@end
