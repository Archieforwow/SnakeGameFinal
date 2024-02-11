// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_CameraShake.h"

USG_CameraShake::USG_CameraShake()
{
	OscillationDuration = 1.0f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.2f;

	RotOscillation.Pitch.Amplitude = 2.0f;
	RotOscillation.Pitch.Frequency = 3.0;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Pitch.Waveform = EOscillatorWaveform::PerlinNoise;

	LocOscillation.X.Amplitude = 2.0f;
	LocOscillation.X.Frequency = 3.0;
	LocOscillation.X.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.X.Waveform = EOscillatorWaveform::PerlinNoise;

	LocOscillation.Y.Amplitude = 2.0f;
	LocOscillation.Y.Frequency = 3.0;
	LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;

	LocOscillation.Z.Amplitude = 2.0f;
	LocOscillation.Z.Frequency = 3.0;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;
}
