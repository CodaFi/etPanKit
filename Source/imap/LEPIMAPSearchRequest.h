//
//  LEPIMAPSearchRequest.h
//  etPanKit
//
//  Created by Robert Widmann on 11/24/12.
//
//

#import <EtPanKit/LEPIMAPRequest.h>

/**
 An object that encapsulates IMAP folder Searches.  Provide it with a path, then provide one of the following parameters before 
 starting the request, and it will return an NSIndexSet of UIDs that match the query.  Only one property will be searched for per request 
 (because there is only one result indexed set), even if multiple properties are provided.
 */

@interface LEPIMAPSearchRequest : LEPIMAPRequest

//Standard Initializer
- (id) initWithPath:(NSString*)path;
@property (nonatomic, copy, readonly) NSString *path;

//Will be nil if the request errors out and if it matches nothing.
@property (nonatomic, strong, readonly) NSIndexSet *foundUIDs;

/************************************************************
 Search Properties (In order of importance).
 ************************************************************/
@property (nonatomic, copy) NSString *text;
@property (nonatomic, copy) NSString *subject;
@property (nonatomic, strong) NSString *from;
@property (nonatomic, strong) NSString *to;


@end
