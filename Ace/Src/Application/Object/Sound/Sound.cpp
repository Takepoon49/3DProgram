#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::Init()
{
	for (int i = 0; i < BGM_end; i++)
	{
		switch (i)
		{
		case BGM_test:
			InitBGM("test.wav", 0.30f, i);
			break;

		default:
			break;
		}
	}
}

void Sound::StopAllBGM()
{
	for (int i = 0; i < BGM_end; i++)
	{
		BGM_Inst[i]->Stop();
	}
}

void Sound::InitBGM(std::string file, float vol, int num)
{
	// BGMの読み込みと初期化
	BGM[num] = std::make_shared<KdSoundEffect>();
	BGM[num]->CreateInstance(DirectX::SoundEffectInstance_Default);

	BGM[num]->Load(file, m_audio);

	//BGM_Inst[num] = BGM[num]->CreateInstance(DirectX::SoundEffectInstance_Default);s
	//BGM_Inst[num] = ;

	BGM_Inst[num]->SetVolume(vol);
}
