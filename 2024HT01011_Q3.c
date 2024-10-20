#include <LPC23xx.h> // Include the header file for LPC2378

void setup_timer() {
    // Step 1: Enable Timer 0
    PCONP |= (1 << 1); // Power on Timer 0 by setting bit 1 in the Power Control for Peripherals register (PCONP)

    // Step 2: Set Timer Mode
    T0CTCR = 0x0; // Set Timer 0 to Timer Mode (not Counter Mode)

    // Step 3: Load Prescaler
    T0PR = 0; // Set prescaler to 0 for maximum PCLK frequency (48 MHz in this case)

    // Step 4: Load Match Register
    T0MR0 = 96000000; // Load match register with 96,000,000 for a 2-second delay (48 MHz * 2 seconds)

    // Step 5: Set Match Control Register
    T0MCR = (1 << 0) | (1 << 1); // Configure Match Control Register to generate an interrupt and reset on match (MR0)

    // Step 6: Start Timer
    T0TCR = 0x1; // Start Timer 0 by setting bit 0 in the Timer Control Register (TCR)

    // Step 7: Wait for Timer Interrupt
    while (!(T0IR & 0x1)); // Wait for the MR0 interrupt flag to be set (indicating the timer has reached the match value)
    
    // Step 8: Clear Interrupt Flag
    T0IR = 0x1; // Clear the MR0 interrupt flag by writing a 1 to bit 0 in the Interrupt Register (IR)

    // Step 9: Stop Timer
    T0TCR = 0x0; // Stop Timer 0 by clearing bit 0 in the Timer Control Register (TCR)
}

int main() {
    setup_timer(); // Call the function to setup and start the timer

    // Your main code here
    while (1) {
        // Main loop
    }

    return 0;
}
