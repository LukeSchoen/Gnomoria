#include "Audio.h"
#include <windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <stdio.h>

//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

static char cmd[256];

void Audio_PlayMP3(char* path, char *name, int volume)
{
  sprintf(cmd, "open \"%s\" type mpegvideo alias %s", path, name);
  mciSendStringA(cmd, 0, 0, 0);

  sprintf(cmd, "setaudio %s volume to %d", name, volume);
  mciSendStringA(cmd, 0, 0, 0);

  sprintf(cmd, "play %s", name);
  mciSendStringA(cmd, 0, 0, 0);
}

void Audio_StopMP3(char *name)
{
  sprintf(cmd, "stop %s", name);
  mciSendStringA(cmd, 0, 0, 0);

  sprintf(cmd, "close %s", name);
  mciSendStringA(cmd, 0, 0, 0);
}

void Audio_ChangeVolume(int volume, char *name)
{
  sprintf(cmd, "setaudio %s volume to %d", name, volume);
  mciSendStringA(cmd, 0, 0, 0);
}