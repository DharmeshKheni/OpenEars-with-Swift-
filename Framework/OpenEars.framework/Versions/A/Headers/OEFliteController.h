//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEFliteController.h
//  OpenEars
//
//  OEFliteController is a class which manages text-to-speech
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.


#import <AVFoundation/AVFoundation.h>

#import "OEEventsObserver.h"
//#import "OEAudioConstants.h"
/**\cond HIDDEN_SYMBOLS*/   
#import "flite.h"
/**\endcond */   
#import "OEFliteVoice.h"
#import <dispatch/dispatch.h>
/**
@class  OEFliteController
@brief  The class that controls speech synthesis (TTS) in OpenEars.

## Usage examples
> Preparing to use the class:
@htmlinclude OEFliteController_Preconditions.txt
> What to add to your header:
@htmlinclude OEFliteController_Header.txt
> What to add to your implementation:
@htmlinclude OEFliteController_Implementation.txt
> How to use the class methods:
@htmlinclude OEFliteController_Calls.txt 
@warning There can only be one OEFliteController instance in your app at any given moment.
*/
 
@interface OEFliteController : NSObject <AVAudioPlayerDelegate, OEEventsObserverDelegate> {
    dispatch_queue_t _backgroundQueue;
}

/**This takes an NSString which is the word or phrase you want to say, and the OEFliteVoice to use to say the phrase.
Usage Example:
 \verbatim
 [self.fliteController say:@"Say it, don't spray it." withVoice:self.slt];
 \endverbatim
 There are a total of nine FliteVoices available for use with OpenEars. The Slt voice is the most popular one and it ships with OpenEars. The other eight voices can be downloaded as part of the OpenEarsExtras package available at the URL <a href="http://bitbucket.org/Politepix/openearsextras">http://bitbucket.org/Politepix/openearsextras</a>. To use them, just drag the desired downloaded voice's framework into your app, import its header at the top of your calling class (e.g. import &lt;Slt/Slt.h&gt; or import &lt;Rms/Rms.h&gt;) and instantiate it as you would any other object, then passing the instantiated voice to this method.
*/
- (void) say:(NSString *)statement withVoice:(OEFliteVoice *)voiceToUse;
/**A read-only attribute that tells you the volume level of synthesized speech in progress. This is a UI hook. You can't read it on the main thread. */
@property (NS_NONATOMIC_IOSONLY, readonly) Float32 fliteOutputLevel;
// End methods to be called directly by an OpenEars project

/**\cond HIDDEN_SYMBOLS*/
// Interruption handling
- (void) interruptionRoutine:(AVAudioPlayer *)player;
- (void) interruptionOverRoutine:(AVAudioPlayer *)player;
- (void) resetAudioPlayer;
- (BOOL) audioPlayerIsNil;

// Handling not doing voice recognition on Flite speech, do not directly call
- (void) sendResumeNotificationOnMainThread;
- (void) sendSuspendNotificationOnMainThread;
- (void) interruptTalking;
/**\endcond*/

/**duration_stretch changes the speed of the voice. It is on a scale of 0.0-2.0 where 1.0 is the default.*/	
@property (nonatomic, assign) float duration_stretch;
/**target_mean changes the pitch of the voice. It is on a scale of 0.0-2.0 where 1.0 is the default.*/
@property (nonatomic, assign) float target_mean;
/**target_stddev changes convolution of the voice. It is on a scale of 0.0-2.0 where 1.0 is the default.*/    
@property (nonatomic, assign) float target_stddev;
/**Set userCanInterruptSpeech to TRUE in order to let new incoming human speech cut off synthesized speech in progress.*/    
@property (nonatomic, assign) BOOL userCanInterruptSpeech;

/**\cond HIDDEN_SYMBOLS*/
@property (nonatomic, assign) BOOL speechInProgress;
@property (nonatomic, strong) AVAudioPlayer *audioPlayer;  // Plays back the speech
@property (nonatomic, strong) OEEventsObserver *openEarsEventsObserver; // Observe status changes from audio sessions and Pocketsphinx
@property (nonatomic, strong) NSData *speechData;

/**\endcond */
@end





