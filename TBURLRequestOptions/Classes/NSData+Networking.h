//
//  NSData+Networking.h
//  TBURLRequestOptions
//
//  Created by Tanner Bennett on 1/7/16.
//  Copyright (c) 2015 Tanner Bennett. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSData (AES)

- (NSData *)tb_AES128EncryptedDataWithKey:(NSString *)key;
- (NSData *)tb_AES128DecryptedDataWithKey:(NSString *)key;
- (NSData *)tb_AES128EncryptedDataWithKey:(NSString *)key iv:(NSString *)iv;
- (NSData *)tb_AES128DecryptedDataWithKey:(NSString *)key iv:(NSString *)iv;
- (NSData *)tb_AES128DecryptedDataWithKeyData:(NSData *)key ivData:(NSData *)iv;

/** Pads data using PKCS5. blockSize defaults to 16 if given 0. */
- (NSData *)tb_pad:(NSUInteger)blockSize;

@end


@interface NSData (FileFormat)

@property (nonatomic, readonly) BOOL tb_isJPEG;
@property (nonatomic, readonly) BOOL tb_isPNG;
@property (nonatomic, readonly) BOOL tb_isGIF;
@property (nonatomic, readonly) BOOL tb_isImage; // All 3
@property (nonatomic, readonly) BOOL tb_isStillImage; // Not include GIF
@property (nonatomic, readonly) BOOL tb_isMPEG4;
@property (nonatomic, readonly) BOOL tb_isMedia; // All of the above and only the above
/// Checks for PK ZIP, GZIP, GZ, TGZ, TAR.Z, 7z, and bzip2
@property (nonatomic, readonly) BOOL tb_isCompressed;
@property (nonatomic, readonly) NSString *tb_appropriateFileExtension;
/// Supports some of the compression types
@property (nonatomic, readonly) NSString *tb_contentType;

@end


@interface NSData (Encoding)

@property (nonatomic, readonly) NSString *tb_base64URLEncodedString;
@property (nonatomic, readonly) NSString *tb_MD5Hash;
@property (nonatomic, readonly) NSString *tb_hexadecimalString;
@property (nonatomic, readonly) NSString *tb_sha256Hash;

@end


@interface NSData (REST)
+ (NSData *)tb_boundary:(NSString *)boundary withKey:(NSString *)key forStringValue:(NSString *)string;
+ (NSData *)tb_boundary:(NSString *)boundary withKey:(NSString *)key forDataValue:(NSData *)data;
@end
