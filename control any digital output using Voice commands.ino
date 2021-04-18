String voice;
int
led1 = 13; //Connect LED 1 To Pin #2
//--------------------------Call A Function-------------------------------//
void allon(){
     digitalWrite(led1, HIGH);
}
void alloff(){
     digitalWrite(led1, LOW);
}
//-----------------------------------------------------------------------//
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
}
//-----------------------------------------------------------------------//
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0) {
    Serial.println(voice);
  if(voice == "*start") {digitalWrite(led1, HIGH);}
  else if(voice == "*stop") {digitalWrite(led1, LOW);}
voice="";}} 
