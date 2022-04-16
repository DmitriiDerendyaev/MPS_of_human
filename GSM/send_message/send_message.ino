//  Данный пример демонстрирует отправку SMS сообщений:                                       //
//  ========================================================================================= //
                                                                                              //
    #include <iarduino_GSM.h>                                                                 // Подключаем библиотеку iarduino_GSM для работы с GSM/GPRS Shield.
    iarduino_GSM gsm;                                                                         // Создаём объект gsm для работы с функциями и методами библиотеки iarduino_GSM.
                                                                                              //
    #include <softwareserial.h>                                                               // Подключаем библиотеку SoftwareSerial для программной реализации шины UART.
    SoftwareSerial softSerial(0,1);                                                           // Создаём объект softSerial указывая выводы RX и TX платы Arduino.
                                                                                              //
void setup(){                                                                                 //
    Serial.begin(9600);                                                                       // Инициируем передачу данных по аппаратной шине UART для вывода результата в монитор последовательного порта.
    Serial.print( "Initialization, please wait ... " );                                       // Выводим текст.
                                                                                              //
    gsm.begin(softSerial);                                                                    // Инициируем работу GSM/GPRS Shield, указывая объект шины UART.
                                                                                              //
//  Ждём готовность GSM/GPRS Shield к работе:                                                 //
    while(gsm.status()!=GSM_OK){Serial.print("."); delay(1000);} Serial.println(" OK!");      // Ждём завершения регистрации модема в сети оператора связи.
                                                                                              //
//  Установка кодировки для символов Кириллицы:                                               //
    gsm.TXTsendCodingDetect("п");                                                             // Выполняем автоопределение кодировки скетча для отправки текста на Русском языке.
                                                                                              //
//  Отправка SMS сообщения:                                                                   //
    if( gsm.SMSsend("Hi, mum!", "79226925766") )                            // Отправляем короткое SMS сообщение на номер +7(012)345-67-89
    { Serial.println("Sent!"); }else{ Serial.println( "Error!" ); }                           // Выводим результат отправки SMS сообщения
                                                                                              //
}                                                                                             //
                                                                                              //
void loop (){                                    
  gsm.SMSsend("Hi, mum!", "79226925766");
  delay(100000);
  //
}                                            
