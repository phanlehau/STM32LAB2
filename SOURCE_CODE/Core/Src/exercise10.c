#include "exercise10.h"

uint8_t matrix_buffer[8] = {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66};
GPIO_TypeDef* ROW_PORT[8] = {ROW0_GPIO_Port, ROW1_GPIO_Port, ROW2_GPIO_Port, ROW3_GPIO_Port, ROW4_GPIO_Port, ROW5_GPIO_Port, ROW6_GPIO_Port, ROW7_GPIO_Port};
uint16_t ROW_PIN[8] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin, ROW5_Pin, ROW6_Pin, ROW7_Pin};
GPIO_TypeDef* COL_PORT[8] = {ENM0_GPIO_Port, ENM1_GPIO_Port, ENM2_GPIO_Port, ENM3_GPIO_Port, ENM4_GPIO_Port, ENM5_GPIO_Port, ENM6_GPIO_Port, ENM7_GPIO_Port};
uint16_t COL_PIN[8] = {ENM0_Pin, ENM1_Pin, ENM2_Pin, ENM3_Pin, ENM4_Pin, ENM5_Pin, ENM6_Pin, ENM7_Pin};
void init_exercise10(){
}

void updateLEDMatrix() {
    for (int i = 0; i < 8; i++) {
        uint8_t first_bit = (matrix_buffer[i] >> 7) & 1; // Get the first bit
        matrix_buffer[i] = matrix_buffer[i] << 1;       // Shift left
        if (first_bit == 1) {
            matrix_buffer[i] |= 0b00000001;               // Set the LSB if the first bit was 1
        }
    }
}

void displayLEDMatrix() {
    for (int i = 0; i < 8; i++) {
        // Vô hiệu hóa tất cả các hàng trước
        for (int k = 0; k < 8; k++) {
            HAL_GPIO_WritePin(ROW_PORT[k], ROW_PIN[k], GPIO_PIN_SET);
        }

        // Kích hoạt hàng hiện tại
        HAL_GPIO_WritePin(ROW_PORT[i], ROW_PIN[i], GPIO_PIN_RESET); // Đặt hàng hiện tại thành LOW

        // Ghi dữ liệu cột
        for (int j = 0; j < 8; j++) {
            HAL_GPIO_WritePin(COL_PORT[j], COL_PIN[j], (matrix_buffer[i] & (1 << (7 - j))) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        }

        // Độ trễ ngắn để giữ hàng hiện tại hiển thị
        HAL_Delay(1); // Điều chỉnh độ trễ này theo nhu cầu của bạn
    }
}


void exercise10_run(){
	updateLEDMatrix();
	displayLEDMatrix();
}



