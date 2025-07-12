//include settings//
#include <Keyboard.h>
#include <FastLED.h>

//MODE//
int SW_MODE = 1;//KEYの割当を変える 1 //コピー　ペースト　など 2-solidworks mode
int Anti_chattering_time=5;//チャタリング防止受付時間
int MODE_CHANGE_time=0;//モードチェンジカウント
int TIME_OUT=0;//タイムアウト
int Not_Touch=0;

//キーボード　関数とpin asainを紐づけ//
//LH//
const int KEY_LH = 15;//pin15指定　左上
int KEY_LH_A_cnt=0;//押している時間
int KEY_LH_B_cnt=0;//離している時間
int KEY_LH_PUSH_Flag=0;//連続入力防止
//SH//
const int KEY_SH = 14;//pin15指定　中上
int KEY_SH_A_cnt=0;//押している時間
int KEY_SH_B_cnt=0;//離している時間
int KEY_SH_PUSH_Flag=0;//連続入力防止
//RH//
const int KEY_RH = 13;//pin15指定 右上
int KEY_RH_A_cnt=0;//押している時間
int KEY_RH_B_cnt=0;//離している時間
int KEY_RH_PUSH_Flag=0;//連続入力防止
//LH//
const int KEY_LL = 12;//pin15指定　左下
int KEY_LL_A_cnt=0;//押している時間
int KEY_LL_B_cnt=0;//離している時間
int KEY_LL_PUSH_Flag=0;//連続入力防止
//SH//
const int KEY_SL = 11;//pin15指定　中下
int KEY_SL_A_cnt=0;//押している時間
int KEY_SL_B_cnt=0;//離している時間
int KEY_SL_PUSH_Flag=0;//連続入力防止
//RH//
const int KEY_RL = 10;//pin15指定 右下
int KEY_RL_A_cnt=0;//押している時間
int KEY_RL_B_cnt=0;//離している時間
int KEY_RL_PUSH_Flag=0;//連続入力防止

//LEDのpush前と後の色指定//
  #define numberOfLEDs 6//個数
  #define controlPin 5//pin指定
  int P_color[]= {60,130,130};//PUSH NOW{95,45,127}赤系紫
  int N_color[]= {130,130,130};//UN PUSH{70,130,130}//水色
  CRGB leds[numberOfLEDs];

void setup() {
//pinmode関数//
  pinMode(KEY_LH, INPUT_PULLUP);//15pin
  pinMode(KEY_SH, INPUT_PULLUP);//14pin
  pinMode(KEY_RH, INPUT_PULLUP);//13pin
  pinMode(KEY_LL, INPUT_PULLUP);//12pin
  pinMode(KEY_SL, INPUT_PULLUP);//11pin
  pinMode(KEY_RL, INPUT_PULLUP);//10pin

  pinMode(7, OUTPUT);//LED右
  pinMode(8, OUTPUT);//LED中
  pinMode(9, OUTPUT);//LED左
  pinMode(25,OUTPUT);//MODE用PICO LED

  digitalWrite(9,HIGH);//9初期値のLED　一番左
  digitalWrite(25,HIGH);//bord上のLEDを光らせる

//初期化//

  Keyboard.begin();
  //serial初期化//
  Serial.begin(9600);
  //LED//
  FastLED.addLeds<WS2812B, controlPin, GRB>(leds, numberOfLEDs);

  SW_MODE=1;

    // leds[0].r = 122;
    // leds[0].g = 122;
    // leds[0].b = 122;
     FastLED.show();
}
void loop() {
//モード切り替え処理//
if(Not_Touch==1){
if((digitalRead(15) == LOW )&&(digitalRead(14) == LOW )&&(digitalRead(13) == LOW )){//上3キー同時押してモード切り替え
 MODE_CHANGE_time=MODE_CHANGE_time+1;
 delay(10);//連続切り替え動作防止
 if(MODE_CHANGE_time>=100){
   if(SW_MODE<=2){//シフトアップ
    SW_MODE=SW_MODE+1;
   }else{
    SW_MODE=1;//3以上でリセット1へ
   }
//インジケータライトpin指定
   digitalWrite(7,LOW);
   digitalWrite(8,LOW);
   digitalWrite(9,LOW);
     if (SW_MODE == 1){
       digitalWrite(9,HIGH);//9
     }else if(SW_MODE == 2){
       digitalWrite(8,HIGH);//8
     }else if(SW_MODE == 3){
       digitalWrite(7,HIGH);//7
     }
    delay(1000);
  } 
}else{
  if(MODE_CHANGE_time!=0){//カウントを途中でやめて0でないときはリセット
   MODE_CHANGE_time=0;
  }
if(SW_MODE==1){//KEY MODE 1 ノーマルモード
//コピー//単品入力
  if(digitalRead(KEY_LH) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_LH_A_cnt<=50){
   KEY_LH_A_cnt=KEY_LH_A_cnt+1;}
   if(( KEY_LH_A_cnt >= Anti_chattering_time )&&(KEY_LH_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('c');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('c');

     KEY_LH_B_cnt=0;
     KEY_LH_PUSH_Flag=1;
   //押した色
     leds[0].r = P_color[0];
     leds[0].g = P_color[1];
     leds[0].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_LH_B_cnt<=50){
    KEY_LH_B_cnt=KEY_LH_B_cnt+1;}
    if( KEY_LH_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[0].r = N_color[0];
     leds[0].g = N_color[1];
     leds[0].b = N_color[2];
     FastLED.show();
     KEY_LH_A_cnt=0;
     KEY_LH_PUSH_Flag=0;
    }
  }
//ペースト//単品入力
  if(digitalRead(KEY_SH) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_SH_A_cnt<=50){
   KEY_SH_A_cnt=KEY_SH_A_cnt+1;}
   if(( KEY_SH_A_cnt >= Anti_chattering_time )&&(KEY_SH_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('v');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('v');

     KEY_SH_B_cnt=0;
     KEY_SH_PUSH_Flag=1;
  //押した色
     leds[1].r = P_color[0];
     leds[1].g = P_color[1];
     leds[1].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_SH_B_cnt<=50){
    KEY_SH_B_cnt=KEY_SH_B_cnt+1;}
    if( KEY_SH_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[1].r = N_color[0];
     leds[1].g = N_color[1];
     leds[1].b = N_color[2];
     FastLED.show();
     KEY_SH_A_cnt=0;
     KEY_SH_PUSH_Flag=0;
    }
  }
//BackSpace//連続入力
  if(digitalRead(KEY_RH) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_RH_A_cnt<=50){
   KEY_RH_A_cnt=KEY_RH_A_cnt+1;
   }else if(KEY_RH_A_cnt>=(Anti_chattering_time+30)){//30はチャタ防止を超過した時間で長押しと判断
    KEY_RH_PUSH_Flag=0;
   }
   if(( KEY_RH_A_cnt >= Anti_chattering_time )&&(KEY_RH_PUSH_Flag==0)){
     Keyboard.press(KEY_BACKSPACE);
     delayMicroseconds(100);
     Keyboard.release(KEY_BACKSPACE);
    
     KEY_RH_B_cnt=0;
     KEY_RH_PUSH_Flag=1;
    delay(50);
     //押した色
     leds[2].r = P_color[0];
     leds[2].g = P_color[1];
     leds[2].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_RH_B_cnt<=50){
    KEY_RH_B_cnt=KEY_RH_B_cnt+1;}
    if( KEY_RH_B_cnt >= Anti_chattering_time ){
    //通常色
     leds[2].r = N_color[0];
     leds[2].g = N_color[1];
     leds[2].b = N_color[2];
     FastLED.show();
     KEY_RH_A_cnt=0;
     KEY_RH_PUSH_Flag=0;
    }
  }
//ALT＋TABウインド切り替え//単品入力
  if(digitalRead(KEY_LL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_LL_A_cnt<=50){
   KEY_LL_A_cnt=KEY_LL_A_cnt+1;}
   if(( KEY_LL_A_cnt >= Anti_chattering_time )&&(KEY_LL_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_ALT);
     Keyboard.press(KEY_TAB);
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_ALT);
     Keyboard.release(KEY_TAB);

     KEY_LL_B_cnt=0;
     KEY_LL_PUSH_Flag=1;
  //押した色
     leds[3].r = P_color[0];
     leds[3].g = P_color[1];
     leds[3].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_LL_B_cnt<=50){
    KEY_LL_B_cnt=KEY_LL_B_cnt+1;}
    if( KEY_LL_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[3].r = N_color[0];
     leds[3].g = N_color[1];
     leds[3].b = N_color[2];
     FastLED.show();
     KEY_LL_A_cnt=0;
     KEY_LL_PUSH_Flag=0;
    }
  }
//Return//単品入力
  if(digitalRead(KEY_SL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_SL_A_cnt<=50){
   KEY_SL_A_cnt=KEY_SL_A_cnt+1;}
   if(( KEY_SL_A_cnt >= Anti_chattering_time )&&(KEY_SL_PUSH_Flag==0)){
     Keyboard.press(0xB0);//Enter code
     delayMicroseconds(100);
     Keyboard.release(0xB0);

     KEY_SL_B_cnt=0;
     KEY_SL_PUSH_Flag=1;
  //押した色
     leds[4].r = P_color[0];
     leds[4].g = P_color[1];
     leds[4].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_SL_B_cnt<=50){
    KEY_SL_B_cnt=KEY_SL_B_cnt+1;}
    if( KEY_SL_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[4].r = N_color[0];
     leds[4].g = N_color[1];
     leds[4].b = N_color[2];
     FastLED.show();
     KEY_SL_A_cnt=0;
     KEY_SL_PUSH_Flag=0;
    }
  }
//space//連続品力
 if(digitalRead(KEY_RL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_RL_A_cnt<=50){
   KEY_RL_A_cnt=KEY_RL_A_cnt+1;
   }else if(KEY_RL_A_cnt>=(Anti_chattering_time+30)){//30はチャタ防止を超過した時間で長押しと判断
    KEY_RL_PUSH_Flag=0;
   }
   if(( KEY_RL_A_cnt >= Anti_chattering_time )&&(KEY_RL_PUSH_Flag==0)){
     Keyboard.press(' ');
     delayMicroseconds(100);
     Keyboard.release(' ');
    
     KEY_RL_B_cnt=0;
     KEY_RL_PUSH_Flag=1;
    delay(50);
     //押した色
     leds[5].r = P_color[0];
     leds[5].g = P_color[1];
     leds[5].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_RL_B_cnt<=50){
    KEY_RL_B_cnt=KEY_RL_B_cnt+1;}
    if( KEY_RL_B_cnt >= Anti_chattering_time ){
    //通常色
     leds[5].r = N_color[0];
     leds[5].g = N_color[1];
     leds[5].b = N_color[2];
     FastLED.show();
     KEY_RL_A_cnt=0;
     KEY_RL_PUSH_Flag=0;
    }
  }
}else if(SW_MODE==2){//KEY MODE 2 solid モード
//1//単品入力 下
 if(digitalRead(KEY_LH) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_LH_A_cnt<=50){
   KEY_LH_A_cnt=KEY_LH_A_cnt+1;}
   if(( KEY_LH_A_cnt >= Anti_chattering_time )&&(KEY_LH_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('6');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('6');

     KEY_LH_B_cnt=0;
     KEY_LH_PUSH_Flag=1;
   //押した色
     leds[0].r = P_color[0];
     leds[0].g = P_color[1];
     leds[0].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_LH_B_cnt<=50){
    KEY_LH_B_cnt=KEY_LH_B_cnt+1;}
    if( KEY_LH_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[0].r = N_color[0];
     leds[0].g = N_color[1];
     leds[0].b = N_color[2];
     FastLED.show();
     KEY_LH_A_cnt=0;
     KEY_LH_PUSH_Flag=0;
    }
  }
//2//単品入力 正面
  if(digitalRead(KEY_SH) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_SH_A_cnt<=50){
   KEY_SH_A_cnt=KEY_SH_A_cnt+1;}
   if(( KEY_SH_A_cnt >= Anti_chattering_time )&&(KEY_SH_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('1');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('1');

     KEY_SH_B_cnt=0;
     KEY_SH_PUSH_Flag=1;
  //押した色
     leds[1].r = P_color[0];
     leds[1].g = P_color[1];
     leds[1].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_SH_B_cnt<=50){
    KEY_SH_B_cnt=KEY_SH_B_cnt+1;}
    if( KEY_SH_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[1].r = N_color[0];
     leds[1].g = N_color[1];
     leds[1].b = N_color[2];
     FastLED.show();
     KEY_SH_A_cnt=0;
     KEY_SH_PUSH_Flag=0;
    }
  }
//3//単品入力 上
 if(digitalRead(KEY_RH) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_RH_A_cnt<=50){
   KEY_RH_A_cnt=KEY_RH_A_cnt+1;}
   if(( KEY_RH_A_cnt >= Anti_chattering_time )&&(KEY_RH_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('5');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('5');

     KEY_RH_B_cnt=0;
     KEY_RH_PUSH_Flag=1;
  //押した色
     leds[2].r = P_color[0];
     leds[2].g = P_color[1];
     leds[2].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_RH_B_cnt<=50){
    KEY_RH_B_cnt=KEY_SH_B_cnt+1;}
    if( KEY_RH_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[2].r = N_color[0];
     leds[2].g = N_color[1];
     leds[2].b = N_color[2];
     FastLED.show();
     KEY_RH_A_cnt=0;
     KEY_RH_PUSH_Flag=0;
    }
  }
//4//単品入力 左面
  if(digitalRead(KEY_LL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_LL_A_cnt<=50){
   KEY_LL_A_cnt=KEY_LL_A_cnt+1;}
   if(( KEY_LL_A_cnt >= Anti_chattering_time )&&(KEY_LL_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('3');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('3');

     KEY_LL_B_cnt=0;
     KEY_LL_PUSH_Flag=1;
  //押した色
     leds[3].r = P_color[0];
     leds[3].g = P_color[1];
     leds[3].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_LL_B_cnt<=50){
    KEY_LL_B_cnt=KEY_LL_B_cnt+1;}
    if( KEY_LL_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[3].r = N_color[0];
     leds[3].g = N_color[1];
     leds[3].b = N_color[2];
     FastLED.show();
     KEY_LL_A_cnt=0;
     KEY_LL_PUSH_Flag=0;
    }
  }
//5//単品入力 裏面
  if(digitalRead(KEY_SL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_SL_A_cnt<=50){
   KEY_SL_A_cnt=KEY_SL_A_cnt+1;}
   if(( KEY_SL_A_cnt >= Anti_chattering_time )&&(KEY_SL_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('2');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('2');

     KEY_SL_B_cnt=0;
     KEY_SL_PUSH_Flag=1;
  //押した色
     leds[4].r = P_color[0];
     leds[4].g = P_color[1];
     leds[4].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_SL_B_cnt<=50){
    KEY_SL_B_cnt=KEY_SL_B_cnt+1;}
    if( KEY_SL_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[4].r = N_color[0];
     leds[4].g = N_color[1];
     leds[4].b = N_color[2];
     FastLED.show();
     KEY_SL_A_cnt=0;
     KEY_SL_PUSH_Flag=0;
    }
  }
//6//単品入力 右面
  if(digitalRead(KEY_RL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_RL_A_cnt<=50){
   KEY_RL_A_cnt=KEY_RL_A_cnt+1;}
   if(( KEY_RL_A_cnt >= Anti_chattering_time )&&(KEY_RL_PUSH_Flag==0)){
     Keyboard.press(KEY_LEFT_CTRL);
     Keyboard.press('4');
     delayMicroseconds(100);
     Keyboard.release(KEY_LEFT_CTRL);
     Keyboard.release('4');

     KEY_RL_B_cnt=0;
     KEY_RL_PUSH_Flag=1;
  //押した色
     leds[5].r = P_color[0];
     leds[5].g = P_color[1];
     leds[5].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_RL_B_cnt<=50){
    KEY_RL_B_cnt=KEY_RL_B_cnt+1;}
    if( KEY_RL_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[5].r = N_color[0];
     leds[5].g = N_color[1];
     leds[5].b = N_color[2];
     FastLED.show();
     KEY_RL_A_cnt=0;
     KEY_RL_PUSH_Flag=0;
    }
  }
}else if(SW_MODE==3){//KEY MODE 3 brows mode
//Return//単品入力
  if(digitalRead(KEY_SL) == LOW ){//PUSH　押されてAnti_chattering_time溜まったら押されていないBを初期化
   if(KEY_SL_A_cnt<=50){
   KEY_SL_A_cnt=KEY_SL_A_cnt+1;}
   if(( KEY_SL_A_cnt >= Anti_chattering_time )&&(KEY_SL_PUSH_Flag==0)){
     Keyboard.press('c');//NEXTtrack
     delayMicroseconds(100);
     Keyboard.release('c');
     KEY_SL_B_cnt=0;
     KEY_SL_PUSH_Flag=1;
  //押した色
     leds[4].r = P_color[0];
     leds[4].g = P_color[1];
     leds[4].b = P_color[2];
     FastLED.show();
   }
  }else{ //high 押されていない時BがAnti_chattering_time溜まったらAのカウントを初期化
    if(KEY_SL_B_cnt<=50){
    KEY_SL_B_cnt=KEY_SL_B_cnt+1;}
    if( KEY_SL_B_cnt >= Anti_chattering_time ){
  //通常色
     leds[4].r = N_color[0];
     leds[4].g = N_color[1];
     leds[4].b = N_color[2];
     FastLED.show();
     KEY_SL_A_cnt=0;
     KEY_SL_PUSH_Flag=0;
    }
  }


}//mode3 end
//delayMicroseconds(1000);//1ms=0.001s=1000μs 
}//MODE切り替え end(else only)

}//無操作end
//bootsel reset cmd
  if(BOOTSEL){
    delay(10);
    while(BOOTSEL);
    delay(10);
    rp2040.reboot();
  }
//長時間操作がなかったらリセット
if((digitalRead(15) == LOW )||(digitalRead(14) == LOW )||(digitalRead(13) == LOW )||(digitalRead(12) == LOW )||(digitalRead(11) == LOW )||(digitalRead(10) == LOW )){

 if ((SW_MODE == 1)&&(Not_Touch==0)){
  digitalWrite(9,HIGH);//インジケータ復帰
 }
  TIME_OUT=0;
  Not_Touch=1;
}else{
 if(Not_Touch==1){
   TIME_OUT=TIME_OUT+1;
   if(TIME_OUT>=100000){//1000秒＝１６分//100000
     rp2040.reboot();//reboot.cmd
    }
  }
}
Serial.println(TIME_OUT);

//無操作時　消灯//
  if(Not_Touch==0){
      leds[0].r = 0;//vack ground
     leds[0].g = 0;
     leds[0].b = 0;
      leds[1].r = 0;
     leds[1].g = 0;
     leds[1].b = 0;
      leds[2].r = 0;
     leds[2].g = 0;
     leds[2].b = 0;
      leds[3].r = 0;
     leds[3].g = 0;
     leds[3].b = 0;
      leds[4].r = 0;
     leds[4].g = 0;
     leds[4].b = 0;
      leds[5].r = 0;
     leds[5].g = 0;
     leds[5].b = 0;
      leds[6].r = 0;
     leds[6].g = 0;
     leds[6].b = 0;

     FastLED.show();

      digitalWrite(7,LOW);//モードインジケータ
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
  }
}//LOOP end