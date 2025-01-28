#include <WiFiNINA.h>
#include "arduino_secrets.h"
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

const int ledPin = 2; const int piezoPin = 8; const int dataPin = 3;
int notes[] = {440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831};

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
int status = WL_IDLE_STATUS;

WiFiServer server(80);
WiFiClient client = server.available();

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  while (!Serial);

  while (!driver.init())
  {
    Serial.println("Driver initialization failed!");
  }
  
  enable_WiFi();
  connect_WiFi();

  server.begin();
  printWiFiStatus();
}

void loop() 
{
  client = server.available();

  if (client)
  {
    WEB();
  }
}

void scanNetworks() 
{
  Serial.println("Scanning for networks...");
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == 0) 
  {
      Serial.println("No networks found.");
  } 
  else 
  {
    Serial.println("Networks found:");
    for (int i = 0; i < numNetworks; i++) 
    {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.println(" dBm)");
    }
  }
}

void enable_WiFi()
{
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with the WiFi module failed!");
    while (true);
  }
  else
  {
    Serial.println("WiFi module detected!");
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0")
  {
    Serial.println("Please upgrade the firmware!");
  }
}

void connect_WiFi()
{
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
    Serial.print("WiFi Status: ");
    Serial.println(status);
    Serial.print("Signal Strength (RSSI): ");
    Serial.println(WiFi.RSSI());

    delay(20000);
  }
}

void printWiFiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");

  // open the client
  Serial.print("To view CosmicWhisper in action, open a browser window to http://");
  Serial.println(ip);
}

void WEB()
{
  if (client)
  {
    Serial.println("New Client!");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);  // print received character to serial monitor

        if (c == '\n') // if newline received
        {
          if (currentLine.length() == 0)
          {
            // send html page with UI
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("  <meta charset=\"UTF-8\">");
            client.println("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("  <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH\" crossorigin=\"anonymous\">");
            client.println("  <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz\" crossorigin=\"anonymous\"></script>");
            client.println("</head>");
            client.println("<body background=\"https://raw.githubusercontent.com/Prithwis-2023/MKR-WiFi1010/refs/heads/main/temp/freepik__expand__61973.png\" style=\"background-size: cover;background-blend-mode: darken;\">");
            client.println("  <center><h1 class=\"display-1\" style=\"padding-top:5%; color:white; filter: brightness(50);\"><strong>Cosmic Whisper 2.0</strong></h1></center>");
            client.println("  <center><hr style=\"width: 50%; color: white;\"></center>");
            client.println("  <center style=\"padding-left: 30%; padding-top:1%\">");
            
            // first row 
            client.println("    <div class=\"btn-toolbar\" role=\"toolbar\" aria-label=\"Toolbar with button groups\">");
            
            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'/A4\'\">Note A4</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-warning btn-lg\" onclick=\"location.href=\'/Bb4\'\">Note A#4/Bb4</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'B4\'\">Note B4</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'C5\'\">Note C5</button>");
            client.println("      </div>");

            client.println("    </div>");
            client.println("  </center>");

            // second row
            client.println("  <center style=\"padding-left: 28.5%; padding-top:3%\">");
            client.println("    <div class=\"btn-toolbar\" role=\"toolbar\" aria-label=\"Toolbar with button groups\">");
            
            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-warning btn-lg\" onclick=\"location.href=\'/Db5\'\">Note C#5/Db5</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'/D5\'\">Note D5</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-warning btn-lg\" onclick=\"location.href=\'Eb5\'\">Note D#5/Eb5</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'E5\'\">Note E5</button>");
            client.println("      </div>");

            client.println("    </div>");
            client.println("  </center>");

            // third row
            client.println("  <center style=\"padding-left: 28.5%; padding-top:3%\">");
            client.println("    <div class=\"btn-toolbar\" role=\"toolbar\" aria-label=\"Toolbar with button groups\">");
            
            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'/F5\'\">Note F5</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-warning btn-lg\" onclick=\"location.href=\'/Gb5\'\">Note F#5/Gb5</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-success btn-lg\" onclick=\"location.href=\'G5\'\">Note G5</button>");
            client.println("      </div>");

            client.println("      <div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\">");
            client.println("        <button type=\"button\" class=\"btn btn-warning btn-lg\" onclick=\"location.href=\'Ab5\'\">Note G#5/Ab5</button>");
            client.println("      </div>");

            client.println("    </div>");
            client.println(" </center>");

            client.println("</body>");
            client.println("</html>");
            break;
          }
          else
          {
            currentLine = "";
          }
        }

        else if (c != '\r')
        {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /A4"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[0], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /Bb4"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[1], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /B4"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[2], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /C5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[3], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /Db5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[4], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /D5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[5], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /Eb5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[6], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /E5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[7], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /F5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[8], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /Gb5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[9], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /G5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[10], 500);
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /Ab5"))
        {
          digitalWrite(ledPin, HIGH);
          playTone(notes[11], 500);
          digitalWrite(ledPin, LOW);
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected");
  }
}

void playTone(int note, int duration)
{
  tone(piezoPin, note, duration);
  delay(duration);
  noTone(piezoPin);
  transmit(note);
}

void transmit(int note)
{
  char message[10];
  sprintf(message, "%i", note);
  driver.send((uint8_t *)message, strlen(message));
  driver.waitPacketSent();
  Serial.println("Sending...");
}
