import time

from clicker_wrapper.clicker import click, move_humanlike
from clicker_wrapper.typer import press_key, press_key_combo


# Example usage test
if __name__ == "__main__":
    time.sleep(2)
    print("Typing single key Z in 2 seconds...")
    press_key("Z", delay=150)  # Press 'Z'

    time.sleep(2)
    print("Typing Shift + Z combo in 2 seconds...")
    press_key_combo(["SHIFT", "Z"], delay_between_keys=100)  # Shift + Z

    # Example: Move mouse and click
    move_humanlike(800, 400, randomness=0.1, speed=4)
    time.sleep(0.5)
    click(left=True, delay=100)
