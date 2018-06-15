#include <ESP8266WiFi.h>

WiFiClient client;
// Server where is the php script
char servername[]="host.es";
// SecretKey shared with php script
String secretKey= "asdfghjkl";
// Initialize server notified to false
boolean server_notified = false;

// Set pinout of components
int button_pin = 13;
int led_pin = 14;
int ldr_pin = A0;

// Set threshold to ldr to detect light
int threshold = 1000;

// Set status as 'disarmed' by default
String currentStatus = "disarmed";

// Set wifi name and password
const char* ssid = "Wifi_name";
const char* password = "wifi_password";

// Declare global variables to read button values and ldr values
int buttonVal, ldrVal, buttonVal1, buttonVal2;

void setup() {
  // Set serial speed to comunicate with console
  Serial.begin(9600);
  // Set button pin as pull up input to conect directly
  pinMode(button_pin, INPUT_PULLUP);
  // Set led pin as output
  pinMode(led_pin, OUTPUT);
  // Set esp wifi as client
  WiFi.mode(WIFI_STA);
  // Initialize wifi ssid and password and connect
  WiFi.begin(ssid, password);
  
  // Wait until esp is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if(currentStatus == "disarmed"){
    // Mantain the led off until button is pressed
    // If the button is pressed go to 'armed' status
    currentStatus = waiting_disarmed();
    
  }else if(currentStatus == "armed"){
    // blink led until ldr doesn't detect light (in that case status change to 'event')
    // Or blink led until button was pressed during one second (in that case status change to 'disarmed')
    currentStatus = waiting_armed();
    
  }else if(currentStatus == "event"){
    // Mantain the led on until the button is not pressed
    // If the button is pressed reset notify server variable and go to 'disarmed' status
    currentStatus = waiting_with_event();
  }
}

String waiting_disarmed(){
  // Turn off led
  digitalWrite(led_pin,LOW);
  // Read button value
  buttonVal = digitalRead(button_pin); 
  // If button was pressed change status to armed
  if (buttonVal == LOW) {
    delay(500);
    return "armed";
  }
  return "disarmed";
}

String waiting_armed(){
  buttonVal1 = digitalRead(button_pin);
  // Turn on led
  digitalWrite(led_pin,HIGH);
  // Read ldr with 25 miliseconds of delay
  // If ldr value is more than the threshold return 'event' status
  for(int i = 0; i<20;i++){
    ldrVal = analogRead(ldr_pin);
    if(ldrVal > threshold) return "event";
    delay(25);
    i++;
  }
  // Turn off led
  digitalWrite(led_pin,LOW);
  // Read ldr with 25 miliseconds of delay
  // If ldr value is more than the threshold return 'event' status
  for(int i = 0; i<20;i++){
    ldrVal = analogRead(ldr_pin);
    if(ldrVal > threshold) return "event";
    delay(25);
    i++;
  }
  buttonVal2 = digitalRead(button_pin);
  // If at the beginning (buttonVal1) and at the end (buttonVal2)
  // The button was pressed, change status to 'disarmed'
  if(buttonVal1 == LOW && buttonVal2 == LOW){
    // Confirm disarmed option blinking led faster
    while(buttonVal1 == LOW){
      digitalWrite(led_pin,HIGH);
      delay(25);
      buttonVal1 = digitalRead(button_pin);
      digitalWrite(led_pin,LOW);
      delay(25);
     }
     return "disarmed";
  }
  return "armed";
}

String waiting_with_event(){
  // Turn on led to show that event was handled
  digitalWrite(led_pin,HIGH);
  // Notify server if it was not done yet
  if(!server_notified) server_notified = notify_server();
  // Read button value
  buttonVal = digitalRead(button_pin);  
  // If it was pressed reset server_notified variable and go to 'disarmed' status
  if (buttonVal == LOW) {
    server_notified = false;
    delay(500);
    return "disarmed";
  }
  return "event";
}

boolean notify_server(){
  // Send request to 80 port
  if (client.connect(servername, 80)) {
    //Define url to host
    client.println("GET /smartWashingMachine/notify.php?secretKey=" + secretKey + " HTTP/1.1");
    client.println("Host: " + String(servername));
    client.println("Connection: close");
    client.println();
  }
  //waits for data
  while(client.connected() && !client.available()) delay(1);
  //stop client
  client.stop();
  return true;
}
