//
//  TBResponseParser.h
//  Pods
//
//  Created by Tanner on 7/2/16.
//
//

#import <Foundation/Foundation.h>


#pragma mark Macros
#define TBDispatchToMain(block) dispatch_async(dispatch_get_main_queue(), ^{ block })
#define TBRunBlock(block) if ( block ) block()
#define TBRunBlockP(block, ...) if ( block ) block( __VA_ARGS__ )
#define TBRunBlockOnMain(block) TBDispatchToMain(TBRunBlock(block))
#define TBRunBlockOnMainP(block, ...) TBDispatchToMain(TBRunBlockP(block, __VA_ARGS__))
#define NSNSString __unsafe_unretained NSString
#define NSNSURL __unsafe_unretained NSURL
#define TB_NAMESPACE(name, vals) extern const struct name vals name
#define TB_NAMESPACE_IMP(name) const struct name name =

@class TBResponseParser;
typedef void (^TBResponseBlock)(TBResponseParser *parser);

#pragma mark - TBResponseParser
@interface TBResponseParser : NSObject
+ (void)parseResponseData:(nullable NSData *)data
                 response:(nullable NSHTTPURLResponse *)response
                    error:(nullable NSError *)error
                 callback:(nullable TBResponseBlock)callback;

#pragma mark

@property (nonatomic, nullable, readonly) NSHTTPURLResponse *response;
@property (nonatomic,           readonly) NSData *data;
@property (nonatomic, nullable, readonly) NSError *error;
@property (nonatomic, nullable, readonly) NSString *contentType;

#pragma mark Response data helper accessors

@property (nonatomic, nullable, readonly) NSDictionary *JSON;
@property (nonatomic, nullable, readonly) NSString *HTML;
@property (nonatomic, nullable, readonly) NSString *XML;
@property (nonatomic, nullable, readonly) NSString *javascript;
@property (nonatomic, nullable, readonly) NSString *text;)\

@end


#pragma mark Status codes

typedef NS_ENUM(NSUInteger, TBHTTPStatusCode) {
    TBHTTPStatusCodeContinue = 100,
    TBHTTPStatusCodeSwitchProtocol,
    
    TBHTTPStatusCodeOK = 200,
    TBHTTPStatusCodeCreated,
    TBHTTPStatusCodeAccepted,
    TBHTTPStatusCodeNonAuthorativeInfo,
    TBHTTPStatusCodeNoContent,
    TBHTTPStatusCodeResetContent,
    TBHTTPStatusCodePartialContent,
    
    TBHTTPStatusCodeMultipleChoice = 300,
    TBHTTPStatusCodeMovedPermanently,
    TBHTTPStatusCodeFound,
    TBHTTPStatusCodeSeeOther,
    TBHTTPStatusCodeNotModified,
    TBHTTPStatusCodeUseProxy,
    TBHTTPStatusCodeUnused,
    TBHTTPStatusCodeTemporaryRedirect,
    TBHTTPStatusCodePermanentRedirect,
    
    TBHTTPStatusCodeBadRequest = 400,
    TBHTTPStatusCodeUnauthorized,
    TBHTTPStatusCodePaymentRequired,
    TBHTTPStatusCodeForbidden,
    TBHTTPStatusCodeNotFound,
    TBHTTPStatusCodeMethodNotAllowed,
    TBHTTPStatusCodeNotAcceptable,
    TBHTTPStatusCodeProxyAuthRequired,
    TBHTTPStatusCodeRequestTimeout,
    TBHTTPStatusCodeConflict,
    TBHTTPStatusCodeGone,
    TBHTTPStatusCodeLengthRequired,
    TBHTTPStatusCodePreconditionFailed,
    TBHTTPStatusCodePayloadTooLarge,
    TBHTTPStatusCodeURITooLong,
    TBHTTPStatusCodeUnsupportedMediaType,
    TBHTTPStatusCodeRequestedRangeUnsatisfiable,
    TBHTTPStatusCodeExpectationFailed,
    TBHTTPStatusCodeImATeapot,
    TBHTTPStatusCodeMisdirectedRequest = 421,
    TBHTTPStatusCodeUpgradeRequired = 426,
    TBHTTPStatusCodePreconditionRequired = 428,
    TBHTTPStatusCodeTooManyRequests,
    TBHTTPStatusCodeRequestHeaderFieldsTooLarge = 431,
    
    TBHTTPStatusCodeInternalServerError = 500,
    TBHTTPStatusCodeNotImplemented,
    TBHTTPStatusCodeBadGateway,
    TBHTTPStatusCodeServiceUnavailable,
    TBHTTPStatusCodeGatewayTimeout,
    TBHTTPStatusCodeHTTPVersionUnsupported,
    TBHTTPStatusCodeVariantAlsoNegotiates,
    TBHTTPStatusCodeAuthenticationRequired = 511,
};

#define TBHTTPStatusCodeDescription(TBHTTPStatusCode) TBHTTPStatusCodeDescriptionFromString(@(#TBHTTPStatusCode))
extern NSString * TBHTTPStatusCodeDescriptionFromString(NSString *codeString);

#pragma mark String constants

TB_NAMESPACE(TBContentType, {
    NSNSString *CSS;
    NSNSString *GZIP;
    NSNSString *HTML;
    NSNSString *javascript;
    NSNSString *JSON;
    NSNSString *JWT;
    NSNSString *markdown;
    NSNSString *multipartFormData;
    NSNSString *multipartEncrypted;
    NSNSString *rtf;
    NSNSString *textXML;
    NSNSString *XML;
    NSNSString *ZIP;
    NSNSString *ZLIB;
});

TB_NAMESPACE(TBHeader, {
    NSNSString *accept;
    NSNSString *acceptEncoding;
    NSNSString *acceptLanguage;
    NSNSString *acceptLocale;
    NSNSString *authorization;
    NSNSString *cacheControl;
    NSNSString *contentLength;
    NSNSString *contentType;
    NSNSString *date;
    NSNSString *expires;
    NSNSString *setCookie;
    NSNSString *status;
    NSNSString *userAgent;
});





















