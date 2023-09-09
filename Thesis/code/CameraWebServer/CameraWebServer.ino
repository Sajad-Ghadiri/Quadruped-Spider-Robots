#include "esp_camera.h"
#include <WiFi.h>
#include "camera_pins.h"

#define CAMERA_MODEL_AI_THINKER // Has PSRAM
const char* ssid = "IRLab";
// The password is hide for personal reason :)
const char* password = "##########";
void startCameraServer();
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  camera_config_t config;
  if(psramFound()){
    config.frame_size = FRAMESIZE_QXGA; // UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA; // SVGA
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
