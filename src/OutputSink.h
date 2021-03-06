#ifndef OUTPUT_SINK_H
#define OUTPUT_SINK_H

#include <alsa/asoundlib.h>
#include <string>
#include <poll.h>

/**
* Adaptor for ALSA audio output. Will create and initialise an ALSA system and allow sound data to be written.
*/
class OutputSink {

	public:	

	/**
	 * Write some samples to the output.
	 * 
	 * This should be written to at a fast enough rate as to provide
	 * enough data for the output. The actual behaviour of this method
	 * will vary depending on which implementation is used, but this
	 * requirement is constant.
	 *
	 * @param buffer Buffer containing the sample data
	 * @param length Number of samples in the buffer
	 */
	virtual void writeSamples(short buffer[], int length) = 0;
	 
	/**
	 * Close the audio system, will wait for sound to finish.
 	 */
	virtual void close() = 0;
	
	virtual ~OutputSink() { }

	/* Exception List */

	/** Thrown when pcm could not be opened */
	class UnableToOpenPCMException {};

};

#endif // OUTPUT_SINK_H
