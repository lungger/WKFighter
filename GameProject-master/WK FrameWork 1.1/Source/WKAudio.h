#pragma once
using namespace std;
namespace WKAudio_namespace
{
    // �w�q�U�ح��Ī��s��
    //�b�o�̥[�J�A�n�ϥΪ��n���W�١A�ƭȤ��୫��
    struct Audio_ID
    {
        const int Ding = 0;
    };
    void LoadSounds(int , string);
    void PlaySounds(int, bool);
	void StopSounds(int soundID);
}
