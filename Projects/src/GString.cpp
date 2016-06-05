#include "GString.h"

int strlen(char* str)
{
  int i = -1;
  while (str[++i] != 0);
  return i;
}

char* strcpy(char* str)
{
  int len = strlen(str);
  char* ret = new char[len + 1];
  for (int i = 0; i <= len; i++)
    ret[i] = str[i];
  return ret;
}
