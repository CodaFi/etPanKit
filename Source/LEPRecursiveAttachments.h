//
//  LEPRecursiveAttachments.h
//  etPanKit
//
//  Created by Robert Widmann on 2/28/13.
//
//

#import <Foundation/Foundation.h>

@protocol LEPRecursiveAttachments <NSObject>

@required
- (NSArray *) allAttachments;
- (NSArray *) plaintextTypeAttachments;
- (NSArray *) calendarTypeAttachments;
- (NSArray *) attachmentsWithContentIDs;

@end