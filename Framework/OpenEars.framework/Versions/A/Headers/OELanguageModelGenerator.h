//  OpenEars 
//  http://www.politepix.com/openears
//
//  OELanguageModelGenerator.h
//  OpenEars
//
//  OELanguageModelGenerator is a class which creates new language models and grammars
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  This file is licensed under the Politepix Shared Source license found in the root of the source distribution.


/**
 @class  OELanguageModelGenerator
 @brief  The class that generates the vocabulary the OEPocketsphinxController is able to understand.
 
 ## Usage examples
 > What to add to your implementation:
 @htmlinclude OELanguageModelGenerator_Implementation.txt
 > How to use the class methods:
 @htmlinclude OELanguageModelGenerator_Calls.txt 
 */

#import <Foundation/Foundation.h>

@class OEGraphemeGenerator;

#import "OEGrammarDefinitions.h"
#import "OEGrammarGenerator.h"

@interface OELanguageModelGenerator : NSObject <OEGrammarGeneratorDelegate>

/**Set this to TRUE to get verbose output*/
@property(nonatomic,assign)    BOOL verboseLanguageModelGenerator;
   /**Advanced: if you are using your own acoustic model or an custom dictionary contained within an acoustic model and these don't use the same phonemes as the English or Spanish acoustic models, you will need to set useFallbackMethod to FALSE so that no attempt is made to use the English or Spanish fallback method for finding pronunciations of words which don't appear in the custom acoustic model's phonetic dictionary.*/ 
@property(nonatomic,assign) BOOL useFallbackMethod;


/**\cond HIDDEN_SYMBOLS*/ 

@property(nonatomic,copy) NSString * pathToCachesDirectory;
@property(nonatomic,strong) OEGraphemeGenerator *graphemeGenerator;
@property(nonatomic,strong) NSNumber *ngrams;
@property(nonatomic, strong) NSMutableArray *iterationStorageArray;

- (NSError *) writeOutCorpusForArray:(NSArray *)normalizedLanguageModelArray toFilename:(NSString *)fileName;
- (void) createLanguageModelFromFilename:(NSString *)fileName;
/**\endcond*/  


/**Generate a probabilistic language model from an array of NSStrings which are the words and phrases you want OEPocketsphinxController or OEPocketsphinxController+RapidEars to understand, using your chosen acoustic model. 
 
 Putting a phrase in as a string makes it somewhat more probable that the phrase will be recognized as a phrase when spoken. If you only ever want certain phrases or word sequences to be recognized at the exclusion of other combinations, use - (NSError *) generateGrammarFromDictionary:(NSDictionary *)grammarDictionary withFilesNamed:(NSString *)fileName forAcousticModelAtPath:(NSString *)acousticModelPath below instead to create a rules-based grammar instead of a probabilistic language model.
 
 fileName is the way you want the output files to be named, for instance if you enter "MyDynamicLanguageModel" you will receive files output to your Caches directory titled MyDynamicLanguageModel.dic, MyDynamicLanguageModel.arpa, and MyDynamicLanguageModel.DMP. 
 
If your input text has numbers such as '1970' or '3' you should spell them out ("Nineteen-seventy", or alternately "One Thousand One Hundred Seventy", or "Three" in a contextually-appropriate way before submitting them to get the most accurate results. This can't be done automatically for you yet and at the moment numbers will trigger the fallback technique, which will only take a best guess at the intention with no alternate pronunciations and give sub-optimal recognition results where the guess is incorrect. 
 
 Additionally, if there are ambiguous symbols in your text such as '$' or '+' they will be removed from the text, as it is not possible to reliably detect the context or intention for these symbols or whether they are even intended to be transcribed at all. Therefore if you intend for them to be spoken or synthesized in your app interface, please replace them with spelled-out forms of the same symbol, e.g. "dollars" or "dollar" for '$' and "plus" or "and" for '+', and for all other similar types of symbols found in your text. 
 
 If you are feeding in arbitrary text and experiencing unexpected results in terms of what is recognized or accuracy rates, please investigate your text for symbols and numbers which are (unavoidably) being transformed by OELanguageModelGenerator and transcribe them yourself for best results. Alphabetical characters and apostrophes and hyphens which appear in a word, as well as sentence ending symbols and clause-separating symbols, will remain intact. 
 
 OELanguageModelGenerator no longer has any case preference when inputting text, so you don't have to be concerned about whether your input is capitalized or not; you only have to pay attention in your own app implementation that phrases you are trying to detect are matchable against the case you actually used to create your model using this class.
 
 If this method is successful it will return nil. If it returns nil, you can use the methods pathToSuccessfullyGeneratedDictionaryWithRequestedName: and pathToSuccessfullyGeneratedLanguageModelWithRequestedName: or pathToSuccessfullyGeneratedGrammarWithRequestedName: to get your paths to your newly-generated language models and grammars and dictionaries for use with OEPocketsphinxController. If it doesn't return nil, it will return an error which you can check for debugging purposes.
 */

- (NSError *) generateLanguageModelFromArray:(NSArray *)languageModelArray withFilesNamed:(NSString *)fileName forAcousticModelAtPath:(NSString *)acousticModelPath;

/** If generateLanguageModelFromArray:withFilesNamed:forAcousticModelAtPath: does not return an error, you can use this method to receive the full path to your generated phonetic dictionary for use with OEPocketsphinxController. */
- (NSString *) pathToSuccessfullyGeneratedDictionaryWithRequestedName:(NSString *)name;
/** If generateLanguageModelFromArray:withFilesNamed:forAcousticModelAtPath: does not return an error, you can use this method to receive the full path to your generated language model for use with OEPocketsphinxController. */
- (NSString *) pathToSuccessfullyGeneratedLanguageModelWithRequestedName:(NSString *)name;
/** If generateLanguageModelFromArray:withFilesNamed:forAcousticModelAtPath: does not return an error, you can use this method to receive the full path to your generated grammar for use with OEPocketsphinxController. */
- (NSString *) pathToSuccessfullyGeneratedGrammarWithRequestedName:(NSString *)name;

/**Dynamically generate a JSGF grammar using OpenEars' natural language system for defining a speech recognition ruleset. This will recognize exact phrases instead of probabilistically recognizing word combinations in any sequence.
 
 The NSDictionary you submit to the argument generateGrammarFromDictionary: is a key-value pair consisting of an NSArray of words stored in NSStrings indicating the vocabulary to be listened for, and an NSString key which is one of the following #defines from GrammarDefinitions.h, indicating the rule for the vocabulary in the NSArray:
\verbatim
ThisWillBeSaidOnce
ThisCanBeSaidOnce
ThisWillBeSaidWithOptionalRepetitions
ThisCanBeSaidWithOptionalRepetitions
OneOfTheseWillBeSaidOnce
OneOfTheseCanBeSaidOnce
OneOfTheseWillBeSaidWithOptionalRepetitions
OneOfTheseCanBeSaidWithOptionalRepetitions
\endverbatim
 
Breaking them down one at a time for their specific meaning in defining a rule:

 \verbatim
 
ThisWillBeSaidOnce // This indicates that the word or words in the array must be said (in sequence, in the case of multiple words), one time.
ThisCanBeSaidOnce // This indicates that the word or words in the array can be said (in sequence, in the case of multiple words), one time, but can also be omitted as a whole from the utterance.
ThisWillBeSaidWithOptionalRepetitions // This indicates that the word or words in the array must be said (in sequence, in the case of multiple words), one time or more.
ThisCanBeSaidWithOptionalRepetitions // This indicates that the word or words in the array can be said (in sequence, in the case of multiple words), one time or more, but can also be omitted as a whole from the utterance.
OneOfTheseWillBeSaidOnce // This indicates that exactly one selection from the words in the array must be said one time.
OneOfTheseCanBeSaidOnce // This indicates that exactly one selection from the words in the array can be said one time, but that all of the words can also be omitted from the utterance.
OneOfTheseWillBeSaidWithOptionalRepetitions // This indicates that exactly one selection from the words in the array must be said, one time or more.
OneOfTheseCanBeSaidWithOptionalRepetitions // This indicates that exactly one selection from the words in the array can be said, one time or more, but that all of the words can also be omitted from the utterance.
\endverbatim
 
Since an NSString in these NSArrays can also be a phrase, references to words above should also be understood to apply to complete phrases when they are contained in a single NSString.
 
A key-value pair can also have NSDictionaries in the NSArray instead of NSStrings, or a mix of NSStrings and NSDictionaries, meaning that you can nest rules in other rules.

Here is an example of a complex rule which can be submitted to the generateGrammarFromDictionary: argument followed by an explanation of what it means:
 
 \verbatim
 @{
     ThisWillBeSaidOnce : @[
         @{ OneOfTheseCanBeSaidOnce : @[@"HELLO COMPUTER", @"GREETINGS ROBOT"]},
         @{ OneOfTheseWillBeSaidOnce : @[@"DO THE FOLLOWING", @"INSTRUCTION"]},
         @{ OneOfTheseWillBeSaidOnce : @[@"GO", @"MOVE"]},
         @{ThisWillBeSaidWithOptionalRepetitions : @[
             @{ OneOfTheseWillBeSaidOnce : @[@"10", @"20",@"30"]}, 
             @{ OneOfTheseWillBeSaidOnce : @[@"LEFT", @"RIGHT", @"FORWARD"]}
         ]},
         @{ OneOfTheseWillBeSaidOnce : @[@"EXECUTE", @"DO IT"]},
         @{ ThisCanBeSaidOnce : @[@"THANK YOU"]}
     ]
 };
\endverbatim
 
 Breaking it down step by step to explain exactly what the contents mean:
 
 \verbatim
 @{
     ThisWillBeSaidOnce : @[ // This means that a valid utterance for this ruleset will obey all of the following rules in sequence in a single complete utterance:
         @{ OneOfTheseCanBeSaidOnce : @[@"HELLO COMPUTER", @"GREETINGS ROBOT"]}, // At the beginning of the utterance there is an optional statement. The optional statement can be either "HELLO COMPUTER" or "GREETINGS ROBOT" or it can be omitted.
         @{ OneOfTheseWillBeSaidOnce : @[@"DO THE FOLLOWING", @"INSTRUCTION"]}, // Next, an utterance will have exactly one of the following required statements: "DO THE FOLLOWING" or "INSTRUCTION".
         @{ OneOfTheseWillBeSaidOnce : @[@"GO", @"MOVE"]}, // Next, an utterance will have exactly one of the following required statements: "GO" or "MOVE"
         @{ThisWillBeSaidWithOptionalRepetitions : @[ // Next, an utterance will have a minimum of one statement of the following nested instructions, but can also accept multiple valid versions of the nested instructions:
             @{ OneOfTheseWillBeSaidOnce : @[@"10", @"20",@"30"]}, // Exactly one utterance of either the number "10", "20" or "30",
             @{ OneOfTheseWillBeSaidOnce : @[@"LEFT", @"RIGHT", @"FORWARD"]} // Followed by exactly one utterance of either the word "LEFT", "RIGHT", or "FORWARD".
         ]},
         @{ OneOfTheseWillBeSaidOnce : @[@"EXECUTE", @"DO IT"]}, // Next, an utterance must contain either the word "EXECUTE" or the phrase "DO IT",
         @{ ThisCanBeSaidOnce : @[@"THANK YOU"]} and there can be an optional single statement of the phrase "THANK YOU" at the end.
     ]
 };
 
 \endverbatim
 
So as examples, here are some sentences that this ruleset will report as hypotheses from user utterances:

 \verbatim
"HELLO COMPUTER DO THE FOLLOWING GO 20 LEFT 30 RIGHT 10 FORWARD EXECUTE THANK YOU"
"GREETINGS ROBOT DO THE FOLLOWING MOVE 10 FORWARD DO IT"
"INSTRUCTION 20 LEFT 20 LEFT 20 LEFT 20 LEFT EXECUTE"

 \endverbatim
 
But it will not report hypotheses for sentences such as the following which are not allowed by the rules:

 \verbatim
"HELLO COMPUTER HELLO COMPUTER"
"MOVE 10"
"GO RIGHT"
\endverbatim
 
Since you as the developer are the designer of the ruleset, you can extract the behavioral triggers from your app from hypotheses which observe your rules.

The words and phrases in languageModelArray must be written with capital letters exclusively, for instance "word" must appear in the array as "WORD".

The last two arguments of the method work identically to the equivalent language model method. The withFilesNamed: argument takes an NSString which is the naming you would like for the files output by this method. The argument acousticModelPath takes the path to the relevant acoustic model.

This method returns an NSError, which will either return an error code or it will return noErr with an attached userInfo NSDictionary containing the paths to your newly-generated grammar (a .gram file) and corresponding phonetic dictionary (a .dic file). Remember that when you are passing .gram files to the Pocketsphinx method:

 \verbatim
- (void) startListeningWithLanguageModelAtPath:(NSString *)languageModelPath dictionaryAtPath:(NSString *)dictionaryPath acousticModelAtPath:(NSString *)acousticModelPath languageModelIsJSGF:(BOOL)languageModelIsJSGF;
\endverbatim
 
you will now set the argument languageModelIsJSGF: to TRUE.
 
*/
- (NSError *) generateGrammarFromDictionary:(NSDictionary *)grammarDictionary withFilesNamed:(NSString *)fileName forAcousticModelAtPath:(NSString *)acousticModelPath;

/**Generate a language model from a text file containing words and phrases you want OEPocketsphinxController to understand, using your chosen acoustic model. The file should be formatted with every word or contiguous phrase on its own line with a line break afterwards. Putting a phrase in on its own line makes it somewhat more probable that the phrase will be recognized as a phrase when spoken.
 
 Give the correct full path to the text file as a string. fileName is the way you want the output files to be named, for instance if you enter "MyDynamicLanguageModel" you will receive files output to your Caches directory titled MyDynamicLanguageModel.dic, MyDynamicLanguageModel.arpa, and MyDynamicLanguageModel.DMP.
 
If this method is successful it will return nil. If it returns nil, you can use the methods pathToSuccessfullyGeneratedDictionaryWithRequestedName: and pathToSuccessfullyGeneratedLanguageModelWithRequestedName: to get your paths to your newly-generated language models and grammars and dictionaries for use with OEPocketsphinxController. If it doesn't return nil, it will return an error which you can check for debugging purposes.
 */

- (NSError *) generateLanguageModelFromTextFile:(NSString *)pathToTextFile withFilesNamed:(NSString *)fileName forAcousticModelAtPath:(NSString *)acousticModelPath;




@end
