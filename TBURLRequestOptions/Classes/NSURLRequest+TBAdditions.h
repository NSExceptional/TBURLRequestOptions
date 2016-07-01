//
//  NSURLRequest+TBAdditions.h
//  Pods
//
//  Created by Ernestine Goates on 6/30/16.
//
//

#import <Foundation/Foundation.h>


typedef void (^TBResponseBlock)(NSDictionary *json, NSData *data, NSError *error, NSInteger code);
#define PropertyRequest(type, name) @property (nonatomic, readonly) void (^name)(type)

@interface NSURLRequest (TBAdditions)

/** @brief Replaces header field values. Useful for changing the user-agent on the fly.
 @discussion Pass \c nil to remove previous overrides. \c overrideHeaderValues:forEndpoint: takes precedence over this method and affects every request, but otherwise functions the same.
 @param headers A dictionary of header-value key-value pairs, i.e. @code @{@"User-Agent": @"iOS 2.0"} @endcode */
+ (void)overrideHeaderValuesGlobally:(NSDictionary *)headers;

/** @brief Replaces header field values for a specific endpoint.
 @discussion Pass \c nil to \c headers to remove previous overrides for a given endpoint. See \c overrideHeaderValues: for more information.
 This method takes precedence over \c overrideHeaderValuesGlobally: and is used before \c overrideEndpoints:, so make sure to override the original endpoint.
 @param headers A dictionary of header-value key-value pairs, i.e. @code @{@"User-Agent": @"iOS 2.0"} @endcode
 @param endpoint The endpoint whose header values you wish to override. */
+ (void)overrideHeaderValues:(NSDictionary *)headers forEndpoint:(NSString *)endpoint;

/** @brief Replaces values for specific query keys in the scope of the given endpoint.
 @discussion Pass \c nil to \e queries to remove previous overrides for \e endpoint.
 This method takes precedence over \c overrideValuesForKeysGlobally: and is used before \c overrideEndpoints:, so make sure to override the original endpoint.
 */
+ (void)overrideValuesForKeys:(NSDictionary *)queries forEndpoint:(NSString *)endpoint;

/** @brief Replaces values for specific query keys in every request.
 @discussion Pass \c nil to remove previous overrides. \c overrideValuesForKeys:forEndpoint: takes precedence over this method and affects every request, but otherwise functions the same. */
+ (void)overrideValuesForKeysGlobally:(NSDictionary *)queries;

/** @brief Replaces endpoint \c some_endpoint with \e endpoints[some_endpoint].
 @discussion \c overrideValuesForKeys:forEndpoint: and \c overrideHeaderValues:forEndpoint: take precedence over this method.
 This method will replace all ekeys in a request query with the given values in \c endpoints. */
+ (void)overrideEndpoints:(NSDictionary *)endpoints;

PropertyRequest(TBResponseBlock, GET);
PropertyRequest(TBResponseBlock, POST);
PropertyRequest(TBResponseBlock, PUT);
PropertyRequest(TBResponseBlock, HEAD);
PropertyRequest(TBResponseBlock, DELETE);
PropertyRequest(TBResponseBlock, OPTIONS);
PropertyRequest(TBResponseBlock, CONNECT);

@end
