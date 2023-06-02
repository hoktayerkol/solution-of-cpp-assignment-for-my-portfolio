import pygame, sys, time, random, math
from pygame.locals import *
import numpy as np
action_dict = {'0': "Up",
               '1': "Down",
               '2': "Right",
               '3': "Left",
               }
# User-defined classes

class Tile:
    # An object in this class represents a single Tile that
    # has an image

    # initialize the class attributes that are common to all
    # tiles.

    borderColor = pygame.Color('black')
    borderWidth = 4  # the pixel width of the tile border

    def __init__(self, x, y, wall, surface, tile_size = (100,100)):
        # Initialize a tile to contain an image
        # - x is the int x coord of the upper left corner
        # - y is the int y coord of the upper left corner
        # - image is the pygame.Surface to display as the
        # exposed image
        # - surface is the window's pygame.Surface object

        self.wall = wall
        self.origin = (x, y)
        self.tile_coord = [x//100, y//100]
        self.surface = surface
        self.tile_size = tile_size

    # def arrow(screen, lcolor, tricolor, start, end, trirad):
    #     pygame.draw.line(screen, lcolor, start, end, 2)
    #     rotation = math.degrees(math.atan2(start[1] - end[1], end[0] - start[0])) + 90
    #     pygame.draw.polygon(screen, tricolor, (
    #     (end[0] + trirad * math.sin(math.radians(rotation)), end[1] + trirad * math.cos(math.radians(rotation))), (
    #     end[0] + trirad * math.sin(math.radians(rotation - 120)),
    #     end[1] + trirad * math.cos(math.radians(rotation - 120))), (
    #     end[0] + trirad * math.sin(math.radians(rotation + 120)),
    #     end[1] + trirad * math.cos(math.radians(rotation + 120)))))



    def draw(self, pos, color = 'white', arrow_direction = 'none'):

        # Draw the tile.
        rectangle = pygame.Rect((self.origin[0],  self.origin[1]), self.tile_size)
        pygame.draw.rect(self.surface, pygame.Color(color), rectangle, 0)

        # if pos == self.tile_coord:
        #     self.surface.blit(Tile.image, self.origin)

        pygame.draw.rect(self.surface, Tile.borderColor, rectangle, Tile.borderWidth)

        if arrow_direction == 'none':
            return

        x = self.origin[0] + self.tile_size[0]/2.0
        y = self.origin[1]+ self.tile_size[1]/2.0
        start = [x, y]
        # draw arrow

        if arrow_direction == 'right':
            end = [x + self.tile_size[0]/4, y]
        elif arrow_direction == 'left':
            end = [x - self.tile_size[0]/4, y]
        elif arrow_direction == 'up':
            end = [x, y - self.tile_size[0]/4]
        elif arrow_direction == 'down':
            end = [x, y + self.tile_size[0]/4]
        else:
            end = start
        trirad = 7
        lcolor = Tile.borderColor
        tricolor = Tile.borderColor

        pygame.draw.line(self.surface, lcolor, start, end, 2)
        rotation = math.degrees(math.atan2(start[1] - end[1], end[0] - start[0])) + 90
        pygame.draw.polygon(self.surface, tricolor, (
            (end[0] + trirad * math.sin(math.radians(rotation)), end[1] + trirad * math.cos(math.radians(rotation))), (
                end[0] + trirad * math.sin(math.radians(rotation - 120)),
                end[1] + trirad * math.cos(math.radians(rotation - 120))), (
                end[0] + trirad * math.sin(math.radians(rotation + 120)),
                end[1] + trirad * math.cos(math.radians(rotation + 120)))))


class Grid_World():
    # An object in this class represents a Grid_World game.
    tile_width = 100
    tile_height = 100
    def __init__(self, surface, board_size = (6,4), wall_coords=[], start_coord=[], goal_coords=[], pitfalls_coords=[], actions={}):
        # Intialize a Grid_World game.
        # - surface is the pygame.Surface of the window

        self.surface = surface
        self.bgColor = pygame.Color('black')
        self.board_size = list(board_size)
        self.pitfalls_coords = pitfalls_coords

        self.actions = {}

        i = 0
        for y in range(board_size[1]):
            for x in range(board_size[0]):
                self.actions[tuple([x,y])]=actions[i]
                i = i + 1





        if not wall_coords:
            self.wall_coords = [[2,i] for i in range(board_size[1]-1)]
        else:
            self.wall_coords = wall_coords

        self.start_coord = list(start_coord)
        self.goal_coords = goal_coords
        self.position = list(start_coord)
        self.reward = 0

        self.calc_wall_coords()
        self.createTiles()

    def calc_wall_coords(self):
        self.board_wall_coords = [[self.board_size[0] - x - 1, y] for x, y in self.wall_coords]

    def find_board_coords(self, pos):
        x = pos[1]
        y = self.board_size[0] - pos[0] -1
        return [x,y]

    def createTiles(self):
        # Create the Tiles
        # - self is the Grid_World game
        self.board = []
        for columnIndex in range(0, self.board_size[0]):
            column = []
            for rowIndex in (range(0, self.board_size[1])):
                x = columnIndex * Grid_World.tile_width
                y = rowIndex * Grid_World.tile_height
                if [rowIndex,columnIndex] in self.board_wall_coords:
                    wall = True
                else:
                    wall = False
                tile = Tile(x, y, wall, self.surface)
                column.append(tile)
            self.board.append(column)

    def draw(self):
        # Draw the tiles.
        # - self is the Grid_World game
        pos = self.find_board_coords(self.position)
        goal = self.find_board_coords(self.goal_coords[0])
        self.surface.fill(self.bgColor)
        for row in self.board:
            for tile in row:
                transformed_coords = tile.tile_coord
                transformed_coords[1] = (self.board_size[1] -1) - transformed_coords[1]  # pygame considers the (0, 0) the upper left corner
                if transformed_coords in self.pitfalls_coords:
                    tile.draw(transformed_coords, 'red')
                elif transformed_coords in self.goal_coords:
                    tile.draw(transformed_coords, 'green')
                else:
                    tile.draw(transformed_coords, 'white', self.actions[tuple(transformed_coords)])
