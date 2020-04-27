#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "audio.h"
#include "WKAudio.h"

using namespace std;
using namespace game_framework;

namespace WKAudio_namespace
{
    void LoadSounds(int ID, string path)
    {
        //�d��
        //CAudio::Instance()->Load(0, "sounds\\ding.wav");
        CAudio::Instance()->Load(ID, &path[0]);	// ���J�s��0���n��ding.wav
    }
    //�����n��(ID,�O�_���Ƽ���)
    void PlaySounds(int soundID, bool replay)
    {
        CAudio::Instance()->Play(soundID, replay);
    }
	void StopSounds(int soundID)
	{
		CAudio::Instance()->Stop(soundID);
	}

}
