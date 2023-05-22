#include <UIPEthernet.h>
#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>  // Add the LCD library

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  // MAC address of your Ethernet module

EthernetClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD module (change the address if necessary)

const int button1Pin = 5;  // Pin number for button 1
const int button2Pin = 6;  // Pin number for button 2
const int button3Pin = 7;  // Pin number for button 3
const int button4Pin = 8;  // Pin number for button 4

// Define LEDs
int LED1 = 4;
int LED2 = 3;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Solar Control!"); // Display initial message
  Ethernet.begin(mac);

  delay(1000);  // Wait for Ethernet module to initialize
  
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
   lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print(Ethernet.localIP());
      
}

void loop() {
  // Check if button 1 is pressed
  if (digitalRead(button1Pin) == HIGH) {
    if (sendMessage("1")) {
      Serial.println("Message sent successfully: 1");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Message sent: 1");
       digitalWrite(LED1,HIGH);
                  digitalWrite(LED2,LOW);
      readServerReply();
    } else {
      Serial.println("Failed to send message: 1");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Failed to send:");
      lcd.setCursor(0, 1); // Set cursor to the second line
      lcd.print("Message 1");
       digitalWrite(LED1,HIGH);
                  digitalWrite(LED2,HIGH);
    }
    delay(500);  // Debounce delay
  }

  // Check if button 2 is pressed
  if (digitalRead(button2Pin) == HIGH) {
    if (sendMessage("2")) {
      Serial.println("Message sent successfully: 2");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Message sent: 2");
       digitalWrite(LED1,HIGH);
                  digitalWrite(LED2,LOW);
      readServerReply();
    } else {
      Serial.println("Failed to send message: 2");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Failed to send:");
      lcd.setCursor(0, 1); // Set cursor to the second line
      lcd.print("Message 2");
       digitalWrite(LED1,HIGH);
                  digitalWrite(LED2,HIGH);
    }
    delay(500);  // Debounce delay
  }

  // Check if button 3 is pressed
  if (digitalRead(button3Pin) == HIGH) {
    if (sendMessage("3")) {
      Serial.println("Message sent successfully: 3");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Message sent: 3");
       digitalWrite(LED1,LOW);
                  digitalWrite(LED2,HIGH);
      readServerReply();
    } else {
      Serial.println("Failed to send message: 3");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Failed to send:");
      lcd.setCursor(0, 1); // Set cursor to the second line
      lcd.print("Message 3");
       digitalWrite(LED1,HIGH);
                  digitalWrite(LED2,HIGH);
    }
    delay(500);  // Debounce delay
  }

  // Check if button 4 is pressed
  if (digitalRead(button4Pin) == HIGH) {
    if (sendMessage("4")) {
      Serial.println("Message sent successfully: 4");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Message sent: 4");
       digitalWrite(LED1,LOW);
                  digitalWrite(LED2,HIGH);
      readServerReply();
    } else {
      Serial.println("Failed to send message: 4");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the first line
      lcd.print("Failed to send:");
      lcd.setCursor(0, 1); // Set cursor to the second line
      lcd.print("Message 4");
       digitalWrite(LED1,HIGH);
                  digitalWrite(LED2,HIGH);
    }
    delay(800);  // Debounce delay
  }
}

bool sendMessage(const char* message) {
  if (client.connect("185.97.132.228", 4080)) {  // Replace "your_server_ip" with the IP of your TCP server
    Serial.print("Connected to server. Server IP address: ");
    Serial.println(client.remoteIP());
    Serial.print("Arduino IP address: ");
    Serial.println(Ethernet.localIP());
    
    client.println(message);
    return true;
  } else {
    return false;
  }
}

void readServerReply() {
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
        client.stop();

  }
  Serial.println();
}
