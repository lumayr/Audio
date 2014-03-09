/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "analyze_peakdetect.h"

// #define PEAKREPORTVERBS

void AudioPeak::update(void)
{
	audio_block_t *block;
	const int16_t *p, *end;
	block = receiveReadOnly();
	if (!block) {
#ifdef PEAKREPORTVERBS
		Serial.println("AudioPeak !block");
#endif
		return;
	}
	if (!m_enabled) {
		release(block);
		return;
	}
	p = block->data;
	end = p + AUDIO_BLOCK_SAMPLES;
	do {
		int16_t d=*p++;
		if(d<min) min=d;
		if(d>max) max=d;
	} while (p < end);
#ifdef PEAKREPORTVERBS
	Serial.println("AudioPeak ran");
#endif
	release(block);
}

void AudioPeak::begin(bool noReset)
{
	if(!noReset)
	{
		min=0;
		max=0;
	}
	m_enabled=true;
}
uint16_t AudioPeak::Dpp(void)
{
	return max-min;
}
