#import <EtPanKit/LEPIMAPRequest.h>
#import <EtPanKit/LEPConstants.h>

@class LEPIMAPFetchFolderMessagesRequest;
@class LEPMessage;
@class LEPIMAPMessage;
@class LEPIMAPAccount;
@class LEPIMAPFolder;
@class LEPIMAPIdleRequest;
@class LEPIMAPCapabilityRequest;
@class LEPIMAPSearchRequest;

/**
 @class LEPIMAPFolder
 @abstract A class that represents an IMAP folder
 @discussion This class encapsulates an IMAP folder, and provides an interface through which one can fetch messages with varying degrees
 of detail (as it were).  It also allows for requests to copy and remove messages from the folder, remove all messages (expunge), and flags requests.  Perhaps most important of all is the IDLE request, which is recommended only for the INBOX folder.
 */

@interface LEPIMAPFolder : NSObject {
    LEPIMAPAccount * _account;
	char _delimiter;
    int _flags;
    NSString * _path;
	uint32_t _uidValidity;
	uint32_t _uidNext;
}

@property (nonatomic, readonly, retain) LEPIMAPAccount * account;
@property (nonatomic, readonly) NSString * path;
@property (nonatomic, readonly) uint32_t uidValidity;
@property (nonatomic, readonly) uint32_t uidNext;
@property (nonatomic, assign, readonly) int flags;
@property (nonatomic, assign) NSUInteger messageCount;

#pragma mark -

/**
 @method displayName
 @abstract The display name of this folder as it appears to the user
 @discussion Set when the folder is completely requested, not when the path is set
 @result An NSString if the folder has been initialized and fetched correctly, otherwise nil
 */
- (NSString *) displayName;

/**
 @method pathComponents
 @abstract Returns an array of the components of the path of the folder
 @discussion Returns the components of the path separated by the path delimiter.
 @result A full NSArray if the folder has a path, an empty Array if it has no path, otherwise nil
 */
- (NSArray *) pathComponents;

#pragma mark -

/**
 @method encodePathName:
 @abstract Encodes the path of the folder in UTF-7
 @discussion A method that encodes a given string in UTF-7 
 @result An NSString if path is non-nil, otherwise nil
 @param path An NSString containing a valid UTF-8 string.
 */
+ (NSString *) encodePathName:(NSString *)path;

/**
 @method decodePathName:
 @abstract Decodes the path of a folder in UTF-7 to UTF-8
 @discussion A method that decodes a given string from UTF-7 to UTF-8
 @result An NSString if path is non-nil, otherwise nil
 @param path An NSString containing a valid UTF-7 string.
 */
+ (NSString *) decodePathName:(NSString *)path;


#pragma mark -

/**
 @method fetchMessagesRequest
 @abstract A request to fetch all messages in a folder.
 @discussion A method that fetches all the messages in a folder.  It fetches UIDs, Flags, and Structure (envelope),
 and is a rather expensive process.  It is more logical to save these requests for last, in order to maintain a speedy UI.
 @result An LEPIMAPFetchFolderMessagesRequest.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesRequest;

/**
 @method fetchMessagesRequest:
 @abstract A request to fetch all messages in a folder from a given UID.
 @discussion A method that fetches all the messages in a folder from a given UID forward to UID 0 (for example, UID 700 to 0).  
 
 It fetches UIDs, Flags, and Structure (envelope), and is a rather expensive process.  It is more logical to save these requests for last, in order to maintain a speedy UI.
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param uid The UID from which to fetch messages.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesRequestFromUID:(uint32_t)uid;

/**
 @method fetchMessagesRequest:toUID:
 @abstract A request to fetch all messages in a folder from a given UID to a given UID.
 @discussion A method that fetches all the messages in a folder from a given UID to a given UID.  
 
 It fetches UIDs, Flags, and Structure (envelope),
 and is a rather expensive process.  It is more logical to save these requests for last, in order to maintain a speedy UI.
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param fromUID The UID from which to fetch messages.
 @param toUID The UID at which to stop fetching messages.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesRequestFromUID:(uint32_t)fromUID toUID:(uint32_t)toUID;

#pragma mark -

/**
 @method fetchMessagesUIDRequest
 @abstract A request to fetch all messages with UIDs in a folder.
 @discussion A method that fetches all the messages along with their UIDs in the folder.  This request does not
 fetch Structure (headers) or Flags, so it is really only to get a fairly quick glance at how many messages are in the folder
 itself.  This is generally a more reliable counter than the `messageCount` property. 
 @result An LEPIMAPFetchFolderMessagesRequest.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDRequest;

/**
 @method fetchMessagesUIDRequest:
 @abstract A request to fetch messages with UIDs in a folder from a given UID.
 @discussion A method that fetches the messages along with their UIDs in the folder from a given UID forward to UID 0 (for example, UID 700 to 0).
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param uid The UID from which to fetch messages.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDRequestFromUID:(uint32_t)uid;

/**
 @method fetchMessagesUIDRequest:toUID:
 @abstract A request to fetch messages with UIDs in a folder from a given UID to a given UID.
 @discussion A method that fetches the messages along with their UIDs in the folder from a given UID to a given UID.
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param fromUID The UID from which to fetch messages.
 @param toUID The UID at which to stop message fetching.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDRequestFromUID:(uint32_t)fromUID toUID:(uint32_t)toUID;

#pragma mark -

/**
 @method fetchMessagesUIDFlagsRequest
 @abstract A request to fetch all messages with UIDs and flags in the folder.
 @discussion A method that fetches the messages along with their UIDs and headers in the folder.  This request is only slightly more expensive than
 fetching only UIDs because of the extra information that flags contain, however it is not as costly as requesting full structure.
 @result An LEPIMAPFetchFolderMessagesRequest.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDFlagsRequest;

/**
 @method fetchMessagesUIDFlagsRequest:
 @abstract A request to fetch messages with UIDs and flags in the folder from a given UID.
 @discussion A method that fetches the messages along with their UIDs and headers in the folder from a 
 given UID forward (for example, UID 700 to 0).
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param uid the UID from which to fetch
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDFlagsRequestFromUID:(uint32_t)uid;

/**
 @method fetchMessagesUIDFlagsRequest:toUID:
 @abstract A request to fetch messages with UIDs and flags in the folder from a given UID to a given UID.
 @discussion A method that fetches the messages along with their UIDs and headers in the folder from a given UID to a given UID.
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param uid the UID from which to fetch
 @param toUID the UID at which to stop fetching messages
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesUIDFlagsRequestFromUID:(uint32_t)fromUID toUID:(uint32_t)toUID;

#pragma mark -

/**
 @method fetchMessagesWithStructureRequest
 @abstract A request to fetch all messages with UIDs, Flags, and Structure in the folder.
 @discussion A method that fetches the messages along with their UIDs, Headers, and Structure in the folder.  This request is the most expensive of them all because structure involves fetching the general outline of the body and the general structure of attachments. Calling this does not
 fetch attachment data automatically, but it does fetch and store attachment classes which can then be used to get individual attachments
 @result An LEPIMAPFetchFolderMessagesRequest.
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesWithStructureRequest;

/**
 @method fetchMessagesWithStructureRequest:
 @abstract A request to fetch messages with UIDs, Flags, and Structure from a given UID in the folder.
 @discussion A method that fetches the messages along with their UIDs, Headers, and Structure from a given UID forward in the folder.
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param uid the UID from which to fetch
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesWithStructureRequestFromUID:(uint32_t)uid;

/**
 @method fetchMessagesWithStructureRequest:
 @abstract A request to fetch messages with UIDs, Flags, and Structure from a given UID to a given UID in the folder.
 @discussion A method that fetches the messages along with their UIDs, Headers, and Structure from a given UID to a given UID in the folder.
 @result An LEPIMAPFetchFolderMessagesRequest.
 @param uid the UID from which to fetch
 @param toUID the UID at which to stop fetching messages
 */
- (LEPIMAPFetchFolderMessagesRequest *) fetchMessagesWithStructureRequestFromUID:(uint32_t)fromUID toUID:(uint32_t)toUID;

#pragma mark -

- (LEPIMAPRequest *) appendMessageRequest:(LEPMessage *)message;
- (LEPIMAPRequest *) appendMessageRequest:(LEPMessage *)message flags:(LEPIMAPMessageFlag)flags;
- (LEPIMAPRequest *) copyMessages:(NSArray * /* LEPIMAPMessage */)messages toFolder:(LEPIMAPFolder *)folder;
- (LEPIMAPRequest *) copyMessagesUIDs:(NSArray * /* NSNumber uint32_t */)messagesUids toFolder:(LEPIMAPFolder *)folder;

- (LEPIMAPRequest *) subscribeRequest;
- (LEPIMAPRequest *) unsubscribeRequest;

- (LEPIMAPSearchRequest*)searchRequest;

- (LEPIMAPRequest *) deleteRequest;
- (LEPIMAPRequest *) renameRequestWithNewPath:(NSString *)newPath;

- (LEPIMAPRequest *) expungeRequest;

// update uidValidity and uidNext
- (LEPIMAPRequest *) selectRequest;

- (LEPIMAPRequest *) addFlagsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages flags:(LEPIMAPMessageFlag)flags;
- (LEPIMAPRequest *) removeFlagsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages flags:(LEPIMAPMessageFlag)flags;
- (LEPIMAPRequest *) setFlagsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages flags:(LEPIMAPMessageFlag)flags;

- (LEPIMAPRequest *) addLabelsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages labels:(NSArray*)labels;
- (LEPIMAPRequest *) addLabelsToMessagesUIDsRequest:(NSArray * /* LEPIMAPMessage */)messages labels:(NSArray*)labels;

- (LEPIMAPRequest *) removeLabelsToMessagesRequest:(NSArray * /* LEPIMAPMessage */)messages labels:(NSArray*)labels;
- (LEPIMAPRequest *) removeLabelsToMessagesUIDsRequest:(NSArray * /* LEPIMAPMessage */)messages labels:(NSArray*)labels;

- (LEPIMAPIdleRequest *) idleRequest;
- (LEPIMAPCapabilityRequest *) capabilityRequest;

@end
