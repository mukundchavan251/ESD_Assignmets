#include <stdint.h>
#include "lcd.h"
#include <lpc23xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function for delay
void wait(int time) {
    int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1000; j++);
}

int main() {
    char voltage_display[20] = "";
    uint32_t adc_value = 0;
    float voltage = 0;

    // Initialize the ADC
    PCONP |= (1 << 12);        // Turn on the ADC power
    PINSEL1 |= (1 << 14);      // Configure P0.23 as AD0.0
    PINSEL1 &= ~(1 << 15);     
    AD0INTEN |= (1 << 0);      // Enable interrupt for AD0.0

    // Configure the ADC: select AD0.0, 4 MHz clock, 10-bit resolution, operational mode
    AD0CR &= ~(1 << 0);        // Clear the channel select bits
    AD0CR |= (1 << 9);         // Set the clock divider to achieve a 4 MHz clock
    AD0CR |= (1 << 16);        // Disable BURST mode (manual control)
    AD0CR |= (1 << 21);        // Enable the ADC

    // Initialize the LCD
    lcd_init();
    lcd_clear();

    // Display BITS ID on the first row
    set_cursor(0, 0);
    lcd_print((unsigned char *)"BITS 2024HT01011");

    while (1) {
        set_cursor(0, 1);

        // Wait for the ADC conversion to complete
        while (!(AD0STAT & (1 << 0))) {};

        // Retrieve the ADC result
        adc_value = (AD0DR0 & 0x0000FFC0) >> 6;

        // Convert the ADC value to voltage
        voltage = ((adc_value / 1023.0) * 3.3);

        // Format the voltage as a string for display
        sprintf(voltage_display, "%.2fV ", voltage);

        // Display the voltage and date on the second row
        lcd_print((const unsigned char *)voltage_display);
        lcd_print((const unsigned char *)"Date:16/10");

        wait(1);
    }
}
