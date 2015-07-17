//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEContinuousModel.h
//  OpenEars
//
//  OEContinuousModel is a class which consists of the continuous listening loop used by Pocketsphinx.
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.


//  This class is _never_ directly accessed by a project making use of OpenEars.


#import <Foundation/Foundation.h>
#import "OEContinuousAudioUnit.h"
#import "OESmartCMN.h"
#import "prim_type.h"

#define kUtteranceStateUnstarted 0
#define kUtteranceStateStarted 1
#define kUtteranceStateEnded 2
#define kMaximumSampleSize 2048

typedef struct ps_decoder_s ps_decoder_t;
typedef struct ps_astar_s ps_nbest_t;
typedef struct ps_search_s ps_search_t;


@interface OEContinuousModel : NSObject {
    BOOL _stopping;
    dispatch_source_t _heartbeatTimer;
}

- (void) listeningSessionWithLanguageModelAtPath:(NSString *)languageModelPath dictionaryAtPath:(NSString *)dictionaryPath acousticModelAtPath:(NSString *)acousticModelPath languageModelIsJSGF:(BOOL)languageModelIsJSGF;
- (void) runRecognitionOnWavFileAtPath:(NSString *)wavPath usingLanguageModelAtPath:(NSString *)languageModelPath dictionaryAtPath:(NSString *)dictionaryPath acousticModelAtPath:(NSString *)acousticModelPath languageModelIsJSGF:(BOOL)languageModelIsJSGF;
- (void) resumeRecognition;
- (void) suspendRecognition;
- (void) changeLanguageModelToFile:(NSString *)languageModelPathAsString withDictionary:(NSString *)dictionaryPathAsString;
- (void) removeCmnPlist;
- (void)  testFileChange;
- (NSError *) stopListening;
- (BOOL) dictionaryAtPathIsFromRuleORama:(NSString *)dictionaryPath;
- (BOOL) dictionaryAtPathIsFromRejecto:(NSString *)dictionaryPath;
- (void) announceSetupFailureForReason:(NSString *)reasonForFailure;
- (BOOL) openEarsLoggingIsOn;
- (BOOL) verbosePocketsphinxIsOn;
- (void) heartBeat;
- (ps_decoder_t *) initializeDecoderForLanguageModelAtPath:(NSString *)languageModelPath dictionaryAtPath:(NSString *)dictionaryPath acousticModelAtPath:(NSString *)acousticModelPath languageModelIsJSGF:(BOOL)languageModelIsJSGF usingBestpath:(NSNumber *)usingBestpath;
- (void) setDecoder:(ps_decoder_t *)pocketSphinxDecoder toCmnValue:(float)previouscmn forAcousticModelAtPath:(NSString *)pathToAcousticModel;
- (void) announceListening;
- (void) announceLoopHasStartedWithDictionaryAtPath:(NSString *)dictionaryPath;
- (void) validateAndPerformLanguageModelChange;
- (void) performSingularStopForDecoder:(ps_decoder_t *)pocketSphinxDecoder;
- (void) resetForNewUtteranceWithContextString:(NSString *)contextString;
- (void) announceSpeechDetection;
- (void) announceSpeechCompleted;
- (void) getAndReturnHypothesisForDecoder:(ps_decoder_t *)pocketSphinxDecoder;
- (NSInteger) startUtterance;
- (void) processRaw:(NSData *)buffer;
- (NSInteger) getInSpeech;
- (void) endUtterance;
- (void) getNbestForDecoder:(ps_decoder_t *)pocketSphinxDecoder withHypothesis:(char const *)hypothesis andRecognitionScore:(int32)recognitionScore;
- (char const *) getHypothesisFromDecoder:(ps_decoder_t *)pocketSphinxDecoder withScore:(SInt32 *)recognitionScore;
- (SInt32) getProbabilityFromDecoder:(ps_decoder_t *)pocketSphinxDecoder;
- (ps_nbest_t *) nBest;
- (ps_nbest_t *)nBestNext:(ps_nbest_t *)nbest;
- (char const *)nBestHypothesis:(ps_nbest_t *)nbest withScore:(int32 *)recognitionScore;
- (void) nBestFree:(ps_nbest_t *)nbest;
- (char const *) searchHyp:(ps_decoder_t *)ps bestScore:(int *)out_best_score final:(int *)final;

@property (NS_NONATOMIC_IOSONLY, getter=getMeteringLevel, readonly) float meteringLevel;
@property (nonatomic, assign) BOOL useSmartCMNWithTestFiles;
@property(nonatomic, assign) BOOL returnNbest;
@property(nonatomic, assign) NSInteger nBestNumber;
@property(nonatomic, assign) BOOL outputAudio;
@property(nonatomic, assign) BOOL isListening;
@property(nonatomic, assign) BOOL returnNullHypotheses;
@property (nonatomic, assign) float secondsOfSpeechToDetect;
@property (nonatomic, assign) float secondsOfSilenceToDetect;
@property (nonatomic, readonly) float lastCMNUsed;
@property (nonatomic,copy) NSString *pathToTestFile;
@property (nonatomic,copy) NSString *audioMode;
@property (nonatomic, strong) OEContinuousAudioUnit *audioDriver;
@property (nonatomic, assign) NSInteger utteranceState;
@property (nonatomic, readonly) OESmartCMN *smartCMN;
@property (nonatomic, assign) BOOL isSuspended;
@property (nonatomic, assign) BOOL safeToCallStart;
@property (nonatomic, assign) BOOL safeToCallStop;
@property (nonatomic, assign) ps_decoder_t *pocketSphinxDecoder;
@property (nonatomic, strong) NSMutableData *bufferAccumulator;
@property (nonatomic, copy) NSString *languageModelFileToChangeTo;
@property (nonatomic, copy) NSString *dictionaryFileToChangeTo;
@property (nonatomic, copy) NSString *acousticModelPath;
@property (nonatomic, strong) dispatch_source_t heartbeatTimer;
@property (nonatomic, assign) BOOL shouldUseSmartCMN;
@property (nonatomic, assign) BOOL speechFramesFound;
@property (nonatomic, assign) BOOL speechAlreadyInProgress;
@property (nonatomic, assign) BOOL thereIsALanguageModelChangeRequest;
@property (nonatomic, assign) NSInteger utteranceID;
@property (nonatomic, assign) NSTimeInterval stuckUtterance;
@property (nonatomic, assign) BOOL legacy3rdPassMode;
@property (nonatomic, assign) BOOL requestToResume;
@property (nonatomic, assign) BOOL defaultSecondsOfSilenceInUse;
@property (nonatomic, assign) int frameRate;
@property (nonatomic, assign) BOOL removingNoise;
@property (nonatomic, assign) BOOL removingSilence;
@property (nonatomic, assign) BOOL disableBluetooth;
@property (nonatomic, assign) BOOL disableMixing;
@property (nonatomic, assign) float vadThreshold;

@end

