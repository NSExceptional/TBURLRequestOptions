//
//  NSDictionary+Networking.h
//  TBURLRequestOptions
//
//  Created by Tanner Bennett on 1/7/16.
//  Copyright (c) 2015 Tanner Bennett. All rights reserved.
//

#import <Foundation/Foundation.h>


#define MergeDictionaries(a, b) [a tb_dictionaryByReplacingValuesForKeys: b]

@interface NSDictionary (JSON)
@property (nonatomic, readonly) NSString *tb_JSONString;
- (NSString *)tb_JWTStringWithSecret:(NSString *)secret;
@end


@interface NSDictionary (REST)
/// @return An empty string if no parameters
@property (nonatomic, readonly) NSString *tb_queryString;
/// @return An empty string if no parameters
@property (nonatomic, readonly) NSString *tb_URLEscapedQueryString;
@end

@interface NSDictionary (Util)

@property (nonatomic, readonly) NSArray *tb_allKeyPaths;

/// \c entryLimit must be greater than \c 0.
- (NSArray *)tb_split:(NSUInteger)entryLimit;

- (NSDictionary *)tb_dictionaryByReplacingValuesForKeys:(NSDictionary *)dictionary;
- (NSDictionary *)tb_dictionaryByReplacingKeysWithNewKeys:(NSDictionary *)oldKeysToNewKeys;

@end
