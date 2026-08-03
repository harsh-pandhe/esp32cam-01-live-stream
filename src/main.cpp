#include "esp_camera.h"
#include <WiFi.h>
#include "mbedtls/base64.h"

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define LED_FLASH_GPIO     4

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_FLASH_GPIO, OUTPUT);
  digitalWrite(LED_FLASH_GPIO, LOW);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA; // 640x480 for fast 100% reliable decode
    config.jpeg_quality = 10;
    config.fb_count = 1;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_camera_init(&config);
  
  sensor_t * s = esp_camera_sensor_get();
  if (s) {
    s->set_brightness(s, 1);
    s->set_contrast(s, 1);
    s->set_sharpness(s, 1);
    s->set_whitebal(s, 1);
    s->set_exposure_ctrl(s, 1);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'C') {
      digitalWrite(LED_FLASH_GPIO, HIGH);
      delay(200);
      camera_fb_t * fb = esp_camera_fb_get();
      digitalWrite(LED_FLASH_GPIO, LOW);

      if (fb) {
        size_t b64_len = 0;
        mbedtls_base64_encode(NULL, 0, &b64_len, fb->buf, fb->len);
        unsigned char * b64_buf = (unsigned char *)malloc(b64_len + 1);
        if (b64_buf) {
          mbedtls_base64_encode(b64_buf, b64_len, &b64_len, fb->buf, fb->len);
          b64_buf[b64_len] = '\0';
          Serial.printf("B64_START:%u\n", (unsigned int)b64_len);
          Serial.println((char*)b64_buf);
          Serial.println("B64_END");
          free(b64_buf);
        }
        esp_camera_fb_return(fb);
      }
    }
  }
}
