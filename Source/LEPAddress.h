//
//  LEPAddress.h
//  etPanKit
//
//  Created by DINH Viêt Hoà on 30/01/2010.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 An LEPAddress is meant to represent the address objects in a message.  When creating or recieving messages, all address-related fields will store their values in this object.
 */
@interface LEPAddress : NSObject <NSCopying, NSCoding> {
	NSString * _displayName;
    NSString * _mailbox;
}

///******************************************************************************
///@name Initializers
///******************************************************************************

/** Initializes and returns an LEPAddress object with it's displayName and mailbox properties set.
 
 @param displayName An NSString representing an alias the user has defined for themself (e.g. Bob Smith).
 @param mailbox An NSString representing the email address of the user (e.g. myEmailAddress@gmail.com).
 @return An LEPAddress object.
 */
+ (LEPAddress *) addressWithDisplayName:(NSString *)displayName mailbox:(NSString *)mailbox;

/** Initializes and returns an LEPAddress object with it's mailbox property set and it's displayName property nil.
 
 @param mailbox An NSString representing the email address of the user (e.g. myEmailAddress@gmail.com).
 @return An LEPAddress object.
 */
+ (LEPAddress *) addressWithMailbox:(NSString *)mailbox;

/** Initializes and returns an LEPAddress object with it's displayName and mailbox properties set from an RFC822 encoded NSString.
 
 @param string An RFC822 encoded NSString.
 @return An LEPAddress object.
 */
+ (LEPAddress *) addressWithRFC822String:(NSString *)string;

/** Initializes and returns an LEPAddress object with it's displayName and mailbox properties set from a non-encoded RFC822 NSString.
 
 @param string A non-encoded RFC822 NSString.
 @return An LEPAddress object.
 */
+ (LEPAddress *) addressWithNonEncodedRFC822String:(NSString *)string;

///******************************************************************************
///@name Properties
///******************************************************************************

/** The user defined display name associated with the account (e.g. Bob Smith). 
 @note This property may be nil.
 */
@property (nonatomic, copy) NSString * displayName;

/** The email address of the user (e.g. myEmailAddress@gmail.com).*/
@property (nonatomic, copy) NSString * mailbox;

///******************************************************************************
///@name Getting Values
///******************************************************************************

/**
 The value of the object represented as a non-encoded RFC822 NSString.
 
 @return A non-encoded RFC822 NSString
 */
- (NSString *) nonEncodedRFC822String;

/**
 The value of the object represented as an encoded RFC822 NSString.
 
 @return An encoded RFC822 NSString
 */
- (NSString *) RFC822String;

/**
 The value of the object represented in the format  "John Doe <john.doe@email.com>".  Returns nil in 
 the case of a malformed address.
 
 @return An NSString or nil
 */
- (NSString*) prettifiedStringValue;

@end

@interface LEPAddress (LEPNSArray)

/**
 Returns an NSArray of LEPAddress objects that contain the parsed forms of the RFC822 encoded NSString passed to it.
 
 @param string An RFC822 encoded NSString object containing multiple addresses.
 @return An array of LEPAddress objects
 */
+ (NSArray *) addressesWithRFC822String:(NSString *)string;

/**
 Returns an NSArray of LEPAddress objects that contain the parsed forms of the RFC822 non-encoded NSString passed to it.
 
 @param string An RFC822 non-encoded NSString object containing multiple addresses.
 @return An array of LEPAddress objects
 */
+ (NSArray *) addressesWithNonEncodedRFC822String:(NSString *)string;

@end

/**
 A category on NSArray that can separate itself into either an encoded or non-encoded RFC822 addresses string.
  */
@interface NSArray (LEPNSArray)

/**
 Returns an RFC822 encoded NSString from the LEPAddress objects in the array.
 
 @return An RFC822 encoded NSString.
 */
- (NSString *) lepRFC822String;

/**
 Returns a non-encoded RFC822 NSString from the LEPAddress objects in the array.
 
 @return A non-encoded RFC822 NSString.
 */
- (NSString *) lepNonEncodedRFC822String;

@end
