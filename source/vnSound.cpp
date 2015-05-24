 /* 'vnSound.cpp' */

 /* Complement header file */
#include "vnSound.h"

 /* Default constructor */
vnSound::vnSound (void)
{
 m_lpkSound = NULL;
}

 /* Default destructor */
vnSound::~vnSound (void)
{
 if (NULL != m_lpkSound)
 {
  m_lpkSound->Release ();
  m_lpkSound = NULL;
 }
}

 /* Load the wave from file */
vnError32 vnSound::LoadFromFile (LPSTR lpszFilename)
{
 fstream     kWave;

  /* Open the wave file */
 kWave.open (lpszFilename, ios::in | ios::binary);

 if (kWave.is_open ())
 {
  vnInt8 aiID [5];
   /* Read the string RIFF identifier */
  kWave.read (aiID, sizeof (vnInt8) * 4);
  aiID [4] = '\0';
   /* If not RIFF, it is not supported */
  if (0 != strcmp (aiID, "RIFF"))
  {
   return vnErrorWaveNotSupported;
  }

  vnUInt32 iSize;
   /* Read the size of the wave */
  kWave.read ((vnInt8 *) &iSize, sizeof (vnUInt32));

   /* Read the string WAVE identifier */
  kWave.read (aiID, sizeof (vnInt8) * 4);
  aiID [4] = '\0';
   /* If not WAVE, it is not supported */
  if (0 != strcmp (aiID, "WAVE"))
  {
   return vnErrorWaveNotSupported;
  }
   /* Ignore 'fmt ' string */
  kWave.seekg (4, ios::cur);

   /* Read the 'fmt ' chunk length  */
  vnUInt32 iFormatLength;
  kWave.read ((vnInt8 *) &iFormatLength, sizeof (vnUInt32));

   /* Read the WAVEFORMATEX structure */
  WAVEFORMATEX kWaveFormat;

  kWave.read ((vnInt8 *) &kWaveFormat, sizeof (WAVEFORMATEX));
   /* Ignore two bytes since we already read the first two of
      the 'data' chunk string since WAVEFORMATEX has an extra
      two bytes */
  kWave.seekg (2, ios::cur);
  kWaveFormat.cbSize = 0;

   /* Read the size of the wave data */
  vnUInt32 iDataSize;
  kWave.read ((vnInt8 *) &iDataSize, sizeof (vnUInt32));

   /* Read the sound data */
  vnUInt8 * pkSoundBuffer = new vnUInt8 [iDataSize];
  kWave.read ((vnInt8 *) pkSoundBuffer, iDataSize);

   /* Fill DirectSound buffer description */
  DSBUFFERDESC         kBufferDesc;

  ZeroMemory (&kBufferDesc, sizeof (DSBUFFERDESC));
  kBufferDesc.dwSize        = sizeof (DSBUFFERDESC);
  kBufferDesc.dwBufferBytes = iDataSize;
  kBufferDesc.lpwfxFormat   = &kWaveFormat; 
  kBufferDesc.dwFlags       = DSBCAPS_CTRLVOLUME;
 
   /* Create the sound buffer */
  if (FAILED (vnSoundPlayer::GetSingleton()->GetSound ()->
              CreateSoundBuffer (&kBufferDesc, &m_lpkSound, NULL)) )
  {
   return vnErrorCreateSoundBuffer;
  }

   /* Lock the sound buffer */
  LPVOID lpvAudio;
  DWORD  dwBytes;
  if (FAILED (m_lpkSound->Lock(0, 0,&lpvAudio, &dwBytes, NULL, NULL, 
                               DSBLOCK_ENTIREBUFFER)) )
  {
   return vnErrorSoundBufferLock;
  }

   /* Copy the wave data to the DirectSound buffer */
  memcpy (lpvAudio, pkSoundBuffer, dwBytes);
  m_lpkSound->Unlock(lpvAudio, dwBytes, NULL, 0);

   /* Delete the memory used by the wave data and close the file */
  delete [] pkSoundBuffer;
  kWave.close ();
 }
  
 return vnNoError;
}

 /* Set the sound volume */
vnError32 vnSound::SetVolume (vnUInt32 iVolume)
{
 if (FAILED (m_lpkSound->SetVolume ((100-iVolume) * 100)) )
 {
  return vnErrorSoundSetVolume;
 }

 return vnNoError;
}

 /* Play the sound */
vnError32 vnSound::Play (vnUInt32 iLoop)
{
  /* Go to beggining of sound */
 m_lpkSound->SetCurrentPosition (0);
  /* Play sound */
 if (FAILED (m_lpkSound->Play (0, NULL, 
            (iLoop != 0) ? DSBPLAY_LOOPING : 0)) )
 {
  return vnErrorPlay;
 }
 return vnNoError;
}

 /* Stop playing the sound */
vnError32 vnSound::Stop (void)
{
 if (FAILED (m_lpkSound->Stop ()) )
 {
  return vnErrorStop;
 }
 return vnNoError;
}
