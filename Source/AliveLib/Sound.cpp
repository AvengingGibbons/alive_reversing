#include "stdafx.h"
#include "Sound.hpp"
#include "Function.hpp"
#include "stdlib.hpp"
#include "Error.hpp"
#include "Sys.hpp"
#include "Midi.hpp"
#include "BackgroundMusic.hpp"
#if !USE_SDL2_SOUND
#include <mmeapi.h>
#include <timeapi.h>
#endif
#include <mutex>
#include "Path.hpp"
#include "MusicController.hpp"
#include "Map.hpp"
#include "Slig.hpp"
#include "Slog.hpp"
#include "Fleech.hpp"

bool gReverbEnabled = false;
bool gAudioStereo = true;

#if !USE_SDL2_SOUND
ALIVE_VAR(1, 0xBBC344, LPDIRECTSOUND, sDSound_BBC344, nullptr);
ALIVE_VAR(1, 0xbbc388, LPDIRECTSOUNDBUFFER, sPrimarySoundBuffer_BBC388, 0);
#endif

ALIVE_VAR(1, 0xBBC394, int, sLoadedSoundsCount_BBC394, 0);
ALIVE_VAR(1, 0xbbbab0, char, sPrimarySoundBufferChannels_BBBAB0, 0);
ALIVE_VAR(1, 0xbbc338, char, sPrimarySoundBufferBitsPerSample_BBC338, 0);
ALIVE_VAR(1, 0xbbc340, int, sPrimarySoundBufferSampleRate_BBC340, 0);
ALIVE_VAR(1, 0xbbc33c, int, sLastNotePlayTime_BBC33C, 0);


ALIVE_ARY(1, 0xBBBAB8, SoundBuffer, 32, sSoundBuffers_BBBAB8, {});
ALIVE_ARY(1, 0xBBBD38, int, 127, sVolumeTable_BBBD38, {});
ALIVE_ARY(1, 0xBBBF38, SoundEntry*, 256, sSoundSamples_BBBF38, {});
ALIVE_ARY(1, 0xBBC348, char, 64, sDSoundErrorBuffer_BBC348, {});

const DWORD k127_dword_575158 = 127;

#if !USE_SDL2_SOUND
EXPORT char * CC SND_HR_Err_To_String_4EEC70(HRESULT hr)
{
    switch (hr)
    {
    case S_OK:
        return "";
    case DSERR_INVALIDCALL:
        return "DSERR_INVALIDCALL: This function is not valid for the current state of this object.";
    case DSERR_PRIOLEVELNEEDED:
        return "DSERR_PRIOLEVELNEEDED: The caller does not have the priority level required for the function to succeed.";
    case DSERR_NODRIVER:
        return "DSERR_NODRIVER: No sound driver is available for use.";
    case DSERR_OTHERAPPHASPRIO:
        return "DSERR_OTHERAPPHASPRIO: This value is obsolete and is not used.";
    case DSERR_UNINITIALIZED:
        return "DSERR_UNINITIALIZED: The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called.";
    case DSERR_CONTROLUNAVAIL:
        return "DSERR_CONTROLUNAVAIL: The control (volume, pan, and so forth) requested by the caller is not available.";
    case DSERR_INVALIDPARAM:
        return "DSERR_INVALIDPARAM: An invalid parameter was passed to the returning function.";
    case DSERR_ALLOCATED:
        return "DSERR_ALLOCATED: The request failed because resources, such as a priority level, were already in use by another caller.";
    case DSERR_OUTOFMEMORY:
        return "DSERR_OUTOFMEMORY: The DirectSound subsystem could not allocate sufficient memory to complete the caller's request.";
    case DSERR_UNSUPPORTED:
        return "DSERR_UNSUPPORTED: The function called is not supported at this time. ";
    case DSERR_GENERIC:
        return "DSERR_GENERIC: An undetermined error occurred inside the DirectSound subsystem.";
    case DSERR_NOAGGREGATION:
        return "DSERR_NOAGGREGATION: The object does not support aggregation.";
    }

    if (FAILED(hr))
    {
        sprintf(sDSoundErrorBuffer_BBC348, "DirectSound error %ld %lx", hr, hr);
        return sDSoundErrorBuffer_BBC348;
    }

    return "";
}

EXPORT signed int CC SND_CreateDS_4EEAA0(unsigned int sampleRate, int bitsPerSample, int isStereo)
{
    if (sDSound_BBC344)
    {
        // Already created
        return 0;
    }

    HRESULT dsoundHR = DirectSoundCreate(0, &sDSound_BBC344, 0);

    if (dsoundHR)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 471, -1, SND_HR_Err_To_String_4EEC70(dsoundHR));
        return -1;
    }
    else
    {
        // TODO: HACK
        HWND hwnd;
#if USE_SDL2
        hwnd = Sys_Win32FromSDLWindow(Sys_GetHWnd_4F2C70());
#else
        hwnd = Sys_GetHWnd_4F2C70();
#endif

        if (hwnd)
        {
            if (sDSound_BBC344->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE))
            {
                Error_PushErrorRecord_4F2920(
                    "C:\\abe2\\code\\POS\\SND.C",
                    483,
                    -1,
                    "SND_Init(): IDirectSound_SetCooperativeLevel failed");
                return -1;
            }
            else
            {
                DSCAPS dsCaps;
                dsCaps.dwSize = 96;
                if (!sDSound_BBC344->GetCaps(&dsCaps))
                {
                    if (dsCaps.dwFlags & DSCAPS_PRIMARY16BIT)
                    {
                        bitsPerSample = 16;
                    }
                    else if (dsCaps.dwFlags & DSCAPS_PRIMARY8BIT)
                    {
                        bitsPerSample = 8;
                    }

                    if (dsCaps.dwFlags & DSCAPS_PRIMARYSTEREO)
                    {
                        if (!(dsCaps.dwFlags & DSCAPS_PRIMARYMONO))
                        {
                            isStereo = 1;
                        }
                    }
                    else
                    {
                        isStereo = 0;
                    }
                    if (dsCaps.dwPlayCpuOverheadSwBuffers > 5)
                    {
                        if (dsCaps.dwPlayCpuOverheadSwBuffers > 10)
                        {
                            int newBitsPerSample = bitsPerSample;
                            if (dsCaps.dwPlayCpuOverheadSwBuffers > 20)
                            {
                                newBitsPerSample = bitsPerSample >> 1;
                            }
                            SND_CreatePrimarySoundBuffer_4EEEC0(sampleRate >> 1, newBitsPerSample, 0);
                        }
                        else
                        {
                            SND_CreatePrimarySoundBuffer_4EEEC0(sampleRate >> 1, bitsPerSample, isStereo);
                        }
                    }
                    else
                    {
                        SND_CreatePrimarySoundBuffer_4EEEC0(sampleRate, bitsPerSample, isStereo);
                    }
                }

                sPrimarySoundBufferSampleRate_BBC340 = sampleRate;
                sPrimarySoundBufferBitsPerSample_BBC338 = static_cast<char>(bitsPerSample);
                sPrimarySoundBufferChannels_BBBAB0 = static_cast<char>(isStereo);

                SND_InitVolumeTable_4EEF60();

                if (sLoadedSoundsCount_BBC394)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        if (sSoundSamples_BBBF38[i])
                        {
                            SND_Renew_4EEDD0(sSoundSamples_BBBF38[i]);
                            SND_Reload_4EF1C0(sSoundSamples_BBBF38[i], 0, sSoundSamples_BBBF38[i]->field_8_pSoundBuffer, sSoundSamples_BBBF38[i]->field_C_buffer_size_bytes / (unsigned __int8)sSoundSamples_BBBF38[i]->field_1D_blockAlign);
                            if ((i + 1) == sLoadedSoundsCount_BBC394)
                                break;
                        }
                    }
                }
                sLastNotePlayTime_BBC33C = timeGetTime();
                return 0;
            }
        }
        else
        {
            Error_PushErrorRecord_4F2920(
                "C:\\abe2\\code\\POS\\SND.C",
                477,
                -1,
                "SND_Init(): SYS_GetOutputDevice() == NULL !!");
            return -1;
        }
    }
}


EXPORT int CC SND_Reload_4EF350(SoundEntry* pSoundEntry, unsigned int sampleOffset, unsigned int size)
{
    if (!sDSound_BBC344)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 692, -1, "DirectSound not initialized");
        return -1;
    }

    const DWORD alignedOffset = sampleOffset * pSoundEntry->field_1D_blockAlign;
    const DWORD alignedSize = size * pSoundEntry->field_1D_blockAlign;

    LPVOID pLocked1 = nullptr;
    DWORD locked1Size = 0;

    LPVOID pLocked2 = nullptr;
    DWORD locked2Size = 0;

    HRESULT hr = pSoundEntry->field_4_pDSoundBuffer->Lock(
        alignedOffset,
        alignedSize,
        &pLocked1,
        &locked1Size,
        &pLocked2,
        &locked2Size,
        0);

    if (hr == DSERR_BUFFERLOST)
    {
        if (FAILED(pSoundEntry->field_4_pDSoundBuffer->Restore()))
        {
            Error_PushErrorRecord_4F2920(
                "C:\\abe2\\code\\POS\\SND.C",
                702,
                -1,
                "SND_Reload(): Cannot restore the lost ds buffer");
            return -1;
        }

        hr = pSoundEntry->field_4_pDSoundBuffer->Lock(
            alignedOffset,
            alignedSize,
            &pLocked1,
            &locked1Size,
            &pLocked2,
            &locked2Size,
            0);
    }

    if (FAILED(hr))
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 710, -1, "SND_Reload(): Cannot lock the ds buffer");
        return -1;
    }

    if (pLocked1)
    {
        BYTE* ptr = (BYTE*)pLocked1;
        memset(ptr, 0, locked1Size);
    }

    if (pLocked2)
    {
        BYTE* ptr = (BYTE*)pLocked2;
        memset(ptr, 0, locked2Size);
    }

    pSoundEntry->field_4_pDSoundBuffer->Unlock(pLocked1, locked1Size, pLocked2, locked2Size);
    return 0;
}

EXPORT void CC SND_SsQuit_4EFD50()
{
    if (sDSound_BBC344)
    {
        for (int i = 0; i < 32; i++)
        {
            if (sSoundBuffers_BBBAB8[i].field_0_pDSoundBuffer)
            {
                sSoundBuffers_BBBAB8[i].field_0_pDSoundBuffer->Stop();
                sSoundBuffers_BBBAB8[i].field_0_pDSoundBuffer->Release();
                sSoundBuffers_BBBAB8[i].field_0_pDSoundBuffer = nullptr;
            }
        }

        for (int i = 0; i < sLoadedSoundsCount_BBC394; i++)
        {
            SoundEntry* pEntry = sSoundSamples_BBBF38[i];
            if (pEntry->field_4_pDSoundBuffer)
            {
                pEntry->field_4_pDSoundBuffer->Stop();
                pEntry->field_4_pDSoundBuffer->Release();
                pEntry->field_4_pDSoundBuffer = nullptr;
                pEntry->field_10 = 0;
            }
        }

        sDSound_BBC344->Release();
        sDSound_BBC344 = nullptr;
    }
}

EXPORT signed int CC SND_Free_4EFA30(SoundEntry* pSnd)
{
    if (!sDSound_BBC344)
    {
        return -1;
    }

    pSnd->field_10 = 0;

    if (pSnd->field_8_pSoundBuffer)
    {
        mem_free_4F4EA0(pSnd->field_8_pSoundBuffer);
        pSnd->field_8_pSoundBuffer = 0;
    }

    if (pSnd->field_4_pDSoundBuffer)
    {
        pSnd->field_4_pDSoundBuffer->Release();
        pSnd->field_4_pDSoundBuffer = nullptr;
    }

    sSoundSamples_BBBF38[pSnd->field_0_tableIdx] = nullptr;
    sLoadedSoundsCount_BBC394--;
    return 0;
}

EXPORT void CC SND_InitVolumeTable_4EEF60()
{
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

    for (int i = 0; i < 127; i++)
    {
        sVolumeTable_BBBD38[i] = static_cast<int>(min(max(log2f((i + 1) / 128.0f) / log2f(2.0f) * 1000.0f, -10000), 0));
    }
    sVolumeTable_BBBD38[0] = -10000;
}

EXPORT char CC SND_CreatePrimarySoundBuffer_4EEEC0(int sampleRate, int bitsPerSample, int isStereo)
{
    DSBUFFERDESC bufferDesc = {};
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwBufferBytes = 0;
    bufferDesc.dwFlags = 1;
    bufferDesc.dwReserved = 0;
    bufferDesc.lpwfxFormat = 0;

    if (FAILED(sDSound_BBC344->CreateSoundBuffer(&bufferDesc, &sPrimarySoundBuffer_BBC388, nullptr)))
    {
        return -1;
    }

    if (SUCCEEDED(sPrimarySoundBuffer_BBC388->Play(0, 0, 1)))
    {
        return SND_SetPrimarySoundBufferFormat_4EE990(sampleRate, bitsPerSample, static_cast<unsigned char>(isStereo)) != 0 ? 0xFD : 0;
    }

    sPrimarySoundBuffer_BBC388->Release();
    return -2;
}

EXPORT void CC SND_Init_WaveFormatEx_4EEA00(WAVEFORMATEX *pWaveFormat, int sampleRate, unsigned __int8 bitsPerSample, int isStereo)
{
    pWaveFormat->nSamplesPerSec = 0;
    pWaveFormat->nAvgBytesPerSec = 0;
    pWaveFormat->cbSize = 0;
    pWaveFormat->nSamplesPerSec = sampleRate;
    pWaveFormat->nChannels = (isStereo != 0) + 1;
    pWaveFormat->wBitsPerSample = bitsPerSample;
    pWaveFormat->wFormatTag = WAVE_FORMAT_PCM;
    pWaveFormat->nBlockAlign = bitsPerSample * ((isStereo != 0) + 1) / 8;
    pWaveFormat->nAvgBytesPerSec = sampleRate * pWaveFormat->nBlockAlign;
}

EXPORT int CC SND_SetPrimarySoundBufferFormat_4EE990(int sampleRate, int bitsPerSample, unsigned __int8 isStereo)
{
    WAVEFORMATEX pWaveFormat = {};

    if (!sPrimarySoundBuffer_BBC388)
    {
        return -2;
    }

    pWaveFormat.wFormatTag = 0;
    pWaveFormat.nSamplesPerSec = 0;
    pWaveFormat.nAvgBytesPerSec = 0;
    pWaveFormat.nBlockAlign = 0;
    pWaveFormat.cbSize = 0;
    SND_Init_WaveFormatEx_4EEA00(&pWaveFormat, sampleRate, static_cast<unsigned char>(bitsPerSample), isStereo);
    return -(sPrimarySoundBuffer_BBC388->SetFormat(&pWaveFormat) != 0);
}

EXPORT signed int CC SND_Renew_4EEDD0(SoundEntry *pSnd)
{
    if (!sDSound_BBC344)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 351, -1, "DirectSound not initialized");
        return -1;
    }

    WAVEFORMATEX waveFormat;
    DSBUFFERDESC bufferDesc;

    waveFormat.wFormatTag = 0;
    waveFormat.nSamplesPerSec = 0;
    waveFormat.nAvgBytesPerSec = 0;
    waveFormat.nBlockAlign = 0;
    waveFormat.cbSize = 0;

    SND_Init_WaveFormatEx_4EEA00(&waveFormat, pSnd->field_18_sampleRate, pSnd->field_1C_bitsPerSample, pSnd->field_20_isStereo & 1);

    bufferDesc.dwBufferBytes = pSnd->field_14_buffer_size_bytes;
    bufferDesc.dwReserved = 0;
    bufferDesc.lpwfxFormat = &waveFormat;
    bufferDesc.dwSize = 20;
    bufferDesc.dwFlags = 82144; // TODO: Fix constants

    if (sDSound_BBC344->CreateSoundBuffer(&bufferDesc, &pSnd->field_4_pDSoundBuffer, 0))
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 371, -1, "SND_Renew(): Cannot create ds sound buffer");
        return -1;
    }
    else
    {
        pSnd->field_10 = 0;
        return 0;
    }
}

EXPORT signed int CC SND_Reload_4EF1C0(const SoundEntry* pSnd, DWORD sampleOffset, unsigned char* pSoundBuffer, unsigned int sampleCount)
{
    const int offsetBytes = sampleOffset * pSnd->field_1D_blockAlign;
    const unsigned int bufferSizeBytes = sampleCount * pSnd->field_1D_blockAlign;

    if (!sDSound_BBC344)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 644, -1, "DirectSound not initialized");
        return -1;
    }

    unsigned int *leftChannelBuffer;
    int leftChannelSize;
    char * rightChannelBuffer;
    int rightChannelSize;

    int lockHR = pSnd->field_4_pDSoundBuffer->Lock(offsetBytes, bufferSizeBytes, (LPVOID *)&leftChannelBuffer, (LPDWORD)&leftChannelSize, (LPVOID *)&rightChannelBuffer, (LPDWORD)&rightChannelSize, 0);

    if (lockHR == DSERR_BUFFERLOST)
    {
        if (pSnd->field_4_pDSoundBuffer->Restore())
        {
            Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 654, -1, "SND_Reload(): Cannot restore the lost ds buffer");
            return -1;
        }
        lockHR = pSnd->field_4_pDSoundBuffer->Lock(offsetBytes, bufferSizeBytes, (LPVOID *)&leftChannelBuffer, (LPDWORD)&leftChannelSize, (LPVOID *)&rightChannelBuffer, (LPDWORD)&rightChannelSize, 0);
    }

    if (lockHR)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 662, -1, "SND_Reload(): Cannot lock the ds buffer");
        return -1;
    }

    if (pSnd->field_1C_bitsPerSample == 8) // All samples are 16 bits per sample, so....
    {
        if (leftChannelBuffer)
        {
            SND_4F00B0(leftChannelBuffer, (unsigned int)pSoundBuffer, (int)leftChannelSize);
        }
        if (rightChannelBuffer)
        {
            SND_4F00B0((unsigned int *)rightChannelBuffer, (DWORD)pSoundBuffer + (unsigned int)leftChannelSize, rightChannelSize);
        }
    }
    else
    {
        if (leftChannelBuffer)
        {
            memcpy(leftChannelBuffer, pSoundBuffer, leftChannelSize);
        }
        if (rightChannelBuffer) // dual buffers never really exist, so this is always null
        {
            memcpy(rightChannelBuffer, &pSoundBuffer[leftChannelSize], rightChannelSize);
        }
    }

    pSnd->field_4_pDSoundBuffer->Unlock(leftChannelBuffer, leftChannelSize, rightChannelBuffer, rightChannelSize);

    return 0;
}

EXPORT signed int CC SND_New_4EEFF0(SoundEntry *pSnd, int sampleLength, int sampleRate, int bitsPerSample, int isStereo)
{
    if (!sDSound_BBC344)
    {
        return -1;
    }

    if (sLoadedSoundsCount_BBC394 < 256)
    {
        WAVEFORMATEX waveFormatEx;
        DSBUFFERDESC bufferDesc;

        waveFormatEx.wFormatTag = 0;
        waveFormatEx.nSamplesPerSec = 0;
        waveFormatEx.nAvgBytesPerSec = 0;
        waveFormatEx.nBlockAlign = 0;
        waveFormatEx.cbSize = 0;
        SND_Init_WaveFormatEx_4EEA00(&waveFormatEx, sampleRate, static_cast<unsigned char>(bitsPerSample), isStereo & 1);

        const int sampleByteSize = sampleLength * waveFormatEx.nBlockAlign;
        bufferDesc.dwReserved = 0;
        bufferDesc.lpwfxFormat = &waveFormatEx;
        pSnd->field_1D_blockAlign = static_cast<unsigned char>(waveFormatEx.nBlockAlign);
        bufferDesc.dwSize = 20;
        bufferDesc.dwBufferBytes = sampleByteSize;
        bufferDesc.dwFlags = 82152;

        const HRESULT sbHR = sDSound_BBC344->CreateSoundBuffer(&bufferDesc, &pSnd->field_4_pDSoundBuffer, 0);

        if (sbHR)
        {
            Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 598, -1, "SND_New(): Cannot create ds sound buffer");
            Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 599, -1, SND_HR_Err_To_String_4EEC70(sbHR));
            return -1;
        }
        else
        {
            pSnd->field_10 = 0;
            unsigned char * bufferData = static_cast<unsigned char *>(malloc_4F4E60(sampleByteSize));
            pSnd->field_8_pSoundBuffer = bufferData;
            if (bufferData)
            {
                pSnd->field_18_sampleRate = sampleRate;
                pSnd->field_1C_bitsPerSample = static_cast<char>(bitsPerSample);
                pSnd->field_C_buffer_size_bytes = sampleByteSize;
                pSnd->field_14_buffer_size_bytes = sampleByteSize;
                pSnd->field_20_isStereo = isStereo;

                for (int i = 0; i < 256; i++)
                {
                    if (!sSoundSamples_BBBF38[i])
                    {
                        sSoundSamples_BBBF38[i] = pSnd;
                        pSnd->field_0_tableIdx = i;
                        sLoadedSoundsCount_BBC394++;
                        return 0;
                    }
                }

                return 0; // No free spaces left. Should never get here as all calls to Snd_NEW are checked before hand.
            }
            else
            {
                pSnd->field_4_pDSoundBuffer->Release();
                Error_PushErrorRecord_4F2920(
                    "C:\\abe2\\code\\POS\\SND.C",
                    608,
                    -1,
                    "SND_New(): Cannot create original data sound buffer");
                return -1;
            }
        }
    }
    else
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 568, -1, "SND_New: out of samples");
        return -1;
    }
}

EXPORT int CC SND_PlayEx_4EF740(const SoundEntry* pSnd, int panLeft, int panRight, float freq, MIDI_Struct1* pMidiStru, int playFlags, int priority)
{
    if (!sDSound_BBC344)
    {
        return -1;
    }

    if (!pSnd)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 845, -1, "SND_PlayEx: NULL SAMPLE !!!");
        return -1;
    }

    AE_BUFFERTYPE* pDSoundBuffer = pSnd->field_4_pDSoundBuffer;
    if (!pDSoundBuffer)
    {
        return -1;
    }

    sLastNotePlayTime_BBC33C = timeGetTime();

    int panLeft2 = panLeft;
    int panRight2 = panRight;
    if (panLeft > panRight)
    {
        panRight2 = panLeft;
    }

    int panRightConverted = 120 * panRight2 * k127_dword_575158 >> 14;// >> 14 = 16384
    if (panRightConverted < 0)
    {
        panRightConverted = 0;
    }
    else if (panRightConverted > 127)
    {
        panRightConverted = 127;
    }

    if (pSnd->field_20_isStereo & 2)
    {
        DWORD status = 0;
        if (FAILED(pDSoundBuffer->GetStatus(&status)))
        {
            return -1;
        }

        if (status & DSBSTATUS_PLAYING)
        {
            pDSoundBuffer->SetFrequency(static_cast<DWORD>((pSnd->field_18_sampleRate * freq) + 0.5)); // This freq don't get clamped for some reason
            pDSoundBuffer->SetVolume(sVolumeTable_BBBD38[panRightConverted]);
            pDSoundBuffer->SetCurrentPosition(0);
            return 0;
        }
    }
    else
    {
        SoundBuffer* pSoundBuffer = SND_Get_Sound_Buffer_4EF970(pSnd->field_0_tableIdx, panRightConverted + priority);
        if (!pSoundBuffer)
        {
            return -1;
        }

        HRESULT v15 = sDSound_BBC344->DuplicateSoundBuffer(pDSoundBuffer, &pSoundBuffer->field_0_pDSoundBuffer);
        if (FAILED(v15))
        {
            Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 921, -1, SND_HR_Err_To_String_4EEC70(v15));
            return -1;
        }

        pDSoundBuffer = pSoundBuffer->field_0_pDSoundBuffer;

        if (pMidiStru)
        {
            pMidiStru->field_0_sound_buffer_field_4 = pSoundBuffer->field_4;
        }
    }

    DWORD freqHz = static_cast<DWORD>((pSnd->field_18_sampleRate * freq) + 0.5);
    if (freqHz < DSBFREQUENCY_MIN)
    {
        freqHz = DSBFREQUENCY_MIN;
    }
    else if (freqHz >= DSBFREQUENCY_MAX)
    {
        freqHz = DSBFREQUENCY_MAX;
    }

    pDSoundBuffer->SetFrequency(freqHz);
    pDSoundBuffer->SetVolume(sVolumeTable_BBBD38[panRightConverted]);

    const int panConverted = (DSBPAN_RIGHT * (panLeft2 - panRight)) / 127; // From PSX pan range to DSound pan range
    pDSoundBuffer->SetPan(panConverted);

    if (playFlags & DSBPLAY_LOOPING)
    {
        playFlags = DSBPLAY_LOOPING;
    }

    HRESULT hr = pDSoundBuffer->Play(0, 0, playFlags);
    if (SUCCEEDED(hr))
    {
        return 0;
    }

    if (hr == DSERR_BUFFERLOST)
    {
        // Restore the lost buffer
        if (SND_Reload_4EF1C0(pSnd, 0, pSnd->field_8_pSoundBuffer, pSnd->field_C_buffer_size_bytes / pSnd->field_1D_blockAlign) == 0)
        {
            // Try again
            if (SUCCEEDED(pDSoundBuffer->Play(0, 0, playFlags)))
            {
                return 0;
            }
        }
    }

    return -1;
}

#endif
/////////////

EXPORT unsigned int CC SND_Get_Sound_Entry_Pos_4EF620(SoundEntry* pSoundEntry)
{
    DWORD dwReadPos = 0;
    DWORD dwWritePos = 0;
    pSoundEntry->field_4_pDSoundBuffer->GetCurrentPosition(&dwReadPos, &dwWritePos);
    return dwReadPos / pSoundEntry->field_1D_blockAlign;
}

// Never seems to get called?
// TODO: Clean up!
EXPORT DWORD * CC SND_4F00B0(unsigned int* /*a1*/, unsigned int /*a2*/, int /*a3*/)
{
    NOT_IMPLEMENTED();
    return 0;
    //DWORD *result; // eax
    //unsigned int *v4; // edx
    //unsigned int v5; // ecx
    //int v6; // esi
    //int v7; // esi

    //result = (DWORD *)a2;
    //v4 = a1;
    //v5 = a2 + a3;
    //if (a2 < a2 + a3)
    //{
    //    do
    //    {
    //        v6 = *result;
    //        ++result;
    //        *v4 = v6 ^ 0x80808080;
    //        ++v4;
    //    } while ((unsigned int)result < v5);
    //    if ((unsigned int)result < v5)
    //    {
    //        v7 = (char *)v4 - (char *)result;
    //        do
    //        {
    //            *((BYTE *)result + v7) = *(BYTE *)result ^ 0x80;
    //            result = (DWORD *)((char *)result + 1);
    //        } while ((unsigned int)result < v5);
    //    }
    //}
    //return result;
}

EXPORT int CC SND_Load_4EF680(SoundEntry* pSnd, const void* pWaveData, int waveDataLen)
{
    SND_Free_4EFA30(pSnd);
    if (!SND_New_4EEFF0(pSnd, waveDataLen, pSnd->field_18_sampleRate, pSnd->field_1C_bitsPerSample, pSnd->field_20_isStereo))
    {
        if (waveDataLen * pSnd->field_1D_blockAlign > pSnd->field_C_buffer_size_bytes)
        {
            Error_PushErrorRecord_4F2920("C:\\abe2\\code\\POS\\SND.C", 804, -1, "SND_Load(): data too big !!");
            return -1;
        }

        if (pSnd->field_8_pSoundBuffer)
        {
            memcpy(pSnd->field_8_pSoundBuffer, pWaveData, waveDataLen * pSnd->field_1D_blockAlign);
        }
    }
    return SND_Reload_4EF1C0(pSnd, 0, pSnd->field_8_pSoundBuffer, pSnd->field_C_buffer_size_bytes / pSnd->field_1D_blockAlign);
}

EXPORT int CC SND_Buffer_Set_Frequency_4EFC90(int idx, float hzChangeFreq)
{
    SoundBuffer* pSoundBuffer = &sSoundBuffers_BBBAB8[idx & 511];
    AE_BUFFERTYPE* pDSoundBuffer = pSoundBuffer->field_0_pDSoundBuffer;

    if (!pDSoundBuffer || ((idx ^ pSoundBuffer->field_4) & ~511)) // TODO: Refactor
    {
        return -1;
    }

    if (!sSoundSamples_BBBF38[pSoundBuffer->field_8])
    {
        return -2;
    }

    DWORD currrentFreqHz = 0;
    if (!pDSoundBuffer->GetFrequency(&currrentFreqHz))
    {
        DWORD freqHz = static_cast<DWORD>(currrentFreqHz * hzChangeFreq);
        if (freqHz < DSBFREQUENCY_MIN)
        {
            freqHz = DSBFREQUENCY_MIN;
        }
        else if (freqHz >= DSBFREQUENCY_MAX)
        {
            freqHz = DSBFREQUENCY_MAX;
        }
        pSoundBuffer->field_0_pDSoundBuffer->SetFrequency(freqHz);
    }
    return 0;
}

EXPORT int CC SND_Buffer_Get_Status_4F00F0(int idx, int a2)
{
    // TODO: Figure out the meaning of the constants in here
    SoundBuffer* pSoundBuffer = &sSoundBuffers_BBBAB8[idx];
    if (!pSoundBuffer->field_0_pDSoundBuffer)
    {
        return 0x40000000;
    }

    DWORD status = 0;
    pSoundBuffer->field_0_pDSoundBuffer->GetStatus(&status);

    int fromStatus = 0;
    if (!(status & 1))
    {
        fromStatus = 0x8000000;
    }
    if (!(status & 4))
    {
        fromStatus += 0x8000000;
    }

    int v6 = (a2 - pSoundBuffer->field_10) >> 2; // >> 2 = / 2 ? 
    if (v6 > 2)
    {
        v6 = 2;
    }
    else if (v6 < -2)
    {
        v6 = -2;
    }

    return fromStatus + 2 * (sLastNotePlayTime_BBC33C + (v6 << 8) - pSoundBuffer->field_C); // << 8 = * 256 ?
}

EXPORT signed int CC SND_Buffer_Set_Volume_4EFAD0(int idx, int vol)
{
    AE_BUFFERTYPE* pSoundBuffer = sSoundBuffers_BBBAB8[idx & 511].field_0_pDSoundBuffer;
    if (!pSoundBuffer || (idx ^ sSoundBuffers_BBBAB8[idx & 511].field_4) & ~511)
    {
        return -1;
    }

    unsigned int volConverted = (unsigned int)(vol * k127_dword_575158) >> 7; // Conversion used else where
    if (volConverted > 127)
    {
        volConverted = 127;
    }
    pSoundBuffer->SetVolume(sVolumeTable_BBBD38[120 * volConverted >> 7]);
    return 0;
}

EXPORT int CC SND_Buffer_Set_Frequency_4EFC00(int idx, float freq)
{
    AE_BUFFERTYPE* pDSoundBuffer = sSoundBuffers_BBBAB8[idx & 511].field_0_pDSoundBuffer;
    SoundBuffer* pSoundBuffer = &sSoundBuffers_BBBAB8[idx & 511];

    if (!pDSoundBuffer || (idx ^ pSoundBuffer->field_4) & ~511)
    {
        return -1;
    }

    DWORD freqHz = static_cast<DWORD>(sSoundSamples_BBBF38[pSoundBuffer->field_8]->field_18_sampleRate * freq);
    if (freqHz < DSBFREQUENCY_MIN)
    {
        freqHz = DSBFREQUENCY_MIN;
    }
    else if (freqHz >= DSBFREQUENCY_MAX)
    {
        freqHz = DSBFREQUENCY_MAX;
    }
    pDSoundBuffer->SetFrequency(freqHz);
    return 0;

}

EXPORT signed int CC SND_Stop_Sample_At_Idx_4EFA90(int idx)
{
    AE_BUFFERTYPE* pBuffer = sSoundBuffers_BBBAB8[idx & 511].field_0_pDSoundBuffer;
    if (!pBuffer || (idx ^ sSoundBuffers_BBBAB8[idx & 511].field_4) & ~511) // TODO: Same unknown field_4 conversion
    {
        return -1;
    }
    pBuffer->Stop();
    return 0;
}

EXPORT SoundBuffer* CC SND_Recycle_Sound_Buffer_4EF9C0(int idx, int field8, int field10)
{
    SoundBuffer* pSoundBuffer = &sSoundBuffers_BBBAB8[idx];
    if (pSoundBuffer->field_0_pDSoundBuffer)
    {
        pSoundBuffer->field_0_pDSoundBuffer->Release();
        pSoundBuffer->field_0_pDSoundBuffer = nullptr;
    }

    // TODO: What is this shorthand for ?
    const int oldField4 = pSoundBuffer->field_4 ^ ((unsigned __int16)idx ^ (unsigned __int16)pSoundBuffer->field_4) & 511;
    pSoundBuffer->field_4 = oldField4 & 511 ^ ((oldField4 & ~511) + 512);

    pSoundBuffer->field_8 = field8;
    pSoundBuffer->field_C = sLastNotePlayTime_BBC33C;
    pSoundBuffer->field_10 = field10;
    return pSoundBuffer;
}

EXPORT int CC SND_Get_Buffer_Status_4EE8F0(int idx)
{
    AE_BUFFERTYPE* pBuffer = sSoundBuffers_BBBAB8[idx & 511].field_0_pDSoundBuffer;
    if (!pBuffer || (idx ^ sSoundBuffers_BBBAB8[idx & 511].field_4) & ~511)
    {
        return 0;
    }

    DWORD status = 0;
    pBuffer->GetStatus(&status);
    if (status & 4)
    {
        // Looped
        return 2;
    }
    else
    {
        // Playing
        return status & 1;
    }
}

EXPORT SoundBuffer* CC SND_Get_Sound_Buffer_4EF970(int tableIdx, int field10)
{
    int idx = -1;
    int statusToMatch = 0xC0000000;

    for (int i = 0; i < 32; i++)
    {
        int status = SND_Buffer_Get_Status_4F00F0(i, field10);
        if (status >= statusToMatch)
        {
            idx = i;
            statusToMatch = status;
        }
    }

    if (idx < 0)
    {
        return &sSoundBuffers_BBBAB8[0];
    }
    return SND_Recycle_Sound_Buffer_4EF9C0(idx, tableIdx, field10);
}

class ScopedSeq
{
public:
    EXPORT ScopedSeq* ctor_4CB210(char ambianceId, CameraPos direction)
    {
        SetVTable(this, 0x547838);

        short leftVol = 0;
        short rightVol = 0;

        if (direction == CameraPos::eCamLeft_3)
        {
            leftVol = 1;
            rightVol = 0;
        }
        else
        {
            leftVol = direction != CameraPos::eCamRight_4;
            rightVol = 1;
        }

        field_4_seq_id = -1;
        field_8_channel_mask = 0;

        switch (ambianceId)
        {
        case 0:
            field_4_seq_id = 22;
            break;
        case 1:
            field_4_seq_id = 21;
            break;
        case 2:
            field_4_seq_id = 23;
            break;
        case 3:
            field_4_seq_id = 24;
            break;
        case 4:
            field_4_seq_id = 26;
            break;
        case 5:
            field_4_seq_id = 25;
            break;
        default:
            break;
        }

        if (field_4_seq_id != -1)
        {
            SND_SEQ_Play_4CAB10(field_4_seq_id, 0, 40 * leftVol + 15, 40 * rightVol + 15);
        }

        return this;
    }

    virtual ScopedSeq* VDestructor(signed int flags)
    {
        return vdtor_4CB410(flags);
    }

private:
    EXPORT ScopedSeq* vdtor_4CB410(signed int flags)
    {
        dtor_4CB440();
        if (flags & 1)
        {
            Mem_Free_495540(this);
        }
        return this;
    }

    EXPORT void dtor_4CB440()
    {
        SetVTable(this, 0x547838);

        if (field_4_seq_id >= 0)
        {
            SND_SEQ_Stop_4CAE60(field_4_seq_id);
        }

        if (field_8_channel_mask)
        {
            SND_Stop_Channels_Mask_4CA810(field_8_channel_mask);
        }
    }


private:
    __int16 field_4_seq_id;
    __int16 field_6;
    int field_8_channel_mask;
};
ALIVE_ASSERT_SIZEOF(ScopedSeq, 0xC);

struct Sound_Ambiance
{
    int field_0;
    int field_4;
    ScopedSeq* field_8_pScopedSeq;
};
ALIVE_ASSERT_SIZEOF(Sound_Ambiance, 0xC);

struct Sound_Ambiance_Array
{
    Sound_Ambiance mArray[8];
};

ALIVE_VAR(1, 0xBB3078, Sound_Ambiance_Array, sTopBottomAmbiance_BB3078, {});
ALIVE_VAR(1, 0xBB30D8, Sound_Ambiance_Array, sRightAmbiance_BB30D8, {});
ALIVE_VAR(1, 0xBB3138, Sound_Ambiance_Array, sLeftAmbiance_BB3138, {});

EXPORT void CC SND_Init_Ambiance_4CB480()
{
    for (auto& amb : sTopBottomAmbiance_BB3078.mArray)
    {
        amb.field_8_pScopedSeq = nullptr;
    }

    for (auto& amb : sRightAmbiance_BB30D8.mArray)
    {
        amb.field_8_pScopedSeq = nullptr;
    }

    for (auto& amb : sLeftAmbiance_BB3138.mArray)
    {
        amb.field_8_pScopedSeq = nullptr;
    }
}

EXPORT void CC SND_Reset_Ambiance_4CB4B0()
{
    for (auto& amb : sTopBottomAmbiance_BB3078.mArray)
    {
        if (amb.field_8_pScopedSeq)
        {
            amb.field_8_pScopedSeq->VDestructor(1);
            amb.field_8_pScopedSeq = nullptr;
        }
    }

    for (auto& amb : sRightAmbiance_BB30D8.mArray)
    {
        if (amb.field_8_pScopedSeq)
        {
            amb.field_8_pScopedSeq->VDestructor(1);
            amb.field_8_pScopedSeq = nullptr;
        }
    }

    for (auto& amb : sLeftAmbiance_BB3138.mArray)
    {
        if (amb.field_8_pScopedSeq)
        {
            amb.field_8_pScopedSeq->VDestructor(1);
            amb.field_8_pScopedSeq = nullptr;
        }
    }
}


EXPORT void CC Start_Sounds_for_TLV_4CB530(CameraPos direction, Path_TLV* pTlv)
{
    Sound_Ambiance_Array* pAmbianceTbl = nullptr;
    switch (direction)
    {
    case CameraPos::eCamTop_1:
    case CameraPos::eCamBottom_2:
        pAmbianceTbl = &sTopBottomAmbiance_BB3078;
        break;

    case CameraPos::eCamLeft_3:
        pAmbianceTbl = &sLeftAmbiance_BB3138;
        break;

    case CameraPos::eCamRight_4:
        pAmbianceTbl = &sRightAmbiance_BB30D8;
        break;

    default:
        return;
    }

    switch (pTlv->field_4_type)
    {
    case Slig_15:
    {
        auto pSligTlv = static_cast<Path_Slig*>(pTlv);
        if (pSligTlv->field_12_start_state == Path_Slig::StartState::Paused_1)
        {
            if (!pAmbianceTbl->mArray[1].field_8_pScopedSeq)
            {
                pAmbianceTbl->mArray[1].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(1, direction);
            }
        }
        else if (pSligTlv->field_12_start_state == Path_Slig::StartState::Sleeping_2)
        {
            if (!pAmbianceTbl->mArray[0].field_8_pScopedSeq)
            {
                pAmbianceTbl->mArray[0].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(0, direction);
            }
        }
        break;
    }

    case Slog_16:
    {
        if (static_cast<Path_Slog*>(pTlv)->field_14_asleep)
        {
            if (!pAmbianceTbl->mArray[3].field_8_pScopedSeq)
            {
                pAmbianceTbl->mArray[3].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(3, direction);
            }
        }
        else
        {
            if (!pAmbianceTbl->mArray[2].field_8_pScopedSeq)
            {
                pAmbianceTbl->mArray[2].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(2, direction);
            }
        }
        break;
    }

    case Paramite_26:
        if (!pAmbianceTbl->mArray[5].field_8_pScopedSeq)
        {
            pAmbianceTbl->mArray[5].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(5, direction);
        }
        break;

    case Scrab_41:
        if (!pAmbianceTbl->mArray[6].field_8_pScopedSeq)
        {
            pAmbianceTbl->mArray[6].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(6, direction);
        }
        break;

    case Fleech_83:
    {
        auto pFleechTlv = static_cast<Path_Fleech*>(pTlv);
        if ((pFleechTlv->field_14_asleep || pFleechTlv->field_20_hanging))
        {
            if (!pAmbianceTbl->mArray[4].field_8_pScopedSeq)
            {
                pAmbianceTbl->mArray[4].field_8_pScopedSeq = alive_new<ScopedSeq>()->ctor_4CB210(4, direction);
            }
        }
        break;
    }

    default:
        return;
    }
}

EXPORT void CC Start_Slig_sounds_4CB980(CameraPos direction, char kZero)
{
    Sound_Ambiance_Array* pTable = nullptr;
    switch (direction)
    {
    case CameraPos::eCamTop_1:
    case CameraPos::eCamBottom_2:
        pTable = &sTopBottomAmbiance_BB3078;
        break;
    case CameraPos::eCamLeft_3:
        pTable = &sLeftAmbiance_BB3138;
        break;
    case CameraPos::eCamRight_4:
        pTable = &sRightAmbiance_BB30D8;
        break;
    default:
        return;
    }

    ScopedSeq** ppSeqPtr = &pTable->mArray[kZero].field_8_pScopedSeq;
    if (!*ppSeqPtr)
    {
        *ppSeqPtr = alive_new<ScopedSeq>()->ctor_4CB210(kZero, direction);
    }
}

EXPORT void CC Stop_slig_sounds_4CBA70(CameraPos direction, char kZero)
{
    Sound_Ambiance_Array* pTable = nullptr;
    switch (direction)
    {
    case CameraPos::eCamTop_1:
    case CameraPos::eCamBottom_2:
        pTable = &sTopBottomAmbiance_BB3078;
        break;
    case CameraPos::eCamLeft_3:
        pTable = &sLeftAmbiance_BB3138;
        break;
    case CameraPos::eCamRight_4:
        pTable = &sRightAmbiance_BB30D8;
        break;
    default:
        return;
    }

    if (pTable->mArray[kZero].field_8_pScopedSeq)
    {
        pTable->mArray[kZero].field_8_pScopedSeq->VDestructor(1);
    }
}

EXPORT void CC Start_Sounds_For_Objects_In_Near_Cameras_4CBB60()
{
    SND_Reset_Ambiance_4CB4B0();
    Path::Start_Sounds_For_Objects_In_Camera_4CBAF0(CameraPos::eCamLeft_3, -1, 0);
    Path::Start_Sounds_For_Objects_In_Camera_4CBAF0(CameraPos::eCamRight_4, 1, 0);
    Path::Start_Sounds_For_Objects_In_Camera_4CBAF0(CameraPos::eCamTop_1, 0, -1);
    Path::Start_Sounds_For_Objects_In_Camera_4CBAF0(CameraPos::eCamBottom_2, 0, 1);
}

EXPORT void CC SND_Restart_4CB0E0()
{
    MusicController::EnableMusic_47FE10(TRUE);
    BackgroundMusic::Play_4CB030();
    Start_Sounds_For_Objects_In_Near_Cameras_4CBB60();
}
