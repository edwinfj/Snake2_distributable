 /* 'vnSound.h' */

 /* Mirus base types header */
#include "vnDatatypes.h"
 /* Mirus error definitions header */
#include "vnError.h"
 /* Mirus sound player header file */
#include "vnSoundPlayer.h"
 /* Windows header file */
#include <windows.h>
 /* C++ file stream header file */
#include <fstream>
 /* Direct Music header file */
#include <dsound.h>

 /* Include this file only once */
#pragma once
using namespace std;
 /* Vino Sound class */
class vnSound
{
protected:
  /* DirectSound objects */
 LPDIRECTSOUNDBUFFER          m_lpkSound;

public:
  /* Constructors / Destructor */
 vnSound (void);
 ~vnSound (void);

  /* Sound manipulation routines */
 vnError32 LoadFromFile (LPSTR lpszFilename);
 vnError32 SetVolume (vnUInt32 iVolume);
 vnError32 Play (vnUInt32 iLoop);
 vnError32 Stop (void);
};