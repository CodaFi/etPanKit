#ifndef LEPSINGLETON_H

#define LEPSINGLETON_H

#define LEPSINGLETON(className) \
{ \
static className *sharedInstance = nil; \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
	sharedInstance = [[className alloc] init]; \
}); \
return sharedInstance; \
}

#endif
