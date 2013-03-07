//
//  LEPAbstractAlternativeAttachment.m
//  etPanKit
//
//  Created by DINH Viêt Hoà on 31/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "LEPAbstractAlternativeAttachment.h"

@implementation LEPAbstractAlternativeAttachment

@synthesize attachments = _attachments;

- (id) init
{
	self = [super init];
	
	return self;
}

- (void) dealloc
{
	[_attachments release];
	[super dealloc];
}

- (void) setMessage:(LEPAbstractMessage *)message
{
	_message = message;
	for (NSArray *oneAlternative in _attachments) {
		for (LEPAbstractAttachment *attachment in oneAlternative) {
			[attachment setMessage:message];
		}
	}
}

- (NSString *) description
{
	NSMutableString *result;
	
	result = [NSMutableString string];
	[result appendFormat:@"{%@: 0x%p %@\n", [self class], self, [self mimeType]];
	for (NSArray *oneAlternative in _attachments) {
		[result appendFormat:@"  {"];
		for (unsigned int i = 0; i < [oneAlternative count]; i++) {
			LEPAbstractAttachment *attachment;
			
			attachment = [oneAlternative objectAtIndex:i];
			if (i == [oneAlternative count] - 1) {
				[result appendFormat:@"%@", attachment];
			}
			else {
				[result appendFormat:@"%@, ", attachment];
			}
		}
		[result appendFormat:@"}\n"];
	}
	[result appendFormat:@"}"];
	
	return result;
}

- (id) initWithCoder:(NSCoder *)decoder
{
	self = [super initWithCoder:decoder];
	
	_attachments = [[decoder decodeObjectForKey:@"attachments"] retain];
	
	return self;
}

- (void) encodeWithCoder:(NSCoder *)encoder
{
	[super encodeWithCoder:encoder];
	[encoder encodeObject:_attachments forKey:@"attachments"];
}

- (id) copyWithZone:(NSZone *)zone
{
	LEPAbstractAlternativeAttachment *attachment;
	
	attachment = [super copyWithZone:zone];
	
	NSMutableArray *alternatives;
	
	alternatives = [[NSMutableArray alloc] init];
	for (NSArray *oneAlternative in[self attachments]) {
		NSMutableArray *attachments;
		
		attachments = [[NSMutableArray alloc] init];
		for (LEPAbstractAttachment *attachment in oneAlternative) {
			[attachments addObject:[[attachment copy] autorelease]];
		}
		[alternatives addObject:attachments];
		[attachments release];
	}
	[attachment setAttachments:alternatives];
	
	[alternatives release];
	
	return attachment;
}

#pragma mark - LEPRecursiveAttachments

- (NSArray *) allAttachments {
	NSMutableArray *result = [NSMutableArray array];
	NSArray *prefferedAlternative = [self _bodyTypeAttachments];
	for (LEPAbstractAttachment *attachment in prefferedAlternative) {
		[result addObjectsFromArray:[attachment allAttachments]];
	}
	if (self.attachments.count != 0) {
		int counter = 0;
		do
		{
			if (prefferedAlternative != [self.attachments objectAtIndex:counter]) {
				for (LEPAbstractAttachment *attachment in[self.attachments objectAtIndex : counter]) {
					[result addObjectsFromArray:[attachment allAttachments]];
				}
			}
			counter++;
		}
		while (counter < self.attachments.count);
	}
	return result;
}

- (NSArray *) calendarTypeAttachments {
	NSMutableArray *result = [NSMutableArray array];
	if (self.attachments.count != 0) {
		int counter = 0;
		do
		{
			for (LEPAbstractAttachment *attachment in[self.attachments objectAtIndex : counter]) {
				[result addObjectsFromArray:[attachment calendarTypeAttachments]];
			}
			counter++;
		}
		while (counter < self.attachments.count);
	}
	return result;
}

- (NSArray *) plaintextTypeAttachments {
	NSMutableArray *result = [NSMutableArray array];
	NSArray *prefferedAlternative = [self _bodyTypeAttachments];
	for (LEPAbstractAttachment *attachment in prefferedAlternative) {
		[result addObjectsFromArray:[attachment plaintextTypeAttachments]];
	}
	return result;
}

- (NSArray*) attachmentsWithContentIDs {
	NSMutableArray *result = [NSMutableArray array];
	NSArray *prefferedAlternative = [self _bodyTypeAttachments];
	for (LEPAbstractAttachment *attachment in prefferedAlternative) {
		[result addObjectsFromArray:[attachment attachmentsWithContentIDs]];
	}
	if (self.attachments.count != 0) {
		int counter = 0;
		do
		{
			if (prefferedAlternative != [self.attachments objectAtIndex:counter]) {
				for (LEPAbstractAttachment *attachment in[self.attachments objectAtIndex : counter]) {
					[result addObjectsFromArray:[attachment attachmentsWithContentIDs]];
				}
			}
			counter++;
		}
		while (counter < self.attachments.count);
	}
	return result;
}

//Try reeeeally really hard to get an HTML attachment out of this.
- (NSArray *) _bodyTypeAttachments {
	if (self.attachments.count != 0) {
		int counter = 0;
		NSInteger htmlIndex = NSIntegerMax;
		NSInteger textIndex = NSIntegerMax;
		do
		{
			if ([self.attachments objectAtIndex:counter] != nil) {
				for (LEPAbstractAttachment *attachment in[self.attachments objectAtIndex : counter]) {
					if ([attachment.mimeType.lowercaseString isEqualToString:@"text/html"]) {
						htmlIndex = counter;
						break;
					}
					else if ([attachment.mimeType.lowercaseString isEqualToString:@"text/plain"]) {
						textIndex = counter;
					}
				}
			}
			counter++;
		}
		while (counter < self.attachments.count);
		if (htmlIndex == NSIntegerMax) {
			if (textIndex == NSIntegerMax) {
				return nil;
			}
			return [self.attachments objectAtIndex:textIndex];
		}
		return [self.attachments objectAtIndex:htmlIndex];
	}
	return nil;
}

@end