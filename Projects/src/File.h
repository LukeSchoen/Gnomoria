#ifndef File_h__
#define File_h__

void WriteFile(char* filePath, void* fileData, int fileSize);

void ReadFile(char* filePath, void* fileBuffer, int fileSize);

#endif // File_h__