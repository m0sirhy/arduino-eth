/*
   Created by ArduinoGetStarted.com
   This example code is in the public domain
   Tutorial page: https://arduinogetstarted.com/tutorials/communication-between-two-arduino
*/

// ARDUINO #2: TCP SERVER + AN LED
#include <Ethernet.h>
#include <ezButton.h>
#include <SPI.h>

#include <utility/w5100.h>

byte socketStat[MAX_SOCK_NUM];
const int RELAY_1 = 9;
const int RELAY_2 = 8;
const int RELAY_3 = 7;
const int RELAY_4 = 6;
const char lasts;
ezButton button1(2); // create ezButton object that attach to pin 6;
ezButton button2(3); // create ezButton object that attach to pin 7;
ezButton button3(A0); // create ezButton object that attach to pin 8;
ezButton button4(5);

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

EthernetServer TCPserver(4080);
boolean gotAMessage = false; // whether or not you got a message from the client yet
char command;
void setup()
{
    digitalWrite(RELAY_1, HIGH); //  Turn Switch on relay - on forn unit 1
    digitalWrite(RELAY_2, HIGH); // Turn Switch off relay - OFF forn unit 1

    digitalWrite(RELAY_3, HIGH); // Turn Switch off relay - OFF forn unit 1
    digitalWrite(RELAY_4, HIGH); // Turn Switch off relay - OFF forn unit 1
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
    button2.setDebounceTime(50);  // set debounce time to 50 milliseconds
    button3.setDebounceTime(50);  // set debounce time to 50 milliseconds
    button4.setDebounceTime(50);  // set debounce time to 50 milliseconds
    
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);

    pinMode(RELAY_3, OUTPUT);
    pinMode(RELAY_4, OUTPUT);

    Serial.println("ARDUINO #2: TCP SERVER + AN LED");

    // Initialize Ethernet Shield:
    if (Ethernet.begin(mac) == 0)
        Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true)
        {
            delay(1); // do nothing, no point running without Ethernet hardware
        }
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    }
    // initialize the Ethernet device not using DHCP:
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
    delay(200); // add a delay here

    // Print your local IP address:
    Serial.print("TCP Server IP address: ");
    Serial.println(Ethernet.localIP());
    Serial.println("-> Please update the serverAddress in Arduino #1 code");

    // Listening for a TCP client (from Arduino #1)
    TCPserver.begin();
}

void loop()
{ 
    button1.loop(); // MUST call the loop() function first
    button2.loop(); // MUST call the loop() function first
    button3.loop(); // MUST call the loop() function first
    button4.loop(); // MUST call the loop() function first
   

    EthernetClient client = TCPserver.available();
     
    if (client)
    {
        if (!gotAMessage)
        {
            Serial.println("We have a new client");
            client.println("Hello, client!");
            gotAMessage = true;
            command = client.read();
            Serial.println("command: ");
            Serial.print(command);
            
        }
    }

    // Read the command from the TCP client:
    if (gotAMessage)
    {
       if (command == '1' || button1.isPressed() && lasts!='1') {
    digitalWrite(RELAY_4, LOW);
    delay(300);
    digitalWrite(RELAY_4, HIGH);
    Serial.print("- relay 1");
    client.println("1");

    digitalWrite(RELAY_1, LOW);
    delay(400);
    digitalWrite(RELAY_1, HIGH);

    gotAMessage = false;
    command = '\0';
} else if (command == '2' || button2.isPressed() && lasts!='2') {
    digitalWrite(RELAY_3, LOW);
    delay(300);
    digitalWrite(RELAY_3, HIGH);
    Serial.print("- Received command: 2");
    client.println("2");

    digitalWrite(RELAY_2, LOW);
    delay(200);
    digitalWrite(RELAY_2, HIGH);

    gotAMessage = false;
    command = '\0';
} else if (command == '3' || button3.isPressed() && lasts!='3') {
    digitalWrite(RELAY_3, LOW);
    delay(300);
    digitalWrite(RELAY_3, HIGH);
    client.println("3");
    Serial.print("- Received command: 3");

    gotAMessage = false;
    command = '\0';
} else if (command == '4'  || button4.isPressed() && lasts!='4') {
    digitalWrite(RELAY_4, LOW);
    delay(300);
    digitalWrite(RELAY_4, HIGH);
    client.println("4");
    Serial.print("- Received command: 4");

    gotAMessage = false;
    command = '\0';
} else {
    command = '\0';
    gotAMessage = false;
}

    }
}
