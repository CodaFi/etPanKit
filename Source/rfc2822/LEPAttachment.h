#import <EtPanKit/LEPAbstractAttachment.h>

@interface LEPAttachment : LEPAbstractAttachment <NSCoding, NSCopying> {
    NSData * _data;
}

@property (nonatomic, retain) NSData * data;

+ (NSString *) mimeTypeFromFilename:(NSString *)filename;

- (id) initWithContentsOfFile:(NSString *)filename;

+ (LEPAbstractAttachment *) attachmentWithContentsOfFile:(NSString *)filename;

+ (LEPAbstractAttachment *) attachmentWithHTMLString:(NSString *)html; // with alternative by default
+ (LEPAbstractAttachment *) attachmentWithHTMLString:(NSString *)html withTextAlternative:(BOOL)hasAlternative;

+ (LEPAbstractAttachment *) attachmentWithString:(NSString *)stringValue;

@end
