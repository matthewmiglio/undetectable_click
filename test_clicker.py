import time

from clicker_wrapper.clicker import click, move_humanlike

# Example: Move mouse and click
move_humanlike(800, 400, randomness=0.1, speed=4)
time.sleep(0.5)
click(left=True, delay=100)
