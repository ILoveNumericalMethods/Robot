#include "sensors.h"


SensorData::SensorData()
  : front(INVALID_DISTANCE),
    front_left(INVALID_DISTANCE),
    front_right(INVALID_DISTANCE),
    rear_right(INVALID_DISTANCE),
    prev_front(INVALID_DISTANCE),
    prev_front_left(INVALID_DISTANCE),
    prev_front_right(INVALID_DISTANCE),
prev_rear_right(INVALID_DISTANCE) {}


void Sensors::begin() {
  Wire.begin();
  Wire.setClock(100000);

  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    pinMode(XSHUTS[i], OUTPUT);
    digitalWrite(XSHUTS[i], LOW);
  }

  delay(20);

  VL53L0X* sensors[NUMBER_OF_SENSORS] = {
    &front_sensor,
    &front_left_sensor,
    &front_right_sensor,
    &rear_right_sensor
  };


  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    pinMode(XSHUTS[i], INPUT);

    delay(50);
 
    //Serial.print("Started");
    //Serial.print(i);
    //Serial.print('\n');

    sensors[i]->setTimeout(MAX_TIME_ON_SENSOR);
    
    //Serial.print("timeout succsess");
    //Serial.print(i);
    //Serial.print('\n');

    if (!sensors[i]->init()) {
      Serial.print("VL53L0X init error, sensor ");
      Serial.println(i);

      while (true) {
      }
    }
    Serial.print("adress started");
    Serial.print(i);
    Serial.print('\n');

    sensors[i]->setAddress(SENSOR_ADDRESSES[i]);

    //Serial.print("adress succsess");
    //Serial.print(i);
    //Serial.print('\n');



    if (!sensors[i]->setMeasurementTimingBudget(33000)) {
      Serial.print("VL53L0X timing budget error, sensor ");
      Serial.println(i);

      while (true) {
      }
    }
    //Serial.print("Succsess");
    //Serial.print(i);
    //Serial.print('\n');
  }
}

int Sensors::read_sensor_cm(VL53L0X& sensor) {
  uint16_t distance_mm = sensor.readRangeSingleMillimeters();

  if (sensor.timeoutOccurred() || distance_mm == 65535) {
      return INVALID_DISTANCE;
  }

  // Перевод мм -> см
  int distance_cm = (distance_mm + 5) / 10;

  if (distance_cm > INVALID_DISTANCE) {
      return INVALID_DISTANCE;
  }

  return distance_cm;
}


void Sensors::update() {
  //int time = millis();
  data.prev_front = data.front;
  data.front = read_sensor_cm(front_sensor);

  data.prev_rear_right = data.rear_right;
  data.rear_right = read_sensor_cm(rear_right_sensor);

  data.prev_front_left = data.front_left;
  data.front_left = read_sensor_cm(front_left_sensor);

  data.prev_front_right = data.front_right;
  data.front_right = read_sensor_cm(front_right_sensor);
  //int newtime = millis();

  //Serial.print(newtime-time);
  //Serial.print("\n");
}