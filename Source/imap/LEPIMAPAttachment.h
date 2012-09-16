#import <EtPanKit/LEPAbstractAttachment.h>

@class LEPIMAPFetchAttachmentRequest;

/**
 
 An LEPIMAPAttachment object is a concrete form of the LEPAbstractAttachment object, and is used to encapsulate the body of a message (both in plain text, and in HTML).  This class automatically sets its partID and size when the object returned from its `fetchRequest` method is started.  
 
 When a message object is recieved, it's attachments are known, however they are not yet fetched.  As such, this object acts as a placeholder until such a time as its data is requested.
 
 Because the size of the attachment is unknown until it is requested, it is not recommended that you fetch in tight loops unless data is cached or persisted on disk.  
 */

@interface LEPIMAPAttachment : LEPAbstractAttachment <NSCoding, NSCopying> {
	NSString * _partID;
	int _encoding;
	size_t _size;
}

/** The part ID of the current attachment.
 
 This property denotes the partID of the current attachment.  
  */
@property (nonatomic, retain, readonly) NSString * partID;
/** The size of the current attachment.
 
 This property denotes the size of the current attachment.
 */
@property (nonatomic, assign, readonly) size_t size;

/** An LEPIMAPFetchAttachmentRequest object used to fetch the attachment and its properties.
 
@return Returns an LEPIMAPFetchAttachmentRequest object.
 */
- (LEPIMAPFetchAttachmentRequest *) fetchRequest;

/** The size of the current attachment after decoding.
 
 @return Returns a size_t value.
 */
- (size_t) decodedSize;

@end
