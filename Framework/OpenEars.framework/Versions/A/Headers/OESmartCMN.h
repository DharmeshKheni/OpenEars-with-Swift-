//
//  OESmartCMN.h
//  OpenEars
//
//  Created by Halle on 1/27/13.
//  Copyright (c) 2014 Politepix. All rights reserved.
//



/**\cond HIDDEN_SYMBOLS*/

#import <Foundation/Foundation.h>

@interface OESmartCMN : NSObject 

- (void) finalizeCmn:(float)cmnFloat atRoute:(NSString *)routeString forAcousticModelAtPath:(NSString *)acousticModelPath withModelName:(NSString *)modelName;
- (float) smartCmnValuesForRoute:(NSString *)routeString forAcousticModelAtPath:(NSString *)acousticModelPath withModelName:(NSString *)modelName;
- (void) removeCmnPlist;
- (float) defaultCMNForAcousticModelAtPath:(NSString *)path;

@end
/**\endcond */