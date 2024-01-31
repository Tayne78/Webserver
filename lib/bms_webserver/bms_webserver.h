#ifndef BMS_WEBSERVER_H
#define BMS_WEBSERVER_H

#define NUMBER_OF_SLAVES 6

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <iostream>

extern AsyncWebServer server;

static int temperature[NUMBER_OF_SLAVES] = {67,76,54,45,182,12};
static float voltage[NUMBER_OF_SLAVES] = {6.1,7.2,5.3,4.4,3.1,2.2};

void notFound(AsyncWebServerRequest *request);
void handleRoot(AsyncWebServerRequest *request);
void handleStyle(AsyncWebServerRequest *request);
void handleScriptJS(AsyncWebServerRequest *request);
void handleBootstrap(AsyncWebServerRequest *request);
void handleLog(AsyncWebServerRequest *request);
void handleFetch(AsyncWebServerRequest *request);

void setupWebServer(const char* ssid, const char* password);


#endif