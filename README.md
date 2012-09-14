# EtPanKit

EtPanKit is an Objective-C interface for the  libEtPan framework for Mac and iOS.  It features:

* Fast, efficient, and secure IMAP and SMTP connections and requests with some POP requests built in.
* Many abstract classes for maximum subclass-ability.
* Abstraction from the LibEtPan C-interface.
* IDLE support.
* NSOperation based classes which are submitted asynchronously to their queue.   
* Block-based and delegate-based callbacks for operations.

# Setup

To use the current development version, add etPanKit as a subproject, then link to either the static library, or the framework.  LibEtPan is automatically included as a dependency if added as a subproject.  Make absolutely sure that the framework is being copied over, but not installed.

# Usage

EtPanKit revolves around the use of request classes, which are submitted to a queue maintained internally by the framework.  To pull down a list of all the emails in the inbox of an IMAP/SMTP based account, initialize an `LEPIMAPAccount` object, set its properties to your liking, then request it's `-inboxFolder`.  At this point, you can get a valid `LEPIMAPFetchMessageRequest` object by using `-fetchMessagesRequest`.  To execute the request, call `-startRequest` on the `LEPIMAPFetchMessageRequest` object.  A sample of such a request is provided below:

```Objective-C
-(id)init {
    if (self = [super init]) {
        /**
        initialize an account with the proper credentials.  
        Invalid credentials return NULL objects, or crash certificate checks.  
        You can get around this with an account check request
        */

        LEPIMAPAccount *sampleAccount = [[LEPIMAPAccount alloc]init];
        [sampleAccount setHost:@"imap.gmail.com"];
        [sampleAccount setPort:587];
        [sampleAccount setLogin:@"myExampleAccount@gmail.com"];
        [sampleAccount setPassword:@"someSecurePassword"];
        [sampleAccount setAuthType:LEPAuthTypeTLS];

        /**
        initialize a fetch request with a delegate callback.  
        Make sure your class conforms to the LEPIMAPRequestDelegate protocol
        */

        LEPIMAPFetchMessageRequest *fetchRequest = [[sampleAccount inboxFolder]fetchMessagesRequest];
        [fetchRequest setDelegate:self];
        [fetchRequest startRequest];
    }
    return self;
}

- (void) LEPIMAPRequest_finished:(LEPIMAPRequest *)op {

    if (!op.error)
        NSLog(@"Success!");
}
```

# Example Project

Unfortunately, EtPanKit does not include a sample project.  This will change in the future.

# Status

While this framework is in use in applications such as Sparrow, this version may be considered volatile and unstable.  Use it at your own risk.

As changes and tweaks are committed, this API may change in backwards-incompatible ways, or break many current projects.  It is my goal to minimize such instances, so future development will revolve around cleanup and documentation work.

The main goal of EtPanKit is to provide a high-quality mail framework with an easy to use interface, while maintaining the ability to subclass and tweak at will.  There are only a few other options for mail frameworks on OSX and iOS, and we aim to be a contender for the top spot.

# Contributing

We will happily accept pull requests that meet one of the following criteria:

 1. It fixes something that is already in EPK. This might be a bug, or something that doesn't work as expected.
 2. It's something so basic or important that EPK really should have it.
 3. Documentation!

# Copyright and License

Copyright 2010 DINH Viet Hoà.

Released Open Source 2010.