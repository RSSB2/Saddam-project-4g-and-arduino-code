#include<SoftwareSerial.h>
SoftwareSerial Serial1(3, 2);

#include<LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

#define light 13
#define tv 12
#define fan 4


int sms_flag3, sms_flag2, sms_flag1, sms_flag;
int light_flag, tv_flag, fan_flag, all_flag;

void setup()
{
  //delay(15000);
  
  Serial1.begin(115200);
  Serial1.println("AT+IPR=9600");
  Serial1.end();
  Serial1.begin(9600);
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(light, OUTPUT);
  pinMode(tv, OUTPUT);
  pinMode(fan, OUTPUT);
  
  Serial1.println("ATE0");
  delay(500);
  
  

  lcd.setCursor(0, 0);
  lcd.print("GSM Control Home");
  lcd.setCursor(0, 1);
  lcd.print("   Automaton    ");
  delay(2000);
  lcd.clear();
  lcd.print("BABA TECHNICAL");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("  KNOWLEDGE    ");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fan   Light  TV ");
  lcd.setCursor(0, 1);
  lcd.print("OFF    OFF   OFF ");
  
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Fan   Light  TV");
  
  //Serial1.println("AT");
  //delay(500);
  serialEvent();
 if (light_flag == 1 and sms_flag == 0)
  {
    senssms("Light Turned ON");
    sms_flag = 1;
  }
  else if (light_flag == 0 and sms_flag == 1)
  {
   senssms("Light Turned OFF");
    sms_flag = 0;
  }

  if (tv_flag == 1 and sms_flag1 == 0)
  {
   senssms("(tv Turned ON");
    sms_flag1 = 1;
  }
  else if (tv_flag == 0 and sms_flag1 == 1)
  {
   senssms("tv Turned OFF");
    sms_flag1 = 0;
  }
  if (fan_flag == 1 and sms_flag2 == 0)
  {
  senssms("fan Turned ON");
    sms_flag2 = 1;
  }
  else if (fan_flag == 0 and sms_flag2 == 1)
  {
   senssms("fan Turned OFF");
   sms_flag2 = 0;
  }
  if (all_flag == 1 and sms_flag3 == 0)
  {
   senssms("all Turned ON");
   sms_flag3 = 1;
   lcd.setCursor(0,1); 
   lcd.print("ON     ON    ON  ");
   delay(200);
  }
  if (all_flag == 1 and sms_flag3 == 0)
  {
   senssms("all Turned OFF");
   sms_flag3 = 0;
   lcd.setCursor(0,1); 
   lcd.print("OFF   OFF    OFF  ");
   delay(200);
  }
}
void serialEvent()
{
  
  String str = "";
  while (Serial1.available())
  {
    char ch = Serial1.read();
    str += ch;
    Serial.print(ch);

    if (str.indexOf("LIGHT ON") >= 0)
    {
      digitalWrite(light, HIGH);
      light_flag = 1;
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(200);
      
      
    }

    else if (str.indexOf("LIGHT OFF")>=0)
    {
      digitalWrite(light, LOW);
      light_flag = 0;
      lcd.setCursor(7,1); 
      lcd.print("OFF    ");
      delay(200);
      
    }

   else if (str.indexOf("TV ON")>=0)
    {
     digitalWrite(tv, HIGH);
      tv_flag = 1;
      lcd.setCursor(13, 1);
      lcd.print("ON    ");
      delay(200);
    }

    else if (str.indexOf("TV OFF")>=0)
    {
      digitalWrite(tv, LOW);
      tv_flag = 0;
      lcd.setCursor(13, 1);
      lcd.print("OFF    ");
      delay(200);
    }
    else if (str.indexOf("FAN ON")>=0)
    {
     digitalWrite(fan, HIGH);
      fan_flag = 1;
      lcd.setCursor(0, 1);
      lcd.print("ON    ");
      delay(200);
    }

    else if (str.indexOf("FAN OFF")>=0)
    {
      digitalWrite(fan, LOW);
      fan_flag = 0;
      lcd.setCursor(0, 1);
      lcd.print("OFF    ");
      delay(200);
    }
    else if (str.indexOf("ALL ON")>=0)
    {
      digitalWrite(light, HIGH);
      digitalWrite(tv, HIGH);
      digitalWrite(fan, HIGH);
      all_flag = 1;
      lcd.setCursor(0,1); 
      lcd.print("ON     ON    ON  ");
      delay(200);
    }
     else if (str.indexOf("ALL OFF")>=0)
    {
      digitalWrite(light, LOW);
      digitalWrite(tv, LOW);
      digitalWrite(fan, LOW);
      all_flag = 0;
      lcd.setCursor(0,1); 
      lcd.print("OFF   OFF    OFF  ");
      delay(200);
    }
  }
}

void senssms(String msg)
{
  Serial.println("Sending SMS");
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.println("AT+CMGS=\"8802313594\""); // ;put numbner hrer
  delay(500);
  Serial1.print(msg);
  Serial1.write(26);
  delay(3000);
}
