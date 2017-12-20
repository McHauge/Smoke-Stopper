
// #### Config ####

//Max Current
const int IMax = 410;        //Deafult:  2A = 410     ~(1A=205   2A=410   3A=614   4A=819   5A=1023)

//I/O Setup
const byte OnOff = 10;       //Deafult:  10
const byte Reset = 9;        //Deafult:  9
const byte Out = 7;          //Deafult:  7
const byte SCL1 = 6;         //Deafult:  6
const byte SDA1 = 4;         //Deafult:  4
const byte GreenOutOn = 3;   //Deafult:  3
const byte RedError = 2;     //Deafult:  2
const byte I_Sense = 0;      //Deafult:  0

//Variables
int Current = 0;
byte S_OnOff = 0;
byte S_Reset = 0;
byte OutState = 0;
byte CurrentState = 0;
byte ResetState = 0;
byte GreenState = LOW;
byte RedState = LOW;


// #### Main Setup ####

void setup() {
//Setup of in- and outputs 
  pinMode(RedError, OUTPUT);
  pinMode(GreenOutOn, OUTPUT);
  pinMode(OnOff, INPUT);
  pinMode(Reset, INPUT);
  pinMode(Out, OUTPUT); 

//Sets deafult Off
  digitalWrite(Out, 0);
  OutState = 0;
  CurrentState = 0;
  ResetState = 0;

// ---- Debug ----
  Serial.begin(9600);
}


// #### Main Loop ####

void loop() {
//Reads Inputs
  Current = analogRead(I_Sense); 
  S_OnOff = digitalRead(OnOff);
  S_Reset = digitalRead(Reset);

//Does a Condition Check
  OutstateCheck();
  ResetCheck();
  CurrentCheck();

// Switchs Output
  if (Current <= IMax && OutState >= 1 && ResetState >= 1 && CurrentState >= 1)
  {   digitalWrite(Out, 1);  }
  else 
  {   digitalWrite(Out, 0);  }

//Sets LED's
  GreenLED();
  RedLED();
  digitalWrite(GreenOutOn, GreenState);
  digitalWrite(RedError, RedState); 

// ---- Debug ----
  Serial.print("Current:  ");
  Serial.print(Current);
  Serial.print("    ");
  Serial.print("S_OnOff:  ");
  Serial.print(S_OnOff);
  Serial.print("  ");
  Serial.print("S_Reset:  ");
  Serial.print(S_Reset);
  Serial.print("  ");
  Serial.print("CurrentState:  ");
  Serial.print(CurrentState);
  Serial.print("  ");
  Serial.print("OutState:  ");
  Serial.print(OutState);
  Serial.print("  ");
  Serial.print("ResetState:  ");
  Serial.print(ResetState);
  Serial.print("  "); 
  Serial.print("Out_on:  ");
  Serial.print(digitalRead(Out));
  Serial.println("  "); 
}


// #### Functions ####

//Checks if ON/OFF switch is High
int OutstateCheck() {
  if (S_OnOff == 1)
  {   OutState = 1; }
  else 
  {   OutState = 0; }
}

//Checks if RESET switch is presed
int ResetCheck() {
  if (Current <= IMax && S_Reset >= 1) 
  {   ResetState = 1;  }
}

//Checks for over current, also sets: "ResetState = 0"
int CurrentCheck() {
  if (Current <= IMax)
  {  CurrentState = 1;  }
  else
  {  CurrentState = 0;
     ResetState = 0;}
}

//Green LED control
int GreenLED() {
  if (digitalRead(Out) >= 1)
  {  GreenState = HIGH;  }
  else
  {  GreenState = LOW;  }
}

//Red LED control
int RedLED() {
  if (ResetState <=0)
  {  RedState = HIGH; }
  else
  {  RedState = LOW; } 
}
  

