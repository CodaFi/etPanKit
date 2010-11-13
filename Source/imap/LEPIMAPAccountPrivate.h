/*
 *  LEPIMAPAccountPrivate.h
 *  etPanKit
 *
 *  Created by DINH Viêt Hoà on 18/01/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "LEPIMAPAccount.h"

@interface LEPIMAPAccount (LEPIMAPAccountPrivate)

- (void) _setSubscribedFolders:(NSArray * )folders;
- (void) _setAllFolders:(NSArray * )folders;

- (void) _setupSession;
- (void) _unsetupSession;

- (void) _setupRequest:(LEPIMAPRequest *)request;

- (BOOL) _isGmailFolder:(LEPIMAPFolder *)folder;

@end
