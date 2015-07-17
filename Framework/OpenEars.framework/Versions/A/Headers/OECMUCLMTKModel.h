//
//  OECMUCLMTKModel.h
//  OpenEars 
//  http://www.politepix.com/openears
//
//  OECMUCLMTKModel is a class which abstracts the conversion of vocabulary into language models
//  OpenEars
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.
/**\cond HIDDEN_SYMBOLS*/

//#define KEEPFILES

#import <Foundation/Foundation.h>

@interface OECMUCLMTKModel : NSObject

- (void) runCMUCLMTKOnCorpusFile:(NSString *)fileName withDMP:(BOOL)withDMP;
- (void) convertARPAAtPath:(NSString *)arpaFileName toDMPAtPath:(NSString *)dmpFileName;

@property (nonatomic, copy) NSString *algorithmType;
@property (nonatomic, assign) int verbosity;
@property (nonatomic, strong) NSNumber *ngrams;

@end
/**\endcond */
