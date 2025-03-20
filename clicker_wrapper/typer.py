import ctypes
import os
import time

VK_CODES = {
    # Letters
    "A": 0x41,
    "B": 0x42,
    "C": 0x43,
    "D": 0x44,
    "E": 0x45,
    "F": 0x46,
    "G": 0x47,
    "H": 0x48,
    "I": 0x49,
    "J": 0x4A,
    "K": 0x4B,
    "L": 0x4C,
    "M": 0x4D,
    "N": 0x4E,
    "O": 0x4F,
    "P": 0x50,
    "Q": 0x51,
    "R": 0x52,
    "S": 0x53,
    "T": 0x54,
    "U": 0x55,
    "V": 0x56,
    "W": 0x57,
    "X": 0x58,
    "Y": 0x59,
    "Z": 0x5A,
    # Numbers (top row)
    "0": 0x30,
    "1": 0x31,
    "2": 0x32,
    "3": 0x33,
    "4": 0x34,
    "5": 0x35,
    "6": 0x36,
    "7": 0x37,
    "8": 0x38,
    "9": 0x39,
    # Function keys
    "F1": 0x70,
    "F2": 0x71,
    "F3": 0x72,
    "F4": 0x73,
    "F5": 0x74,
    "F6": 0x75,
    "F7": 0x76,
    "F8": 0x77,
    "F9": 0x78,
    "F10": 0x79,
    "F11": 0x7A,
    "F12": 0x7B,
    # Control keys
    "ENTER": 0x0D,
    "ESC": 0x1B,
    "BACKSPACE": 0x08,
    "TAB": 0x09,
    "SPACE": 0x20,
    "SHIFT": 0x10,
    "CTRL": 0x11,
    "ALT": 0x12,
    # Arrows
    "LEFT": 0x25,
    "UP": 0x26,
    "RIGHT": 0x27,
    "DOWN": 0x28,
    # Special keys
    "CAPSLOCK": 0x14,
    "PAGEUP": 0x21,
    "PAGEDOWN": 0x22,
    "END": 0x23,
    "HOME": 0x24,
    "INSERT": 0x2D,
    "DELETE": 0x2E,
    # Punctuation / symbols
    "SEMICOLON": 0xBA,
    "EQUALS": 0xBB,
    "COMMA": 0xBC,
    "MINUS": 0xBD,
    "PERIOD": 0xBE,
    "SLASH": 0xBF,
    "BACKQUOTE": 0xC0,
    "LBRACKET": 0xDB,
    "BACKSLASH": 0xDC,
    "RBRACKET": 0xDD,
    "QUOTE": 0xDE,
}


# Locate the DLL
dll_path = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__), "..", "mouse_engine", "build", "MouseEngine.dll"
    )
)
mouse_engine = ctypes.WinDLL(dll_path)

# Define function prototypes if not already done
mouse_engine.press_key.argtypes = [ctypes.c_ushort, ctypes.c_int]
mouse_engine.press_key_combo.argtypes = [
    ctypes.POINTER(ctypes.c_ushort),
    ctypes.c_int,
    ctypes.c_int,
]


def press_key(key, delay=100):
    """
    Press a single key.

    Args:
        vk_code (int): Virtual key code (example: 0x5A for 'Z').
        delay (int): Delay in ms between key down and key up.
    """
    mouse_engine.press_key(VK_CODES[key], delay)


def press_key_combo(keys, delay_between_keys=50):
    """
    Press multiple keys as a combo.

    Args:
        vk_codes (list of int): List of virtual key codes (example: [0x10, 0x5A] for Shift+Z).
        delay_between_keys (int): Delay between pressing each key.
    """
    vk_codes = [VK_CODES[key] for key in keys]
    array_type = ctypes.c_ushort * len(vk_codes)
    arr = array_type(*vk_codes)
    mouse_engine.press_key_combo(arr, len(vk_codes), delay_between_keys)
