#include "key_event.hpp"

String virt_key_to_string(VirtKey key) {
    switch (key) {
        case VirtKeyUnknown: return "Unknown";
        case VirtKeySpace: return "Space";
        case VirtKeyApostrophe: return "'";
        case VirtKeyComma: return ",";
        case VirtKeyMinus: return "-";
        case VirtKeyPeriod: return ".";
        case VirtKeySlash: return "/";
        case VirtKey0: return "0";
        case VirtKey1: return "1";
        case VirtKey2: return "2";
        case VirtKey3: return "3";
        case VirtKey4: return "4";
        case VirtKey5: return "5";
        case VirtKey6: return "6";
        case VirtKey7: return "7";
        case VirtKey8: return "8";
        case VirtKey9: return "9";
        case VirtKeySemicolon: return ";";
        case VirtKeyEqual: return "=";
        case VirtKeyA: return "A";
        case VirtKeyB: return "B";
        case VirtKeyC: return "C";
        case VirtKeyD: return "D";
        case VirtKeyE: return "E";
        case VirtKeyF: return "F";
        case VirtKeyG: return "G";
        case VirtKeyH: return "H";
        case VirtKeyI: return "I";
        case VirtKeyJ: return "J";
        case VirtKeyK: return "K";
        case VirtKeyL: return "L";
        case VirtKeyM: return "M";
        case VirtKeyN: return "N";
        case VirtKeyO: return "O";
        case VirtKeyP: return "P";
        case VirtKeyQ: return "Q";
        case VirtKeyR: return "R";
        case VirtKeyS: return "S";
        case VirtKeyT: return "T";
        case VirtKeyU: return "U";
        case VirtKeyV: return "V";
        case VirtKeyW: return "W";
        case VirtKeyX: return "X";
        case VirtKeyY: return "Y";
        case VirtKeyZ: return "Z";
        case VirtKeyLeftBracket: return "[";
        case VirtKeyBackslash: return "\\";
        case VirtKeyRightBracket: return "]";
        case VirtKeyGraveAccent: return "`";
        case VirtKeyWorld1: return "World 1";
        case VirtKeyWorld2: return "World 2";
        case VirtKeyEscape: return "Escape";
        case VirtKeyEnter: return "Enter";
        case VirtKeyTab: return "Tab";
        case VirtKeyBackspace: return "Backspace";
        case VirtKeyInsert: return "Insert";
        case VirtKeyDelete: return "Delete";
        case VirtKeyRight: return "Right";
        case VirtKeyLeft: return "Left";
        case VirtKeyDown: return "Down";
        case VirtKeyUp: return "Up";
        case VirtKeyPageUp: return "Page Up";
        case VirtKeyPageDown: return "Page Down";
        case VirtKeyHome: return "Home";
        case VirtKeyEnd: return "End";
        case VirtKeyCapsLock: return "Caps Lock";
        case VirtKeyScrollLock: return "Scroll Lock";
        case VirtKeyNumLock: return "Num Lock";
        case VirtKeyPrintScreen: return "Print Screen";
        case VirtKeyPause: return "Pause";
        case VirtKeyF1: return "F1";
        case VirtKeyF2: return "F2";
        case VirtKeyF3: return "F3";
        case VirtKeyF4: return "F4";
        case VirtKeyF5: return "F5";
        case VirtKeyF6: return "F6";
        case VirtKeyF7: return "F7";
        case VirtKeyF8: return "F8";
        case VirtKeyF9: return "F9";
        case VirtKeyF10: return "F10";
        case VirtKeyF11: return "F11";
        case VirtKeyF12: return "F12";
        case VirtKeyF13: return "F13";
        case VirtKeyF14: return "F14";
        case VirtKeyF15: return "F15";
        case VirtKeyF16: return "F16";
        case VirtKeyF17: return "F17";
        case VirtKeyF18: return "F18";
        case VirtKeyF19: return "F19";
        case VirtKeyF20: return "F20";
        case VirtKeyF21: return "F21";
        case VirtKeyF22: return "F22";
        case VirtKeyF23: return "F23";
        case VirtKeyF24: return "F24";
        case VirtKeyF25: return "F25";
        case VirtKeyKp0: return "Numpad 0";
        case VirtKeyKp1: return "Numpad 1";
        case VirtKeyKp2: return "Numpad 2";
        case VirtKeyKp3: return "Numpad 3";
        case VirtKeyKp4: return "Numpad 4";
        case VirtKeyKp5: return "Numpad 5";
        case VirtKeyKp6: return "Numpad 6";
        case VirtKeyKp7: return "Numpad 7";
        case VirtKeyKp8: return "Numpad 8";
        case VirtKeyKp9: return "Numpad 9";
        case VirtKeyKpDecimal: return "Numpad .";
        case VirtKeyKpDivide: return "Numpad /";
        case VirtKeyKpMultiply: return "Numpad *";
        case VirtKeyKpSubtract: return "Numpad -";
        case VirtKeyKpAdd: return "Numpad +";
        case VirtKeyKpEnter: return "Numpad Enter";
        case VirtKeyKpEqual: return "Numpad =";
        case VirtKeyLeftShift: return "Left Shift";
        case VirtKeyLeftControl: return "Left Control";
        case VirtKeyLeftAlt: return "Left Alt";
        case VirtKeyLeftSuper: return "Left Super";
        case VirtKeyRightShift: return "Right Shift";
        case VirtKeyRightControl: return "Right Control";
        case VirtKeyRightAlt: return "Right Alt";
        case VirtKeyRightSuper: return "Right Super";
        case VirtKeyMenu: return "Menu";
    }
    return "Unknown";
}

bool null_key_sequence(const KeySequence &seq) {
    return seq.modifiers == -1;
}

String key_sequence_to_string(const KeySequence &seq) {
    String result;
    if (key_mod_ctrl(seq.modifiers))
        result.append("Ctrl+");
    if (key_mod_shift(seq.modifiers))
        result.append("Shift+");
    if (key_mod_alt(seq.modifiers))
        result.append("Alt+");
    if (key_mod_super(seq.modifiers))
        result.append("Super+");
    result.append(virt_key_to_string(seq.key));
    return result;
}

bool key_sequence_match(const KeySequence &seq, const KeyEvent *event) {
    return (seq.modifiers == event->modifiers) && (seq.key == event->virt_key);
}
