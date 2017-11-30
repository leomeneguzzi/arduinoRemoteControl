#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected) {
    float x = PS3.getAnalogHat(LeftHatX), velocity = PS3.getAnalogButton(R2), vR = velocity, vL = velocity, reverse = PS3.getAnalogButton(L2);
    /*Serial.println();
    Serial.print("LeftHatX: ");
    Serial.println(x);
    Serial.print("R2: ");
    Serial.println(velocity);
    Serial.print("L2: ");
    Serial.println(reverse);*/

    if(x < 117){
      vL *= x/117.;
    }else if(x > 137){
      vR *= -0.00847457627118 * x + 2.16101694915254;
    }

    Serial.print("Velocidade: ");
    Serial.println(velocity);
    Serial.print("vL: ");
    Serial.println(vL);
    Serial.print("vR: ");
    Serial.println(vR);


    delay(100);
    
  
    
    /*if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
    }

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
    }else if (PS3.getAnalogButton(R2)) {
        Serial.print(F("\rR2: "));
        Serial.print(PS3.getAnalogButton(R2));
    }*/

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
  }
}
