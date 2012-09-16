//
//  LEPAlternativeAttachment.h
//  etPanKit
//
//  Created by DINH Viêt Hoà on 31/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/**
 An LEPAlternativeAttachment is a container class that can hold instances of LEPAttachment objects or other LEPAlternativeAttachment objects in it's `attachments` property.  The existence of only one class of object in the array returned by this property is not guaranteed, so class checking is a must.  It is recommended that you loop through this class' `attachments` property and retrieve its LEPAttachment objects instead of directly using this class.
 
 
 */
#import <EtPanKit/LEPAbstractAlternativeAttachment.h>

@interface LEPAlternativeAttachment : LEPAbstractAlternativeAttachment <NSCoding, NSCopying> {

}

@end
