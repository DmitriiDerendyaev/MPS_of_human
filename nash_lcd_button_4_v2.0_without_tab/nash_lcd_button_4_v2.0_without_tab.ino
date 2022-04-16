#include <SoftwareSerial.h>

// Создать объект программного последовательного порта для связи с SIM900
// Tx и Rx SIM900 подключены к выводам 7 и 8 Arduino
SoftwareSerial mySerial(7, 8);

void setup()
{
  // Начать последовательную связь Arduino и Arduino IDE (монитор последовательного порта)
  Serial.begin(9600);
  
  // Начать последовательную связь Arduino и SIM900
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  // Рукопожатие с SIM900
  mySerial.println("AT");
  updateSerial();
  // Тест качества сигнала, диапазон значений 0-31, 31 - лучший
  mySerial.println("AT+CSQ");
  updateSerial();
  // Прочитать информацию о SIM карте, чтобы убедиться, что SIM карта подключена
  mySerial.println("AT+CCID");
  updateSerial();
  // Проверяем, зарегистрирован ли модуль в сети
  mySerial.println("AT+CREG?");
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    // Пересылка того, что было получено с аппаратного последовательного порта, 
    // на программный последовательный порт
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    // Пересылка того, что было получено с программного последовательного порта, 
    // на аппаратный последовательный порт
    Serial.write(mySerial.read());
  }
}

void loop()
{
  updateSerial();
}
