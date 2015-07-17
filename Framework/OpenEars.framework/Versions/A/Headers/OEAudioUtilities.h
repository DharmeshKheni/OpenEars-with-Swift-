
//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEAudioUtilities.h
//  OpenEars
//
//  Some utilities to help with Core Audio needs in C rather than C++.
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>

#define kOEPCMFormatOther 0
#define kOEPCMFormatFloat32 1
#define kOEPCMFormatInt16 2
#define kOEPCMFormatFixed824 3

#define kVerboseCallback

#define kLowPassFilterTimeSlice .001 // For calculating decibel levels
#define kDBOffset -120.0 // This is the negative offset for calculating decibel levels

void reportAudioUnitError(OSStatus error);
float getInputDecibels(SInt16 * samples, UInt32 inNumberFrames);
NSString* stringFromAudioStreamBasicDescription (AudioStreamBasicDescription audioFormat);
AudioBufferList *AllocateABL(UInt32 channelsPerFrame, UInt32 bytesPerFrame, bool interleaved, UInt32 capacityFrames);
void DeallocateABL(AudioBufferList * bufferList);
AudioStreamBasicDescription setupPCMAudioStreamBasicDescription(float sampleRate, int channels, int pcmFormat, BOOL interleaved);
void ReportError(OSStatus error, NSString *description);