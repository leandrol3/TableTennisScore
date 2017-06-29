/*
Project Table Tennis Digital Score

Send IR commands to update displays following the Olympic Games Rules
best of 5 sets until 11 each one. Deuce 

 */

#include <IRremote.h>
#include <SerialDisplay.h>


//RoboCore Remote Control

const long N0 = 0xFF6897;
const long N1 = 0xFF30CF;
/*const N2 FF18E7;
const N3 FF7A85;
const N4 FF10EF;
const N5 FF38C7;
const N6 FF5AA5;
const N7 FF42BD;
const N8 FF4AB5;
const N9 FF52AD;

BCH- = FFA25D;
BCH = FF629D;
BCH+ = FFE21D;
B<< = 
*/

const int BPRV = 1;

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

SerialDisplay displays(4,5,1); // (data, clock, number of modules)

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

//Displays Off
  displays.Off(0);
  displays.Info(&Serial);
  
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch (results.value){
      
    case N1:  //1
      displays.Print(1);   
      break;
    case 16718055:  //2
      displays.Print(2);   
      break;

    case 16743045:  //3
      displays.Print(3);   
      break;
    
    case 16716015: //4
      displays.Print(4);   
      break;
      
    case 16726215:  //5
      displays.Print(5);   
      break;
      
    case 16734885:  //6
      displays.Print(6);   
      break;
      
    case 16728765:  //7
      displays.Print(7);   
      break;
      
    case 16730805: //8
      displays.Print(8);   
      break;
      
    case 16732845:  //9
      displays.Print(9);   
      break;
      
   case N0: //0
      displays.Print(0);   
      break;
   case 0xFFFFFFFF: // Repetition
      break;
      
    default: 
 
      displays.Off(1);
      break;
  }

    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
