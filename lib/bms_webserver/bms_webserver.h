#ifndef BMS_WEBSERVER_H
#define BMS_WEBSERVER_H

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>

extern AsyncWebServer server;

void notFound(AsyncWebServerRequest *request);
void handleRoot(AsyncWebServerRequest *request);
void handleStyle(AsyncWebServerRequest *request);
void handleScriptJS(AsyncWebServerRequest *request);
void handleBootstrap(AsyncWebServerRequest *request);
void handlelog(AsyncWebServerRequest *request);

void setupWebServer(const char* ssid, const char* password);
void startWebServer();

#endif