//
//  LEPMimeManager.m
//  etPanKit
//
//  Created by Robert Widmann on 11/21/12.
//
//

#import "LEPMimeManager.h"
#import "LEPSingleton.h"

@interface LEPMimeManager ()

@property (nonatomic, retain) NSDictionary *mimeTypesMap;
@property (nonatomic, retain) NSDictionary *extensionsAsMimesMap;

@property (nonatomic, retain) NSArray *possibleImageExtensions;
@property (nonatomic, retain) NSArray *possibleImageMimeTypes;
@property (nonatomic, retain) NSArray *possibleArchiveMimeTypes;

@end

@implementation LEPMimeManager

+ (LEPMimeManager *) sharedManager
{
	LEPSINGLETON(LEPMimeManager);
}

- (id) init {
	if (self = [super init]) {
		self.possibleImageExtensions = [NSArray arrayWithObjects:@"jpg", @"jpeg", @"png", @"gif", @"tiff", @"tif", nil];
		self.possibleImageMimeTypes = [NSArray arrayWithObjects:@"image/jpeg", @"image/gif", @"image/png", @"image/tiff", @"image/tif", nil];
		self.possibleArchiveMimeTypes = [NSArray arrayWithObjects:@"zip", @"sfark", @"s7z", @"ace", @"cpt", @"dar", @"pit", @"sea", @"sit", @"par",
										 @"par2", @"gz", @"tgz", @"bz2", @"tbz", @"Z", @"taz", @"lz", @"tlz", @"7z", nil];
		self.mimeTypesMap = [NSDictionary dictionaryWithObjectsAndKeys:@"image/jpeg", @"jpg", @"image/jpeg", @"jpeg",
							 @"application/pdf", @"pdf", @"image/gif", @"gif", @"image/png", @"png", @"image/tiff", @"tiff",
							 @"image/tiff", @"tif", @"image/bmp", @"bmp", @"application/zip", @"zip", @"text/calendar", @"ics",
							 @"message/rfc822", @"eml", nil];
		self.extensionsAsMimesMap = [NSDictionary dictionaryWithObjectsAndKeys:@"jpg", @"image/jpeg", @"jpeg", @"image/jpeg",
									 @"pdf", @"application/pdf", @"gif", @"image/gif", @"png", @"image/png", @"tiff", @"image/tiff",
									 @"tiff", @"image/tif", @"bmp", @"image/bmp", @"zip", @"application/zip", @"ics", @"text/calendar",
									 @"eml", @"message/rfc822", nil];
	}
	return self;
}

//Just grab the path extension.  Nothing fancy.
- (BOOL) isFileTypePDF:(NSString *)filename {
	return [[filename.pathExtension lowercaseString] isEqualToString:@"pdf"];
}

- (BOOL) isMimeTypePDF:(NSString *)mimeType {
	return [[mimeType.pathExtension lowercaseString] hasSuffix:@"pdf"];
}

//-[NSArray containsObject:] doesn't cut it, we have to loop.
//break; when we have the first match, because files extensions don't usually
//freak out and change all that often... I hope.
- (BOOL) isFileTypeImage:(NSString *)filename {
	BOOL result = NO;
	NSString *pathExt = [filename.pathExtension lowercaseString];
	for (NSString *imageExt in self.possibleImageExtensions) {
		if ([imageExt isEqualToString:pathExt]) {
			result = YES;
			break;
		}
	}
	return result;
}

//Same as above: looping, break on first match, yadda yadda yadda.
- (BOOL) isMimeTypeImage:(NSString *)mimeType {
	BOOL result = NO;
	NSString *mimeString = [mimeType lowercaseString];
	for (NSString *imageExt in self.possibleImageMimeTypes) {
		if ([imageExt isEqualToString:mimeString]) {
			result = YES;
			break;
		}
	}
	return result;
}

//Same as above: looping, break on first match, yadda yadda yadda.
- (BOOL) isFileTypeZip:(NSString *)filename {
	BOOL result = NO;
	NSString *pathExt = [filename.pathExtension lowercaseString];
	for (NSString *archiveExt in self.possibleArchiveMimeTypes) {
		if ([archiveExt isEqualToString:pathExt]) {
			result = YES;
			break;
		}
	}
	return result;
}

- (NSString *) mimeTypeForFile:(NSString *)filename {
	return [self.mimeTypesMap objectForKey:[filename.pathExtension lowercaseString]];
}

- (NSString *) pathExtensionForMimeType:(NSString *)mimeType {
	return [self.extensionsAsMimesMap objectForKey:[mimeType lowercaseString]];
}

- (void)dealloc {
	[_extensionsAsMimesMap release];
	[_mimeTypesMap release];
	[_possibleImageExtensions release];
	[_possibleImageMimeTypes release];
	[_possibleArchiveMimeTypes release];
	[super dealloc];
}

@end