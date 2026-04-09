#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SLAVE_ADDR 50
#define ONE_WIRE_BUS A0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ===== Pin Driver Peltier (Cooling Mode) =====
const int indingin1 = 3;
const int indingin2 = 2;
const int pwmdingin = 9;

// ===== Parameter PID =====
float kp = 12;
float ki = 0.2;
float kd = 20;

// ===== Variabel PID =====
float temp;
float error = 0, error_prev = 0;
float p, i, d, pid;
float sumerr = 0;

// ===== Setpoint =====
float sp = 25;

// ===== Anti-windup =====
float integral_max = 100;
float integral_min = -100;

// ===== Timing =====
unsigned long lastTime = 0;
const float dt = 0.2;               // 200 ms
const unsigned long interval = 200; // ms

void setup() {
  Wire.begin(SLAVE_ADDR);     // Arduino Nano sebagai slave
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  Serial.begin(9600);
  sensors.begin();

  pinMode(indingin1, OUTPUT);
  pinMode(indingin2, OUTPUT);
  pinMode(pwmdingin, OUTPUT);

  // Set arah pendinginan
  digitalWrite(indingin1, HIGH);
  digitalWrite(indingin2, LOW);
}

void loop() {

  unsigned long now = millis();

  if (now - lastTime >= interval) {

    lastTime = now;

    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);

    // ===== Proteksi Sensor =====
    if (temp == DEVICE_DISCONNECTED_C) {
      Serial.println("Sensor Error!");
      analogWrite(pwmdingin, 0);
      return;
    }

    // ===== PID =====
    error = temp - sp;

    // Proportional
    p = kp * error;

    // Integral (aktif hanya saat cooling dibutuhkan)
    if (error > 0) {
      sumerr += error * dt;
      sumerr = constrain(sumerr, integral_min, integral_max);
    }
    i = ki * sumerr;

    // Derivative (lebih stabil)
    d = kd * (error - error_prev) / dt;

    // Total PID
    pid = p + i + d;
    pid = constrain(pid, 0, 255);

    error_prev = error;

    // ===== Aktuator =====
    if (error > 0) {
      analogWrite(pwmdingin, pid);
    } else {
      analogWrite(pwmdingin, 0);
    }

    // ===== Monitoring =====
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" | PID: ");
    Serial.println(pid);
    Serial.print(" | SP: ");
    Serial.println(sp);
  }
}

void requestEvent()
{
  byte *data = (byte*) &temp;

  Wire.write(data, 4);   // kirim float 4 byte
}

void receiveEvent(int howMany)
{
  byte command = Wire.read();

  if(command == 0x02)
  {
    byte data[4];

    for(int i=0;i<4;i++)
      data[i] = Wire.read();

    sp = *((float*)data);
  }
}