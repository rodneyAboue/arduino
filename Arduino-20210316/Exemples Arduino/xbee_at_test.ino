
char xbee_buffer_in[200];
char xbee_buffer_out[200];

void setup() {
	Serial.begin(9600);
	delay(2000);
	Serial.println("Arduino OK");
}

void loop() {


	//lecture nouvelle commande
	if (Serial.available()) {
		int c = Serial.read();
		if (c == '\n') {
			sprintf(xbee_buffer_out,"Arduino : %s",xbee_buffer_in);
			Serial.println(xbee_buffer_out);
			xbee_buffer_in[0] = 0;
		}
		else {
			int pos = strlen(xbee_buffer_in);
			xbee_buffer_in[pos] = c;
			xbee_buffer_in[pos+1] = 0;
		}
	}

}

