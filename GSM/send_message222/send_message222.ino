//  Данный пример демонстрирует отправку SMS сообщений:                                       //
//  ========================================================================================= //
                                                                                              //
    #include <iarduino_GSM.h>                                                                 // Подключаем библиотеку iarduino_GSM для работы с GSM/GPRS Shield.
    iarduino_GSM gsm;                                                                         // Создаём объект gsm для работы с функциями и методами библиотеки iarduino_GSM.
                                                                                              //
    #include <SoftwareSerial.h>                                                               // Подключаем библиотеку SoftwareSerial для программной реализации шины UART.
    SoftwareSerial softSerial(7,8);                                                           // Создаём объект softSerial указывая выводы RX и TX платы Arduino.
                                                                                             

    #define button_sos  2     // button B3 is connected to Arduino pin 2
    
void setup(){                                                                                 //
    Serial.begin(9600);                                                                       // Инициируем передачу данных по аппаратной шине UART для вывода результата в монитор последовательного порта.
    Serial.print( "Initialization, please wait ... " );                                       // Выводим текст.
                                                                                              //
    gsm.begin(softSerial);                                                                    // Инициируем работу GSM/GPRS Shield, указывая объект шины UART.
                                  
    pinMode(button_sos, INPUT_PULLUP);
    
//  Ждём готовность GSM/GPRS Shield к работе:                                                 //
    while(gsm.status() != GSM_OK)
    {
      Serial.print("."); 
      delay(1000);
    } Serial.println(" OK! ");      // Ждём завершения регистрации модема в сети оператора связи.
                                                                                              //
//  Установка кодировки для символов Кириллицы:                                               //
    gsm.TXTsendCodingDetect("п");                                                             // Выполняем автоопределение кодировки скетча для отправки текста на Русском языке.
                                                                                              //
//  Отправка SMS сообщения:                                                                   //
    if( gsm.SMSsend("Это короткое SMS сообщение", "79225070232") )                            // Отправляем короткое SMS сообщение на номер +7(012)345-67-89
    { Serial.println("Sent!"); }else{ Serial.println( "Error!" ); }                           // Выводим результат отправки SMS сообщения
                                                                                              //
}                                                                                             //
                                                                                              //
void loop (){  
  
  if( !digitalRead(button_sos))
  {
    gsm.SMSsend("Это короткое SMS сообщение", "79225070232");
    if( gsm.SMSsend("Это короткое SMS сообщение", "79225070232") )                            // Отправляем короткое SMS сообщение на номер +7(012)345-67-89
    { Serial.println("Sent!"); }else
    { Serial.println( "Error!" ); }     
  }
}
  
  
  //
                                      
