//
//  GrammarGenerator.h
//  OpenEars
//
//  Created by Halle on 9/30/13.
//  Copyright (c) 2013 Politepix. All rights reserved.
//
/**\cond HIDDEN_SYMBOLS*/
#import <Foundation/Foundation.h>
#import "OEGrammarDefinitions.h"

@protocol OEGrammarGeneratorDelegate;

@interface OEGrammarGenerator : NSObject

@property (weak) id<OEGrammarGeneratorDelegate> delegate;
@property(nonatomic, copy) NSString *acousticModelPath;
@property(nonatomic, copy) NSString *plistPath;

- (NSMutableString *) deriveRuleString:(NSString *)workingString withRuleType:(NSString *)ruleType addingWordsToMutableArray:(NSMutableArray *)phoneticDictionaryArray;
- (void) addWorkingString:(NSString *)workingString toRuleArray:(NSMutableArray *)arrayToAdd withRuleType:(NSString *)ruleType isPublic:(BOOL)isPublic;
- (NSError *) createGrammarFromDictionary:(NSDictionary *)grammarDictionary withRequestedName:(NSString *)fileName creatingPhoneticDictionaryArray:(NSArray *)phoneticDictionaryArray;
- (NSString *) analyzeRuleString:(NSString *)ruleString;
- (NSError *) outputJSGFFromRuleArray:(NSArray *)ruleArray usingRuleNumberArray:(NSArray *)ruleNumberArray withRequestedName:(NSString *)fileName;
- (void) processMutableString:(NSMutableString *)mutableString fromRuleArray:(NSArray *)ruleArray atIndex:(int)arrayIndex withSeparator:(NSString *)separator bracket:(BOOL)bracket endCharacter:(NSString *)endCharacter;
- (NSError *) prepareGrammarForGenerationUsingDictionary:(NSDictionary *)grammarDictionary withRequestedName:(NSString *)fileName creatingPhoneticDictionaryArray:(NSMutableArray *)phoneticDictionaryArray  withRuleArray:(NSMutableArray *)ruleArray andRuleNumberArray:(NSMutableArray *)ruleNumberArray;
- (void) cleanUpAfterGeneration;

@end

@protocol OEGrammarGeneratorDelegate <NSObject>

@optional 

- (NSArray *) compactWhitespaceAndFixCharactersOfArrayEntries:(NSArray *)array;
- (NSError *) checkModelForContent:(NSArray *)normalizedLanguageModelArray;
- (void) checkCaseOfWords:(NSArray *)languageModelArray forAcousticModelAtPath:(NSString *)acousticModelPath;
- (NSError *) createDictionaryFromWordArray:(NSArray *)normalizedLanguageModelArray intoDictionaryArray:(NSArray *)dictionaryResultsArray usingAcousticModelAtPath:(NSString *)acousticModelPath;

@end
/**\endcond */