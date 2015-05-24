 /* 'vnSoundPlayer.h' */

 /* Mirus base types header */
#include "vnDatatypes.h"
 /* Mirus error definitions header */
#include "vnError.h"
 /* Windows header file */
#include <windows.h>
 /* Direct Music header file */
#include <dsound.h>
/* Assert header file */
#include <assert.h> 

 /* Include this file only once */
#pragma once

 /* Vino Sound Player class */
class vnSoundPlayer
{
protected:
  /* DirectSound objects */
 LPDIRECTSOUND8         m_lpkDSound;

  /* Singleton */
 static vnSoundPlayer * m_pkSingleton;

public:
  /* Constructors / Destructor */
 vnSoundPlayer (void);
 ~vnSoundPlayer (void);

  /* Sound player manipulation routines */
 vnError32 Init (HWND hWindow);

  /* Sound player maintainance routines */
 LPDIRECTSOUND8 GetSound (void);

  /* Singleton */
 static vnSoundPlayer * GetSingleton (void);
};