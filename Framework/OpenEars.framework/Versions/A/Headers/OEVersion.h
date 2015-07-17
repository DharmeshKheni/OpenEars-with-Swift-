//
//  OEVersion.h
//  OpenEars
//
//  Created by Halle on 9/24/12.
//  Copyright (c) 2012 Politepix. All rights reserved.
//

#define kCurrentVersionTokenized @"{{{{2.041}}}}"
#define kCurrentVersion [[kCurrentVersionTokenized stringByReplacingOccurrencesOfString:@"{" withString:@""] stringByReplacingOccurrencesOfString:@"}" withString:@""]
