#include <IRremote.h>
#include "SHT1x.h"
#include "U8glib.h"

//unsigned int rawCodes_ac_24[199] = {4500,4400,600,1600,550,550,550,1650,550,1650,550,500,600,500,600,1600,550,550,550,550,550,1650,550,500,600,500,600,1600,550,1650,550,500,600,1650,550,1600,600,500,550,550,550,1650,550,1650,550,1600,600,1600,550,1650,550,500,600,1600,600,1600,600,500,550,550,550,550,550,550,550,500,600,500,600,1600,600,500,550,550,550,550,550,550,550,500,600,500,600,1600,600,500,550,1650,550,1650,550,1600,600,1600,600,1600,550,1650,550,5250,4500,4400,600,1600,600,500,550,1650,550,1650,550,500,600,500,600,1600,600,500,550,550,550,1650,550,500,600,500,600,1600,600,1600,550,550,550,1650,550,1600,600,500,600,500,600,1600,550,1650,550,1600,600,1600,600,1600,550,550,550,1650,550,1600,600,500,600,500,550,550,550,550,550,550,550,500,600,1600,600,500,600,500,550,550,550,550,550,550,550,500,600,1600,600,500,600,1600,550,1650,550,1650,550,1600,600,1600,550,1650,550};
//unsigned int rawCodes_ac_28[199] = {4450,4450,550,1600,600,500,600,1600,600,1600,550,550,550,550,550,1600,600,500,600,500,600,1600,550,550,550,550,550,1650,550,1600,600,500,600,1600,550,1650,550,500,600,500,600,1600,600,1600,550,1650,550,1650,550,1600,600,500,600,1600,550,1650,550,500,600,500,600,500,600,500,600,500,550,1650,550,500,600,500,600,550,550,500,600,500,600,500,550,550,550,550,550,1650,550,1650,550,1600,600,1600,550,1650,550,1650,550,1600,600,5250,4450,4450,550,1650,550,500,600,1650,550,1600,600,500,550,550,550,1650,550,500,600,500,600,1600,600,500,550,550,550,1650,550,1650,550,500,600,1600,600,1600,550,550,550,500,600,1650,550,1600,600,1600,550,1650,550,1650,550,500,600,1600,550,1650,550,550,550,500,600,500,600,500,600,500,600,1600,550,550,550,550,550,500,600,500,600,500,600,500,600,500,600,500,550,1650,550,1650,550,1600,600,1600,550,1650,550,1650,550,1600,600};
//unsigned int rawCodes_ac_29[199] = {4500,4400,600,1600,550,550,550,1650,550,1650,550,500,600,500,600,1600,550,550,550,550,550,1650,550,500,600,500,600,1600,550,1650,550,500,600,1650,550,1600,600,500,550,550,550,1650,550,1650,550,1600,600,1600,550,1650,550,500,600,1600,600,1600,600,500,550,550,550,550,550,550,550,500,550,1650,550,550,550,1650,550,550,550,550,550,550,550,500,600,500,550,550,550,1650,550,550,550,1650,550,1600,600,1600,600,1600,550,1650,550,5250,4500,4400,600,1600,550,550,550,1650,550,1650,550,500,600,500,600,1600,550,550,550,550,550,1650,550,500,600,500,600,1600,550,1650,550,500,600,1650,550,1600,600,500,550,550,550,1650,550,1650,550,1600,600,1600,550,1650,550,500,600,1600,600,1600,600,500,550,550,550,550,550,550,550,500,550,1650,550,550,550,1650,550,550,550,550,550,550,550,500,600,500,550,550,550,1650,550,550,550,1650,550,1600,600,1600,600,1600,550,1650,550};

IRsend irsend;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

#define dataPin 10
#define clockPin 11
SHT1x sht1x(dataPin, clockPin);
  
float temp;
float temp_f;
float humidity;

int ac_temp;

void display()
{ 
  u8g.setFont(u8g_font_profont11);
  u8g.drawStr(0, 12, "Temperature:");
  u8g.setFont(u8g_font_profont22);
  u8g.setPrintPos(0, 30);
  u8g.print(temp);
  u8g.setFont(u8g_font_profont11);
  u8g.drawStr(64, 24, "C");
  u8g.setPrintPos(76, 24);
  u8g.print(temp_f);
  u8g.drawStr(106, 24, "F");
  
  u8g.setFont(u8g_font_profont11);
  u8g.drawStr(0, 44, "Humidity:");
  u8g.setFont(u8g_font_profont22);
  u8g.setPrintPos(0, 62);
  u8g.print(humidity);
  u8g.setFont(u8g_font_profont11);
  u8g.drawStr(64, 54, "%");
}

void controlac()
{
  if (temp > 28.5 && ac_temp != 28)
  {
    irsend.sendMidea(0xb24d9f60807fLL, 48);
    ac_temp = 28;
  }
  else if (temp < 26.2 && ac_temp != 29)
  {
    irsend.sendMidea(0xb24d9f60a05fLL, 48);
    ac_temp = 29;
  }
}

void setup()
{
  // IR send
  // irsend.sendMidea(0xb24d9f6040bfLL, 48);
  // delay(4000);
  // irsend.sendMidea(0xb24d9f60807fLL, 48);
  // delay(4000);
  // irsend.sendMidea(0xb24d9f60a05fLL, 48);
}

void loop()
{
  // Read values from the sensor
  temp = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();

  controlac();

  // picture loop
  u8g.firstPage();  
  do {
    display();
  } while( u8g.nextPage() );
  
  delay(1000);
}
