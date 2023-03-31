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
char lasts;

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
   

    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);

    pinMode(RELAY_3, OUTPUT);
    pinMode(RELAY_4, OUTPUT);

    Serial.println("ARDUINO #2: TCP SERVER + AN Solar");

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
    EthernetClient client = TCPserver.available();

    if (client)
    {
        if (!gotAMessage)
        {
            Serial.println("We have a new order");
            client.println("Order, Recived!");
            gotAMessage = true;
            command = client.read();
            Serial.println("command: ");
            Serial.print(command);
        }
    }

    // Read the command from the TCP client:
    if (gotAMessage)
    {
        if (command == '1'  && lasts != '1')
        {
           relay1act();
               client.println("1");

        }
        else if (command == '2' && lasts != '2')
        {
           relay2act();
               client.println("2");

        }
        else if (command == '3' && lasts != '3')
        {
           relay3act();
               client.println("3");

        }
        
        else if (command == '4' && lasts != '4')
        {
           relay4act();
               client.println("4");

        }
        
        else
        {
            command = '\0';
            gotAMessage = false;
        }
    }
}

void relay1act()
{
    digitalWrite(RELAY_4, HIGH);
    delay(400);
    digitalWrite(RELAY_4, LOW);
    Serial.print("- relay 1");

    digitalWrite(RELAY_1, HIGH);
    delay(400);
    digitalWrite(RELAY_1, LOW);
    lasts = '1';
    gotAMessage = false;
    command = '\0';
}
void relay2act()
{
    digitalWrite(RELAY_3, HIGH);
    delay(400);
    digitalWrite(RELAY_3, LOW);
    Serial.print("- Received command: 2");

    digitalWrite(RELAY_2, HIGH);
    delay(400);
    digitalWrite(RELAY_2, LOW);
    lasts = '2';
    gotAMessage = false;
    command = '\0';
}
void relay3act()
{
    digitalWrite(RELAY_3, HIGH);
    delay(400);
    digitalWrite(RELAY_3, LOW);
    Serial.print("- Received command: 3");
    lasts = '3';
    gotAMessage = false;
    command = '\0';
}

void relay4act()
{
    digitalWrite(RELAY_4, HIGH);
    delay(400);
    digitalWrite(RELAY_4, LOW);
    Serial.print("- Received command: 4");
    lasts = '4';
    gotAMessage = false;
    command = '\0';
}
