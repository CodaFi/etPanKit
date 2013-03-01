//
//  LEPAbstractAttachment.m
//  etPanKit
//
//  Created by DINH Viêt Hoà on 03/01/2010.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "LEPAbstractAttachment.h"
#import "LEPUtils.h"

@implementation LEPAbstractAttachment

- (id) init
{
	self = [super init];
	
	return self;
}

- (void) dealloc
{
	[_contentLocation release];
	[_contentID release];
	[_charset release];
	[_filename release];
	[_mimeType release];
	[super dealloc];
}

- (NSString *) description
{
	return [NSString stringWithFormat:@"<%@: 0x%p %@ %@>", [self class], self, [self mimeType], [self filename]];
}

- (id) initWithCoder:(NSCoder *)decoder
{
	self = [super init];
	
	_filename = [[decoder decodeObjectForKey:@"filename"] retain];
	_mimeType = [[decoder decodeObjectForKey:@"mimeType"] retain];
	_charset = [[decoder decodeObjectForKey:@"charset"] retain];
	_inlineAttachment = [decoder decodeBoolForKey:@"inlineAttachment"];
	_contentID = [[decoder decodeObjectForKey:@"contentID"] retain];
	_contentLocation = [[decoder decodeObjectForKey:@"contentLocation"] retain];
	
	return self;
}

- (void) encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:_filename forKey:@"filename"];
	[encoder encodeObject:_mimeType forKey:@"mimeType"];
	[encoder encodeObject:_charset forKey:@"charset"];
	[encoder encodeBool:_inlineAttachment forKey:@"inlineAttachment"];
	[encoder encodeObject:_contentID forKey:@"contentID"];
	[encoder encodeObject:_contentLocation forKey:@"contentLocation"];
}

- (id) copyWithZone:(NSZone *)zone
{
	LEPAbstractAttachment *attachment;
	
	attachment = [[[self class] alloc] init];
	
	[attachment setFilename:[self filename]];
	[attachment setMimeType:[self mimeType]];
	[attachment setCharset:[self charset]];
	[attachment setContentID:[self contentID]];
	[attachment setContentLocation:[self contentLocation]];
	[attachment setInlineAttachment:[self isInlineAttachment]];
	[attachment setMessage:_message];
	
	return attachment;
}

- (BOOL) isPlainTextAttachment {
	BOOL result = NO;
	if (self.isInlineAttachment) {
		if (![[self.mimeType lowercaseString] isEqualToString:@"text/html"]) {
			result = [[self.mimeType lowercaseString] isEqualToString:@"text/plain"];
		}
	}
	return result;
}

- (NSArray *) plainTextAttachments {
	if ([self isPlainTextAttachment]) {
		return [NSArray arrayWithObject:self];
	}
	else {
		return [NSArray array];
	}
}

@end