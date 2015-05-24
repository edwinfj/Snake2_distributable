 /* 'vnSoundPlayer.cpp' */

 /* Complement header file */
#include "vnSoundPlayer.h"

 /* Singleton object */
vnSoundPlayer * vnSoundPlayer::m_pkSingleton = NULL;

 /* Default constructor */
vnSoundPlayer::vnSoundPlayer (void)
{
 m_lpkDSound = NULL;

 assert (!m_pkSingleton);
 m_pkSingleton = this;
}

 /* Default destructor */
vnSoundPlayer::~vnSoundPlayer (void)
{
 if (NULL != m_lpkDSound)
 {
  m_lpkDSound->Release ();
  m_lpkDSound = NULL;
 }

 assert (m_pkSingleton);
 m_pkSingleton = NULL;
}

 /* Initializes the sound player */
vnError32 vnSoundPlayer::Init (HWND hWindow)
{
  /* Create DirectSound object */
 DirectSoundCreate8 (NULL, &m_lpkDSound, NULL);

 if (NULL == m_lpkDSound)
 {
  return vnErrorCreateSoundDevice;
 }

  /* Set DirectSound cooperative level */
 if (FAILED (m_lpkDSound->SetCooperativeLevel (hWindow, DSSCL_NORMAL)) )
 {
  return vnErrorSetCooperativeLevel;
 }
 return vnNoError;
}

 /* Returns a pointer to the DirectSound interface */
LPDIRECTSOUND8 vnSoundPlayer::GetSound (void)
{
 return m_lpkDSound;
}

 /* Returns the vnSoundPlayer singleton */
vnSoundPlayer * vnSoundPlayer::GetSingleton (void)
{
 assert (m_pkSingleton);
 return m_pkSingleton;
}
