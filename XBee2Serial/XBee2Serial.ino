/*

*/
#include <XBee.h>
#include <ArduinoJson.h>

XBee xbee = XBee();
ZBRxIoSampleResponse ZBioSample = ZBRxIoSampleResponse();

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.begin(Serial1);
}

void loop() 
{
  xbee.readPacket();
  
  if (xbee.getResponse().isAvailable()) 
  {
    //Serial.println("Packet Available");
    if (xbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE) 
    {
      //Serial.println("Packet is in IO form");
      xbee.getResponse().getZBRxIoSampleResponse(ZBioSample);
      
      int address = ZBioSample.getRemoteAddress16();
      //Serial.print("Packet Address = ");
      //Serial.println(address);

      int data = ZBioSample.getAnalog(1); 
      //Serial.print("Packet Data = ");
      //Serial.println(data);
      
      //Encode JSON data
      const int capacity = JSON_OBJECT_SIZE(20);
      StaticJsonDocument<capacity> doc;
      
      doc["timestamp"] = "13:37";
      
      //JsonObject sensorValues = doc.createNestedObject("sensorValues");
      if(address == 28144) 
      {
        String prepend = "{\"ROUTER_1\": \"";
        String postpend = "\"}";
        String sensorValues = prepend + data + postpend;
        //Serial.print(sensorValues);
        char sensorValuesChar[sensorValues.length()];
        sensorValues.toCharArray(sensorValuesChar, sensorValues.length());
        doc["sensorValues"] = sensorValuesChar;
      }
      if(address == 14552) 
      {
        String prepend = "{\"ROUTER_2\": \"";
        String postpend = "\"}";
        String sensorValues = prepend + data + postpend;
        //Serial.print(sensorValues);
        char sensorValuesChar[sensorValues.length()];
        sensorValues.toCharArray(sensorValuesChar, sensorValues.length());
        doc["sensorValues"] = sensorValuesChar;
      }
      if(address == -809) 
      {
        String prepend = "{\"ROUTER_3\": \"";
        String postpend = "\"}";
        String sensorValues = prepend + data + postpend;
        //Serial.print(sensorValues);
        char sensorValuesChar[sensorValues.length()];
        sensorValues.toCharArray(sensorValuesChar, sensorValues.length());
        doc["sensorValues"] = sensorValuesChar;
      }
    
      //Convert JSON to string and save to postData
      String postData;
      serializeJson(doc, postData);
      Serial.println(postData);
  
    }
  }
}
