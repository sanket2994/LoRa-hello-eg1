#include <SPI.h>
#include <RH_RF95.h>

#define SS_RFM95 10
#define INT_RFM95 2
#define RST_RFM95 9

#define FREQ_RFM95 915.0
RH_RF95 rf95(SS_RFM95,INT_RFM95);

char buff[]="Hello BRO!!! ";
uint8_t recvBuff[20];
 bool chkAck;
void setup() {
  pinMode(RST_RFM95,OUTPUT);
  digitalWrite(RST_RFM95,HIGH);

  Serial.begin(38600);
  

  digitalWrite(RST_RFM95,LOW);
  delay(10);
  digitalWrite(RST_RFM95,HIGH);
  delay(10);

  while(!rf95.init())
  {
      Serial.println("Initializing LoRa module......");
  }
    Serial.println("Initialization of LoRa module complete");

    if(!rf95.setFrequency(FREQ_RFM95))
    {
      Serial.println("Frequency not set");
      while(1);
    }

    Serial.println("The frequency is set :");
    Serial.println(FREQ_RFM95,DEC);

    rf95.setTxPower(5,false);
    Serial.println();
  
}

uint8_t len = sizeof(recvBuff);
void loop() {
 rf95.send(buff,sizeof(buff));
 rf95.waitPacketSent();

 //check if acknowledgement is received

  chkAck=rf95.waitAvailableTimeout(1000);
  if(chkAck)
  {
    rf95.recv(recvBuff,&len);
    Serial.println("The received ack is: ");
    Serial.println((char*)recvBuff);
  }
  else
    Serial.println("Acknowledgement not Received");

 delay(5000);
}
