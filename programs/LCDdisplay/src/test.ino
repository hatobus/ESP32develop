#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// コンパイル時にヘッダーファイルが適切に編集されていない場合に
// "Height incorrect, please fix Adafruit_SSD1306.h!"
// というエラーを表示するための記述
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define pulsein 13
#define pulseout 12

// RSTピンがない互換品を使用するので-1を指定
Adafruit_SSD1306 display(-1);

void setup() {
//  int SDA = 23;
//  int SCL = 25;
//  Wire.begin(SDA, SCL);
// I2Cアドレスは使用するディスプレイに合わせて変更する
  pinMode(pulsein, INPUT);
  pinMode(pulseout, OUTPUT);
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {

  double dist=0;

  dist = distget();
  
  if(dist > 200) dist = 200;
  // 画面表示をクリア
  display.clearDisplay();

  // テキストサイズを設定
  display.setTextSize(3);
  // テキスト色を設定
  display.setTextColor(WHITE);
  // テキストの開始位置を設定
  display.setCursor(0, 10);

  // 1行目に"Hello"を表示
  display.println("Dist :");
  // 2行目に"World!"を表示
  display.print(dist);

  display.println(" cm");

  // 描画バッファの内容を画面に表示
  display.display();

  delay(100);
}

double distget(){
    int delayms = 10;
    double dist = 0;

    digitalWrite(pulseout, LOW);
    delayMicroseconds(2);
    
    digitalWrite(pulseout, HIGH);
    delayMicroseconds(delayms);
    
    digitalWrite(pulseout, LOW);
    dist = pulseIn(pulsein, HIGH);

    if(dist > 0){
        dist = dist / 2;
        dist = dist * 340 * 100/1000000;
        Serial.println("Distance :");
        Serial.println(dist);
        Serial.println(" cm ");    
    }

    return dist;
}
