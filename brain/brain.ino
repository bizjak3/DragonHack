#define PUMP_1 5  //D1 - 5 
#define PUMP_2 4  //D2 - 4
#define PUMP_3 13 //D7
#define PUMP_4 2  //D4
#define PUMP_5 14 //D5
#define PUMP_6 12 //D6

#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <FirebaseESP8266.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

const char* ssid     = "esp";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "qwertzy123";     // The password of the Wi-Fi network

// Insert Firebase project API Key
#define API_KEY "AIzaSyAQ08OHgV3sYeyjJvyyln5FXV73mm2YU8Q"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://drinkmixer-bf89e-default-rtdb.europe-west1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup() {
  
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pinMode(PUMP_1, OUTPUT);
  pinMode(PUMP_2, OUTPUT);
  pinMode(PUMP_3, OUTPUT);
  pinMode(PUMP_4, OUTPUT);
  pinMode(PUMP_5, OUTPUT);
  pinMode(PUMP_6, OUTPUT);
}

int drinkToMake = 0;
int drinkMade = 0;
int pump_1_time;
int pump_2_time;
int pump_3_time;
int pump_4_time;
int pump_5_time;
int pump_6_time;
void loop() {



  if (drinkToMake == 0 && Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    /*if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;*/
    
    //Reset receipe
    if(drinkMade == 1){
      if (Firebase.RTDB.setInt(&fbdo, "drink/make", 0)){
        Firebase.RTDB.setInt(&fbdo, "drink/0", 0);
        Firebase.RTDB.setInt(&fbdo, "drink/1", 0);
        Firebase.RTDB.setInt(&fbdo, "drink/2", 0);
        Firebase.RTDB.setInt(&fbdo, "drink/3", 0);
        Firebase.RTDB.setInt(&fbdo, "drink/4", 0);
        Firebase.RTDB.setInt(&fbdo, "drink/5", 0);
        Firebase.RTDB.setInt(&fbdo, "drink/6", 0);
        Serial.println("PASSED");
        drinkMade = 0;
        //Serial.println("PATH: " + fbdo.dataPath());
        //Serial.println("TYPE: " + fbdo.dataType());
        Serial.println("Drink was made, we cleared the queue");
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
    }
    if (Firebase.RTDB.getInt(&fbdo, "/drink/make")) {
      if (fbdo.dataType() == "int") {
        drinkToMake = fbdo.intData();        
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if(drinkToMake == 1){
      //Read pump ml
      Serial.print("We have a drink to make:");
      Serial.println(drinkToMake);
      if (Firebase.RTDB.getInt(&fbdo, "/drink/0")) {
        if (fbdo.dataType() == "int") {
          pump_1_time = fbdo.intData();
          Serial.print("Pump_1: ");
          Serial.println(pump_1_time);
        }
      }
      if (Firebase.RTDB.getInt(&fbdo, "/drink/1")) {
        if (fbdo.dataType() == "int") {
          pump_2_time = fbdo.intData();
          Serial.print("Pump_2: ");
          Serial.println(pump_2_time);
        }
      }
      if (Firebase.RTDB.getInt(&fbdo, "/drink/2")) {
        if (fbdo.dataType() == "int") {
          pump_3_time = fbdo.intData();
          Serial.print("Pump_3: ");
          Serial.println(pump_3_time);
        }
      }
      if (Firebase.RTDB.getInt(&fbdo, "/drink/3")) {
        if (fbdo.dataType() == "int") {
          pump_4_time = fbdo.intData();
          Serial.print("Pump_4: ");
          Serial.println(pump_4_time);
        }
      }
      if (Firebase.RTDB.getInt(&fbdo, "/drink/5")) {
        if (fbdo.dataType() == "int") {
          pump_5_time = fbdo.intData();
          Serial.print("Pump_5: ");
          Serial.println(pump_5_time);
        }
      }
      if (Firebase.RTDB.getInt(&fbdo, "/drink/6")) {
        if (fbdo.dataType() == "int") {
          pump_6_time = fbdo.intData();
          Serial.print("Pump_6: ");
          Serial.println(pump_6_time);
        }
      }
      
    }
  }

  if(drinkToMake == 1){
    Serial.println("Making a drink.");
    Serial.println("Pump 1 working.");
    digitalWrite(PUMP_1, HIGH);
    delay(pump_1_time*20);
    digitalWrite(PUMP_1, LOW);

    Serial.println("Pump 2 working.");
    digitalWrite(PUMP_2, HIGH);
    delay(pump_2_time*20);
    digitalWrite(PUMP_2, LOW);

    Serial.println("Pump 3 working.");
    digitalWrite(PUMP_3, HIGH);
    delay(pump_3_time*20);
    digitalWrite(PUMP_3, LOW);

    Serial.println("Pump 4 working.");
    digitalWrite(PUMP_4, HIGH);
    delay(pump_4_time*20);
    digitalWrite(PUMP_4, LOW);

    /*digitalWrite(PUMP_5, HIGH);
    delay(pump_5_time);
    digitalWrite(PUMP_5, LOW);

    digitalWrite(PUMP_6, HIGH);
    delay(pump_6_time);
    digitalWrite(PUMP_6, LOW);*/

    drinkToMake = 0;
    drinkMade = 1;
  }

  digitalWrite(PUMP_1, LOW);
  digitalWrite(PUMP_2, LOW);
  digitalWrite(PUMP_3, LOW);
  digitalWrite(PUMP_4, LOW);
  //digitalWrite(PUMP_5, LOW);
  //digitalWrite(PUMP_6, LOW);

}