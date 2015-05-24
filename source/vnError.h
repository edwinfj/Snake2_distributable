/* 'vnError.h' */
#ifndef _VNERROR_H
#define _VNERROR_H

/* Error codes */

enum vnError32
{
	vnNoError = 0,
	vnErrorRegisterClass,
	vnErrorInitScreen,
	

	vnErrorSetCooperativeLevel												= 17,
	/* Sound component */
	vnErrorWaveNotSupported													= 35,
	vnErrorPlay																= 36,
	vnErrorCreateSoundBuffer												= 37,
	vnErrorSoundBufferLock													= 38,
	vnErrorSoundSetVolume													= 39,
	vnErrorStop																= 40,
	vnErrorCreateSoundDevice												= 41,
	vnError32_Force32 = 0xFFFFFFFF
};
#endif

