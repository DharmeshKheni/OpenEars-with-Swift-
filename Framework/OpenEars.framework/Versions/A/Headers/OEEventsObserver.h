//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEEventsObserver.h
//  OpenEars
// 
//  OEEventsObserver is a class which allows the return of delegate methods delivering the status of various functions of Flite, Pocketsphinx and OpenEars
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.



// A protocol for delegates of OEEventsObserver.

#import <Foundation/Foundation.h>

@protocol OEEventsObserverDelegate;
/**
 @class  OEEventsObserver
 @brief  OEEventsObserver provides a large set of delegate methods that allow you to receive information about the events in OpenEars from anywhere in your app. You can create as many OEEventsObservers as you need and receive information using them simultaneously. All of the documentation for the use of OEEventsObserver is found in the section OEEventsObserverDelegate.
 
 */
@interface OEEventsObserver : NSObject

/**To use the OEEventsObserverDelegate methods, assign this delegate to the class hosting OEEventsObserver and then use the delegate methods documented under OEEventsObserverDelegate. There is a complete example of how to do this explained under the OEEventsObserverDelegate documentation. */

@property (weak) id<OEEventsObserverDelegate> delegate; // the delegate will be sent events.

@end
/**
 @protocol  OEEventsObserverDelegate
 @brief  OEEventsObserver provides a large set of delegate methods that allow you to receive information about the events in OpenEars from anywhere in your app. You can create as many OEEventsObservers as you need and receive information using them simultaneously.
 
 ## Usage examples
 > What to add to your header:
 @htmlinclude OEEventsObserver_Header.txt
 > What to add to your implementation:
 @htmlinclude OEEventsObserver_Implementation.txt
 > How to use the class methods:
 @htmlinclude OEEventsObserver_Calls.txt 
 @warning It is a requirement that any OEEventsObserver you use in a view controller or other object is a property of that object, or it won't work.
 */
@protocol OEEventsObserverDelegate <NSObject>

@optional 

// Delegate Methods you can implement in your app.

// Audio Session Status Methods.
/** There was an interruption.*/
- (void) audioSessionInterruptionDidBegin; 
/** The interruption ended.*/
- (void) audioSessionInterruptionDidEnd; 
/** The input became unavailable.*/
- (void) audioInputDidBecomeUnavailable; 
/** The input became available again.*/
- (void) audioInputDidBecomeAvailable; 
 /** The audio route changed.*/
- (void) audioRouteDidChangeToRoute:(NSString *)newRoute;

// Pocketsphinx Status Methods.

/** Pocketsphinx isn't listening yet but it has entered the main recognition loop.*/
- (void) pocketsphinxRecognitionLoopDidStart; 
/** Pocketsphinx is now listening.*/
- (void) pocketsphinxDidStartListening;
 /** Pocketsphinx heard speech and is about to process it.*/
- (void) pocketsphinxDidDetectSpeech;
/** Pocketsphinx detected a second of silence indicating the end of an utterance*/
- (void) pocketsphinxDidDetectFinishedSpeech; 
/** Pocketsphinx has a hypothesis.*/
- (void) pocketsphinxDidReceiveHypothesis:(NSString *)hypothesis recognitionScore:(NSString *)recognitionScore utteranceID:(NSString *)utteranceID; 
 /** Pocketsphinx has an n-best hypothesis dictionary.*/
- (void) pocketsphinxDidReceiveNBestHypothesisArray:(NSArray *)hypothesisArray;
/** Pocketsphinx has exited the continuous listening loop.*/
- (void) pocketsphinxDidStopListening; 
 /** Pocketsphinx has not exited the continuous listening loop but it will not attempt recognition.*/
- (void) pocketsphinxDidSuspendRecognition;
 /** Pocketsphinx has not existed the continuous listening loop and it will now start attempting recognition again.*/
- (void) pocketsphinxDidResumeRecognition;
 /** Pocketsphinx switched language models inline.*/
- (void) pocketsphinxDidChangeLanguageModelToFile:(NSString *)newLanguageModelPathAsString andDictionary:(NSString *)newDictionaryPathAsString;
/** Some aspect of setting up the continuous loop failed, turn on OELogging for more info.*/
- (void) pocketSphinxContinuousSetupDidFailWithReason:(NSString *)reasonForFailure; 
/** Some aspect of tearing down the continuous loop failed, turn on OELogging for more info.*/
- (void) pocketSphinxContinuousTeardownDidFailWithReason:(NSString *)reasonForFailure; 
/** Your test recognition run has completed.*/
- (void) pocketsphinxTestRecognitionCompleted;
/** Pocketsphinx couldn't start because it has no mic permissions (will only be returned on iOS7 or later).*/
- (void) pocketsphinxFailedNoMicPermissions;
/** The user prompt to get mic permissions, or a check of the mic permissions, has completed with a TRUE or a FALSE result  (will only be returned on iOS7 or later).*/
- (void) micPermissionCheckCompleted:(BOOL)result;

// Flite Status Methods.
/** Flite started speaking. You probably don't have to do anything about this.*/
- (void) fliteDidStartSpeaking; 
/** Flite finished speaking. You probably don't have to do anything about this.*/
- (void) fliteDidFinishSpeaking; 

@end
