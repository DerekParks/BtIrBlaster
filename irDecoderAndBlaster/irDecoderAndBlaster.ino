
//          KEY_POWER                0xC1AA09F6                #  Was: power

//          KEY_OFF                  0XC1AA8976 


#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;
char input[10];
int i;
void setup() {
  Serial.begin(9600);


  i = 0;
  Serial.println ("Enter code:");
}

void loop() {

  while(Serial.available() != 0){
    
    input[i] = Serial.read();
    if(input[i] == 'r') {
      irrecv.enableIRIn(); // Start the receiver
      irrecv.blink13(true);
      Serial.println("Send IR code");
      irrecv.resume();
      delay(5000);
      if (irrecv.decode(&results) && results.rawlen > 15) {
        if (results.decode_type == NEC) {
          Serial.print("NEC: ");
        } else if (results.decode_type == SONY) {
          Serial.print("SONY: ");
        } else if (results.decode_type == RC5) {
          Serial.print("RC5: ");
        } else if (results.decode_type == RC6) {
          Serial.print("RC6: ");
        } else if (results.decode_type == UNKNOWN) {
          Serial.print("UNKNOWN: ");
        }
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value
      }
      
      i=0;
      Serial.println ("Enter code:");
    }
    i++;
    if(i == 10) {
      Serial.println("Sending:");
      Serial.println(input);
      Serial.println(strtoul(input, 0, 16));
      irsend.sendNEC(strtoul(input, 0, 16), 32);
      i = 0;
      Serial.println ("Enter code:");
    }
    
  }
}

