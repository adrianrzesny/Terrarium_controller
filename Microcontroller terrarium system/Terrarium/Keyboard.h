#include <Keypad.h> //biblioteka od klawiatury

class Keyboard {
  public:
    Keyboard();
    void refresh();
    void readCode();
    const char * getCode();
    const char * getCodeAccept();
    bool getMode();

  private:
    const static byte ROWS = 4; // ROWS
    const static byte COLS = 4; //COLUMNS 
    char code[16];
    char code_accept[16];
    int setMode = false;
    const byte rowPins[ROWS] = {9, 8, 7, 6}; //Pins columns
    const byte colPins[COLS] = {5, 4, 3, 2}; //Pins rows

    const char keys[ROWS][COLS] = { //keyboard mapping
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}
    };
    Keypad keyboard_keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //keyboard initialize


};
