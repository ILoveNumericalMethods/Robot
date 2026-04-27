import time

import pygame
import serial


PORT = "COM12"
BAUD = 115200

SEND_INTERVAL = 0.03


def build_command(keys):
    command = ""

    if keys[pygame.K_w]:
        command += "w"
    if keys[pygame.K_a]:
        command += "a"
    if keys[pygame.K_s]:
        command += "s"
    if keys[pygame.K_d]:
        command += "d"

    return command


def send_line(ser, line):
    ser.write((line + "\n").encode("utf-8"))


def read_arduino_logs(ser):
    while ser.in_waiting > 0:
        line = ser.readline().decode("utf-8", errors="replace").strip()
        if line:
            print(line)


def main():
    ser = serial.Serial(PORT, BAUD, timeout=0.001)

    # Arduino Nano usually resets after opening the serial port.
    time.sleep(2.0)

    pygame.init()
    screen = pygame.display.set_mode((500, 250))
    pygame.display.set_caption("Robot manual control")

    print("Controls:")
    print("M       - enable manual mode")
    print("U       - return to automatic/waiting mode")
    print("W/A/S/D - hold keys to move")
    print("SPACE   - stop")
    print("ESC     - quit")
    print("-------------------------------------")

    running = True
    manual_enabled = False

    last_send_time = 0.0
    last_command = ""

    try:
        while running:
            now = time.time()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        running = False

                    elif event.key == pygame.K_m:
                        send_line(ser, "m")
                        manual_enabled = True
                        last_send_time = now
                        last_command = ""
                        print("sent: m")

                    elif event.key == pygame.K_u:
                        send_line(ser, "u")
                        manual_enabled = False
                        last_send_time = now
                        last_command = ""
                        print("sent: u")

                    elif event.key == pygame.K_SPACE:
                        send_line(ser, "x")
                        last_send_time = now
                        last_command = ""
                        print("sent: x")

            if manual_enabled:
                keys = pygame.key.get_pressed()
                command = build_command(keys)

                if command != "":
                    # While at least one WASD key is held,
                    # repeatedly send the current keyboard state.
                    if now - last_send_time >= SEND_INTERVAL:
                        send_line(ser, command)
                        last_send_time = now

                        if command != last_command:
                            print("sent:", command)
                            last_command = command

                else:
                    # If the robot was moving and now all WASD keys are released,
                    # send stop command only once.
                    if last_command != "":
                        send_line(ser, "x")
                        last_send_time = now
                        last_command = ""
                        print("sent: x")

            read_arduino_logs(ser)

            screen.fill((30, 30, 30))
            pygame.display.flip()

            time.sleep(0.002)

    finally:
        try:
            send_line(ser, "x")
            time.sleep(0.05)
            ser.close()
        finally:
            pygame.quit()


if __name__ == "__main__":
    main()