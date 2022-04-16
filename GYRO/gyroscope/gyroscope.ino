#include "I2Cdev.h"     //Библиотека для работы с I2C устройствами
#include "MPU6050.h"    //Библиотека для работы с MPU6050
//#include <cmath>

using namespace std;

//В строках 5, 6 и 7: в зависимости от версии библиотеки I2Cdev проверяем, нужна ли библиотека Wire
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//MPU6050 accelgyro;          //Инициализируем объект MPU5060 с именем accelegyro; По умолчанию, если к пину ADO модуля MPU6050 ничего не подключено оставьте все как есть...
MPU6050 accelgyro(0x69);  //Если же пин AD0 подтянут к 5 или 3.3 вольтам раскоментируйте эту строку, и закоментируйте предыдущую

int16_t ax, ay, az;         //Переменные для хранения значений полученных с акселерометра
int16_t gx, gy, gz;         //Переменные для хранения значений полученных с гироскопа
int16_t ax_last = 0;
int16_t i = 0;
int alarm = 15000;

unsigned long timing; // Переменная для хранения точки отсчета

void setup() {
  //Те же настройки, что и в строках 5, 6 и 7...
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  Serial.begin(9600);                                     //Инициализируем Serial со скоростью 112500 бод
  Serial.println("Initializing I2C devices...");            //Выводим сообщение о начале инициализации MPU5060
  accelgyro.initialize();                                   //Инициализируем MPU6050
  Serial.println("Testing device connections...");          //Выводим сообщение о проверке, подключен ли модуль MP6050 к Arduino
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");         //Выводим сообщение с результатом проверки
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //Получаем данные с акселерометра и гироскопа и заносим их в ранее созданные переменные
    //accelgyro.getAcceleration(&ax, &ay, &az);             //Вариант получения данных только с акселерометра
    //accelgyro.getRotation(&gx, &gy, &gz);                 //Вариант получения данных только с гироскопа

    
    Serial.print("a/g:\t");
    Serial.print(ax); Serial.println("\t");     //Выводим значение полученное с оси x акселерометра и делаем табуляцию

    delay(100);

    
    


    if((ax - ax_last) < 1000)
    {
      i++;
    }
    else
    {
      i = 0;
    }

    ax_last = ax;

    if(i > 50)
    {
      Serial.println(alarm);
    }
    else
    {
      Serial.println(0);
    }
    
    /*Serial.print(ay); Serial.print("\t");     //Выводим значение полученное с оси y акселерометра и делаем табуляцию
    Serial.print(az); Serial.println("\t");     //Выводим значение полученное с оси z акселерометра и делаем табуляцию
    
    /*Serial.print(gx); Serial.print("\t");     //Выводим значение полученное с оси x гироскопа и делаем табуляцию
    Serial.print(gy); Serial.print("\t");     //Выводим значение полученное с оси y гироскопа и делаем табуляцию
    Serial.println(gz);                       //Выводим значение полученное с оси z гироскопа и переходим на новую строку*/
     

}
