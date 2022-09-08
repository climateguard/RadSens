// Инициализируем библиотеки
#include <radSens1v2.h>
#include <Wire.h>
#include <GyverOLED.h>

#define ADC_pin A0 // задаём значение пина АЦП

GyverOLED<SSH1106_128x64> oled; // Инициализируем 1.3" OLED-экран 
ClimateGuard_RadSens1v2 radSens(RS_DEFAULT_I2C_ADDRESS); // Инициализируем RadSens

uint16_t ADC; // Переменная для значений АЦП
uint32_t timer_cnt; // Таймер для измерений дозиметра
uint32_t timer_bat; // Таймер для измерения заряда батареи

void setup() {
  pinMode(ADC_pin, OUTPUT); // Инициализируем АЦП как получатель данных
  radSens.radSens_init();
  oled.init(); // Инициализируем OLED в коде
  oled.flipV(1); // Я перевернул экран для удобства
  oled.flipH(1); // Для нормального отображения после переворота нужно инвертировать текст по горизонтали
  oled.setScale(2); // Устанавливаем размер шрифта
  oled.setScale(1);
  oled.clear();
  oled.update();  // Обновляем экран
  delay(3000);
}

void loop() {
  if (millis() - timer_cnt > 1000) { // Снимаем показания с дозиметра и выводим их на экран
    timer_cnt = millis();
    // Проверяем, обновляются ли данные с дозиметра. Если да - выводим их, если нет - предупреждаем об ошибке
    if (radSens.getData()) {
      char buf1[50];
      char buf2[50];
      char buf3[50];
      sprintf(buf1, "Дин: %.2f мкр/ч", radSens.getRadIntensyDynamic()); // Собираем строку с показаниями динамической интенсивности
      sprintf(buf2, "Стат: %.2f мкр/ч ", radSens.getRadIntensyStatic()); // Собираем строку с показаниями средней интенсивности за период работы
      oled.setCursor(0, 2);
      oled.print(buf1);
      oled.setCursor(0, 4);
      oled.print(buf2);
    }
    else {
      oled.setCursor(45, 3);
      oled.print("ERROR");  
    }
  }

  if (millis() - timer_bat > 10000) { // Считываем показание с АЦП, рисуем батарею и создаём индикацию заряда
    timer_bat = millis();
    ADC = analogRead(ADC_pin); // Считываем показание с АЦП
    oled.rect(104, 3, 124, 10, OLED_STROKE); // Рисуем иконку батарейки
    oled.rect(125, 5, 127, 8, OLED_FILL);
    if (ADC >= 970) {
      oled.rect(104, 3, 124, 10, OLED_FILL);
      oled.setCursor(6, 1);
      oled.setCursor(104, 2);
      oled.print("100%");
    }
    if (ADC < 970 && ADC >= 870) {
      oled.rect(106, 3, 119, 10, OLED_FILL);
      oled.setCursor(104, 2);
      oled.print("75%");
    }
    if (ADC < 870 && ADC >= 770) {
      oled.rect(106, 3, 114, 10, OLED_FILL);
      oled.setCursor(104, 2);
      oled.print("50%");
    }
    if (ADC < 770) {
      oled.setCursor(104, 2);
      oled.print("LOW");
    }
  }
  oled.update(); // Обновляем экран в конце цикла
}
