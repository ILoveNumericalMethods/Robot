import sys
import time
import pygame
import serial


PORT = "COM5"       # <-- замени на свой порт
BAUDRATE = 9600
SEND_INTERVAL = 0.05   # секунды между отправками


def build_command(keys_pressed: set[str]) -> str:
    order = ["w", "a", "s", "d"]
    command = "".join(k for k in order if k in keys_pressed)
    return command if command else "x"


def main() -> None:
    try:
        ser = serial.Serial(PORT, BAUDRATE, timeout=0.1)
    except serial.SerialException as e:
        print(f"Не удалось открыть порт {PORT}: {e}")
        sys.exit(1)

    pygame.init()
    screen = pygame.display.set_mode((500, 220))
    pygame.display.set_caption("Arduino manual control")

    font = pygame.font.SysFont(None, 28)
    clock = pygame.time.Clock()

    pressed: set[str] = set()
    last_sent = None
    last_send_time = 0.0
    running = True
    manual_enabled = False

    print("Управление:")
    print("  M  -> manual mode")
    print("  U  -> auto mode")
    print("  W A S D -> движение")
    print("  ESC -> выход")

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
                    print("Отправлено: m")

                elif event.key == pygame.K_u:
                    ser.write(b"u\n")
                    manual_enabled = False
                    print("Отправлено: u")

                elif event.key == pygame.K_w:
                    pressed.add("w")
                elif event.key == pygame.K_a:
                    pressed.add("a")
                elif event.key == pygame.K_s:
                    pressed.add("s")
                elif event.key == pygame.K_d:
                    pressed.add("d")

            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_w:
                    pressed.discard("w")
                elif event.key == pygame.K_a:
                    pressed.discard("a")
                elif event.key == pygame.K_s:
                    pressed.discard("s")
                elif event.key == pygame.K_d:
                    pressed.discard("d")

        if manual_enabled and now - last_send_time >= SEND_INTERVAL:
            command = build_command(pressed)
            if command != last_sent:
                ser.write((command + "\n").encode("utf-8"))
                print(f"Отправлено: {command}")
                last_sent = command
            last_send_time = now

        screen.fill((245, 245, 245))

        lines = [
            f"PORT: {PORT}",
            f"Mode: {'MANUAL' if manual_enabled else 'AUTO'}",
            f"Pressed: {''.join(sorted(pressed)) if pressed else '(none)'}",
            f"Command: {build_command(pressed) if manual_enabled else '(auto mode)'}",
            "Keys: M=manual, U=auto, WASD=drive, ESC=exit",
        ]

        y = 20
        for line in lines:
            img = font.render(line, True, (20, 20, 20))
            screen.blit(img, (20, y))
            y += 35

        pygame.display.flip()
        clock.tick(60)

    try:
        ser.write(b"x\n")
    except Exception:
        pass

    ser.close()
    pygame.quit()


if __name__ == "__main__":
    main()