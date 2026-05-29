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

  //front_left_sensor = VL53L0X();
  //front_sensor = VL53L0X();
  //front_right_sensor = VL53L0X();
  //rear_right_sensor = VL53L0X();

  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    pinMode(XSHUTS[i], OUTPUT);
    digitalWrite(XSHUTS[i], LOW);
  }

  delay(50);

  VL53L0X* sensors[NUMBER_OF_SENSORS] = {
    &front_left_sensor,
    &front_sensor,
    &front_right_sensor,
    &rear_right_sensor
  };


  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    digitalWrite(XSHUTS[i], HIGH);

    delay(20);
 
    sensors[i]->setTimeout(MAX_TIME_ON_SENSOR);
    //Serial.print("suc1 ");

    if (!sensors[i]->init()) {
      Serial.print("VL53L0X init error, sensor ");
      Serial.println(i);

      while (true) {
      }
    }
    //Serial.print("suc2 ");
    
    sensors[i]->setAddress(SENSOR_ADDRESSES[i]);
    //Serial.print("suc3 ");
    if (!sensors[i]->setMeasurementTimingBudget(33000)) {
      Serial.print("VL53L0X timing budget error, sensor ");
      Serial.println(i);

      while (true) {
      }
    }
    //Serial.print("suc4 ");

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


bool Sensors::i2c_alive(uint8_t address) {
  Wire.beginTransmission(address);
  return Wire.endTransmission() == 0;
}

void Sensors::print_i2c_state() {
  uint8_t addresses[] = {0x29, 0x2A, 0x2B, 0x2C, 0x2D};

  Serial.println("I2C state:");
  for (uint8_t addr : addresses) {
      Serial.print("0x");
      Serial.print(addr, HEX);
      Serial.print(": ");
      Serial.println(i2c_alive(addr) ? "OK" : "NO");
  }
}


void Sensors::update() {
  /*bool need_reinit = false;

  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    if (!i2c_alive(SENSOR_ADDRESSES[i])) {
      need_reinit = true;
      break;
    }
  }

  if (need_reinit) {
    begin();
  }*/ 


  //int time = millis();
  data.prev_front = data.front;
  data.front = read_sensor_cm(front_sensor);

  data.prev_rear_right = data.rear_right;
  data.rear_right = read_sensor_cm(rear_right_sensor);

  data.prev_front_left = data.front_left;
  data.front_left = read_sensor_cm(front_left_sensor);

  data.prev_front_right = data.front_right;
  data.front_right = read_sensor_cm(front_right_sensor);

  //print_i2c_state();
}




