const int a = 2;  //For displaying segment "a"
const int b = 3;  //For displaying segment "b"
const int c = 4;  //For displaying segment "c"
const int d = 5;  //For displaying segment "d"
const int e = 6;  //For displaying segment "e"
const int f = 7;  //For displaying segment "f"
const int g = 8;  //For displaying segment "g"
bool bPress = false;
const int IncbuttonPin = 10;
const int DecbuttonPin = 11;
// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int IncbuttonState = 0;         // current state of the button
int lastIncbuttonState = 0;     // previous state of the button
int DecbuttonState = 0;         // current state of the button
int lastDecbuttonState = 0;     // previous state of the button
void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode( IncbuttonPin , INPUT_PULLUP );
  pinMode( DecbuttonPin , INPUT_PULLUP );
  Serial.begin(9600);
  displayDigit(buttonPushCounter);
}
void loop() {
   IncbuttonState = digitalRead(IncbuttonPin);
   DecbuttonState = digitalRead(DecbuttonPin);
   checkIncButtonPress();
   checkDecButtonPress();
  if( bPress ){
    bPress = false;
     turnOff();
     displayDigit(buttonPushCounter);
  }
   /*
  for(int i=0;i<10;i++)
 {
   displayDigit(i);
   delay(1000);
   turnOff();
 }
 */
}
void checkIncButtonPress()
{
   // compare the IncbuttonState to its previous state
  if (IncbuttonState != lastIncbuttonState) {
    // if the state has changed, increment the counter
    if (IncbuttonState == LOW) {
      // if the current state is HIGH then the button went from off to on:
      bPress = true;
      buttonPushCounter++;
      if( buttonPushCounter > 9) buttonPushCounter =0 ;
      Serial.println("on");
    } else {
      
      Serial.println("off");
    }
    
    delay(50);
  }
  
  lastIncbuttonState = IncbuttonState;
}
void checkDecButtonPress()
{
   
  if (DecbuttonState != lastDecbuttonState) {

    if (DecbuttonState == LOW) {
      
      bPress = true;
      buttonPushCounter--;
      if( buttonPushCounter < 0) buttonPushCounter =9 ;
      Serial.println("on");
    } else {
      
      Serial.println("off");
    }
   
    delay(50);
  }
  
  lastDecbuttonState = DecbuttonState;
}
void displayDigit(int digit)
{
 
 if(digit!=1 && digit != 4)
 digitalWrite(a,LOW);

 if(digit != 5 && digit != 6)
 digitalWrite(b,LOW);
 
 if(digit !=2)
 digitalWrite(c,LOW);

 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,LOW);

 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,LOW);
 
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
 digitalWrite(f,LOW);
 if (digit!=0 && digit!=1 && digit !=7)
 digitalWrite(g,LOW);
}
void turnOff()
{
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}
