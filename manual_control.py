import serial
import time
import pygame

PORT = "COM12"
BAUD = 115200

SEND_INTERVAL = 0.02  # 20 ms = 50 commands/sec


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

    if command == "":
        command = "x"

    return command


def main():
    ser = serial.Serial(PORT, BAUD, timeout=0.001)
    time.sleep(2)

    pygame.init()
    screen = pygame.display.set_mode((400, 200))
    pygame.display.set_caption("Robot manual control")

    print("M - manual mode")
    print("U - auto mode")
    print("W/A/S/D - move")
    print("SPACE - stop")
    print("ESC - quit")
    print("Logs from Arduino will appear below:")
    print("-------------------------------------")

    running = True
    manual_enabled = False
    last_send_time = 0
    last_command = None

    while running:
        now = time.time()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

                elif event.key == pygame.K_m:
                    ser.write(b"m\n")
                    manual_enabled = True
                    print("sent: m")

                elif event.key == pygame.K_u:
                    ser.write(b"u\n")
                    manual_enabled = False
                    print("sent: u")

                elif event.key == pygame.K_SPACE:
                    ser.write(b"x\n")
                    last_command = "x"
                    print("sent: x")

        keys = pygame.key.get_pressed()

        if manual_enabled and now - last_send_time >= SEND_INTERVAL:
            command = build_command(keys)
            ser.write((command + "\n").encode("utf-8"))

            if command != last_command:
                print("sent:", command)
                last_command = command

            last_send_time = now

        while ser.in_waiting > 0:
            line = ser.readline().decode("utf-8", errors="replace").strip()
            if line:
                print(line)

        pygame.display.flip()
        time.sleep(0.002)

    ser.write(b"x\n")
    ser.close()
    pygame.quit()


if __name__ == "__main__":
    main()