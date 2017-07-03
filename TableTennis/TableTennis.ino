/*
Project Table Tennis Digital Score

Send IR commands to update placarJogador1 following the Olympic Games Rules
best of 5 sets until 11 each one. Deuce 

 */

#include <IRremote.h>
#include <SerialDisplay.h>


//RoboCore Remote Control Map-----------------
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
BPRV = FF22DD;
BNXT = FF02FD;
BPP = FFC23D;
BMIN = FFE01F;
BPLU = FFA857;
BEQU = FF906F;
B100 = FF9867;
B200 = FFB04F;
*/

const long BMIN = 0xFFE01F;  //Botao de Menos - 
const long BPLU = 0xFFA857;  //Botao de Mais +
const long BEQU = 0xFF906F;  //Botao Zerar 0

const int BPRV = 1;

//Mapa do Seven Digits Display------------

byte seven_seg_digits[17][7] = { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 },  // = Digito 9
                                 { 1,1,1,0,1,1,1 },  // = Digito A
                                 { 0,0,1,1,1,1,1 },  // = Digito B
                                 { 1,0,0,1,1,1,0 },  // = Digito C
                                 { 0,1,1,1,1,0,1 },  // = Digito D
                                 { 1,0,0,1,1,1,1 },  // = Digito E
                                 { 1,0,0,0,1,1,1 },   // = Digito F
                                 { 0,0,0,0,0,0,0 },   // = APAGADO
                                 };



int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Inicializa os Display 7 segmentos
SerialDisplay placarJogador1(12,13,2); // (data, clock, number of modules)
//SerialDisplay placarJogador2(X,X,2); // (data, clock, number of modules)

//Pontuacao dos jogadores
//Jogador 1
byte PontosJogador1 = 0;
byte P1Dezena = 0;
byte P1Unidade = 0;
byte P1Set = 0;


//Jogador 2
byte PontosJogador2 = 0;
byte P2Dezena = 0;
byte P2Unidade = 0;
byte P2Set = 0;

void setup()
{
  
  Serial.begin(9600);
  
  //inicializa Controle Remoto
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

//Diplays Off
  placarJogador1.Off(0);
  placarJogador1.Info(&Serial);
/*
  placarJogador2.Off(0);
  placarJogador2.Info(&Serial);
 
*/
  //Set das portas do miniDisplay1
  pinMode(2, OUTPUT); //Pino 2 do Arduino ligado ao segmento A  
  pinMode(3, OUTPUT); //Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); //Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); //Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); //Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); //Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); //Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); //Pino 9 do Arduino ligado ao segmento PONTO

  //Inicializa PLACAR com ZERO
  placarJogador1.Print(P1Unidade, 2);
  placarJogador1.Print(P1Dezena, 1);
  sevenSegWrite(P1Set);
  writePonto(0);
  

}

void writePonto(byte dot)   //Funcao que aciona o ponto no display
{  
  digitalWrite(9, dot);
}

void sevenSegWrite(byte digit)  //Funcao que aciona o display
{
  byte pin = 2;

  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount)  
  { 
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
    //delay(500);
  }
    //writePonto(1);  //Liga o ponto
   //delay(100);   //Aguarda 100 milisegundos
    //writePonto(0);  //Desliga o ponto
}


void loop() {
  
  //Verifica se recebeu um comando de controle remoto
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    delay(50);
    //Enviar comando para cada botao apertado
    switch (results.value){ 
      
    case N1:  //1
      placarJogador1.Print(1);   
      break;
    case 16718055:  //2
      placarJogador1.Print(2);   
      break;

    case 16743045:  //3
      placarJogador1.Print(3);   
      break;
    
    case 16716015: //4
      placarJogador1.Print(4);   
      break;
      
    case 16726215:  //5
      placarJogador1.Print(5);   
      break;
      
    case 16734885:  //6
      placarJogador1.Print(6);   
      break;
      
    case 16728765:  //7
      placarJogador1.Print(7);   
      break;
      
    case 16730805: //8
      placarJogador1.Print(8);   
      break;
      
    case 16732845:  //9
      placarJogador1.Print(9);   
      break;
      
   case N0: //0
      placarJogador1.Print(0);   
      break;
   
   case BMIN: //Botao Menos
      
      Serial.println("Botao Menos apertado");
      alterarPlacar1(1);
      break;

   case BPLU: //Botao Mais
      
      Serial.println("Botao Mais apertado");
      alterarPlacar1(2);
      break;

   case BEQU: //Botao Zerar
      Serial.println("Botao Eq apertado");
      alterarPlacar1(3);
      
      break;
   
   case 0xFFFFFFFF: // Repetition
      break;
      
    default: 
 
   //   placarJogador1.Off(1);
   //   placarJogador1.Off(2);
      break;
  }

    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

void alterarPlacar1(int comando) {
  Serial.println(PontosJogador1);
  Serial.println(comando);
  
  switch (comando){ 
    case 1: //Subtrai do placar 1
      if (PontosJogador1 != 0) {
        PontosJogador1 = PontosJogador1 - 1;
        
      }

     if (P1Unidade == 0) {
        P1Dezena = P1Dezena - 1;
        P1Unidade = 9;
      }
      else
      { 
        P1Unidade = P1Unidade - 1;
      }
      PontosJogador1 = PontosJogador1 - 1;

      
      break;

    case 2: //Soma do placar 1
      if (P1Unidade == 9) {
        P1Dezena = P1Dezena + 1;
        P1Unidade = 0;
      }
      else
      { 
        P1Unidade = P1Unidade + 1;
      }
      PontosJogador1 = PontosJogador1 + 1;
      
      break;
    
    case 3: //Zerar Placar 1
      delay(50);
      Serial.println(irrecv.decode(&results));
      Serial.println(results.value, HEX);
      Serial.println("resume");
      irrecv.resume();  //aguarda a proxima tecla
      Serial.println(irrecv.decode(&results));
      Serial.println(results.value, HEX);
      
   
        Serial.println("Inicio do While");
        while (true)
        {
          Serial.println("While");
          Serial.println(irrecv.decode(&results));
          if (irrecv.decode(&results)) 
          {
            Serial.println(results.value, HEX);
            if (results.value == BEQU) 
            {
              PontosJogador1 = 0;
              P1Dezena = 0;
              P1Unidade = 0;
              P1Set = 0;
              Serial.println("Break 1");

              break;    
            }
            else 
           {
              Serial.println("Else 2");
              Serial.println(results.value, HEX);
              if (results.value != 0xFFFFFFFF) //Para evitar a repeticao do botao apertado por muito tempo
              {
                  Serial.println("Break 2");
                  break;
              }
              irrecv.resume();  //aguarda a proxima tecla

           }
        }
        
        placarJogador1.Off(0);
        sevenSegWrite(16);
        
        
        delay(500);
        placarJogador1.Print(P1Unidade, 2);
        placarJogador1.Print(P1Dezena, 1);
        sevenSegWrite(P1Set);

        delay(500);
    }
  }
  placarJogador1.Print(P1Unidade, 2);
  placarJogador1.Print(P1Dezena, 1);
  sevenSegWrite(P1Set);

  if (PontosJogador1 == 11) {
    P1Set++;

    delay(500);
    placarJogador1.Off(0);
    delay(500);
    placarJogador1.Print(P1Unidade, 2);
    placarJogador1.Print(P1Dezena, 1);
    delay(500);
    placarJogador1.Off(0);
    delay(500);
    placarJogador1.Print(P1Unidade, 2);
    placarJogador1.Print(P1Dezena, 1);
    delay(500);
    placarJogador1.Off(0);
    delay(500);
    placarJogador1.Print(P1Unidade, 2);
    placarJogador1.Print(P1Dezena, 1);

    delay(1000);
    sevenSegWrite(P1Set);

    PontosJogador1 =0;
    P1Dezena = 0;
    P1Unidade = 0;
    placarJogador1.Print(P1Unidade, 2);
    placarJogador1.Print(P1Dezena, 1);
    //placarJogador1.Dot(2);

   }

}

