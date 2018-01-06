#include<LiquidCrystal.h>
#include<Keypad.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS=4;
const byte COLS=4;
const char keys[ROWS][COLS]= {
 { '1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
  
};
 byte rowPins[ROWS]={7,8,9,10};
 byte colPins[COLS]={0,1,6,13};
String p="",ps="";
int flag=0;
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
 lcd.print("ENTER PASSWORD");
 delay(2000);
 lcd.setCursor(0,1);
 pinMode(A0,OUTPUT);
 digitalWrite(A0,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
char key=keypad.getKey();
if(key){
if(p.length()<4 && key!='#' && flag==0)
{
  p=p+key;
 lcd.print('*');
}
else if(flag==0)
{
  flag=1;
 lcd.clear();
 lcd.print("Password set");
 delay(3000);
 lcd.clear();
 lcd.print("Enter passwword");
 lcd.setCursor(0,1);
 delay(100);
}
else if(flag==1)
{
  if(key!='#')
  ps=ps+key;
  lcd.print('*');
  if(ps.length()>=4 || key=='#')
  {
    
    if(ps.equals(p))
    {
      ps="";
      lcd.clear();
      lcd.print("Password Accepted");
      lcd.setCursor(0,1);
      lcd.print("Door Opened");
      digitalWrite(A0,HIGH);
      delay(1000);
      flag=2;
    }
    else
    {
      ps="";
      lcd.clear();
      lcd.print("Wrong Password");
      delay(3000);
       lcd.setCursor(0,1);
      lcd.print("Access Denied");
      delay(5000);
      lcd.clear();
      lcd.print("ENTER PASSWORD");
      delay(200);
      lcd.setCursor(0,1);
    }
  }
}
else if(flag==2)
{
  if(key=='*')
  {
    p="";
    flag=0;
    lcd.clear();
    lcd.print("Password Reset");
    delay(2000);
    digitalWrite(A0,LOW);
    lcd.clear();
    lcd.print("Enter password");
    lcd.setCursor(0,1);
    delay(100);
  }
  else if(key=='#')
  {
    flag=1;
    lcd.clear();
    lcd.print("Password set");
    delay(5000);
    digitalWrite(A0,LOW);
 lcd.clear();
 lcd.print("Enter passwword");
 lcd.setCursor(0,1);
 delay(500);
  }
}
}
}


