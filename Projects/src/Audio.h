#ifndef Audio_h__
#define Audio_h__

void Audio_PlayMP3(char* path, char *name = "SongFoo", int volume = 1000);

void Audio_ChangeVolume(int volume = 1000, char *name = "SongFoo");

void Audio_StopMP3(char *name = "SongFoo");

#endif // Audio_h__
