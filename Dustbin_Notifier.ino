#include <ESPert.h>

ESPert espert;

int sensorPin=0;         // Analog Pin A0
int sum=0;               // Variable to calculate SUM
int avgrange=60;         // Quantity of values to average
int sensorValue;         // Value for te average
int i,media,d,a=1;       // Variables
float cm,inch;           // Converted to cm

const char *host = "www.espert.io";
String smartphone_key = "5750392948260864"; //replace with your channel's espert smartphone key

void setup()
{  
  Serial.begin(115200);
  pinMode(02, OUTPUT);
  
  espert.init();
  espert.dht.init();
  espert.oled.init();
  delay(2000);

  espert.oled.clear();
  espert.oled.println(espert.info.getId());
  espert.oled.println();

int mode = espert.wifi.init();

  if (mode == ESPERT_WIFI_MODE_CONNECT)
  {
    espert.println(">>> WiFi mode: connected.");
    espert.oled.println("WiFi: connected.");
    espert.oled.print("IP..: ");
    espert.oled.println(espert.wifi.getLocalIP());
  }
  else if (mode == ESPERT_WIFI_MODE_DISCONNECT)
  {
    espert.println(">>> WiFi mode: disconnected.");
    espert.oled.println("WiFi: not connected.");
  }
  else if (mode == ESPERT_WIFI_MODE_SMARTCONFIG)
  {
    espert.println(">>> WiFi mode: smart config.");
  }
  else if (mode == ESPERT_WIFI_MODE_SETTINGAP)
  {
    espert.println(">>> WiFi mode: access point.");
  }
}

void loop()
{
  espert.loop();
  d=analogRead(sensorPin);            // Read the analog value
    if (d<35)
    {
      Serial.println(a);
      if(a>4)
      {
      Serial.println("Detect");
      digitalWrite(02, HIGH);        // Turn on LED
  
      String message = "Range of Ultrasonic is " + (String)(d) + ". Dustbin is FULL" + ". Come, Pick up the rubbish";
      message.replace(String(" "), String("%20"));
      String path = "/MySmartphone/send?key=" + smartphone_key + "&message=" + message;
      espert.println(">>" + espert.wifi.getHTTP(host, path.c_str()) + "<<");
      espert.oled.println("Range=" + (String)(d) + "cm");
      espert.oled.println("Dustbin is FULL");
      espert.oled.println("Pick up the rubbish");
      a=0;
      }
      else
      a++;
    }
    else
    {
     a=0;
     digitalWrite(02, LOW);             // Turn off LED
    }
  delay(1000);
  cm = (d / 2) * 2.4;                 // Convert the value to centimeters
  inch = d/2;                         // Value in inches
    
  Serial.println(cm);                 //Print average of all measured values
}
