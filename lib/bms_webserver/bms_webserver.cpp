#include "bms_webserver.h"

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not Found");
}

void handleRoot(AsyncWebServerRequest *request)
{
  File file = SPIFFS.open("/index.html");
  if (file)
  {
    request->send(SPIFFS, "/index.html", "text/html");
    file.close();
  }
  else
  {
    notFound(request);
  }
}

void handleAboutUs(AsyncWebServerRequest *request)
{
  File file = SPIFFS.open("/about-us.html");
  if (file)
  {
    request->send(SPIFFS, "/about-us.html", "text/html");
    file.close();
  }
  else
  {
    notFound(request);
  }
}

void handleBootstrap(AsyncWebServerRequest *request)
{
  File file = SPIFFS.open("/css/bootstrap.min.css");
  if (file)
  {
    request->send(SPIFFS, "/css/bootstrap.min.css", "text/css");
    file.close();
  }
  else
  {
    notFound(request);
  }
}

void handleScriptJS(AsyncWebServerRequest *request)
{
  String filePath = request->url();
  File file = SPIFFS.open(filePath);
  if (file)
  {
    request->send(SPIFFS, filePath, "application/javascript");
    file.close();
  }
  else
  {
    notFound(request);
  }
}

void handleLog(AsyncWebServerRequest *request)
{
  File file = SD.open("/log.txt"); // Replace with your file path
  if (file)
  {
    request->send(SD, "/log.txt", "text/plain");
    file.close();
  }
  else
  {
    Serial.println("ERROR loading log file!!!");
    request->send(404, "text/plain", "File not found");
  }
}

void handleFetch(AsyncWebServerRequest *request)
{
  DynamicJsonDocument jsonDoc(256);
  
  jsonDoc["NUMBER_OF_SLAVES"] = NUMBER_OF_SLAVES;

  for (int i = 0; i < NUMBER_OF_SLAVES; i++)
  {
    jsonDoc["voltage" + std::to_string(i+1)] = voltage[i];
    jsonDoc["temperature" + std::to_string(i+1)] = voltage[i];
  }

  String response;
  serializeJson(jsonDoc, response);
  request->send(200, "application/json", response);
}

void setupWebServer(const char *ssid, const char *password)
{
  Serial.begin(115200);

  // Starte den Access Point
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP-Adresse: ");
  Serial.println(IP);

  // Initialisiere SPIFFS
  if (!SPIFFS.begin())
  {
    Serial.println("Fehler beim Initialisieren von SPIFFS");
    return;
  }
  Serial.println("SPIFFS initialisiert");

  server.on("/", HTTP_GET, handleRoot);
  server.on("/about-us.html", HTTP_GET, handleAboutUs);
  server.on("/css/bootstrap.min.css", HTTP_GET, handleBootstrap);
  server.on("/js/jquery-3.2.1.slim.min.js", HTTP_GET, handleScriptJS);
  server.on("/js/popper.min.js", HTTP_GET, handleScriptJS);
  server.on("/js/bootstrap.min.js", HTTP_GET, handleScriptJS);
  server.on("/js/script.js", HTTP_GET, handleScriptJS);
  server.on("/log", HTTP_GET, handleLog);
  server.on("/api/measured-values", HTTP_GET, handleFetch);

  // Fange 404-Fehler ab
  server.onNotFound(notFound);

  server.begin();
}
