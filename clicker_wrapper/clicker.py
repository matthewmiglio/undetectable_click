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
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_int,
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
]


mouse_engine.click_mouse.argtypes = [ctypes.c_bool, ctypes.c_int]


def move_humanlike(
    x,
    y,
    base_randomness=0.5,
    base_speed=0.3,
    randomness_gradient=0.1,
    speed_gradient=0.1,
    curve_count=3,
    curve_severity=0.5,
    curve_severity_randomness=0.2,
    curve_time_randomness=0.1,
):
    mouse_engine.move_mouse_humanlike(
        x,
        y,
        base_randomness,
        base_speed,
        randomness_gradient,
        speed_gradient,
        curve_count,
        curve_severity,
        curve_severity_randomness,
        curve_time_randomness,
    )


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
