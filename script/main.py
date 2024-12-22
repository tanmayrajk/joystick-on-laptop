import serial
from collections import namedtuple
from pynput.mouse import Controller, Button

Point = namedtuple('Point', ['x', 'y'])

ser = serial.Serial(
    port='COM10',
    baudrate=115200,
    timeout=1
)

isStarted = False

mouse = Controller()
SPEED = 1

if ser.is_open:
    print(f"Serial port {ser.name} is open.")

while True:
    line = ser.readline();

    if line and line.decode().strip() == "start":
        isStarted = True

    if line and line.decode().strip() == "click":
        mouse.click(Button.left)
        
    if isStarted and line and "," in line.decode():
        vals = line.decode().strip().split(",")
        point = Point(x=float(vals[0]),y=float(vals[1]))
        mouse.move(point.x * SPEED, point.y * SPEED)
            