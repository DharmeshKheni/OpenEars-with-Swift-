//
//  ViewController.swift
//  SpeechToText
//
//  Created by Anil on 08/07/15.
//  Copyright (c) 2015 Variya Soft Solutions. All rights reserved.
//

import UIKit

var lmPath: String!
var dicPath: String!
var words: Array<String> = []
var currentWord: String!

var kLevelUpdatesPerSecond = 18

class ViewController: UIViewController, OEEventsObserverDelegate {
    
    var openEarsEventsObserver = OEEventsObserver()
    var startupFailedDueToLackOfPermissions = Bool()

    var buttonFlashing = false

    @IBOutlet weak var recordButton: UIButton!
    @IBOutlet weak var heardTextView: UITextView!
    @IBOutlet weak var statusTextView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loadOpenEars()
    }
    
    @IBAction func record(_ sender: AnyObject) {
        
        if !buttonFlashing {
            startFlashingbutton()
            startListening()
        } else {
            stopFlashingbutton()
            stopListening()
        }
    }
    
    func startFlashingbutton() {

        buttonFlashing = true
        recordButton.alpha = 1
        
        UIView.animate(withDuration: 0.5, delay: 0.0, options: [.curveEaseInOut, .repeat, .autoreverse], animations: { [unowned self] in
            self.recordButton.alpha = 0.1
            }, completion: nil)
    }

    func stopFlashingbutton() {
 
        buttonFlashing = false
        
        UIView.animate(withDuration: 0.1, delay: 0.0, options: [.curveEaseInOut,.beginFromCurrentState], animations: { [unowned self] in
            self.recordButton.alpha = 1
            }, completion: nil)
    }
    //OpenEars methods begin
    
    func loadOpenEars() {

        self.openEarsEventsObserver = OEEventsObserver()
        self.openEarsEventsObserver.delegate = self

        let lmGenerator: OELanguageModelGenerator = OELanguageModelGenerator()

        addWords()
        let name = "LanguageModelFileStarSaver"
        lmGenerator.generateLanguageModel(from: words, withFilesNamed: name, forAcousticModelAtPath: OEAcousticModel.path(toModel: "AcousticModelEnglish"))
        
        lmPath = lmGenerator.pathToSuccessfullyGeneratedLanguageModel(withRequestedName: name)
        dicPath = lmGenerator.pathToSuccessfullyGeneratedDictionary(withRequestedName: name)
    }


    func pocketsphinxDidStartListening() {
        print("Pocketsphinx is now listening.")
        statusTextView.text = "Pocketsphinx is now listening."
    }
    
    func pocketsphinxDidDetectSpeech() {
        print("Pocketsphinx has detected speech.")
        statusTextView.text = "Pocketsphinx has detected speech."
    }
    
    func pocketsphinxDidDetectFinishedSpeech() {
        print("Pocketsphinx has detected a period of silence, concluding an utterance.")
        statusTextView.text = "Pocketsphinx has detected a period of silence, concluding an utterance."
    }
    
    func pocketsphinxDidStopListening() {
        print("Pocketsphinx has stopped listening.")
        statusTextView.text = "Pocketsphinx has stopped listening."
    }
    
    func pocketsphinxDidSuspendRecognition() {
        print("Pocketsphinx has suspended recognition.")
        statusTextView.text = "Pocketsphinx has suspended recognition."
    }
    
    func pocketsphinxDidResumeRecognition() {
        print("Pocketsphinx has resumed recognition.")
        statusTextView.text = "Pocketsphinx has resumed recognition."
    }
    
    @objc(pocketsphinxDidChangeLanguageModelToFile:andDictionary:) func pocketsphinxDidChangeLanguageModel(toFile newLanguageModelPathAsString: String, andDictionary newDictionaryPathAsString: String) {
        print("Pocketsphinx is now using the following language model: \(newLanguageModelPathAsString) and the following dictionary: \(newDictionaryPathAsString)")
    }
    
    func pocketSphinxContinuousSetupDidFail(withReason reasonForFailure: String) {
        print("Listening setup wasn't successful and returned the failure reason: \(reasonForFailure)")
        statusTextView.text = "Listening setup wasn't successful and returned the failure reason: \(reasonForFailure)"
    }
    
    func pocketSphinxContinuousTeardownDidFail(withReason reasonForFailure: String) {
        print("Listening teardown wasn't successful and returned the failure reason: \(reasonForFailure)")
        statusTextView.text = "Listening teardown wasn't successful and returned the failure reason: \(reasonForFailure)"
    }
    
    func testRecognitionCompleted() {
        print("A test file that was submitted for recognition is now complete.")
        statusTextView.text = "A test file that was submitted for recognition is now complete."
    }
    
    func startListening() {
        do {
            try OEPocketsphinxController.sharedInstance().setActive(true)
        } catch {
            print(error)
        }

        OEPocketsphinxController.sharedInstance().startListeningWithLanguageModel(atPath: lmPath, dictionaryAtPath: dicPath, acousticModelAtPath: OEAcousticModel.path(toModel: "AcousticModelEnglish"), languageModelIsJSGF: false)
    }

    func stopListening() {
        OEPocketsphinxController.sharedInstance().stopListening()
    }
    
    func addWords() {
        //add any thing here that you want to be recognized. Must be in capital letters
        words.append("SUNDAY")
        words.append("MONDAY")
        words.append("TUESDAY")
        words.append("WEDNESDAY")
        words.append("THURSDAY")
        words.append("FRIDAY")
        words.append("SATURDAY")
        
        words.append("JANUARY")
        words.append("FEBRUARY")
        words.append("MARCH")
        words.append("APRIL")
        words.append("MAY")
        words.append("JUNE")
        words.append("JULY")
        words.append("AUGUST")
        words.append("SEPTEMBER")
        words.append("OCTOBER")
        words.append("NOVEMBER")
        words.append("DECEMBER")
    }
    
    func getNewWord() {
        let randomWord = Int(arc4random_uniform(UInt32(words.count)))
        currentWord = words[randomWord]
    }
    
    func pocketsphinxFailedNoMicPermissions() {

        NSLog("Local callback: The user has never set mic permissions or denied permission to this app's mic, so listening will not start.")
        self.startupFailedDueToLackOfPermissions = true
        if OEPocketsphinxController.sharedInstance().isListening {
            let error = OEPocketsphinxController.sharedInstance().stopListening() // Stop listening if we are listening.
            if(error != nil) {
                print("Error while stopping listening in micPermissionCheckCompleted \(error)");
            }
        }
    }
    
    func pocketsphinxDidReceiveHypothesis(_ hypothesis: String!, recognitionScore: String!, utteranceID: String!) {
        
        heardTextView.text = "Heard: \(hypothesis)"
    }
}

