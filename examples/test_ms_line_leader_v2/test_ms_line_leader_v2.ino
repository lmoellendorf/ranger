#include <LmMsLineLeaderV2.h>

MsLineLeaderV2 ll = MsLineLeaderV2();

void getDeviceInfo(void) {
  char fw_str[9] = { 0 };
  size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
  int ret;

  ret = ll.getVersion(fw_str, len);

  if (!ret) {
    Serial.println("version: ");
    Serial.println(fw_str);
  }

  ret = ll.getVendorId(fw_str, len);

  if (!ret) {
    Serial.println("vendor: ");
    Serial.println(fw_str);
  }

  ret = ll.getDeviceId(fw_str, len);

  if (!ret) {
    Serial.println("device: ");
    Serial.println(fw_str);
  }
}

void setup() {
  Serial.begin(9600);
  getDeviceInfo();
}

void loop() {
  char readings[8];
  size_t n_readings = sizeof(readings) / sizeof(readings[0]);
  int voltage[8];
  size_t n_voltage = sizeof(voltage) / sizeof(voltage[0]);
  char key;
  const char v = 'v';
  const char c = 'c';
  const char w = 'w';
  const char b = 'b';
  const char W = 'W';
  const char B = 'B';
  const char V = 'V';
  const char s = 's';
  const char a = 'a';
  const char r = 'r';
  const char p = 'p';
  const char u = 'u';
  int addr;
  int ret;

  Serial.print(v);
  Serial.println(": getVersion, getVendorId, getDeviceId");
  Serial.print(c);
  Serial.println(": getCalibrated");
  Serial.print(w);
  Serial.println(": getWhiteLimit");
  Serial.print(b);
  Serial.println(": getBlackLimit");
  Serial.print(W);
  Serial.println(": getWhiteCalibration");
  Serial.print(B);
  Serial.println(": getBlackCalibration");
  Serial.print(V);
  Serial.println(": getVoltage");
  Serial.print(s);
  Serial.println(": getSteering");
  Serial.print(a);
  Serial.println(": getAverage");
  Serial.print(r);
  Serial.println(": getResult");
  Serial.print(p);
  Serial.println(": putToSleep");
  Serial.print(u);
  Serial.println(": wakeUp");
  Serial.println("1-9: Change address");

  while (!Serial.available())
    ;

  key = Serial.read();

  switch (key) {
    case v:
      getDeviceInfo();
      break;

    case c:
      ret = ll.getCalibrated(readings, n_readings);
      Serial.println("calibrated: ");

      for (int i = 0; i < n_readings; i++) {
        Serial.print((int)readings[i]);

        if (i != n_readings - 1)
          Serial.print(":");
      }

      Serial.println("");
      break;

    case w:
      ret = ll.getWhiteLimit(readings, n_readings);
      Serial.println("white limit: ");

      for (int i = 0; i < n_readings; i++) {
        Serial.print((int)readings[i]);

        if (i != n_readings - 1)
          Serial.print(":");
      }

      Serial.println("");
      break;

    case b:
      ret = ll.getBlackLimit(readings, n_readings);
      Serial.println("black limit: ");

      for (int i = 0; i < n_readings; i++) {
        Serial.print((int)readings[i]);

        if (i != n_readings - 1)
          Serial.print(":");
      }

      Serial.println("");
      break;

    case W:
      ret = ll.getWhiteCalibration(readings, n_readings);
      Serial.println("white calibration: ");

      for (int i = 0; i < n_readings; i++) {
        Serial.print((int)readings[i]);

        if (i != n_readings - 1)
          Serial.print(":");
      }

      Serial.println("");
      break;

    case B:
      ret = ll.getBlackCalibration(readings, n_readings);
      Serial.println("black calibration: ");

      for (int i = 0; i < n_readings; i++) {
        Serial.print((int)readings[i]);

        if (i != n_readings - 1)
          Serial.print(":");
      }

      Serial.println("");
      break;

    case V:
      ret = ll.getVoltage(voltage, n_voltage);
      Serial.println("voltage: ");

      for (int i = 0; i < n_voltage; i++) {
        Serial.print((int)voltage[i]);

        if (i != n_voltage - 1)
          Serial.print(":");
      }

      Serial.println("");
      break;

    case s:
      ret = ll.getSteering();
      Serial.println("steering: ");
      Serial.println(ret);
      break;

    case a:
      ret = ll.getAverage();
      Serial.println("average: ");
      Serial.println(ret);
      break;

    case r:
      ret = ll.getResult();
      Serial.println("result: ");
      Serial.println(ret);
      break;

    case p:
      ll.putToSleep();
      delay(500);
      break;

    case u:
      ll.wakeUp();
      delay(250);
      break;

    default:
      addr = key - 0x30;

      if (addr > 0 && addr < 10) {
        ll.changeAddress(addr);
        Serial.print("New address: ");
        Serial.println(addr);
      }

      break;
  }
}
