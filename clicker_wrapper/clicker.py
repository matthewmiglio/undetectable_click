import ctypes
import os

# Locate the compiled DLL
dll_path = os.path.join(
    os.path.dirname(__file__), "..", "mouse_engine", "build", "MouseEngine.dll"
)
mouse_engine = ctypes.WinDLL(dll_path)

# Define function prototypes
mouse_engine.move_mouse_humanlike.argtypes = [
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_double,
    ctypes.c_double,
]
mouse_engine.click_mouse.argtypes = [ctypes.c_bool, ctypes.c_int]


def move_humanlike(x, y, randomness=0.5, speed=0.3):
    """
    Move the mouse cursor to a target (x, y) position with human-like randomness and smooth motion.

    Args:
        x (int): The target X-coordinate on the screen.
        y (int): The target Y-coordinate on the screen.
        randomness (float, optional):
            Controls jitter and imperfect movement paths.
            Higher values introduce more randomness (typical range: 0.1 to 1.0).
            Default is 0.5.
        speed (float, optional):
            Controls movement speed.
            Lower values move slower (e.g., 0.2 = slow, 1.0 = fast).
            Default is 0.3.

    Example:
        move_humanlike(800, 400, randomness=0.6, speed=0.4)
    """
    mouse_engine.move_mouse_humanlike(x, y, randomness, speed)


def click(left=True, delay=50):
    """
    Simulate a mouse click.

    Args:
        left (bool, optional):
            If True, performs a left-click.
            If False, performs a right-click.
            Default is True.
        delay (int, optional):
            Time in milliseconds between mouse down and mouse up events (simulates press duration).
            Default is 50 milliseconds.

    Example:
        click(left=True, delay=100)  # Left-click with a longer press
        click(left=False)            # Right-click with default press duration
    """
    mouse_engine.click_mouse(left, delay)
