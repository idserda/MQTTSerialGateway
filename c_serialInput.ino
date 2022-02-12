void SerialMessageReceived(String message)
{
  //Message is send to state topic
  message.trim(); //remove any spaces
  MQTTclient.publish(MQTT_STATE_TOPIC, message.c_str()); 
}
