#include "RFID.h"

int card_detected() {
    // Simulate card detection
    // In a real implementation, this would interface with RFID hardware
    // For now, we just return a dummy card ID
    CD = 1; // Set the flag to indicate a card has been detected
    return 0x00010002; // Dummy card ID BH card 2
}