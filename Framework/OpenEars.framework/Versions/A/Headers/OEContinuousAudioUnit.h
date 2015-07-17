//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEContinuousAudioUnit.h
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


//  This class is _never_ directly accessed by a project making use of OpenEars.

#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/ExtendedAudioFile.h>

#define kBufferLength .128
#define kBufferLengthDelta .12

#define kAudioUnitIsStopped 0
#define kAudioUnitIsStarted 1

@interface OEContinuousAudioUnit : NSObject

OSStatus ConverterDataCallback(AudioConverterRef inAudioConverter, UInt32* ioNumberDataPackets, AudioBufferList* ioData, AudioStreamPacketDescription** outDataPacketDescription,void* inUserData);
@property (NS_NONATOMIC_IOSONLY, copy) NSString *pathToTestFile;
@property (NS_NONATOMIC_IOSONLY, getter=getInputDecibels, readonly) float inputDecibels;
@property (nonatomic, copy) NSString *audioMode; 
@property (nonatomic, assign) int audioUnitState; 
@property (nonatomic, assign) BOOL disableBluetooth; 
@property (nonatomic, assign) BOOL disableMixing; 

- (void) suspendRecognition;
- (void) resumeRecognition;
- (void) testFileChange;
- (NSError *) startAudioUnit;
- (NSError *) stopAudioUnit;
- (NSError *) setupAudioSession;
- (NSError *) setupAudioUnit;
- (NSString *) getCurrentRoute;
- (NSError *)teardownAudioSession;
- (NSError *)teardownAudioUnit;

@end
