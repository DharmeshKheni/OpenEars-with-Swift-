//
//  OEFliteVoice.h
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
/**\cond HIDDEN_SYMBOLS*/
#import <Foundation/Foundation.h>
 
#import "flite.h"
 
@interface OEFliteVoice : NSObject

@property (nonatomic, assign) int target_mean_default;
@property (nonatomic, assign) int target_stddev_default;
@property (nonatomic, assign) int duration_stretch_default;
@property (nonatomic, assign) cst_voice *voice;

@end

/**\endcond*/ 
