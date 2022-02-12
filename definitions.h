// a_mqtt
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

// c_serialInput
void SerialMessageReceived(String message);

// d_subscribtions
void subscribeTo(String Topic);
