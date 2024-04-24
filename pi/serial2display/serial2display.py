"""

this python file is used to get serial input from the pi and output to a grid of large "pixel". no other processing or control here

"""

# setup
import pygame
import serial
pygame.init()

# "screen" setup
grid_width = 48
grid_height = 32
pixel_size = 20
width, height = grid_width * pixel_size, grid_height * pixel_size
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Survive!")

# colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# build grid
pixels = [[BLACK for _ in range(grid_height)] for _ in range(grid_width)] 

# serial setup
ser = serial.Serial('/dev/ttyACM0', 9600)  # linux
#ser = serial.Serial('COM3', 9600) # windows

# draw pixels
def draw_pixels(screen, pixels, pixel_size):
    for x in range(grid_width):
        for y in range(grid_height):
            pygame.draw.rect(screen, pixels[x][y], (x * pixel_size, y * pixel_size, pixel_size, pixel_size))
    
    pygame.display.flip()

# process command (ex: "PIXEL,3,4,255-0-0"  to set 3,4 to red)
def process_command(command, pixels):
    if len(command) == 4 and command[0] == 'PIXEL':
        x = int(command[1])
        y = int(command[2])
        color = command[3]
        #print("x:", x, "y:", y, "color:", color)
        pixels[x][y] = pygame.Color(*map(int, color.split('-')))
    return pixels

# display loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    # get serial input
    if ser.in_waiting > 0:
        command = ser.readline().decode().strip().split(',')
        pixels = process_command(command, pixels)

    draw_pixels(screen, pixels, pixel_size)

pygame.quit()