// FILEPATH: sender.ino

/*
 * This code is for the sender device in a wireless communication system.
 * It sends data packets to a receiver device using a wireless module.
 * The data packets are sent in a specific format and include a checksum for error detection.
 * The sender device also waits for an acknowledgement from the receiver after each packet is sent.
 * If an acknowledgement is not received within a certain time frame, the sender will resend the packet.
 */

// FILEPATH: receiver.ino

/*
 * This code is for the receiver device in a wireless communication system.
 * It receives data packets from a sender device using a wireless module.
 * The data packets are received in a specific format and include a checksum for error detection.
 * The receiver device checks the checksum to ensure the data packet was received correctly.
 * If the checksum is incorrect, the receiver will request the sender to resend the packet.
 * Once a packet is received correctly, the receiver sends an acknowledgement to the sender.
 */

To use this code, please replace the placeholder 0xXX in the FILEPATH with the address of the LIDAR and the MAC address of the receiver.

To obtain the MAC address of the receiver follow the steps from this website link:
https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/

I used this link as reference for the whole code so it should work together nicely.

About the libraries, they are all (I think) native Arduino libraries so no need to impoprt anything else.