#include<SPI.h>
#include<RH_RF95.h>

#define RST_RFM95 9
#define SS_RFM95 10
#define INT_RFM95 2

#define FREQ_RFM95 915.0

RH_RF95 rf95;
uint8_t buff[50];
uint8_t sendAck[]="ok bro i got the msg";
uint8_t len=sizeof(buff);
void setup() {
  pinMode(RST_RFM95,OUTPUT);
  digitalWrite(RST_RFM95,HIGH);

  Serial.begin(38400);

  digitalWrite(RST_RFM95,LOW);
  delay(10);
  digitalWrite(RST_RFM95,HIGH);
  delay(10);
  while(!rf95.init())
  {
    Serial.println("initialization in progress");
  }
    Serial.println("Initialized the LoRa Receiver");

    if(!rf95.setFrequency(FREQ_RFM95))
    {
        Serial.println("problem settin freq\n");
        while(1);
    }
    Serial.println("Frequency set to:");
    Serial.println(FREQ_RFM95,DEC);

    rf95.setTxPower(5,false);
}

void loop() {
  while(!rf95.available());
  //int len=sizeof(buff);
  if(rf95.recv(buff,&len))
  {
    Serial.println("The msg received is");
    Serial.println((char*)buff);

    rf95.send(sendAck,sizeof(sendAck));
    rf95.waitPacketSent();
    
  }
  
}
