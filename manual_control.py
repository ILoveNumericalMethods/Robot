import os
import time

import pygame
import serial


PORT = "COM12"
BAUD = 115200

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_FILE = os.path.join(SCRIPT_DIR, "log.csv")

FPS = 100
AUTO_SEND_MANUAL_MODE = True


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


def send_command(ser, command):
    try:
        ser.reset_output_buffer()
    except serial.SerialException:
        pass

    ser.write((command + "\n").encode("utf-8"))


def read_logs_to_file(ser, log_file):
    n = ser.in_waiting

    if n <= 0:
        return 0

    data = ser.read(n)
    text = data.decode("utf-8", errors="replace")

    # Пишем в файл
    log_file.write(text)
    log_file.flush()

    # Одновременно выводим в терминал
    print(text, end="")

    return n


def main():
    print("Log file:", LOG_FILE)

    with open(LOG_FILE, "w", encoding="utf-8", newline="") as log_file:
        ser = serial.Serial(PORT, BAUD, timeout=0)

        # Arduino Nano обычно перезагружается при открытии Serial.
        time.sleep(1.0)

        pygame.init()
        screen = pygame.display.set_mode((500, 250))
        pygame.display.set_caption("Robot manual control")

        clock = pygame.time.Clock()

        print("Controls:")
        print("W/A/S/D - move")
        print("SPACE - stop")
        print("M - send manual mode command")
        print("U - send waiting/auto mode command")
        print("ESC - quit")
        print("--------------------------------")

        last_sent_command = None

        if AUTO_SEND_MANUAL_MODE:
            send_command(ser, "m")
            last_sent_command = "m"
            print("sent: m")

        running = True

        try:
            while running:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        running = False

                    elif event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_ESCAPE:
                            running = False

                        elif event.key == pygame.K_m:
                            send_command(ser, "m")
                            last_sent_command = "m"
                            print("sent: m")

                        elif event.key == pygame.K_u:
                            send_command(ser, "u")
                            last_sent_command = "u"
                            print("sent: u")

                        elif event.key == pygame.K_SPACE:
                            send_command(ser, "x")
                            last_sent_command = "x"
                            print("sent: x")

                # 1. Считываем текущее состояние клавиатуры.
                keys = pygame.key.get_pressed()
                command = build_command(keys)

                # 2. Отправляем только если команда изменилась.
                if command != last_sent_command:
                    send_command(ser, command)
                    last_sent_command = command
                    print("sent:", command)

                # 3. Забираем все логи из Serial, пишем в файл и печатаем в терминал.
                read_logs_to_file(ser, log_file)

                screen.fill((30, 30, 30))
                pygame.display.flip()

                clock.tick(FPS)

        finally:
            try:
                send_command(ser, "x")
                time.sleep(0.05)
            except Exception:
                pass

            log_file.flush()
            ser.close()
            pygame.quit()


if __name__ == "__main__":
    main()