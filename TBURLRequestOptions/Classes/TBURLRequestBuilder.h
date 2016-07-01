//
//  TBURLRequestBuilder.h
//  Pods
//
//  Created by Ernestine Goates on 6/30/16.
//
//

#import <Foundation/Foundation.h>


#define PropertyOption(type, name) @property (nonatomic, readonly) TBURLRequestBuilder *(^name)(type)

@interface TBURLRequestBuilder : NSObject

/// Access to enable background upload. Returns the reciever.
@property (nonatomic, readonly) TBURLRequestBuilder *background;

/// The full URL for the request, excluding any query parameters.
PropertyOption(NSString *, URL);
/// Must use with endpoint.
PropertyOption(NSString *, baseURL);
/// Relative to \c baseURL, must use if using it and must use after \c baseURL.
PropertyOption(NSString *, endpoint);

PropertyOption(NSDictionary *, headers);
/// Automatically supplied by the body helpers, overriden if it appears in \c headers.
/// If multipart, please set the boundary in \c boundary.
PropertyOption(NSString     *, contentTypeHeader);

/// Queries to be appended to the final request URL. Automatically URL encoded.
PropertyOption(NSDictionary *, queries);
/// The HTTP request body. You must explicitly set the MIME content type when using this.
PropertyOption(NSData       *, body);
/// Convenience getter/setter for the \c body as a string.
PropertyOption(NSString     *, bodyString);
/// Convenience getter/setter for the \c body as JSON.
PropertyOption(NSDictionary *, bodyJSON);
/// Convenience getter/setter for the \c body as a URL form encoded string.
PropertyOption(NSString     *, bodyFormString);
/// Convenience getter/setter for the \c body as a URL form encoded string given JSON.
PropertyOption(NSDictionary *, bodyJSONFormString);

/// Convenience getter/setter for the \c body as multipart form data.
PropertyOption(NSData *, multipartData);
/// Used when the content type is \c multipart/form-data
PropertyOption(NSString *, boundary);

@end
