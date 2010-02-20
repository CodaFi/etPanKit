//
//  LEPIMAPFolder.m
//  etPanKit
//
//  Created by DINH Viêt Hoà on 03/01/2010.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "LEPIMAPFolder.h"
#import "LEPIMAPFolderPrivate.h"

#import "LEPIMAPAccount.h"
#import "LEPIMAPAccountPrivate.h"
#import "LEPIMAPRenameFolderRequest.h"
#import "LEPIMAPDeleteFolderRequest.h"
#import "LEPIMAPSubscribeFolderRequest.h"
#import "LEPIMAPUnsubscribeFolderRequest.h"
#import "LEPIMAPAppendMessageRequest.h"
#import "LEPIMAPCopyMessageRequest.h"
#import "LEPIMAPFetchFolderMessagesRequest.h"
#import "LEPIMAPExpungeRequest.h"
#import "LEPIMAPMessage.h"
#import "LEPMessage.h"
#import "LEPError.h"
#import "LEPUtils.h"
#import "LEPIMAPSelectRequest.h"
#import "NSString+LEP.h"
#import "LEPIMAPStoreFlagsRequest.h"
#import "LEPConstants.h"
#import <libetpan/libetpan.h>

@implementation LEPIMAPFolder

@synthesize account = _account;
@synthesize uidValidity = _uidValidity;
@synthesize path = _path;
@synthesize uidNext = _uidNext;

- (id) init
{
	self = [super init];
	
	return self;
} 

- (void) dealloc
{
    [_path release];
	[super dealloc];
}

- (void) _setDelimiter:(char)delimiter
{
	_delimiter = delimiter;
}

- (void) _setPath:(NSString *)path
{
    [_path release];
    _path = [path copy];
}

- (void) _setFlags:(int)flags
{
    _flags = flags;
}

- (NSArray *) pathComponents
{
    return [[self path] componentsSeparatedByString:[NSString stringWithFormat:@"%c", _delimiter]];
}

- (void) _setupRequest:(LEPIMAPRequest *)request
{
	[_account _setupRequest: request];
}

- (LEPIMAPRequest *) deleteRequest
{
	LEPIMAPDeleteFolderRequest * request;
	
	request = [[LEPIMAPDeleteFolderRequest alloc] init];
    [request setPath:[self path]];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) renameRequestWithNewPath:(NSString *)newPath
{
	LEPIMAPRenameFolderRequest * request;
	
	request = [[LEPIMAPRenameFolderRequest alloc] init];
    [request setOldPath:[self path]];
    [request setNewPath:newPath];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) subscribeRequest
{
	LEPIMAPSubscribeFolderRequest * request;
	
	request = [[LEPIMAPSubscribeFolderRequest alloc] init];
    [request setPath:[self path]];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) unsubscribeRequest
{
	LEPIMAPUnsubscribeFolderRequest * request;
	
	request = [[LEPIMAPUnsubscribeFolderRequest alloc] init];
    [request setPath:[self path]];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) appendMessageRequest:(LEPMessage *)message;
{
	LEPIMAPAppendMessageRequest * request;
	
	request = [[LEPIMAPAppendMessageRequest alloc] init];
    [request setData:[message data]];
    [request setPath:[self path]];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) copyMessages:(NSArray * /* LEPIMAPMessage */)messages toFolder:(LEPIMAPFolder *)toFolder;
{
	LEPIMAPCopyMessageRequest * request;
	LEPIMAPAccount * account;
    LEPIMAPFolder * sourceFolder;
    NSMutableArray * uidSet;
    
    LEPAssert([messages count] > 0);
    
    uidSet = [[NSMutableArray alloc] init];
    sourceFolder = [[messages objectAtIndex:0] folder];
    LEPAssert([sourceFolder account] == account);
    for(LEPIMAPMessage * message in messages) {
        LEPAssert([message folder] == sourceFolder);
        [uidSet addObject:[NSNumber numberWithUnsignedLong:[message uid]]];
    }
    
	request = [[LEPIMAPCopyMessageRequest alloc] init];
    [request setUidSet:uidSet];
    [request setFromPath:[self path]];
    [request setToPath:[toFolder path]];
    
    [self _setupRequest:request];
    
    [uidSet release];
    
    return [request autorelease];
}

- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesRequest
{
	LEPLog(@"fetch message request");
    return [self fetchMessagesRequestFromUID:1];
}

- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesRequestFromUID:(uint32_t)uid
{
	return [self fetchMessagesRequestFromUID:uid toUID:0];
}

- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesRequestFromUID:(uint32_t)fromUID toUID:(uint32_t)toUID
{
	LEPIMAPFetchFolderMessagesRequest * request;
	
	request = [[LEPIMAPFetchFolderMessagesRequest alloc] init];
    [request setFetchKind:LEPIMAPMessagesRequestKindFlags | LEPIMAPMessagesRequestKindHeaders];
    [request setPath:[self path]];
    [request setFromUID:fromUID];
    [request setToUID:toUID];
	[request setFolder:self];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDFlagsRequest
{
    return [self fetchMessagesUIDFlagsRequestFromUID:1];
}

- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDFlagsRequestFromUID:(uint32_t)uid
{
	return [self fetchMessagesUIDFlagsRequestFromUID:uid toUID:0];
}

- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDFlagsRequestFromUID:(uint32)fromUID toUID:(uint32_t)toUID
{
	LEPIMAPFetchFolderMessagesRequest * request;
	
	request = [[LEPIMAPFetchFolderMessagesRequest alloc] init];
    [request setFetchKind:LEPIMAPMessagesRequestKindFlags];
    [request setPath:[self path]];
    [request setFromUID:fromUID];
    [request setToUID:toUID];
	[request setFolder:self];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) expungeRequest
{
	LEPIMAPExpungeRequest * request;
	
	request = [[LEPIMAPExpungeRequest alloc] init];
    [request setPath:[self path]];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (LEPIMAPRequest *) selectRequest
{
	LEPIMAPSelectRequest * request;
	
	request = [[LEPIMAPSelectRequest alloc] init];
    [request setPath:[self path]];
	[request setFolder:self];
    
    [self _setupRequest:request];
    
    return [request autorelease];
}

- (void) _setAccount:(LEPIMAPAccount *)account
{
	[_account release];
	_account = [account retain];
}

- (NSString *) description
{
	return [NSString stringWithFormat:@"<%@: 0x%p %@ %@>", [self class], self, [self path], [self displayName]];
}

- (void) _setUidValidity:(uint32_t)uidValidity
{
	_uidValidity = uidValidity;
}

- (void) _setUidNext:(uint32_t)uidNext
{
	_uidNext = uidNext;
}

- (NSString *) displayName
{
	NSArray * components;
	NSString * name;
	
	components = [self pathComponents];
	name = [[components lastObject] lepDecodeFromModifiedUTF7];
	
	return name;
}

- (LEPIMAPRequest *) addFlagsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages
{
	LEPIMAPStoreFlagsRequest * request;
	NSMutableArray * uids;
	
	request = [[LEPIMAPStoreFlagsRequest alloc] init];
	[request setKind:LEPIMAPStoreFlagsRequestKindAdd];
	[request setPath:[self path]];
	uids = [[NSMutableArray alloc] init];
	for(LEPIMAPMessage * msg in messages) {
		[uids addObject:[NSNumber numberWithUnsignedLong:[msg uid]]];
	}
	[request setUids:uids];
	[uids release];
	
	return [request autorelease];
}

- (LEPIMAPRequest *) removeFlagsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages
{
	LEPIMAPStoreFlagsRequest * request;
	NSMutableArray * uids;
	
	request = [[LEPIMAPStoreFlagsRequest alloc] init];
	[request setKind:LEPIMAPStoreFlagsRequestKindRemove];
	[request setPath:[self path]];
	uids = [[NSMutableArray alloc] init];
	for(LEPIMAPMessage * msg in messages) {
		[uids addObject:[NSNumber numberWithUnsignedLong:[msg uid]]];
	}
	[request setUids:uids];
	[uids release];
	
	return [request autorelease];
}

- (LEPIMAPRequest *) setFlagsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages
{
	LEPIMAPStoreFlagsRequest * request;
	NSMutableArray * uids;
	
	request = [[LEPIMAPStoreFlagsRequest alloc] init];
	[request setKind:LEPIMAPStoreFlagsRequestKindSet];
	[request setPath:[self path]];
	uids = [[NSMutableArray alloc] init];
	for(LEPIMAPMessage * msg in messages) {
		[uids addObject:[NSNumber numberWithUnsignedLong:[msg uid]]];
	}
	[request setUids:uids];
	[uids release];
	
	return [request autorelease];
}

@end

