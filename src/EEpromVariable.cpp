#include "EEpromVariable.h"
#include <EEPROM.h>

/**
 * Constructs an instance of the EEpromVariable class.
 */
EEpromVariable::EEpromVariable(byte projID, variablePointer* variablePointers, bool overwrite) : _projID(projID) {
    for (byte i = 0; i < 255; i++) {
        if (variablePointers[i].pointer == nullptr) {
            _variablesCount = i;
            break;
        }
    }
    _variablePointers = new variablePointer[_variablesCount];
    _variablePointers = variablePointers;

    if(overwrite && EEPROM.read(0) != _projID) {
        EEPROM.update(0, _projID);
        save();
    }
};

/**
 * Destructor for the EEpromVariable class.
 */
EEpromVariable::~EEpromVariable() {
    delete[] _variablePointers;
};

/**
 * Retrieves the EEPROM project ID.
 *
 * @return The project ID stored in the EEPROM.
 */
byte EEpromVariable::getEEpromProjID() {
    return EEPROM.read(0);
}

/**
 * Saves the values of the EEpromVariable to EEPROM.
 *
 * @return true if the values are successfully saved, false otherwise (eg. the project ID doesn't match).
 */
bool EEpromVariable::save() {
    if (EEPROM.read(0) == _projID) {
        int adress = 1;
        for (size_t i = 0; i < _variablesCount; i++) {
            for (size_t j = 0; j < _variablePointers[i].size; j++) {
                uint8_t* ptr = static_cast<byte*>(_variablePointers[i].pointer)+j;
                EEPROM.update(adress, *ptr);
                adress++;
            }
            // EEPROM.put(adress, _settingPointers[i].pointer);
            // adress += _settingPointers[i].size;
            
        }
        return true;
    }
    return false;
};

/**
 * Loads the values from EEPROM and returns a boolean indicating whether the loading was successful or not.
 *
 * @return true if the loading was successful, false otherwise (eg. the project ID doesn't match).
 */
bool EEpromVariable::load() {
    if (EEPROM.read(0) == _projID) {
        int adress = 1;
        for (size_t i = 0; i < _variablesCount; i++) {
            for (size_t j = 0; j < _variablePointers[i].size; j++) {
                byte* ptr = static_cast<byte*>(_variablePointers[i].pointer)+j;
                *ptr = (byte)EEPROM.read(adress);
                adress++;
            }
            // EEPROM.get(adress, _settingPointers[i].pointer);
            // adress += _settingPointers[i].size;
        }
        return true;
    }
    return false;
};
