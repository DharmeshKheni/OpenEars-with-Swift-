//
//  OEDynamicMethod.h
//  OpenEars
//
//  Created by Halle on 1/27/13.
//  Copyright (c) 2014 Politepix. All rights reserved.
//

#import <Foundation/Foundation.h>

/**\cond HIDDEN_SYMBOLS*/

@interface OEDynamicMethod : NSObject


/** Calls method dynamically only on an object which responds to it, with the ability to detect leaks, and returns whether the requested object did respond to the selector. */
+ (BOOL) callDynamicMethodFromName:(NSString *)name onObject:(id)object;

@end
/**\endcond */