//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEPocketsphinxController.h
//  OpenEars
//
//  OEPocketsphinxController is a class which controls the creation and management of
//  a continuous speech recognition loop.
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.


#import <Foundation/Foundation.h>
#import <UIKit/UIDevice.h>

#import "OEEventsObserver.h"
/**\cond HIDDEN_SYMBOLS*/  
#import "OEContinuousModel.h"
#import "OENotification.h"


#define SYSTEM_VERSION_LESS_THAN(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

/**\endcond */   

/**
 @class  OEPocketsphinxController
 @brief  The class that controls local speech recognition in OpenEars.
 
 ## Usage examples
 > What to add to your header:
 @htmlinclude OEPocketsphinxController_Header.txt
 > How to use the class methods:
 @htmlinclude OEPocketsphinxController_Calls.txt 
 @warning OEPocketsphinxController is a singleton which is called with [OEPocketsphinxController sharedInstance]. You cannot initialize an instance of OEPocketsphinxController.
 */

@interface OEPocketsphinxController : NSObject <OEEventsObserverDelegate> {
    BOOL _starting; 
}
// These are the OpenEars methods for controlling Pocketsphinx. You should use these.

/**Start the speech recognition engine up. You provide the full paths to a language model and a dictionary file which are created using OELanguageModelGenerator and the acoustic model you want to use (for instance [OEAcousticModel pathToModel:@"AcousticModelEnglish"]).*/
- (void) startListeningWithLanguageModelAtPath:(NSString *)languageModelPath dictionaryAtPath:(NSString *)dictionaryPath acousticModelAtPath:(NSString *)acousticModelPath languageModelIsJSGF:(BOOL)languageModelIsJSGF;  // Starts the recognition loop.
/**Shut down the engine. You must do this before releasing a parent view controller that contains OEPocketsphinxController.*/
- (NSError *) stopListening; // Exits from the recognition loop.
/**Keep the engine going but stop listening to speech until resumeRecognition is called. Takes effect instantly.*/
- (void) suspendRecognition; // Stops interpreting sounds as speech without exiting from the recognition loop. You do not need to call these methods on behalf of Flite.
/**Resume listening for speech after suspendRecognition has been called.*/
- (void) resumeRecognition; // Starts interpreting sounds as speech after suspending recognition with the preceding method. You do not need to call these methods on behalf of Flite.
/**Change from one language model to another. This lets you change which words you are listening for depending on the context in your app. If you have already started the recognition loop and you want to switch to a different language model, you can use this and the model will be changed at the earliest opportunity. Will not have any effect unless recognition is already in progress. It isn't possible to change acoustic models in the middle of an already-started listening loop, just language model and dictionary.*/
- (void) changeLanguageModelToFile:(NSString *)languageModelPathAsString withDictionary:(NSString *)dictionaryPathAsString; 
/**Gives the volume of the incoming speech. This is a UI hook. You can't read it on the main thread or it will block.*/
@property (NS_NONATOMIC_IOSONLY, readonly) Float32 pocketsphinxInputLevel; // This gives the input metering levels. This can only be run in a background thread that you create, otherwise it will block recognition
- (void) removeCmnPlist; // You can use this to remove the SmartCMN plist if you want to reset it.

/**\cond HIDDEN_SYMBOLS*/ 

// Do not call these directly.
- (void) suspendRecognitionForFliteSpeech;
- (void) resumeRecognitionForFliteSpeech;
- (void) setSecondsOfSilence;
- (void) validateNBestSettings;

/**\endcond */ 

// Run one synchronous recognition pass on a recording from its beginning to its end and stop.
/**You can use this to run recognition on an already-recorded WAV file for testing. The WAV file has to be 16-bit and 16000 samples per second.*/
- (void) runRecognitionOnWavFileAtPath:(NSString *)wavPath usingLanguageModelAtPath:(NSString *)languageModelPath dictionaryAtPath:(NSString *)dictionaryPath acousticModelAtPath:(NSString *)acousticModelPath languageModelIsJSGF:(BOOL)languageModelIsJSGF;
/**You can use this to request mic permission in advance of running speech recognition.*/
- (void) requestMicPermission;
/**Returns whether your app has record permission. This is expected to be used after the user has at some point been prompted with requestMicPermission and the result has come back in the permission results OEEventsObserver delegate methods. If this is used before that point, accuracy of results are not guaranteed. If the user has either granted or denied permission in the past, this will return a boolean indicating the permission state.*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL micPermissionIsGranted;
/**The OEPocketsphinxController singleton, used for all references to the object.*/
+ (OEPocketsphinxController *)sharedInstance;
/**This needs to be called with the value TRUE before setting properties of OEPocketsphinxController for the first time in a session, and again before using OEPocketsphinxController in case it has been called with the value FALSE.*/
- (BOOL)setActive:(BOOL)active error:(NSError **)outError;

- (instancetype) init __attribute__((unavailable("Do not initialize OEPocketsphinxController directly – use [[OEPocketsphinxController sharedInstance] setActive:TRUE error:nil] instead.")));
- (void)dealloc __attribute__((unavailable("Do not dealloc OEPocketsphinxController directly – calling [[OEPocketsphinxController sharedInstance] setActive:FALSE error:nil] will allow memory to be released when needed.")));
/**\cond HIDDEN_SYMBOLS*/ 
@property (nonatomic, strong) OEContinuousModel *continuousModel; // The continuous model is the actual recognition loop.
@property(nonatomic,strong) NSOperationQueue *pocketsphinxControllerQueue;    
@property (nonatomic, strong) OEEventsObserver *openEarsEventsObserver; // We use an OEEventsObserver here to get important information from other objects which may be instantiated.
/**\endcond */ 
/**This is how long OEPocketsphinxController should wait after speech ends to attempt to recognize speech. This defaults to .7 seconds.*/
@property (nonatomic, assign) float secondsOfSilenceToDetect;
/**Advanced: set this to TRUE to receive n-best results.*/    
@property (nonatomic, assign) BOOL returnNbest;
/**Advanced: the number of n-best results to return. This is a maximum number to return -- if there are null hypotheses fewer than this number will be returned.*/
@property (nonatomic, assign) int nBestNumber;
/**Turn on extended logging for speech recognition processes. In order to get assistance with a speech recognition issue in the forums, it is necessary to turn this on and show the output.*/
@property (nonatomic, assign) BOOL verbosePocketSphinx;
/**By default, OEPocketsphinxController won't return a hypothesis if for some reason the hypothesis is null (this can happen if the perceived sound was just noise). If you need even empty hypotheses to be returned, you can set this to TRUE before starting OEPocketsphinxController.*/
@property (nonatomic, assign) BOOL returnNullHypotheses;
/**Check if the listening loop is suspended*/
@property (nonatomic, assign) BOOL isSuspended; 
/**Check if the listening loop is in progress*/
@property (nonatomic, assign) BOOL isListening;
/**Set this to true if you encounter unusually slow-to-return searches with Rejecto*/
@property (nonatomic, assign) BOOL legacy3rdPassMode;
/**Try not to decode probable noise as speech (this can result in more noise robustness, but it can also result in omitted segments – defaults to YES, override to set to NO)*/
@property (nonatomic, assign) BOOL removingNoise;
/**Try not to decode probable silence as speech (this can result in more accuracy, but it can also result in omitted segments – defaults to YES, override to set to NO)*/
@property (nonatomic, assign) BOOL removingSilence;
/**Speech/Silence threshhold setting. You may not need to make any changes to this, however, if you are experiencing quiet background noises triggering speech recognition, you can raise this to a value from 2-5 to 3.5 for the English acoustic model, and between 3.0 and 4.5 for the Spanish acoustic model. If you are experiencing too many words being ignored you can reduce this. The maximum value is 5.0 and the minimum is .5. For the English model, values less than 1.5 or more than 3.5 are likely to lead to poor results. For the Spanish model, higher values can be used. Please test any changes here carefully to see what effect they have on your user experience.*/
@property (nonatomic, assign) float vadThreshold;
/**Optionally disable bluetooth support for a listening session in case you never want bluetooth to be an audio route. Only set TRUE if you are sure you want this; defaults to FALSE (meaning that the default audio session supports bluetooth as a route unless you use this to declare otherwise).*/
@property (nonatomic, assign) BOOL disableBluetooth;
/**Optionally disable audio session mixing. Only set TRUE if you are sure you want this; defaults to FALSE (meaning that the default audio session mode is with mixing enabled unless you use this to declare otherwise).*/
@property (nonatomic, assign) BOOL disableMixing;
/**
 Set audio modes for the audio session manager to use.
 This can be set to the following:
 \verbatim
 @"Default" to use AVAudioSessionModeDefault
 @"VoiceChat" to use AVAudioSessionModeVoiceChat
 @"VideoRecording" AVAudioSessionModeVideoRecording
 @"Measurement" AVAudioSessionModeMeasurement
 \endverbatim
 If you don't set it to anything, @"Default" will automatically be used.
 
 */
@property (nonatomic, copy) NSString *audioMode; 
/**By setting pathToTestFile to point to a recorded audio file you can run the main Pocketsphinx listening loop (not runRecognitionOnWavFileAtPath but the main loop invoked by using startListeningWithLanguageModelAtPath:) over a pre-recorded audio file instead of using it with live input. 
 
 In contrast with using the method runRecognitionOnWavFileAtPath to receive a single recognition from a file, with this approach the audio file will have its buffers injected directly into the audio driver circular buffer for maximum fidelity to the goal of testing the entire codebase that is in use when doing a live recognition, including the whole driver and the listening loop including all of its features. This is for creating tests for yourself and for sharing automatically replicable issue reports with Politepix. 
 
 To use this, make an audio recording on the same device (i.e., if you are testing OEPocketsphinxController on an iPhone 5 with the internal microphone, make a recording on an iPhone 5 with the internal microphone, for instance using Apple's Voice Memos app) and then convert the resulting file to a 16-bit, 16000 sample rate, mono WAV file. You can do this with the output of Apple's Voice Memos app by taking the .m4a file that Voice Memos outputs and run it through this command in Terminal.app: 
 
 \verbatim
 afconvert -f WAVE -d LEI16@16000 -c 1 ~/Desktop/Memo.m4a ~/Desktop/Memo.wav
 \endverbatim
 
 Or you can capture a WAV file of your session using the SaveThatWave demo: http://www.politepix.com/savethatwave
 
 Then add the WAV file to your app, and right before sending the call to startListeningWithLanguageModelAtPath, set this property pathToTestFile to the path to your audio file in your app as an NSString (e.g. [[NSBundle mainBundle] pathForResource:@"Memo" ofType:@"wav"]). 
 
 Note: when you record the audio file you will be using to test with, give it a second of quiet lead-in before speech so there is time for the engine to fully start before listening begins. If you have any difficulty getting this to work, remember to turn on OELogging to get error output, which will probably explain what is not working.
 
 SmartCMN is disabled during testing so that the test gets the same results when run for different people and for different devices. Please keep in mind that there are some settings in Pocketsphinx which may prevent a deterministic outcome from a recognition, meaning that you should expect a <b>similar</b> score over multiple runs of a test but you may not always see the <b>identical</b> score. There are examples of asynchronous testing using this tool in this project in the test target.*/

@property (nonatomic, copy) NSString *pathToTestFile;

/**If you are doing testing, you can toggle SmartCMN on or off (it defaults to off and should usually be left off since using it can lead to nondeterministic results on the first runs with new devices).*/
@property (nonatomic, assign) BOOL useSmartCMNWithTestFiles;


/**\cond HIDDEN_SYMBOLS*/ 
@property (nonatomic, assign) BOOL defaultSecondsOfSilenceInUse;
@property (nonatomic, assign) BOOL outputAudio;
@property (nonatomic, assign) BOOL micPermission;  
@property (nonatomic, assign) BOOL doNotWarnAboutPermissions;
@property(nonatomic,assign) BOOL starting; 
/**\endcond*/  

@end
