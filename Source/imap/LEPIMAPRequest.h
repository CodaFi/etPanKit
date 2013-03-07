#import <Foundation/Foundation.h>

@protocol LEPIMAPRequestDelegate;
@class LEPIMAPSession;

/**
 * An abstract class that encapsulates a request to the LibEtPan framework.  This class is meant to
 * serve as a base class for requests, and is freely and highly subclass-able.  Subclasses must 
 * override -mainRequest (not -main), and can optionally override -mainFinished.  Operations should
 * typically be sent a -startRequest message immediately after being created, but this is a general
 * guideline and is not enforced by the class.
 */

@interface LEPIMAPRequest : NSOperation {
	id <LEPIMAPRequestDelegate> _delegate;
	LEPIMAPSession * _session;
	NSError * _error;
    NSMutableArray * _resultUidSet;
	BOOL _started;
    NSString * _mailboxSelectionPath;
    NSString * _welcomeString;
}

@property (nonatomic, assign) id <LEPIMAPRequestDelegate> delegate;
@property (nonatomic, copy) NSString * mailboxSelectionPath;

// response
@property (nonatomic, readonly, copy) NSError * error;
@property (nonatomic, retain) LEPIMAPSession * session;
@property (nonatomic, readonly, retain) NSArray * resultUidSet;
@property (nonatomic, readonly, retain) NSString * welcomeString;

// progress
@property (nonatomic, assign, readonly) size_t currentProgress;
@property (nonatomic, assign, readonly) size_t maximumProgress;

/**
 * Enqueues the operation on an internal session queue and starts it.
 */
- (void) startRequest;

/**
 * Enqueues the operation on an internal session queue and starts it.
 @param completionBlock A block called when the operation completes without error.
 @param errorBlock A block called when the operation completes with an error.
 */
- (void) startRequestWithCompletion:(void(^)(LEPIMAPRequest*))completionBlock error:(void(^)(NSError*))errorBlock;
- (void) cancel;

/**
 * The body of the operation that is executed when -main is called internally.  This method should
 * be subclassed, never -main.
 */
- (void) mainRequest;

/**
 * A callback to the operation executed when it has finished.
 */
- (void) mainFinished;

@end

@protocol LEPIMAPRequestDelegate

- (void) LEPIMAPRequest_finished:(LEPIMAPRequest *)op;

@end
