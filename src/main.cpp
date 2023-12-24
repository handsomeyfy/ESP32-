#include<Arduino.h>      //基本头文件Arduino.h
#include<WiFi.h>          //WiFi头文件WiFi.h
#include<HTTPClient.h>     //http协议客户端头文件HttpClient.h
#include<ArduinoJson.h>     //Http请求之后服务器会返回一个响应，响应通常是Json格式，需要进行解析,ArduinoJson.h专门用来解析Json文件！
DynamicJsonDocument doc(1024);            
const char *address = "5201314";        
const char *password= "00000000";

HTTPClient http;

String url = "http://apis.juhe.cn/simpleWeather/query";
String city = "长沙";
String key = "7a1fe03b58a8dd1cf59cbbb9edba37a9";
String response;
void setup() {
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(address,password);
  Serial.println("Wifi start to connect!");
  while(WiFi.status()!=WL_CONNECTED)
  {
    digitalWrite(12,HIGH);
    delay(250);
    digitalWrite(12,LOW);
    delay(250);
    Serial.print(".");
  }

  Serial.println("connected succussfully!");
  Serial.println(WiFi.localIP());
  http.begin(url+"?city="+city+"&key="+key);
  int http_code = http.GET();
  Serial.printf("http_code : %d\n",http_code);
  response = http.getString();
  //Serial.println(response);
  deserializeJson(doc,response);
  int tmperature = doc["result"]["realtime"]["temperature"].as<int>();
  Serial.printf("瀹炴椂娓╁害鏄細%d C`\n",tmperature);
  
  if(WiFi.status()==WL_CONNECTED)
  {
    digitalWrite(12,HIGH);
    delay(4000);
    digitalWrite(12,LOW);
  }
}
void connect_again()
{
  int i = 0;
  Serial.println("disconnected!");
  while(WiFi.status()!=WL_CONNECTED)
  {
    i++;
    if(i%4==0)
    WiFi.begin(address,password);
    digitalWrite(12,HIGH);
    delay(250);
    digitalWrite(12,LOW);
    delay(250);
    Serial.print(".");
    if(i>10000000)i==0;
  }
  Serial.println("connected succesfully!");
  if(WiFi.status()==WL_CONNECTED)
  {
    digitalWrite(12,HIGH);
    delay(6000);
    digitalWrite(12,LOW);
  }

}
void loop() {
   if(WiFi.status()!=WL_CONNECTED)
   {
      connect_again();
   }
}