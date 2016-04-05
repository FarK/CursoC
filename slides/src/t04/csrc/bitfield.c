struct frame {
	uint16_t data_cmd  : 1;
	uint16_t address   : 2;
	uint16_t data_len  : 4;
	uint16_t           : 1;
	uint16_t payload   : 8;
};
