//
//  LEPIMAPSearchRequest.m
//  etPanKit
//
//  Created by Robert Widmann on 11/24/12.
//
//

#import "LEPIMAPSearchRequest.h"
#import "LEPUtils.h"
#include <libetpan/mailimap_types_helper.h>
#import "LEPIMAPSessionPrivate.h"

typedef enum {
	LEPKeyKindTo,
	LEPKeyKindFrom,
	LEPKeyKindSubject,
	LEPKeyKindText
}LEPKeyKind;

@interface LEPIMAPSearchRequest ()

@property (nonatomic, copy) NSString *path;
@property (nonatomic, strong) NSIndexSet *foundUIDs;

@end

@implementation LEPIMAPSearchRequest

- (id) initWithPath:(NSString*)path {
	self = [super init];
	
	[self setPath:path];
	
	return self;
}

- (void) mainRequest {
	struct mailimap_search_key *key;
	key = [self _buildSearchKey];
	
	if (key == NULL) {
		LEPLogInternal("LEPIMAPSearchRequest", "24", 0, @"Unable to build Search Key");
		return;
	}
	self.foundUIDs = [self.session _searchFolder:self.path withKey:[self _buildSearchKey]];
	free(key);
}

-(struct mailimap_search_key *)_buildSearchKey {
	if (self.text == nil) {
		if (self.subject == nil) {
			if (self.from == nil) {
				if (self.to == nil) {
					return NO;
				}
				return [self _buildSearchWithOption:LEPKeyKindTo];
			}
			return [self _buildSearchWithOption:LEPKeyKindFrom];
		}
		return [self _buildSearchWithOption:LEPKeyKindSubject];
	}
	return [self _buildSearchWithOption:LEPKeyKindText];
}

-(char *)_mallocText:(NSString*)text {
	char *buf = malloc([text maximumLengthOfBytesUsingEncoding:NSUTF8StringEncoding] + 1);
	BOOL result = [text getCString:buf maxLength:[text maximumLengthOfBytesUsingEncoding:NSUTF8StringEncoding] encoding:NSUTF8StringEncoding];
	if (result == NO) {
		return NULL;
	}
	return buf;
}

-(struct mailimap_search_key *)_buildSearchWithOption:(LEPKeyKind)option {
	switch (option) {
		case LEPKeyKindTo:
			
			return mailimap_search_key_new(MAILIMAP_SEARCH_KEY_OR, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, mailimap_search_key_new_to([self _mallocText:self.to]), mailimap_search_key_new_or(mailimap_search_key_new_cc([self _mallocText:self.to]), mailimap_search_key_new_bcc([self _mallocText:self.to])), NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
			
		case LEPKeyKindFrom:
			
			return mailimap_search_key_new(MAILIMAP_SEARCH_KEY_FROM, NULL, NULL, NULL, NULL, [self _mallocText:self.from], NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
			
		case LEPKeyKindSubject:
			
			return mailimap_search_key_new(MAILIMAP_SEARCH_KEY_SUBJECT, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, [self _mallocText:self.subject], NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
			
		case LEPKeyKindText:
		
			return [self textSearchKey];
			break;
		default:
			break;
	}
	return NULL;
}
																		   
-(struct mailimap_search_key *)textSearchKey {
	struct mailimap_search_key *toSearch = mailimap_search_key_new(MAILIMAP_SEARCH_KEY_OR, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, mailimap_search_key_new_to([self _mallocText:self.to]), mailimap_search_key_new_or(mailimap_search_key_new_cc([self _mallocText:self.to]), mailimap_search_key_new_bcc([self _mallocText:self.to])), NULL, NULL, NULL, NULL, NULL, NULL, NULL);
																   
   struct mailimap_search_key *or1 = mailimap_search_key_new_or(mailimap_search_key_new_text([self _mallocText:self.text]), toSearch);
   
   struct mailimap_search_key *from = mailimap_search_key_new(MAILIMAP_SEARCH_KEY_FROM, NULL, NULL, NULL, NULL, [self _mallocText:self.from], NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   struct mailimap_search_key *or2 = mailimap_search_key_new_or(mailimap_search_key_new_text([self _mallocText:self.text]), from);
   
   return mailimap_search_key_new_or(or1, or2);
}

@end
