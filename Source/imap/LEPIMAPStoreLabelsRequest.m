//
//  LEPIMAPSetLabelsRequest.m
//  etPanKit
//
//  Created by Robert Widmann on 11/25/12.
//
//

#import "LEPIMAPStoreLabelsRequest.h"

@implementation LEPIMAPStoreLabelsRequest

-(id)init {
	self = [super init];
	
	return self;
}

-(void)mainRequest {
	[self.session _storeLabels:self.labels kind:self.kind messagesUIDs:self.uids path:self.path];
}

-(void)dealloc {
	[self.uids release];
	[self.path release];
	
	[super dealloc];
}

@end
