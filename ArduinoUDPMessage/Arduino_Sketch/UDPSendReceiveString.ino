/* This sketch establishes a UDP Listener and waiting for incoming
 * packets.  After receiving a packet, it parses it and sets
 * a GPIO port to Low or High.
 * UDP Code is based off of code created by Michael Margolis
 */


#include <.libraries/SPI.h>         // needed for Arduino versions later than 0018
#include <./libraries/Ethernet.h>
#include <./libraries/EthernetUdp.h> // UDP library from: bjoern@cs.stanford.edu 12/30/2008

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(172, 16, 0, 20);

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

  int ledPin = 7;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

//  ledON = String('on');

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println(packetBuffer);
    String packetContents = String(packetBuffer);
    String ledOn = String("on ");
    Serial.println(packetContents);
    // Interpret the value in the packetBuffer
    if (packetContents == ledOn)
    {
      digitalWrite(ledPin, HIGH);
      Serial.println("Received LED ON Command");
    }
    else
    {
      digitalWrite(ledPin, LOW);
      Serial.println("Received LED OFF Command");
     }
      
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  delay(10);
}
