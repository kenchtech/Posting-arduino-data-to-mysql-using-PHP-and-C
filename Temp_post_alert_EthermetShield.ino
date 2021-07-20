
//Note the postData1 and postData2 are generating random values for the purpose of testing.
//Visit kenchtech channel on youtube for more info
//Created by Chinua
#include <SPI.h>
#include <Ethernet.h>

#define sensorPin A5

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 88, 253); //static IP for the ethernet shield
//IPAddress myDns(192, 168, 1, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
//int status = WL_IDLE_STATUS;

char server[] = "192.168.88.254"; //My IOT VM on virtualbox or system IP hosting WAMP server

String postData;
String postVariable = "temp=";


String postData2;
String postVariable2 = "& tempc=";

String review;

//WiFiClient client;

void setup() {

  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.println("Connecting.....");
  // else {
    //Serial.print("  DHCP assigned IP ");
    //Serial.println(Ethernet.localIP());

     // give the Ethernet shield a second to initialize:
  delay(1000);

  IPAddress ip = Ethernet.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  }
 

void loop() {
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  postData = postVariable + temperatureF;
  postData2 = postVariable2 + temperatureC;
  review = (postVariable+temperatureF + postVariable2 + temperatureC);
if (temperatureF >= 80){
  if (client.connect(server, 80)) {
    client.println("POST /test/emailScript.php HTTP/1.1");
    client.println("Host: 192.168.88.254");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(review.length());
    client.println();
    client.print(review);
    //client.print(postData2);
    
    //client.print("Content-Length: ");
    //client.println((postData2+postData2).length());
   // client.println();
   // client.print(postData2);
    delay (500);
   // client.println("POST /test/emailScript.php HTTP/1.1");
    //client.println("Host: 192.168.88.254");
    //client.println("Content-Type: application/x-www-form-urlencoded");
   // client.print("Content-Length: ");
    //client.println(postData2.length());
    //client.println();
   // client.print(postData2);
    delay (500);
    Serial.println("Email Sent");
    Serial.println(postData);

    Serial.println("Email2 Sent");
    Serial.println(postData2);
    
    while(client.connected()){
      if(client.available()){
        //Read incoming byte from the server and print to the serial monitor
        char c = client.read();
        Serial.print(c);
      }
    }
//////////////////////////////////////////////////////////////////////
   // delay(1000);

  
delay(1000);
  }

  if (client.connected()) {
    client.stop();
  }

  delay(6000);
}

  //Serial.println(postData);

  delay(3000);
}
