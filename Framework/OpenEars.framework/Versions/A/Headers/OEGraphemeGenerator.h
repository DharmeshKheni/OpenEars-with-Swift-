//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEGraphemeGenerator.h
//  OpenEars
// 
//  OEGraphemeGenerator is a class which creates pronunciations for words which aren't in the dictionary
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.
/**\cond HIDDEN_SYMBOLS*/
#import <Foundation/Foundation.h>
//#import "OEAudioConstants.h"

@interface OEGraphemeGenerator : NSObject

- (NSString *) convertGraphemes:(NSString *)phrase;
@end
/**\endcond */
