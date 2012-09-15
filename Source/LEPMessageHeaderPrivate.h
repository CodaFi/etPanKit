/*
 *  LEPMessageHeaderPrivate.h
 *  etPanKit
 *
 *  Created by DINH Viêt Hoà on 31/01/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "LEPMessageHeader.h"
#include <libetpan/mailimf_types.h>
#include <libetpan/mailimap_types.h>

@interface LEPMessageHeader (LEPMessageHeaderPrivate)

//- (id) _initForCopy;
- (id) _initWithDate:(BOOL)generateDate messageID:(BOOL)generateMessageID;

- (void) setFromIMFFields:(struct mailimf_fields *)fields;
- (struct mailimf_fields *) createIMFFieldsForSending:(BOOL)filter;

- (void) setFromIMAPReferences:(NSData *)data;
- (void) setFromIMAPEnvelope:(struct mailimap_envelope *)env;

- (void) _setFromInternalDate:(struct mailimap_date_time *)date;

- (void) setFromHeadersData:(NSData *)data;

@end
