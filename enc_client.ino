#include <ezButton.h>
#include <UIPEthernet.h>

EthernetClient client;
unsigned long nextConnectTime = 0;
ezButton button1(5,PULLUP); // create ezButton object that attach to pin 5;
ezButton button2(6,PULLUP); // create ezButton object that attach to pin 6;
ezButton button3(7,PULLUP); // create ezButton object that attach to pin 7;
ezButton button4(8,PULLUP); // create ezButton object that attach to pin 8;
const int LED1 = 4;
const int LED2 = 3;
int size;

uint8_t *stat = NULL;

void setup()
{
    Serial.begin(9600);
    button1.setDebounceTime(50); // set debounce time to 50 milliseconds
    button2.setDebounceTime(50);  // set debounce time to 50 milliseconds
    button3.setDebounceTime(50);  // set debounce time to 50 milliseconds
    button4.setDebounceTime(50);  // set debounce time to 50 milliseconds
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

    uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    Ethernet.begin(mac, IPAddress(192, 168, 1, 10));

    Serial.print("localIP: ");
    Serial.println(Ethernet.localIP());
    Serial.print("subnetMask: ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("gatewayIP: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("dnsServerIP: ");
    Serial.println(Ethernet.dnsServerIP());
                    client.stop();

}

void loop()
{
    button1.loop(); // MUST call the loop() function first
    button2.loop(); // MUST call the loop() function first
    button3.loop(); // MUST call the loop() function first
    button4.loop(); // MUST call the loop() function first

    if (button4.isPressed()){
        me('4');
            if(stat!= NULL)
         digitalWrite(LED2,LOW);
                client.stop();

        
    }
    else if (button3.isPressed()){
        me('3');
          if(stat!= NULL)
         digitalWrite(LED1,LOW);
                client.stop();

    }
    else if (button2.isPressed())
    {
        me('2');
         if(stat!= NULL)
         digitalWrite(LED2,HIGH);
                 client.stop();


    }
    else if (button1.isPressed())
    {
        me('1');
        if(stat!= NULL)
  digitalWrite(LED1,HIGH);
        client.stop();

    }
}

void me(char i)
{
    unsigned long currentTime = millis();

    if (currentTime >= nextConnectTime)
    {
        nextConnectTime = currentTime + 3000;

        Serial.println("Connecting to server...");
        if (client.connect(IPAddress(192, 168, 1, 177), 4080))
        {
            Serial.println("Connected to server");
            client.println(i);

            while (client.available() == 0)
            {
                if (millis() >= nextConnectTime)
                {
                    Serial.println("Timeout waiting for server response");
                    void(* resetFunc) (void) = 0;
                }
            }

            size = client.available();
            stat = (uint8_t *)malloc(size);
            if (stat == NULL)
            {
                Serial.println("Failed to allocate memory for response");
            }

            size = client.read(stat, size);
            Serial.write(stat, size);

            if (size > 0)
            {
                          Serial.write(stat, size);

            }
            else
            {
                Serial.println("Invalid server response");
            }

            free(stat);
        }
        else
        {
            Serial.println("Failed to connect to server");
             i = 0;
            stat = NULL; // Erase client message
            size = 0; // Erase client message
        }
    }

}
