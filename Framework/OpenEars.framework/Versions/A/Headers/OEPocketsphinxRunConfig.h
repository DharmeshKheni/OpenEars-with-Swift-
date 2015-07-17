//  OpenEars 
//  http://www.politepix.com/openears
//
//  OEPocketsphinxRunConfig.h
//  OpenEars
//
//  OEPocketsphinxRunConfig.h exposes all of the available options that Pocketsphinx can theoretically run with. 
//
//  Copyright Politepix UG (haftungsbeschränkt) 2014. All rights reserved.
//  http://www.politepix.com
//  Contact at http://www.politepix.com/contact
//
//  this file is licensed under the Politepix Shared Source license found 
//  found in the root of the source distribution. Please see the file "Version.txt" in the root of 
//  the source distribution for the version number of this OpenEars package.

/**\cond HIDDEN_SYMBOLS*/

//#import "OEAudioConstants.h"

// This is the config file for all of the Pocketsphinx run options. This is included as a convenience for development 
// and to make OpenEars suitable for use by research projects that may have a very good reason to get under the hood 
// here. However, absolutely no testing is done on OpenEars using settings below other than the shipping defaults, so 
// it unfortunately won't be possible to offer support for issues arising from making any changes to this file.  
//
// In short, you'll already know beyond a doubt whether you need to change anything here and you'll also know where to 
// ask if it doesn't work out, and understand why I can't help in that case.  You're welcome to get in touch and let me 
// know if something isn't working here that you think probably ought to be working, but I might not have the bandwidth 
// to respond or look into it.
//
// Please note that not every option has an effect on the OpenEars implementation of Pocketsphinx, a few of them if enabled 
// are likely to break OpenEars, and several of the options may be overriden by whatever hmm you choose to use, making 
// them unnecessary or pointless to set here.
//
// In order to use a setting below, uncomment the line it's on and replace the value that is between the @"" quotes with 
// the value you'd like to use.  The only exception to this is -hmm, which just needs to be uncommented since it's required 
// that all hmm files are sought inside the bundle and there is no specific filename that is targeted (unlike in the case 
// of the lm and dict files).

/* Options defining waveform to cepstral parameters */

// #define kLOGSPEC "-logspec", bool, default "no", Write out logspectral files instead of cepstra
// #define kSMOOTHSPEC //"-smoothspec", bool, default "no", Write out cepstral-smoothed logspectral files
// #define kTRANSFORM //"-transform", string, default "legacy", Which type of transform to use to calculate cepstra (legacy, dct, or htk)
// #define kALPHA //"-alpha", ARG_FLOAT32, ARG_STRINGIFY(DEFAULT_PRE_EMPHASIS_ALPHA), Preemphasis parameter
// #define kSAMPRATE //"-samprate", ARG_FLOAT32, ARG_STRINGIFY(DEFAULT_SAMPLING_RATE), Sampling rate
// #define kFRATE //"-frate", int, default ARG_STRINGIFY(DEFAULT_FRAME_RATE), Frame rate
// #define kWLEN //"-wlen", ARG_FLOAT32, ARG_STRINGIFY(DEFAULT_WINDOW_LENGTH), Hamming window length
// #define kNFFT //"-nfft", int, default ARG_STRINGIFY(DEFAULT_FFT_SIZE), Size of FFT
// #define kNFILT //"-nfilt", int, default ARG_STRINGIFY(DEFAULT_NUM_FILTERS), Number of filter banks
// #define kLOWERF //"-lowerf", ARG_FLOAT32, ARG_STRINGIFY(DEFAULT_LOWER_FILT_FREQ), Lower edge of filters
// #define kUPPERF //"-upperf", ARG_FLOAT32, ARG_STRINGIFY(DEFAULT_UPPER_FILT_FREQ), Upper edge of filters
// #define kUNIT_AREA //"-unit_area", bool, default "yes", Normalize mel filters to unit area
// #define kROUND_FILTERS //"-round_filters", bool, default "yes", Round mel filter frequencies to DFT points
// #define kNCEP //"-ncep", int, default ARG_STRINGIFY(DEFAULT_NUM_CEPSTRA), Number of cep coefficients
// #define kDOUBLEBW //"-doublebw", bool, default "no", Use double bandwidth filters (same center freq)
// #define kLIFTER //"-lifter", int, default "0", Length of sin-curve for liftering, or 0 for no liftering.
// #define kVAD_PRESPEECH //"-vad_prespeech", int, default ARG_STRINGIFY(DEFAULT_PRESPCH_STATE_LEN), Num of speech frames to trigger vad from silence to speech.
// #define kVAD_POSTSPEECH //"-vad_postspeech", int, default ARG_STRINGIFY(DEFAULT_POSTSPCH_STATE_LEN), Num of speech frames to trigger vad from speech to silence.
// #define kVAD_THRESHOLD //"-vad_threshold", float, default "2.0", Threshold for decision between noise and silence frames. Log-ratio between signal level and noise level.
// #define kINPUT_ENDIAN //"-input_endian", string, default NATIVE_ENDIAN, Endianness of input data, big or little, ignored if NIST or MS Wav
// #define kWARP_TYPE //"-warp_type", string, default DEFAULT_WARP_TYPE, Warping function type (or shape)
// #define kWARP_PARAMS //"-warp_params", string, default NULL, Parameters defining the warping function
// #define kDITHER //"-dither", bool, default "no", Add 1/2-bit noise
// #define kSEED //"-seed", int, default ARG_STRINGIFY(SEED), Seed for random number generator; if less than zero, pick our own
// #define kREMOVE_DC //"-remove_dc", bool, default "no", Remove DC offset from each frame"
// #define kREMOVE_NOISE //"-remove_noise", bool, default "yes", Remove noise with spectral subtraction in mel-energies
// #define kREMOVE_SILENCE //"-remove_silence", bool, default "yes", Enables VAD, removes silence frames from processing
// #define kVERBOSE //"-verbose", bool, default "no", Show input filenames

/* Options defining cepstral to feature parameters */

// #define kFEAT //"-feat", string, default "1s_c_d_dd", Feature stream type, depends on the acoustic model
// #define kCEPLEN //"-ceplen", int, default "13", Number of components in the input feature vector
// #define kCMN //"-cmn", string, default "current", Cepstral mean normalization scheme ('current', 'prior', or 'none')
// #define kCMNINIT //"-cmninit", string, default "8.0", Initial values (comma-separated) for cepstral mean when 'prior' is used
// #define kVARNORM //"-varnorm", boolean, default "no", Variance normalize each utterance (only if CMN == current)
// #define kAGC //"-agc", string, default "none", Automatic gain control for c0 ('max', 'emax', 'noise', or 'none')
// #define kAGCTHRESH //"-agcthresh", float, default "2.0", Initial threshold for automatic gain control
// #define kLDA //"-lda", string, default NULL, File containing transformation matrix to be applied to features (single-stream features only)
// #define kLDADIM //"-ldadim", int, default "0", Dimensionality of output of feature transformation (0 to use entire matrix)
// #define kSVSPEC //"-svspec", string, default NULL, Subvector specification (e.g., 24,0-11/25,12-23/26-38 or 0-12/13-25/26-38)

/** Options defining beam width parameters for tuning the search. */

//#if __LP64__ 
//#define kBEAM @"1e-96" // "-beam", float, default "1e-48", Beam width applied to every frame in Viterbi search (smaller values mean wider beam)
//#else
//#define kBEAM @"1e-66" // "-beam", float, default "1e-48", Beam width applied to every frame in Viterbi search (smaller values mean wider beam)
//#endif
// #define kWBEAM @"null" // "-wbeam", float, default "7e-29", Beam width applied to word exits
// #define kPBEAM @"null" // "-pbeam", float, default "1e-48", Beam width applied to phone transitions
// #define kLPBEAM @"null" // "-lpbeam", float, default "1e-40", Beam width applied to last phone in words
// #define kLPONLYBEAM @"null" // "-lponlybeam", float, default "7e-29", Beam width applied to last phone in single-phone words
//#if __LP64__ 
//#define kFWDFLATBEAM @"1e-128" // "-fwdflatbeam", float, default "1e-64", Beam width applied to every frame in second-pass flat search
//#endif
// #define kFWDFLATWBEAM @"null" // "-fwdflatwbeam", float, default "7e-29", Beam width applied to word exits in second-pass flat search
// #define kPL_WINDOW @"null" // "-pl_window", int, default "0", Phoneme lookahead window size, in frames
// #define kPL_BEAM @"null" // "-pl_beam", float, default "1e-10", Beam width applied to phone loop search for lookahead
// #define kPL_PBEAM @"null" // "-pl_pbeam", float, default "1e-5", Beam width applied to phone loop transitions for lookahead
// #define kCOMPALLSEN @"null" // "-compallsen", boolean, default "no", Compute all senone scores in every frame (can be faster when there are many senones)
// #define kFWDTREE @"null" // "-fwdtree", boolean, default "yes", Run forward lexicon-tree search (1st pass)
// #define kFWDFLAT @"null" // "-fwdflat", boolean, default "yes", Run forward flat-lexicon search over word lattice (2nd pass)
//#define kBESTPATH @"yes" // "-bestpath", boolean, default "yes", Run bestpath (Dijkstra) search over word lattice (3rd pass)
// #define kBACKTRACE @"null" // "-backtrace", boolean, default "no", Print results and backtraces to log file.
// #define kLATSIZE @"null" // "-latsize", int, default "5000", Initial backpointer table size
// #define kMAXWPF @"null" // "-maxwpf", int, default @"null" // "-1", Maximum number of distinct word exits at each frame (or -1 for no pruning)
// #define kMAXHMMPF @"null" // "-maxhmmpf", int, default "10000", Maximum number of active HMMs to maintain at each frame (or -1 for no pruning)
// #define kMIN_ENDFR @"null" // "-min_endfr", int, default "0", Nodes ignored in lattice construction if they persist for fewer than N frames
// #define kFWDFLATEFWID @"null" // "-fwdflatefwid", int, default "4", Minimum number of end frames for a word to be searched in fwdflat search
// #define kFWDFLATSFWIN @"null" // "-fwdflatsfwin", int, default "25", Window of frames in lattice to search for successor words in fwdflat search",  }

/** Command-line options for keyword spotting */

// #define kKEYPHRASE @"null" // "-keyphrase", string, default NULL, Keyphrase to spot
// #define kKWS @"null" // "-kws", string, default NULL, A file with keyphrases to spot, one per line
// #define kKWS_PLP @"null" // "-kws_plp", float, default "1e-1", Phone loop probability for keyword spotting
// #define kKWS_THRESHOLD @"null" // "-kws_threshold", float, default "1", Threshold for p(hyp)/p(alternatives) ratio

/** Command-line options for finite state grammars. */

// #define kFSG @"null" // "-fsg", string, default NULL, Sphinx format finite state grammar file
// #define kJSGF @"null" // "-jsgf", string, default NULL, JSGF grammar file
// #define kTOPRULE @"null" // "-toprule", string, default NULL, Start rule for JSGF (first public rule is default)
// #define kFSGUSEALTPRON @"null" // "-fsgusealtpron", boolean, default "yes", Add alternate pronunciations to FSG
// #define kFSGUSEFILLER @"null" // "-fsgusefiller", boolean, default "yes", Insert filler words at each state.

/** Command-line options for statistical language models. */

// #define kALLPHONE @"null" // "-allphone", string, default NULL, Perform phoneme decoding with phonetic lm
// #define kALLPHONE_CI @"null" // "-allphone_ci", boolean, default "no", Perform phoneme decoding with phonetic lm and context-independent units only
// #define kLM @"null" // "-lm", string, default NULL, Word trigram language model input file
// #define kLMCTL @"null" // "-lmctl", string, default NULL, Specify a set of language model
// #define kLMNAME @"null" // "-lmname", string, default "default", Which language model in -lmctl to use by default
// #define kLW @"6.5" // "-lw", float, default "6.5", Language model probability weight
// #define kFWDFLATLW @"null" // "-fwdflatlw", float, default "8.5", Language model probability weight for flat lexicon (2nd pass) decoding
// #define kBESTPATHLW @"null" // "-bestpathlw", float, default "9.5", Language model probability weight for bestpath search
// #define kASCALE @"null" // "-ascale", float, default "20.0", Inverse of acoustic model scale for confidence score calculation
// #define kWIP @"null" // "-wip", float, default "0.65", Word insertion penalty
// #define kNWPEN @"null" // "-nwpen", float, default "1.0", New word transition penalty
// #define kPIP @"null" // "-pip", float, default "1.0", Phone insertion penalty
// #define kUW @"null" // "-uw", float, default "1.0", Unigram weight
// #define kSILPROB @"null" // "-silprob", float, default "0.005", Silence word transition probability
// #define kFILLPROB @"null" // "-fillprob", float, default "1e-8  ", Filler word transition probability
// #define kBGHIST @"null" // "-bghist", boolean, default "no", Bigram-mode: If TRUE only one BP entry/frame; else one per LM state
// #define kLEXTREEDUMP @"null" // "-lextreedump", int, default "0", Whether to dump the lextree structure to stderr (for debugging), 1 for Ravi's format, 2 for Dot format, Larger than 2 will be treated as Ravi's format

/** Command-line options for dictionaries. */

// #define kDICT kDictionaryName // "-dict", string, default NULL, Main pronunciation dictionary (lexicon) input file
// #define kFDICT @"null" // "-fdict", string, default NULL, Noise word pronunciation dictionary input file
// #define kDICTCASE @"null" // "-dictcase", boolean, default "no", Dictionary is case sensitive (NOTE: case insensitivity applies to ASCII characters only)
// #define kMAXNEWOOV @"null" // "-maxnewoov", int, default "20", Maximum new OOVs that can be added at run time
// #define kUSEWDPHONES @"null" // "-usewdphones", boolean, default "no", Use within-word phones only

/** Command-line options for acoustic modeling */

// #define kHMM @"null" // "-hmm", string, default NULL, Directory containing acoustic model files."},                            \
// #define kFEATPARAMS @"null" // "-featparams", string, default NULL, File containing feature extraction parameters."},                        \
// #define kMDEF @"null" // "-mdef", string, default NULL, Model definition input file
// #define kSENMGAU @"null" // "-senmgau", string, default NULL, Senone to codebook mapping input file (usually not needed)
// #define kTMAT @"null" // "-tmat", string, default NULL, HMM state transition matrix input file
// #define kTMATFLOOR @"null" // "-tmatfloor", float, default "0.0001", HMM state transition probability floor (applied to -tmat file)
// #define kMEAN @"null" // "-mean", string, default NULL, Mixture gaussian means input file
// #define kVAR @"null" // "-var", string, default NULL, Mixture gaussian variances input file
// #define kVARFLOOR @"null" // "-varfloor", float, default "0.0001", Mixture gaussian variance floor (applied to data from -var file)
// #define kMIXW @"null" // "-mixw", string, default NULL, Senone mixture weights input file (uncompressed)
// #define kMIXWFLOOR @"null" // "-mixwfloor", float, default "0.0000001", Senone mixture weights floor (applied to data from -mixw file)
// #define kAW @"null" // "-aw", int, default "1", Inverse weight applied to acoustic scores.
// #define kSENDUMP @"null" // "-sendump", string, default NULL, Senone dump (compressed mixture weights) input file
// #define kMLLR @"null" // "-mllr", string, default NULL, MLLR transformation to apply to means and variances
// #define kMMAP @"null" // "-mmap", boolean, default "yes", Use memory-mapped I/O (if possible) for model files
// #define kDS @"null" // "-ds", int, default "1", Frame GMM computation downsampling ratio
// #define kTOPN @"null" // "-topn", int, default "4", Maximum number of top Gaussians to use in scoring.
// #define kTOPN_BEAM @"null" // "-topn_beam", string, default "0", Beam width used to determine top-N Gaussians (or a list, per-feature)
// #define kKDTREE @"null" // "-kdtree", string, default NULL, kd-Tree file for Gaussian selection
// #define kKDMAXDEPTH @"null" // "-kdmaxdepth", int, default "0", Maximum depth of kd-Trees to use
// #define kKDMAXBBI @"null" // "-kdmaxbbi", int, default @"null" // "-1", Maximum number of Gaussians per leaf node in kd-Trees
// #define kLOGBASE @"null" // "-logbase", float, default "1.0001", Base in which all log-likelihoods calculated