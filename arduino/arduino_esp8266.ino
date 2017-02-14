#include "uartWIFI.h"
#include <SoftwareSerial.h>
WIFI wifi;
#define SSID       "Codemobiles" // ชื่อ ssid
#define PASSWORD   "cccccccc" // รหัสผ่าน
extern int chlID;  //client id(0-4)

int led = 13;

void setup()
{
  pinMode(led,OUTPUT);
  digitalWrite(led,0);
  wifi.begin(); 
  bool b = wifi.Initialize(STA, SSID, PASSWORD);
  delay(8000);  //หน่วงเวลาให้เครื่องเชื่อมกับ wifi
  wifi.confMux(1);
  delay(200);
  if(wifi.confServer(1,8080)){ // เชื่อมต่อ wifi สำเร็จ ให้แสดงไฟสถานะ
    digitalWrite(led,1);
    delay(2000);
    digitalWrite(led,0);
  }
}
void loop()
{

  char buf[100];
  int iLen = wifi.ReceiveMessage(buf);
  if(iLen > 0)
  {
    if (strcmp(buf, "ON") == 0) // ถ้ามีคำว่า ON จะเปิด/ปิด LED
    {
      if(digitalRead(led)==0){
        digitalWrite(led,1);
        wifi.Send(chlID,"LED ON ");
        // ส่งข้อมูลที่ต้องการให้กับ client
      }
      else{
        digitalWrite(led,0);
        wifi.Send(chlID,"LED OFF");
        // ส่งข้อมูลที่ต้องการให้กับ client
      }
    }
  
  }
}

