int p = 3;


void setup() 

{

pinMode(p, OUTPUT);

}

void loop()

{

tone (p, 500);

delay(100); 

tone(p, 1000);

delay(100);

}
