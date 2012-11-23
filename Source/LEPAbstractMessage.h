#import <Foundation/Foundation.h>

@class LEPMessageHeader;

/**
 An abstract superclass for all directly interactable message objects, including LEPIMAPMessage.
 */

@interface LEPAbstractMessage : NSObject <NSCoding, NSCopying> {
	LEPMessageHeader * _header;
}

/**
 The header for this message
 */
@property (nonatomic, retain, readonly) LEPMessageHeader * header;


@end
