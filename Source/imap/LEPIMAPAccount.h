#import <Foundation/Foundation.h>
#import <EtPanKit/LEPConstants.h>

@class LEPIMAPRequest;
@class LEPIMAPSession;
@class LEPIMAPFetchFoldersRequest;
@class LEPIMAPFolder;
@class LEPIMAPCapabilityRequest;
@class LEPIMAPNamespaceRequest;
@class LEPIMAPNamespace;
@class LEPIMAPCheckRequest;

/** 
 
 An LEPIMAPAccount object is a concrete container for the credentials of an account defined either by the user, or unarchived by the program.  It is necessary that the following properties be satisfied with the proper data, else a nil property will cause some method to fail down the line.
 
 - host
 - port
 - login
 - password
 - authType
 
 An LEPIMAPAccount object should act as a springboard for all requests related to folder management.  
 
 An LEPIMAPAccount object also has the unique ability to provide check and capability requests.  If you need to discover, for example, if an account supports IDLE without having to manually look up the provider of the account, use the -capabilityRequest method to get a valid request object.  
 
 */
@interface LEPIMAPAccount : NSObject {
    BOOL _idleEnabled;
	BOOL _checkCertificate;

	//LEPIMAPSession * _session;
    NSMutableArray * _sessions;
    NSDictionary * _gmailMailboxNames;
    NSDictionary * _xListMapping;
    char _defaultDelimiter;
    LEPIMAPNamespace * _defaultNamespace;
}

///---------------------------------------------------------------------------------------
/// @name Server and Fetch Properties
///---------------------------------------------------------------------------------------

/**
 The name of the current host which requests will be sent to.
 
 @warning *IMPORTANT* This property is required to be set.  If it is not, undefined behavior can occur.
 */
@property (nonatomic, copy) NSString * host;

/**
 The port to which requests will be sent through.  
 
 @note This can be hardcoded, but it is recommended that you use an LEPNetService object initialized through an LEPMailProvider object to get the proper port number(s).
 
 @warning *IMPORTANT* This property is required to be set.  If it is not, undefined behavior can occur.
 */
@property (nonatomic) uint16_t port;

/**
 The auth type that requests will be sent with.
 
 @note This can be hardcoded, but it is recommended that you use an LEPNetService object initialized through an LEPMailProvider object to get the proper auth type(s).
 
 @warning *IMPORTANT* This property is required to be set.  If it is not, undefined behavior can occur.
 */
@property (nonatomic) LEPAuthType authType;

/**
 A Realm required for the Microsoft NTLM (NT LAN Manager) protocols.  It is strictly optional, but it required in the case of servers running this protocol.
 
 @note This can be hardcoded, but it is recommended that you use an LEPNetService object initialized through an LEPMailProvider object to get the proper realm.  This may be nil.
  */
@property (nonatomic, copy) NSString * realm; // for NTLM

///---------------------------------------------------------------------------------------
/// @name User Credentials
///---------------------------------------------------------------------------------------

/**
 The username used to authenticate for requests.
 
 @note This can differ from the actual email address of the user.  It is recommended that you use an LEPNetService object to detect this.
 
 @warning *IMPORTANT* This property is required to be set.  If it is not, undefined behavior can occur.

 */
@property (nonatomic, copy) NSString * login;

/**
 The password used to authenticate for requests.
  
 @warning *IMPORTANT* This property is required to be set.  If it is not, undefined behavior can occur.
 
 */
@property (nonatomic, copy) NSString * password;

///---------------------------------------------------------------------------------------
/// @name Certificate Checks
///---------------------------------------------------------------------------------------

/** The option of whether or not to check the certificate of the server the requests are being sent to.  
 
 While this property is entirely optional, it should be noted that it is always best to check the certificate of a server to protect against MIM attacks.  Valid server certificates should pass this test on 10.6, while on 10.7+, deprecations may cause crashes when the server's certificate is invalid.
 
 */
@property (nonatomic, assign) BOOL checkCertificate;

///---------------------------------------------------------------------------------------
/// @name IDLE Support
///---------------------------------------------------------------------------------------

/** Sets the option of whether or not an IDLE connection can be established.
 
 This property defaults to NO, and as such, must be discovered with an LEPNetService object.  Do not attempt to set this property manually unless you are absolutely sure a server supports IDLE.  It is also possible to use a `capabilityRequest` to check for this.
 
 @see LEPIMAPIdleRequest
 
 */
@property (nonatomic, getter=isIdleEnabled) BOOL idleEnabled;

///---------------------------------------------------------------------------------------
/// @name Session Management
///---------------------------------------------------------------------------------------

/** The number of active sessions currently associated with this account.
 
 As requests are started, a connection is established by the LEPIMAPSession object underlying these requests.  As requests are started and enqueued, this property is incremented, and as requests are finished and connections terminated, this property is decremented.
 
 @warning *IMPORTANT* Do not establish many network requests at once, or use a continuous connection.  Doing so will drain power, decrease battery life, and abuse memory.
 
 @see LEPIMAPSession
 
 */
@property (nonatomic) unsigned int sessionsCount;

///---------------------------------------------------------------------------------------
/// @name Timeout Management
///---------------------------------------------------------------------------------------

/** Sets a timeout delay for the current requests that this account creates.
 
 @param timeout An NSTimeInterval representing the time in seconds in which this accounts requests should timeout.
*/

+ (void) setTimeoutDelay:(NSTimeInterval)timeout;

/** The current timeout delay for this account's operations represented as an NSTimeInterval.
 
 @return An NSTimeInterval representing the time in seconds in which this accounts requests should timeout.
 */

+ (NSTimeInterval) timeoutDelay;

///---------------------------------------------------------------------------------------
/// @name Folder Fetching Requests
///---------------------------------------------------------------------------------------

/** Returns an LEPIMAPFetchFoldersRequest object that is used to fetch the folders the account is subscribed to.
 
 Internally creates a private LEPIMAPFetchSubscribedFoldersRequest operation object and sets up its default properties.  The request should be immediately started once it is created.
 
 @return The LEPIMAPFetchFoldersRequest object.
 */

- (LEPIMAPFetchFoldersRequest *) fetchSubscribedFoldersRequest;

/** Returns an LEPIMAPFetchFoldersRequest object that is used to fetch all folders the account contains.
 
 Internally creates a private LEPIMAPFetchAllFoldersRequest operation object and sets up its default properties.  The request should be immediately started once it is created.
 
 @note This method will fetch labels as well if the account is Gmail based.
 @return The LEPIMAPFetchFoldersRequest object.
 */
- (LEPIMAPFetchFoldersRequest *) fetchAllFoldersRequest;

/** Returns an LEPIMAPFetchFoldersRequest object that is used to fetch all folders using the XList standard.
 
 Internally creates a private LEPIMAPFetchAllFoldersRequest operation object and sets up its default properties.  The request shoud be immediately started once it is created.
 
 @note XLIST is a fairly new standard set up to provide an extension to the LIST command.  It is mostly used with Gmail accounts to get "special folders"
 @return The LEPIMAPFetchFoldersRequest object.

 */
- (LEPIMAPFetchFoldersRequest *) fetchAllFoldersUsingXListRequest;

///---------------------------------------------------------------------------------------
/// @name Folder Creation Requests
///---------------------------------------------------------------------------------------

/** Returns an LEPIMAPRequest object that is used to create a folder at the specified path.
 
 Internally creates a private LEPIMAPCreateFolderRequest operation object and sets up its default properties.
 
 @param path A standard path to the folder that includes the default delimiter (e.g. @"[Gmail]/NewFolder").
 @return The LEPIMAPRequest object.
 
 @see defaultNamespace
 */
- (LEPIMAPRequest *) createFolderRequest:(NSString *)path;

///---------------------------------------------------------------------------------------
/// @name Basic Folder Getters
///---------------------------------------------------------------------------------------

/** Returns an LEPIMAPFolder object that represents the default inbox folder for most accounts.
 
 @return Returns the folder `INBOX`.
 */
- (LEPIMAPFolder *) inboxFolder;

/** Returns an LEPIMAPFolder object that represents the provided path.
 
 @return Returns an LEPIMAPFolder object that represents the provided path.
 @param path The path to the folder that you wish to get.  This should include the default delimiter (e.g. @"[Gmail]/SomeFolder").
 @see defaultNamespace

 */
- (LEPIMAPFolder *) folderWithPath:(NSString *)path;

///---------------------------------------------------------------------------------------
/// @name Folder Rename Requests
///---------------------------------------------------------------------------------------
/** Returns an LEPIMAPRequest object that will rename the provided folder.
 
 @return Returns an LEPIMAPRequest object.
 @param path The path to the folder that you wish to rename.  This should include the default delimiter (e.g. @"[Gmail]/SomeFolder").
 @param newPath The new path to the folder that you are renaming.  This should include the default delimiter (e.g. @"[Gmail]/SomeFolder").
 @see defaultNamespace

 */
- (LEPIMAPRequest *) renameRequestPath:(NSString *)path toNewPath:(NSString *)newPath;

/** Returns an LEPIMAPRequest object that will delete the provided folder.
 
 @return Returns an LEPIMAPRequest object.
 @param path The path to the folder that you wish to delete.  This should include the default delimiter (e.g. @"[Gmail]/SomeFolder").
 @see defaultNamespace

 */
- (LEPIMAPRequest *) deleteRequestPath:(NSString *)path;

///---------------------------------------------------------------------------------------
/// @name Capability and Check Requests
///---------------------------------------------------------------------------------------
/** Returns an LEPIMAPCapabilityRequest object that will check for the capabilities of the current account.
 
 @return Returns an LEPIMAPCapabilityRequest object.
 */
- (LEPIMAPCapabilityRequest *) capabilityRequest;

/** Returns an LEPIMAPCapabilityRequest object that will check for the validity of the current account.
 
 If the account or it's credentials are invalid, this object will return an error through its delegate method after it is started.
 
 @note It is recommended that you call this method before any other when a new account is submitted because the validity of an account is an important factor.
 
 @return Returns an LEPIMAPCheckRequest object.
 */
- (LEPIMAPCheckRequest *) checkRequest;

///---------------------------------------------------------------------------------------
/// @name Cancel
///---------------------------------------------------------------------------------------

/** Cancels all current sessions
  
 @note If you find the need to cut the currently active sessions, call this method on the account object to immediately terminate its connections.
*/
- (void) cancel;

///---------------------------------------------------------------------------------------
/// @name Namespace Management
///---------------------------------------------------------------------------------------

/** Returns the default namespace for the current account.  
 
 This method can also be used to retrieve the path delimiter for inbox folders.
 
@return Returns an LEPIMAPNamespace object.
 */
- (LEPIMAPNamespace *) defaultNamespace;

/** Returns a namespace request for the current account.
 
 This method can also be used to retrieve the path delimiter for inbox folders.
 
 @return Returns an LEPIMAPNamespaceRequest object.
 */
- (LEPIMAPNamespaceRequest *) namespaceRequest;

///---------------------------------------------------------------------------------------
/// @name Folder Initializers
///---------------------------------------------------------------------------------------

/** Sets up the current account with the provided folder paths.
 
 @param paths An array of NSString objects (plus path delimiters) that represent the folders associated with the account.
 
 */
- (void) setupWithFoldersPaths:(NSArray *)paths;

/** Sets up the current account with the provided namespace and delimiter.
 
 @param prefix An NSString object that represent the account's prefix.
 @param delimiter A char used to represent the account's path delimiter.

 */
- (void) setupNamespaceWithPrefix:(NSString *)prefix delimiter:(char)delimiter;

@end
