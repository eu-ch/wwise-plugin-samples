#include "CoreMinimal.h"

#include "AkAudioEvent.h"
#include "AkAudioDevice.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"

#include "AK/AkPlatforms.h"
#include "AK/Plugin/MyAudioInputTypes.h"
#include "AK/SoundEngine/Common/AkCommonDefs.h"

namespace MyAudioInputDemo
{
	struct FSineGen
	{
		MyAudioInput_Cookie Cookie;
		double Time;
		double Freq;
		double SampRate;
		AkPlayingID PlayingID;

		FSineGen(double InFreq, double InSampRate)
			: Time(0.), Freq(InFreq), SampRate(InSampRate), PlayingID(AK_INVALID_PLAYING_ID)
		{
			Cookie = MyAudioInput_CreateEmptyCookie();
			Cookie.m_pfnSetFormatFn = &FSineGen::SetFormat;
			Cookie.m_pfnExecuteFn = &FSineGen::Execute;
			Cookie.m_pUserPayload = this;
		}

		static void AKSOUNDENGINE_CALL SetFormat(void* in_pUserPayload, void* io_pAkAudioFormat) 
		{
			check(in_pUserPayload && io_pAkAudioFormat);
			const FSineGen* SineGen = reinterpret_cast<FSineGen*>(in_pUserPayload);
			AkAudioFormat* AkFormat = reinterpret_cast<AkAudioFormat*>(io_pAkAudioFormat);
			AkFormat->channelConfig.SetStandard(AK_SPEAKER_SETUP_MONO);
			AkFormat->uSampleRate = (AkUInt32)SineGen->SampRate;
		}

		static void AKSOUNDENGINE_CALL Execute(void* in_pUserPayload, void* in_pAkAudioBuffer)
		{
			check(in_pUserPayload && in_pAkAudioBuffer);
			FSineGen* SineGen = reinterpret_cast<FSineGen*>(in_pUserPayload);
			AkAudioBuffer* AkBuf = reinterpret_cast<AkAudioBuffer*>(in_pAkAudioBuffer);
			float* Data = AkBuf->GetChannel(0);

			int32 NumIters = AkBuf->MaxFrames() - AkBuf->uValidFrames;
			while (--NumIters >= 0)
			{
				Data[AkBuf->uValidFrames++] = (float)FMath::Sin(UE_DOUBLE_TWO_PI * SineGen->Freq * SineGen->Time);
				SineGen->Time += 1.0 / SineGen->SampRate;
			}

			AkBuf->eState = AkBuf->uValidFrames > 0 ? AK_DataReady : AK_NoDataReady;
		}
	};


	// --------------------------------------------------------------------------------

	static inline TStrongObjectPtr<UAkAudioEvent> AkEvent;
	static inline TArray<FSineGen> SineGenerators;

	static void OnSineGenEventCompleted(enum AkCallbackType in_eType, struct AkEventCallbackInfo* in_pEventInfo, void*, void*)
	{
		if (in_eType != AK_EndOfEvent)
		{
			return;
		}

		int32 NumActiveSines = 0;
		for (auto& SineGen : SineGenerators)
		{
			if (SineGen.PlayingID == in_pEventInfo->playingID)
			{
				SineGen.PlayingID = AK_INVALID_PLAYING_ID;
			}
			else if (SineGen.PlayingID != AK_INVALID_PLAYING_ID)
			{
				NumActiveSines += 1;
			}
		}

		if (NumActiveSines == 0)
		{
			SineGenerators.Reset();
		}
	}

	static void PlayAudioInputDemo()
	{
		if (!AkEvent.IsValid())
		{
			static FSoftObjectPath AkEventPath(TEXT("/Game/WwiseAudio/Play_PluginTest.Play_PluginTest"));
			if (UAkAudioEvent* Asset = Cast<UAkAudioEvent>(AkEventPath.TryLoad()))
			{
				TStrongObjectPtr Ptr(Asset);
				AkEvent = Ptr;
			}
		}

		if (SineGenerators.Num() > 0 || !AkEvent.IsValid())
		{
			return;
		}

		SineGenerators.Emplace(/*Freq=*/ 110., /*SampRate=*/ 8000.);
		SineGenerators.Emplace(/*Freq=*/ 220., /*SampRate=*/ 16000.);
		SineGenerators.Emplace(/*Freq=*/ 1000., /*SampRate=*/ 16000.);
		for (auto& SineGen : SineGenerators)
		{
			SineGen.PlayingID = IWwiseSoundEngineAPI::Get()->PostEvent(
				AkEvent->GetShortID(), DUMMY_GAMEOBJ, AK_EndOfEvent, &OnSineGenEventCompleted, /*in_pCookie=*/ &SineGen.Cookie);
		}

		const bool bIsActuallyPlaying = SineGenerators.ContainsByPredicate([](auto& SineGen) {
			return SineGen.PlayingID != AK_INVALID_PLAYING_ID; 
		});
		if (!bIsActuallyPlaying)
		{
			SineGenerators.Reset();
		}
	}

	static void StopAudioInputDemo()
	{
		if (SineGenerators.Num() == 0)
		{
			return;
		}
		for (auto& SineGen : SineGenerators)
		{
			IWwiseSoundEngineAPI::Get()->StopPlayingID(SineGen.PlayingID);
		}
	}

	FAutoConsoleCommand Play(
		TEXT("PlayAudioInputDemo"),
		TEXT("Plays test event demonstrating MyAudioInput source plugin."),
		FConsoleCommandDelegate::CreateStatic(&PlayAudioInputDemo));

	FAutoConsoleCommand Stop(
		TEXT("StopAudioInputDemo"),
		TEXT("Stops MyAudioInput test events."),
		FConsoleCommandDelegate::CreateStatic(&StopAudioInputDemo));
}