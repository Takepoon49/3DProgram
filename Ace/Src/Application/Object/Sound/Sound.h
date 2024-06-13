#pragma once

class Sound
{
public:

	Sound();
	~Sound();

	void Init();

	void StopAllBGM();

	void InitBGM(std::string file, float vol, int num);

	std::shared_ptr<KdSoundInstance> GetBGMInst(int num)
	{
		return BGM_Inst[num];
	};

private:

	std::shared_ptr<KdSoundEffect> BGM[BGM_end];
	std::shared_ptr<KdSoundInstance> BGM_Inst[BGM_end];
	
	std::unique_ptr<DirectX::AudioEngine> m_audio;
};