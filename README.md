# Smart-Door-Lock 2020
Two MCUs (AVR Atmega16) connected and communicate with  UART protocol ,
-HMI MCU _Interfacing Module _ for entering the password through the KeyPad and display it on LCD 
  new PassWord is Enterd at the beginning and re-entered again you have 3 time re-entering if wrong go to the 1st step ,if passed then two options :
                                                                                                                                                  -Motor Start
                                                                                                                                                  - Change PassWord.

-Control MCU to restore the password in EEPROM ( I2C ) and controlling the Motor Speed and Directions using PWM and rotating for 10 sec using timer
    and if password is wrong  after 3 times then the system is stopped for 10 mins and Buzzer is on and LCD displaying an Error msg.
