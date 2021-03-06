#ifndef _ARDUINO_IO_H
#define _ARDUINO_IO_H

int canonicalizePin(int pin);
int pinToPort(int pin, ioportid_t *port, uint8_t *pad);
int canUsePin(int pin);
uint32_t palGetPadMode(ioportid_t port, uint8_t pad);

void arduinoIoInit(void);
void arduinoToneInit(void);

#endif /* _ARDUINO_IO_H */