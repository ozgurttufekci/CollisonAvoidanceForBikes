#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};

// Structure to send data
typedef struct struct_message {
    int distance;
} struct_message;

struct_message myData;

// I2C Address of the LiDAR Sensor
// Replace with the address of your specific LiDAR sensor
const int LiDAR_Address = 0xXX;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Last Packet Send Status: ");
    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("Delivery Success");
    }
    else {
        Serial.println("Delivery Fail");
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_send_cb(OnDataSent);
    
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
           
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }

    // Initialize I2C communication
    Wire.begin(); // You can specify SDA and SCL pins if necessary

    // Setup LiDAR sensor (if necessary)
}

void loop() {
    // Read distance from LiDAR sensor
    Wire.beginTransmission(LiDAR_Address);
    // Depending on the sensor, I might need to write a command to it
    // Wire.write(COMMAND_BYTE);
    Wire.endTransmission();
    Wire.requestFrom(LiDAR_Address, 2); // Request 2 bytes of data

    if(Wire.available() >= 2) {
        int highByte = Wire.read();
        int lowByte = Wire.read();
        myData.distance = (highByte << 8) + lowByte; // Combine bytes
    }

    // Send data via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    }
    else {
        Serial.println("Error sending the data");
    }
    delay(2000); // Delay between readings
}
