#include <esp_now.h>
#include <WiFi.h>

// Structure to receive data
// Must match the sender structure
typedef struct struct_message {
    int distance;
} struct_message;

struct_message myData;

// Callback function to receive data
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    // Use myData.distance here to update display
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
