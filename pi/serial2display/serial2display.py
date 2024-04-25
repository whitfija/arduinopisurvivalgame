"""

this python file is used to get serial input from the pi and output to a grid of large "pixel". no other processing or control here

"""

# setup
import pygame
import serial
import threading
import sys

draw_thread_running = True

def game_setup():
    pygame.init()

    # "screen" setup
    window_width = 480
    window_height = 320
    pixel_size = 5
    grid_width = window_width // pixel_size
    grid_height = window_height // pixel_size
    width, height = grid_width * pixel_size, grid_height * pixel_size
    print(f"Window width: {grid_width} blocks")
    print(f"Window height: {grid_height} blocks")
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Survive!")

    # colors
    BLACK = (0, 0, 0)
    WHITE = (255, 255, 255)

    # build grid
    pixels = [[BLACK for _ in range(grid_height)] for _ in range(grid_width)] 

    # serial setup
    #ser = serial.Serial('/dev/ttyACM0', 9600)  # linux
    ser = serial.Serial('COM3', 9600) # windows

    return screen, pixels, pixel_size, ser, grid_width, grid_height

# draw pixels
def draw_pixels(screen, pixels, pixel_size, grid_width, grid_height):
    global draw_thread_running
    while draw_thread_running:
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
        try:
            pixels[x][y] = pygame.Color(*map(int, color.split('-')))
        except Exception as e:
            print(e)
    return pixels

def main():
    screen, pixels, pixel_size, ser, grid_width, grid_height = game_setup()

    # Start draw thread
    draw_thread = threading.Thread(target=draw_pixels, args=(screen, pixels, pixel_size, grid_width, grid_height))
    draw_thread.start()

    # display loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        # get serial input
        if ser.in_waiting > 0:
            command = ser.readline().decode('windows-1252').strip().split(',')
            pixels = process_command(command, pixels)

    global draw_thread_running
    draw_thread_running = False
    draw_thread.join()
    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()