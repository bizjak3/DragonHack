#define PUMP_1 12 
#define PUMP_2 13 
#define PUMP_3 4 
#define PUMP_4 2 
#define PUMP_5 3 
#define PUMP_6 7 

#define INPUT_1 0
#define INPUT_2 1
#define INPUT_3 2
#define INPUT_4 3
//#define INPUT_5 12
//#define INPUT_6 13

int previousPump_1 = 1;
int previousPump_2 = 1;
int previousPump_3 = 1;
int previousPump_4 = 1;
int previousPump_5 = 1;
int previousPump_6 = 1;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  pinMode(PUMP_1, OUTPUT);
  pinMode(PUMP_2, OUTPUT);
  pinMode(PUMP_3, OUTPUT);
  pinMode(PUMP_4, OUTPUT);
  //pinMode(PUMP_5, OUTPUT);
  //pinMode(PUMP_6, OUTPUT);

  pinMode(INPUT_1, INPUT);
  pinMode(INPUT_2, INPUT);
  pinMode(INPUT_3, INPUT);
  pinMode(INPUT_4, INPUT);
  //pinMode(INPUT_5, INPUT);
  //pinMode(INPUT_6, INPUT);

}

void loop() {

  digitalWrite(PUMP_1,1);
  digitalWrite(PUMP_2,1);
  digitalWrite(PUMP_3,1);
  digitalWrite(PUMP_4,1);
  //digitalWrite(PUMP_5,1);
  //digitalWrite(PUMP_6,1);

  //if(digitalRead(INPUT_1) == 1){
  //  Serial.println(analogRead(INPUT_1));

  //}
  /*
  if(digitalRead(INPUT_2) == 1){
    digitalWrite(PUMP_2,0);
    delay(5000);
    digitalWrite(PUMP_2,1);
  }
  if(digitalRead(INPUT_3) == 1){
    digitalWrite(PUMP_3,0);
    delay(5000);
    digitalWrite(PUMP_3,1);
  }
  if(digitalRead(INPUT_4) == 1){
    digitalWrite(PUMP_4,0);
    delay(5000);
    digitalWrite(PUMP_4,1);
  }*/
  if(analogRead(INPUT_1) > 200){
    Serial.print("Input_1:");
    Serial.println(analogRead(INPUT_1));
    while(analogRead(INPUT_1) > 200){
      digitalWrite(PUMP_1,0);
      Serial.println(analogRead(INPUT_4));
    }
    previousPump_1 = analogRead(INPUT_1);
    digitalWrite(PUMP_1,1);
  }

  if(analogRead(INPUT_2) > 200){
    Serial.print("Input_2:");
    while(analogRead(INPUT_2)){
      digitalWrite(PUMP_2,0);
      Serial.println(analogRead(INPUT_2));
    }
    previousPump_2 = analogRead(INPUT_2);
    digitalWrite(PUMP_2,1);
  }

  if(analogRead(INPUT_3) > 200){
    Serial.print("Input_3:");
    while(analogRead(INPUT_3) > 200){
      digitalWrite(PUMP_3,0);
      Serial.println(analogRead(INPUT_3));
    }
    previousPump_3 = analogRead(INPUT_3);
    digitalWrite(PUMP_3,1);
  }

  if(analogRead(INPUT_4) > 200){
    Serial.print("Input_4:");
    while(analogRead(INPUT_4) > 200){
      digitalWrite(PUMP_4,0);
      Serial.println(analogRead(INPUT_4));
    }
    previousPump_4 = analogRead(INPUT_4);
    digitalWrite(PUMP_4,1);
  }
  /*
  if(digitalRead(INPUT_5)){
    Serial.print("Input_5:");
    while(digitalRead(INPUT_5))
      digitalWrite(PUMP_5,0);
    previousPump_5 = digitalRead(INPUT_5);
    digitalWrite(PUMP_5,1);
  }

  if(digitalRead(INPUT_6)){
    Serial.print("Input_6:");
    while(digitalRead(INPUT_6))
      digitalWrite(PUMP_6,0);
    previousPump_6 = digitalRead(INPUT_6);
    digitalWrite(PUMP_6,1);
  }*/
  
  // Serial.println();*/
}
