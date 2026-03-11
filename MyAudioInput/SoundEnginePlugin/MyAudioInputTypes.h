#pragma once

#include "AK/AkPlatforms.h"

#if !defined(MYAUDIOINPUT_MAGIC_NUMBER)
#define MYAUDIOINPUT_MAGIC_NUMBER (0xC0FFEE00)
#endif

#if !defined(AK_CPU_X86_64)
#error "This header assumes 64-bit architecture"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (AKSOUNDENGINE_CALL *MyAudioInput_SetFormatFnPtr)(void* in_pUserPayload, void* io_pAkAudioFormat);
typedef void (AKSOUNDENGINE_CALL *MyAudioInput_ExecuteFnPtr)(void* in_pUserPayload, void* in_pAkAudioBuffer);

typedef struct
{
	AkUInt64 m_uMagicNumber;
	MyAudioInput_SetFormatFnPtr m_pfnSetFormatFn;
	MyAudioInput_ExecuteFnPtr m_pfnExecuteFn;
	void* m_pUserPayload;
} MyAudioInput_Cookie;

static inline MyAudioInput_Cookie MyAudioInput_CreateEmptyCookie()
{
	MyAudioInput_Cookie Cookie;
	Cookie.m_uMagicNumber = MYAUDIOINPUT_MAGIC_NUMBER;
	Cookie.m_pfnSetFormatFn = NULL;
	Cookie.m_pfnExecuteFn = NULL;
	Cookie.m_pUserPayload = NULL;
	return Cookie;
}

#ifdef __cplusplus
}
#endif

