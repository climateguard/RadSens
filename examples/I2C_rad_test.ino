#include <Wire.h>
uint8_t data[19];                                           // Массив принятых данных
float temp;                                                 // Временная переменная хранения данных
uint32_t cnt;

void setup() 
{
  Wire.begin();                                             // Инициализация I2C
  Serial.begin(115200);                                     // Инициализация UART
}

void loop(){
  
//--------------------------------------------- Считывание данных ---------------------------------------------//
 
  Wire.beginTransmission(0x66);                             // Старт передачи данных к устройству с адресом 0x66
  Wire.write(0x0);                                          // Считывать данные начиная с 0x00 регистра
  Wire.endTransmission(false);                              // Перезапустить передачу
  Wire.requestFrom(0x66, 19);                               // Старт чтения 19-ти регистров устройства с адресом 0x66
    
  data[0] = Wire.read();                                    // Чтение регистра №0
  data[1] = Wire.read();                                    // Чтение регистра №1
  data[2] = Wire.read();                                    // Чтение регистра №2
  data[3] = Wire.read();                                    // Чтение регистра №3
  data[4] = Wire.read();                                    // Чтение регистра №4
  data[5] = Wire.read();                                    // Чтение регистра №5
  data[6] = Wire.read();                                    // Чтение регистра №6
  data[7] = Wire.read();                                    // Чтение регистра №7
  data[8] = Wire.read();                                    // Чтение регистра №8
  data[9] = Wire.read();                                    // Чтение регистра №9
  data[10] = Wire.read();                                   // Чтение регистра №10
  data[11] = Wire.read();                                   // Чтение регистра №11
  data[12] = Wire.read();                                   // Чтение регистра №12
  data[13] = Wire.read();                                   // Чтение регистра №13
  data[14] = Wire.read();                                   // Чтение регистра №14
  data[15] = Wire.read();                                   // Чтение регистра №15
  data[16] = Wire.read();                                   // Чтение регистра №16
  data[17] = Wire.read();                                   // Чтение регистра №17
  data[18] = Wire.read();                                   // Чтение регистра №18

  Serial.print("0x"); 
  Serial.print(data[0], HEX);                               // Вывести в порт ID устройства 
  Serial.print(" "); 
  Serial.print(data[1], HEX);                               // Вывести в порт версию прошивки
  Serial.print("\t||\t"); 
  
  temp = ((data[3] << 16)|(data[4] << 8)|data[5])/10.0;     // Перевод значения интенсивности излучения при dT < 123
  Serial.print(temp, 1);                                    // Вывод интенсивности
  Serial.print("\t"); 

  temp = ((data[6] << 16)|(data[7] << 8)|data[8])/10.0;     // Перевод значения интенсивности излучения при dT = 500
  Serial.print(temp, 1);                                    // Вывод интенсивности
  Serial.print("\t"); 

  if(data[0]==0x7D) cnt += (data[9] << 8) | data[10];       // Перевод количества импульсов
  Serial.print(cnt);                                        // Вывод количества импульсов
  Serial.print("\t"); 
   
  Serial.print("0x"); 
  Serial.print(data[16], HEX);                              // Вывести адрес устройства
  Serial.print("-"); 
      
  Serial.print(data[17]);                                   // Вывести состояние HV генератора
  Serial.print("-"); 

  Serial.print(data[18]);                                   // Вывести значение коэф.
  Serial.print("\t"); 
   
  Serial.print(data[12]); Serial.print("|"); Serial.print(data[13]); Serial.print("\t"); 

  Serial.print("\n\r"); 

//--------------------------------------------- Изменение адреса ---------------------------------------------//

  if(Serial.available())                                    // Если по UART пришли данные
  {
    uint8_t c = Serial.read();                              // Считывание первого принятого байта
    while(Serial.available()) Serial.read();                // Отбрасывание остальных (если пришли)

    if(c == '0')                                            // Если принят символ "0"
    {
      Wire.beginTransmission(0x66);                         // Старт передачи данных к устройству с адресом 0x66
      Wire.write(0x10);                                     // Номер регистра 0x10
      Wire.write(0x46);                                     // Записать в регистр (адреса) 0x46
      Wire.endTransmission();                               // Завершить передачу
    } 
    else if(c == '1')                                       // иначе если принят символ "1" (пример включения HV генератора)
    {
      Wire.beginTransmission(0x66);                         // Старт передачи данных к устройству с адресом 0x66
      Wire.write(0x11);                                     // Номер регистра 0x11
      Wire.write(1);                                        // Записать в регистр 1
      Wire.endTransmission();                               // Завершить передачу
    }
    else if(c == '2')                                       // иначе если принят символ "2" (пример отключения HV генератора)
    {
      Wire.beginTransmission(0x66);                         // Старт передачи данных к устройству с адресом 0x66
      Wire.write(0x11);                                     // Номер регистра 0x11
      Wire.write(0);                                        // Записать в регистр 0
      Wire.endTransmission();                               // Завершить передачу
    }
    else if(c == '3')                                       // иначе если принят символ "3" (пример установки коэффициента 68)
    {
      Wire.beginTransmission(0x66);                         // Старт передачи данных к устройству с адресом 0x66
      Wire.write(0x12);                                     // Номер регистра 0x12
      Wire.write(68);                                       // Записать в регистр 68
      Wire.endTransmission();                               // Завершить передачу
    }
    else if(c == '4')                                       // иначе если принят символ "4" (пример установки коэффициента 100)
    {
      Wire.beginTransmission(0x66);                         // Старт передачи данных к устройству с адресом 0x66
      Wire.write(0x12);                                     // Номер регистра 0x12
      Wire.write(105);                                      // Записать в регистр 105
      Wire.endTransmission();                               // Завершить передачу
    }
    else                                                    // иначе
    {
      Wire.beginTransmission(0x46);                         // Старт передачи данных к устройству с адресом 0x46
      Wire.write(0x10);                                     // Номер регистра 0x10
      Wire.write(0x66);                                     // Записать в регистр (адреса) 0x66
      Wire.endTransmission();                               // Завершить передачу
    }
  }
  
  delay(30);
}
