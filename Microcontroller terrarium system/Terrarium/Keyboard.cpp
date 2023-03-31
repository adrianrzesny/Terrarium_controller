#include "Keyboard.h"

Keyboard::Keyboard()
{
  refresh();
}

void Keyboard::refresh()
{
  strcpy(code_accept, "");
}

void Keyboard::readCode()
{
  char key = keyboard_keypad.getKey();

  if (key) {
    if (key == '*')
    {
      setMode = !setMode;
      strcpy(code, "");
      strcpy(code_accept, "*");
    }
    else if (key != '#')
    {
      char str[2] = {key , '\0'};
      strcat(code, str);
    }
    else if (key == '#')
    {
      char str[2] = {key , '\0'};
      strcat(code, str);
      strcpy(code_accept, code);

      strcpy(code, "");
    }

  }
  return code;
}


const char * Keyboard::getCode()
{
  return code;
}

const char * Keyboard::getCodeAccept()
{
  return code_accept;
}


bool Keyboard::getMode()
{
  return setMode;
}
