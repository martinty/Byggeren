#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

uint8_t CAN_init();

enum CAN_id {
	GAMESETTINGS = 1, CONTROLLERS,			// NODE1
	IR = 10									// NODE2
};

typedef struct{
	enum CAN_id ID;
	int lenght;
	uint8_t data[8];

} CAN_message; 


void CAN_transmit(CAN_message* message);
CAN_message CAN_receive();
CAN_message CAN_getMessage();
int CAN_hasMessage();
 

#define RXWAR	0x02
#define TXWAR	0x04

#endif /* CAN_DRIVER_H_ */