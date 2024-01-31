#ifndef BMS_WEBSERVER_H
#define BMS_WEBSERVER_H

#define NUMBER_OF_SLAVES 4

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <iostream>

extern AsyncWebServer server;

static int temperature[NUMBER_OF_SLAVES] = {67,76,54,45};
static int voltage[NUMBER_OF_SLAVES] = {6,7,5,4};

void notFound(AsyncWebServerRequest *request);
void handleRoot(AsyncWebServerRequest *request);
void handleStyle(AsyncWebServerRequest *request);
void handleScriptJS(AsyncWebServerRequest *request);
void handleBootstrap(AsyncWebServerRequest *request);
void handleLog(AsyncWebServerRequest *request);
void handleFetch(AsyncWebServerRequest *request);

void setupWebServer(const char* ssid, const char* password);


#endif