//
//  OENotification.h
//  OpenEars
//
//  Created by Halle on 1/27/13.
//  Copyright (c) 2014 Politepix. All rights reserved.
//

#import <Foundation/Foundation.h>

/**\cond HIDDEN_SYMBOLS*/

@interface OENotification : NSObject


/** Send notification. */
+ (void) performOpenEarsNotificationOnMainThread:(NSString *)notificationNameAsString withOptionalObjects:(NSArray *)objects andKeys:(NSArray *)keys;

@end
/**\endcond */