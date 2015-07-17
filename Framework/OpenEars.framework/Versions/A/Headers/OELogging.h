//
//  OELogging.h
//  OpenEars
//
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.

#import <Foundation/Foundation.h>

/**
 @class  OELogging
 @brief  A singleton which turns logging on or off for the entire framework. The type of logging is related to overall framework functionality such as the audio session and timing operations. Please turn OELogging on for any issue you encounter. It will probably show the problem, but if not you can show the log on the forum and get help.
 @warning The individual classes such as OEPocketsphinxController and OELanguageModelGenerator have their own verbose flags which are separate from OELogging. 
 */

@interface OELogging : NSObject



/**
@brief   This just turns on logging. If you don't want logging in your session, don't send the startOELogging message.

> Example Usage:
Before implementation:
@code
#import <OpenEars/OELogging.h>;
@endcode
In implementation:
@code 
[OELogging startOpenEarsLogging];
@endcode
*/

+ (id)startOpenEarsLogging;

@end
