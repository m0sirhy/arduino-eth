#include <ezButton.h>
#include <UIPEthernet.h>
#include <LiquidCrystal_I2C.h>

EthernetClient client;
unsigned long nextConnectTime = 1;
ezButton button1(5); // create ezButton object that attach to pin 5;
ezButton button2(6); // create ezButton object that attach to pin 6;
ezButton button3(7); // create ezButton object that attach to pin 7;
ezButton button4(8); // create ezButton object that attach to pin 8;
const int LED1 = 4;
const int LED2 = 3;
int size;

uint8_t *stat = NULL;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
    Serial.begin(9600);
    button1.setDebounceTime(50); // set debounce time to 50 milliseconds
    button2.setDebounceTime(50);  // set debounce time to 50 milliseconds
    button3.setDebounceTime(50);  // set debounce time to 50 milliseconds
    button4.setDebounceTime(50);  // set debounce time to 50 milliseconds
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
lcd.init(); // initialize the lcd
  lcd.backlight();

  
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
   

           
}

void loop()
{

    button1.loop(); // MUST call the loop() function first
    button2.loop(); // MUST call the loop() function first
    button3.loop(); // MUST call the loop() function first
    button4.loop(); // MUST call the loop() function first

 
    if (button4.isPressed()){
                    lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("Relay 4");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("Solar 2 off"); // print message at (0, 1)

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
                                lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("Relay 3");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("Solar 3 off"); // print message at (0, 1)

    }
    else if (button2.isPressed())
    {
        me('2');
         if(stat!= NULL)
                  digitalWrite(LED1,LOW);
         digitalWrite(LED2,HIGH);

                 client.stop();
                                 lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("Relay2");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("Solar 2 on"); // print message at (0, 1)


    }
    else if (button1.isPressed())
    {

        me('1');
        if(stat!= NULL)
          digitalWrite(LED2,LOW);

  digitalWrite(LED1,HIGH);
        client.stop();

                lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("Relay 1");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("Solar 1 off"); // print message at (0, 1)
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
