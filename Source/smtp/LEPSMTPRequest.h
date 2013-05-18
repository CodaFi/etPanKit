#import <Foundation/Foundation.h>

@protocol LEPSMTPRequestDelegate;
@class LEPSMTPSession;

@interface LEPSMTPRequest : NSOperation {
	id <LEPSMTPRequestDelegate> _delegate;
	NSError * _error;
	LEPSMTPSession * _session;
	BOOL _started;
}

@property (assign) id <LEPSMTPRequestDelegate> delegate;

@property (nonatomic, readonly, copy) NSError * error;
@property (nonatomic, retain) LEPSMTPSession * session;

// progress
@property (nonatomic, assign, readonly) size_t currentProgress;
@property (nonatomic, assign, readonly) size_t maximumProgress;

- (void) startRequest;
- (void) cancel;

/**
 * Enqueues the operation on an internal session queue and starts it.
 @param completionBlock A block called when the operation completes without error.
 @param errorBlock A block called when the operation completes with an error.
 */
- (void) startRequestWithCompletion:(void(^)(LEPSMTPRequest*))completionBlock error:(void(^)(NSError*))errorBlock;

// can be overridden
- (void) mainRequest;
- (void) mainFinished;

@end

@protocol LEPSMTPRequestDelegate

- (void) LEPSMTPRequest_finished:(LEPSMTPRequest *)op;

@end
