//  Данный пример демонстрирует получение коротких SMS сообщений:                             //
//  ========================================================================================= //
    #include <iarduino_GSM.h>                                                                 // Подключаем библиотеку iarduino_GSM для работы с GSM/GPRS Shield.
    iarduino_GSM gsm;                                                                         // Создаём объект gsm для работы с функциями и методами библиотеки iarduino_GSM.
                                                                                              //
    #include <softwareserial.h>                                                               // Подключаем библиотеку SoftwareSerial для программной реализации шины UART.
    SoftwareSerial softSerial(7,8);                                                           // Создаём объект softSerial указывая выводы RX и TX платы Arduino.
                                                                                              //
    char SMStxt[161];                                                                         // Объявляем строку для хранения текста принятых SMS сообщений.
    char SMSnum[ 13];                                                                         // Объявляем строку для хранения номера отправителя SMS сообщений.
    char SMStim[ 18];                                                                         // Объявляем строку для хранения даты и времени отправки SMS сообщений.
                                                                                              //
void setup(){                                                                                 //
//  Выводим текст в монитор последовательного порта:                                          //
    Serial.begin(9600);                                                                       // Инициируем передачу данных по аппаратной шине UART для вывода результата в монитор последовательного порта.
    Serial.print( "Initialization, please wait ... " );                                       // Выводим текст.
                                                                                              //
    gsm.begin(softSerial);                                                                    // Инициируем работу GSM/GPRS Shield, указывая объект шины UART.
                                                                                              //
//  Ждём готовность GSM/GPRS Shield к работе:                                                 //
    while(gsm.status()!=GSM_OK){Serial.print("."); delay(1000);} Serial.println(" OK!");      // Ждём завершения регистрации модема в сети оператора связи.
                                                                                              //
//  Установка кодировки для символов Кириллицы:                                               //
//  gsm.TXTreadCoding(GSM_TXT_CP866);                                                         // Если символы Кириллицы входящих SMS сообщений некорректно отображаются в мониторе, выберите одну из кодировок: GSM_TXT_CP866 / GSM_TXT_UTF8 / GSM_TXT_WIN1251.
}                                                                                             // По умолчанию для входящих и исходящих SMS сообщений установлена кодировка GSM_TXT_UTF8.
                                                                                              //
void loop (){                                                                                 //
    if(gsm.SMSavailable()){                                                                   // Функция SMSavailable() возвращает количество входящих непрочитанных SMS сообщений.
//  Если есть входящие непрочитанные SMS сообщения:                                           //
        Serial.println( "SMS came, I read ..." );                                             // Выводим текст "Пришла SMS, читаю ... ".
        gsm.SMSread(SMStxt, SMSnum, SMStim);                                                  // Читаем SMS сообщение в ранее объявленные переменные (текст SMS сообщения, адрес отправителя, дата отправки).
        Serial.print  ( "SMS sent on "    ); Serial.print  ( SMStim );                        // Выводим дату отправки.
        Serial.print  ( " from number "   ); Serial.print  ( SMSnum );                        // Выводим номер отправителя.
        Serial.println( ", message text:" ); Serial.println( SMStxt );                        // Выводим текст сообщения.
    }                                                                                         //
}                                           
