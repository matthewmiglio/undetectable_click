import time

from clicker_wrapper.clicker import click, move_humanlike
from clicker_wrapper.typer import press_key, press_key_combo

# Example usage test
if __name__ == "__main__":
    # humanlike testing
    start_time = time.time()
    move_humanlike(
        0,
        800,
        base_randomness=0.6,
        base_speed=0.1,
        randomness_gradient=0.10,
        speed_gradient=0.10,
        curve_count=2,
        curve_severity=1,
        curve_severity_randomness=0.4,
        curve_time_randomness=0.4,
    )
    print(time.time() - start_time)
