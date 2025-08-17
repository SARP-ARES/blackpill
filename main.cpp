#include "mbed.h"
#include "EUSBSerial.h"
#include "string.h"
#define BLINKING_RATE_US 500000 // 0.5 second
#define SLAVE_ADDR 0x02 << 1
#define SLAVE_C_ADDR 0x01 << 1 

DigitalOut led(PC_13);
I2C master(PB_9, PB_8);
I2CSlave slave(PB_9,PB_8);
EUSBSerial pc;
Timer t; 

// Board A main
int main() {

    char msg_buf[32];
    char recieveBuf[32];
    char data_b = 1;
    char data_c = 1;

    while (true) {
        
        if(pc.readline(msg_buf, sizeof(msg_buf))){
            
            if(strcmp(msg_buf, "wb") == 0) {
                led = !led;
                wait_us(250000);
                led = !led;
                int ack = master.write(SLAVE_ADDR, &data_b, sizeof(data_b));
                if(ack != 0){
                    pc.printf("Slave B did not ack\n");
                }
                data_b = (data_b == 1) ? 0 : 1;
            }

            if(strcmp(msg_buf, "rb") == 0){
                led = !led;
                wait_us(500000);
                led = !led;
                int ack = master.read(SLAVE_ADDR, recieveBuf, 1);
                wait_us(25);
                if(ack == 0) {
                    pc.printf("\n======================\n %u \n=====================\n", (unsigned char)recieveBuf[0]);
                } else {
                    pc.printf("Slave B did not ack\n");
                }
            }

            if(strcmp(msg_buf, "wc") == 0) {
                led = !led;
                wait_us(250000);
                led = !led;
                int ack = master.write(SLAVE_C_ADDR, &data_c, sizeof(data_c));
                if(ack != 0){
                    pc.printf("Slave C did not ack\n");
                }
                data_c = (data_c == 1) ? 0 : 1;
            }

            if(strcmp(msg_buf, "rc") == 0){
                led = !led;
                wait_us(500000);
                led = !led;
                int ack = master.read(SLAVE_C_ADDR, recieveBuf, 1);
                wait_us(25);
                if(ack == 0) {
                    pc.printf("\n======================\n %u \n=====================\n", (unsigned char)recieveBuf[0]);
                } else {
                    pc.printf("Slave C did not ack\n");
                }
            }

        }
    }
}

// // Board B main
// int main() {
//     slave.address(SLAVE_ADDR);

//     char write_data[1] = {0x01};  // single byte to send
//     char recv_buf[1];             // single-byte buffer for master writes

//     while (true) {
//         int event = slave.receive();

//         switch (event) {
//             case I2CSlave::WriteAddressed: {
//                 // Read exactly 1 byte sent by master
//                 int err = slave.read(recv_buf, 1);
//                 if (err == 0) { // successful read
//                     if (recv_buf[0] == 0) {
//                         led = 1; // LED ON
//                     } else if (recv_buf[0] == 1) {
//                         led = 0; // LED OFF
//                     }
//                 }
//                 break;
//             }

//             case I2CSlave::ReadAddressed: {
//                 // Immediately send exactly 1 byte to master
//                 slave.write(write_data, 1);
//                 write_data[0]++; // increment for next read
//                 break;
//             }

//             default:
//                 // No event; just continue
//                 break;
//         }
//     }
// }

// Board C main
// int main() {
//     slave.address(SLAVE_C_ADDR);

//     char write_data[1] = {0x01};  // single byte to send
//     char recv_buf[1];             // single-byte buffer for master writes

//     while (true) {
//         int event = slave.receive();

//         switch (event) {
//             case I2CSlave::WriteAddressed: {
//                 // Read exactly 1 byte sent by master
//                 int err = slave.read(recv_buf, 1);
//                 if (err == 0) { // successful read
//                     if (recv_buf[0] == 0) {
//                         led = 1; // LED ON
//                     } else if (recv_buf[0] == 1) {
//                         led = 0; // LED OFF
//                     }
//                 }
//                 break;
//             }

//             case I2CSlave::ReadAddressed: {
//                 // Immediately send exactly 1 byte to master
//                 slave.write(write_data, 1);
//                 write_data[0]++; // increment for next read
//                 break;
//             }

//             default:
//                 // No event; just continue
//                 break;
//         }
//     }
// }

