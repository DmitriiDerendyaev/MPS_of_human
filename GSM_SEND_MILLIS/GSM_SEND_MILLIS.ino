// подключение библиотеки SoftwareSerial
#include <SoftwareSerial.h>
// номер телефона для отправки sms (поменяйте на свой)
#define PHONE "+79225070232"
SoftwareSerial Sim900Serial(7, 8);
//SoftwareSerial Sim900Serial(2, 3);

unsigned long millis1;
void setup()
{
Sim900Serial(19200); // the Hardware serial rate
}
void loop()
{
if (millis()-millis1>30*1000) // прошло 30 сек?
{
SendTextMessage(); // отправить sms
millis1=millis();
}
}
// подпрограмма отправки sms
void SendTextMessage()
{
// AT-команда установки text mode
Sim900Serial.print("AT+CMGF=1\r");
delay(100);
// номер телефона получателя
Sim900Serial.println("AT + CMGS = \"");
Sim900Serial.println(PHONE);
Sim900Serial.println("\"");
delay(100);
//с температурой работа была
Sim900Serial.println(" Pora rabotatI ");
delay(100);
// ASCII код ctrl+z – окончание передачи
Sim900Serial.println((char)26);
delay(100);
Sim900Serial.println();
}
