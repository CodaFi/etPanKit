//
//  LEPIMAPSetLabelsRequest.h
//  etPanKit
//
//  Created by Robert Widmann on 11/25/12.
//
//

#import <EtPanKit/LEPIMAPRequest.h>
#import "LEPIMAPSessionPrivate.h"

@interface LEPIMAPStoreLabelsRequest : LEPIMAPRequest

@property (nonatomic, copy) NSString *path;
@property (nonatomic, copy) NSArray *labels;
@property (nonatomic, copy) NSArray *uids;
@property (nonatomic, assign) LEPIMAPStoreLabelsRequestKind kind;

@end
