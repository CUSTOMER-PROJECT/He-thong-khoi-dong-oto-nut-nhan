
/* Định nghĩa các chân linh kiện */
#define NUT_NHAN  4
#define RELAY     5
#define LED_ACC   6
#define LED_ON    7

/* Định nghĩa các macro */
#define BAT true
#define TAT false

/* Các biến toàn cục */
int SoLanNhanNut = 0;
int ThoiGianNhanNut = 0;
int flag = 0;

/* Các hàm chức năng (tổng quát) */
bool Kiem_Tra_Nut_Nhan();
void Bat_Relay();
void Tat_Relay();
void Bat_Led(int Led);
void Tat_Led(int Led);
//void Dieu_Khien_Led(bool TrangThai); // Có thể dùng hàm Dieu_Khien_Led để thay thể cho hàm Bat_Relay và Tat_Relay
//void Dieu_Khien_Led(int Led, bool TrangThai); // Có thể dùng hàm Dieu_Khien_Led để thay thể cho hàm Bat_Led và Tat_Led

void setup ()
{
  Serial.begin(9600);
  pinMode(NUT_NHAN, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(LED_ACC, OUTPUT);
  pinMode(LED_ON, OUTPUT);
}

void loop ()
{
  if (Kiem_Tra_Nut_Nhan() == true)
  {
    ThoiGianNhanNut = 0;
    
    while (Kiem_Tra_Nut_Nhan() == true)
    {
      ++ThoiGianNhanNut;
      delay(100);
      if (SoLanNhanNut == 2 && flag == 0 && ThoiGianNhanNut > 2)
      {
//        Serial.println("Bat relay");
        Bat_Relay();
        delay(550);
        flag = 1;
      }
    }
    
    SoLanNhanNut++;
    
    if (SoLanNhanNut == 4 && ThoiGianNhanNut < 3)
    {
      SoLanNhanNut--;
    }
//    Serial.print("Lan nhan nut: ");
//    Serial.println(SoLanNhanNut);
  }
   
  switch (SoLanNhanNut)
  {
    case 1:
      {
//        Serial.println("Bat led ACC");
        Bat_Led(LED_ACC);
        break;
      }
    case 2:
      {
//        Serial.println("Bat led ON");
        Bat_Led(LED_ON);
        flag = 0;
        break;
      }
    case 3:
      {
//        Serial.println("Tat relay");
        Tat_Relay();
        break;
      }
    case 4:
      {
        Tat_Led(LED_ACC);
        Tat_Led(LED_ON);
        Tat_Relay();
//        Serial.println("Tat het tat ca");
        SoLanNhanNut = 0;
        break;
      }
    default: 
      break;
  }
}

/* Các hàm chức năng (chi tiết) */
bool Kiem_Tra_Nut_Nhan()
{
  if (digitalRead(NUT_NHAN) == HIGH)
    return true;
  return false;
}
void Bat_Relay()
{
  digitalWrite(RELAY, HIGH);
}
void Tat_Relay()
{
  digitalWrite(RELAY, LOW);
}
void Bat_Led(int Led)
{
  digitalWrite(Led, HIGH);
}
void Tat_Led(int Led)
{
  digitalWrite(Led, LOW);
}
//void Dieu_Khien_Led(int Led, bool TrangThai)
//{
//  if (TrangThai == BAT)
//    digitalWrite(Led, HIGH);
//  else
//    digitalWrite(Led, LOW);
//}
//void Dieu_Khien_Led(bool TrangThai)
//{
//  if (TrangThai == BAT)
//    digitalWrite(RELAY, HIGH);
//  else
//    digitalWrite(RELAY, LOW);
//}
