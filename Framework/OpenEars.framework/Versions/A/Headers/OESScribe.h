//
//  SScribe.h included here as OESScribe.h
//  Silabas
//
//  Created by Cody Brimhall on 9/4/07.
//  Copyright 2007 Cody Brimhall. All rights reserved.
//

// SScribe.h and SScribe.m are licensed under the MIT License: http://opensource.org/licenses/MIT

// From https://github.com/zbrimhall/Silabas

#import <Foundation/Foundation.h>

/**\cond HIDDEN_SYMBOLS*/
@interface OESScribe : NSObject {
/**\endcond */  
/**\cond HIDDEN_SYMBOLS*/    
	NSDictionary *_grammar;
	NSAttributedString *_originalText;
	NSMutableAttributedString *_renderedText;
	NSCharacterSet *_letters;
	NSCharacterSet *_punctuation;
	NSCharacterSet *_consonants;
	NSCharacterSet *_vowels;
	NSCharacterSet *_nonSyllabicVowels;
	NSDictionary *_identities;
	NSArray *_orthographicClusters;
    NSDictionary *spanishGrammar;
/**\endcond */  
    /**\cond HIDDEN_SYMBOLS*/  
}
/**\endcond */  
    /**\cond HIDDEN_SYMBOLS*/  
@property(nonatomic,strong)NSDictionary *spanishGrammar;
// Initializers
- (instancetype)initWithGrammar:(NSDictionary*)grammar forText:(NSAttributedString*)text sender:(id)sender NS_DESIGNATED_INITIALIZER;

// Accessors
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSMutableAttributedString *renderedText;

// Utility Methods
- (void)processText;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray *wordsInText;
- (void)transcribe:(NSMutableString*)wordBuffer;
- (void)syllabify:(NSMutableString*)wordBuffer;
- (void)renderText:(NSArray*)words;

// Debugging Methods
- (void)setRenderedTextToErrorMessage:(NSString*)message;
/**\endcond */ 
/**\cond HIDDEN_SYMBOLS*/ 
@end
/**\endcond */ 

