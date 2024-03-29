#ifndef EEPROMVARIABLE_H
#define EEPROMVARIABLE_H

#include "Arduino.h"

using ptr = void*;

struct variablePointer {
    ptr pointer;
    size_t size;
};

/**
 * A class used to handle saving and loading variables to the EEPROM easily.
 * @param projID The ID of the project. A number 0-255, should be unique for all projects intended for the same board.
 *               It's used to see what project does the EEPROM data belong to.
 * @param variablePointers An array of variable pointers, maximum count: 254. Must be terminated with nullptr and size 0 ({nullptr, 0}).
 * @param overwrite Default value: true.
 *                  If true, the library will overwrite EEPROM data to default values if the project ID doesn't match.
 */
class EEpromVariable {
    public:
        EEpromVariable(byte projID, variablePointer* variablePointers, bool overwrite = true);
        ~EEpromVariable();
        byte getEEpromProjID();
        bool save();
        bool load();
    private:
        byte _projID; // The project ID.
        variablePointer* _variablePointers; // The array of variable pointers.
        size_t _variablesCount; // The count of variables.
        int a;
        int b;
};

#endif //EEPROMVARIABLE_H
