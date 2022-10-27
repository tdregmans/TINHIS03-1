// Hardware Interfacing en Sensoren
// Technische Informatica | 2021-2022 | TINHIS03-1

// Marijn Sopers (1038742) en Thijs Dregmans (1024272)
// Hardware Interfacing en Sensoren Case Study:
// Waterpas met MPU6050
// gemaakt op 12-04-2022

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define noordLed 15
#define oostLed 12
#define zuidLed 13
#define westLed 14

Adafruit_MPU6050 mpu;

const float kalibratieWaardeX = 0.07;
const float kalibratieWaardeY = 0.55;
const int milliSecondenDelay = 50;

const float gevoeligheid = 0.4;

float x;
float y;
float z;

void setup(void) {
  Serial.begin(115200);

  pinMode(noordLed, OUTPUT);
  pinMode(oostLed, OUTPUT);
  pinMode(zuidLed, OUTPUT);
  pinMode(westLed, OUTPUT);
  
  while (!Serial)
    delay(10);
  // test verbinding met MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 chip niet gevonden!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 gevonden!");

  // set range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  // haal waarden op
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print waarden uit
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  x = a.acceleration.x + kalibratieWaardeX;
  y = a.acceleration.y + kalibratieWaardeY;
  z = a.acceleration.z;

  // Print waarden uit
  Serial.print("Acceleration X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.print(y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.println("");

  if(z > 8) {
    // waterpas heeft bovenkant boven
    
    // noord
    if(y < -1 * gevoeligheid) {
      digitalWrite(noordLed, LOW);
    }
    else {
      digitalWrite(noordLed, HIGH);
    }
    // zuid
    if(y > 1 * gevoeligheid) {
      digitalWrite(zuidLed, LOW);
    }
    else {
      digitalWrite(zuidLed, HIGH);
    }
    // oost
    if(x < -1 * gevoeligheid) {
      digitalWrite(oostLed, LOW);
    }
    else {
      digitalWrite(oostLed, HIGH);
    }
    // west
    if(x > 1 * gevoeligheid) {
      digitalWrite(westLed, LOW);
    }
    else {
      digitalWrite(westLed, HIGH);
    }

  } else {
    // waterpas heeft bovenkant onder
    digitalWrite(noordLed, LOW);
    digitalWrite(oostLed, LOW);
    digitalWrite(zuidLed, LOW);
    digitalWrite(westLed, LOW);
  }
  delay(milliSecondenDelay);
}
