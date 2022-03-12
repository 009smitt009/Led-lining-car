#include <Adafruit_NeoPixel.h> // подключаем библиотеку
#define IN_LEFT_PLAF A3
#define IN_RIGHT_PLAF A2
#define IN_CENTER_PLAF A1
#define IN_SWICH_LED A0
#define IN_BUTTON_PIN 2

#define LED_LEFT_SEAT 3
#define LED_RIGHT_SEAT 4
#define LED_BACK_SEAT 5
#define DC_POWER 13
//#define LED_BACK_SEAT2 12
String currentStateInput;
int state = 1;
String temp = "";
unsigned long timing;

#define PIN  3              // указываем пин для подключения ленты
#define NUMPIXELS 16  // указываем количество светодиодов в ленте


// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel strip1 (NUMPIXELS, LED_LEFT_SEAT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 (NUMPIXELS, LED_RIGHT_SEAT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 (NUMPIXELS, LED_BACK_SEAT, NEO_GRB + NEO_KHZ800);

void setup() {
   Serial.begin(9600);
   Serial.println("HI");
   strip1.begin();                     // инициализируем ленту
   strip2.begin();  
   strip3.begin();  
//   strip.setBrightness(255);  // указываем яркость светодиодов (максимум 255)
   
   pinMode(IN_LEFT_PLAF,INPUT);
   pinMode(IN_RIGHT_PLAF,INPUT);
   pinMode(IN_CENTER_PLAF,INPUT);
   pinMode(IN_SWICH_LED,INPUT);
   pinMode(IN_BUTTON_PIN,INPUT_PULLUP);

   pinMode(LED_LEFT_SEAT,OUTPUT);
   pinMode(LED_RIGHT_SEAT,OUTPUT);
   pinMode(LED_BACK_SEAT,OUTPUT);
   pinMode(DC_POWER,OUTPUT);

  temp = LedPlafInput(IN_LEFT_PLAF,IN_RIGHT_PLAF, IN_CENTER_PLAF,IN_SWICH_LED,IN_BUTTON_PIN);
  
}

void loop() {

switch (state) {
    case 1:
      //выполняется когда  var равно 1 если изменяется переменная currentStateInput то заходим в кейс 2 или в случае глюка по таймингу вызывается процедура на второй кейс
      
      currentStateInput = LedPlafInput(IN_LEFT_PLAF,IN_RIGHT_PLAF, IN_CENTER_PLAF,IN_SWICH_LED,IN_BUTTON_PIN); 
  
//      Serial.println(currentStateInput[4]);
      if (temp != currentStateInput){
        temp = currentStateInput;
        state = 2;
      }

      if (millis() - timing > 5000){ // Вместо 10000 подставьте нужное вам значение паузы 
        timing = millis(); 
        //Serial.println ("10 seconds");
        temp = currentStateInput;
        state = 2;
      }
      break;
      
    case 2:
    currentStateInput = LedPlafInput(IN_LEFT_PLAF,IN_RIGHT_PLAF, IN_CENTER_PLAF,IN_SWICH_LED,IN_BUTTON_PIN);
    
      //выполняется, когда var равно 2
//     Serial.println("change state");
      if(currentStateInput[2] == '1'){ //включается центральный плафон
        
        
         for(int i=0; i<15; i++){
             strip1.setPixelColor(i, strip1.Color(255, 255, 255));   // включаем белый цвет слева
             strip2.setPixelColor(i, strip2.Color(255, 255, 255));   // включаем белый цвет справа
             strip3.setPixelColor(i, strip3.Color(255, 255, 255));   // включаем белый цвет сзади
             strip1.show();   // отправляем сигнал на ленту
             strip2.show();   // отправляем сигнал на ленту
             strip3.show();   // отправляем сигнал на ленту
             delay(100);
        }
       }

       if( (currentStateInput[3] == '1')&&(currentStateInput[2] == '0')&&(currentStateInput[0] == '0')&&(currentStateInput[1] == '0')&&(currentStateInput[4] == '1') ){ //включются габариты и выключается центральный,левый,правый плафон
          
          
          for(int i=0; i<15; i++){
             strip1.setPixelColor(i, strip1.Color(255, 0, 0));   // включаем красный цвет слева
             strip2.setPixelColor(i, strip2.Color(255, 0, 0));   // включаем красный цвет справа
             strip3.setPixelColor(i, strip3.Color(255, 0, 0));   // включаем белый цвет сзади
             strip1.show();   // отправляем сигнал на ленту
             strip2.show();   // отправляем сигнал на ленту
             strip3.show();   // отправляем сигнал на ленту
             delay(100);
          }

          
        }

         if( (currentStateInput[3] == '0')&&(currentStateInput[2] == '0')&&(currentStateInput[0] == '0')&& (currentStateInput[1] == '0') ){ //включются габариты и выключается центральный,левый,правый плафон
          for(int i=0; i<15; i++){
             strip1.setPixelColor(i, strip1.Color(0, 0, 0));   // включаем красный цвет слева
             strip2.setPixelColor(i, strip2.Color(0, 0, 0));   // включаем красный цвет справа
             strip3.setPixelColor(i, strip3.Color(0, 0, 0));   // включаем белый цвет сзади
             strip1.show();   // отправляем сигнал на ленту
             strip2.show();   // отправляем сигнал на ленту
             strip3.show();   // отправляем сигнал на ленту
             delay(100);
          }
        }

        if( (currentStateInput[0] == '1') && (currentStateInput[2] == '0') ){ //включается левый плафон и габариты и не горит центральный плафон
           for(int i=0; i<8; i++){
             strip1.setPixelColor(i, strip1.Color(255, 255, 255));   // включаем белый цвет спереди слева
             strip1.show();   // отправляем сигнал на ленту
             delay(100);
           }
        }

        
      
        if( (currentStateInput[1] == '1')&& (currentStateInput[2] == '0') ){ //включается правый плафон и габариты и не горит центральный плафон
          for(int i=0; i<8; i++){
               strip2.setPixelColor(i, strip2.Color(255, 255, 255));   // включаем белый цвет спереди справа
               strip2.show();   // отправляем сигнал на ленту
               delay(100);
          }
        }

//        if(currentStateInput[4] == '1'){
//          
//        }
    
    state = 1;
      break;
    

      
//    default:
      // выполняется, если не выбрана ни одна альтернатива
      // default необязателен
  }

  if(digitalRead(IN_BUTTON_PIN)==LOW){
      
    }
   

//  if(digitalRead(BUTTON_PIN)==LOW){
//    for(int i=0; i<8; i++){
//      strip.setPixelColor(i, strip.Color(255, 255, 255));   // включаем красный цвет на 1 светодиоде
//      strip.show();   // отправляем сигнал на ленту
//      delay(100);
//    }
//  }else{
//   for(int i=0; i<8; i++){
//      strip.setPixelColor(i, strip.Color(255, 0, 0));   // включаем красный цвет на 1 светодиоде
//      strip.show();   // отправляем сигнал на ленту
//      delay(100);
//   }
//   
//  }
//  strip.clear();   // выключаем все светодиоды
  


}

String LedPlafInput(int left, int right, int center, int swich, int button){
      int limit = 100;
      String result = "0";
      String val1, val2, val3, val4, val5 = "";
      if (analogRead(left) > limit){
      val1 = "1";  
      }else{val1 = "0";  }
      
      if (analogRead(right) > limit){
      val2 = "1" ;
      }else{val2 = "0";}
      
      if (analogRead(center) > limit){
      val3 = "1" ;  
      }else{val3 = "0";}

      if (analogRead(swich) > limit){
      val4 = "1" ;  
      }else{val4 = "0" ;  }

      if (digitalRead(button) == HIGH){
      val5 = "1" ;  
      }else{val5 = "0" ;  }
      
  return (String)val1+val2+val3+val4+val5;

}
