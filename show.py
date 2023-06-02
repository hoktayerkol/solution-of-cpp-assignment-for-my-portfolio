import pygame, sys, time, random
from pygame.locals import *
from grid_world import Grid_World
import csv

actions = []


with open('actions.txt', 'r') as myfile:
    data = myfile.readlines()
    for action in data:
        actions.append(action.replace(" ", "").replace("\n", ""))


x_lims = [0, 5]
y_lims = [0, 3]

# walls_states = []
goal_states = [[2, 2]]
pitfalls_states = [[0, 3], [1, 1], [3, 2], [4, 2]]


# Set window size and title, and frame delay
surfaceSize = (100*(x_lims[1]+1), 100*(y_lims[1]+1))
windowTitle = 'Grid_World'
pauseTime = 1  # smaller is faster game

# Create the window
surface = pygame.display.set_mode(surfaceSize, 0, 0)
pygame.display.set_caption(windowTitle)

# create and initialize objects
board = Grid_World(surface, (6, 4), [], [0, 0], goal_states, pitfalls_states, actions)
# Draw objects
board.draw()



# Loop forever
while True:
    # Handle events
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
            # Handle additional events

    # Refresh the display
    pygame.display.update()

    # Set the frame speed by pausing between frames
    time.sleep(pauseTime)
#




