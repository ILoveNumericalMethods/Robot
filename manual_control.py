import os
import time

import pygame
import serial


PORT = "COM12"
BAUD = 115200

LOG_FILE = "robot_log.csv"

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
    # Удаляем то, что еще не успело уйти из буфера компьютера.
    # Это не очищает буфер Arduino, но уменьшает накопление команд со стороны Python.
    try:
        ser.reset_output_buffer()
    except serial.SerialException:
        pass

    ser.write((command + "\n").encode("utf-8"))


def read_logs_to_file(ser, file):
    n = ser.in_waiting

    if n > 0:
        data = ser.read(n)
        file.write(data)
        return n

    return 0


def main():
    print("Log file:", os.path.abspath(LOG_FILE))

    with open(LOG_FILE, "wb") as log_file:
        ser = serial.Serial(PORT, BAUD, timeout=0)

        # Arduino Nano обычно перезагружается при открытии Serial.
        time.sleep(2.0)

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
        last_flush_time = time.time()

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
                # Поэтому команды не накапливаются одинаковыми копиями.
                if command != last_sent_command:
                    send_command(ser, command)
                    last_sent_command = command
                    print("sent:", command)

                # 3. Быстро забираем все логи из Serial и пишем в CSV.
                read_logs_to_file(ser, log_file)

                # 4. Периодически сбрасываем файл на диск.
                now = time.time()
                if now - last_flush_time >= 0.2:
                    log_file.flush()
                    last_flush_time = now

                screen.fill((30, 30, 30))
                pygame.display.flip()

                clock.tick(FPS)

        finally:
            send_command(ser, "x")
            time.sleep(0.05)

            log_file.flush()
            ser.close()
            pygame.quit()


if __name__ == "__main__":
    main()