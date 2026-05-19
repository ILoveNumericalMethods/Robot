
#include "robot.h"

Robot robot;

void setup() {
    robot.begin();
}

void loop() {
    robot.update();
}

/*
void loop() {
}

#include <NewPing.h>

// Количество датчиков
#define SONAR_NUM 4

// Пины для каждого датчика (trig, echo)
// При необходимости измените номера под вашу схему подключения
const uint8_t trigPins[SONAR_NUM] = {13, A1, A3, 11};
const uint8_t echoPins[SONAR_NUM] = {A0, A2, A4, 10};

// Максимальное измеряемое расстояние (в см) – 400 см для HC-SR04
#define MAX_DISTANCE 400

// Создаём массив объектов NewPing
NewPing sonar[SONAR_NUM] = {
  NewPing(trigPins[0], echoPins[0], MAX_DISTANCE),
  NewPing(trigPins[1], echoPins[1], MAX_DISTANCE),
  NewPing(trigPins[2], echoPins[2], MAX_DISTANCE),
  NewPing(trigPins[3], echoPins[3], MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200);          // инициализация последовательного порта
  Serial.println("Start scanning 4 ultrasonic sensors...");
  delay(200);                   // небольшая пауза перед началом измерений
}

void loop() {
    unsigned int startTime = millis();         // запоминаем время начала
    for (uint8_t i = 0; i < SONAR_NUM; i++) {

        unsigned int echoTime_us = sonar[i].ping_median(2);   // медианное время в мкс
        unsigned int distance = sonar[i].convert_cm(echoTime_us); // переводим в см

        //unsigned int distance = sonar[i].ping_cm();

        
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(": distance = ");
        Serial.print(distance);
        Serial.print("\n");
        delay(10);
    }

    unsigned int duration = millis() - startTime;
    Serial.print(", measurement time = ");
    Serial.print(duration);
    Serial.println(" ms");

  delay(50);   // пауза 50 мс перед следующим циклом опроса
}*/