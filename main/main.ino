#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22

//전역 변수 라인
byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
byte ip[] = {192,168,0,12};
EthernetServer server(80);
String readString;
Servo myservo1,myservo2;
int angle = 90;
DHT dht(DHTPIN,DHTTYPE);
float a;

//셋업 부분
void setup(){
  Ethernet.begin(mac,ip);
  server.begin();
  myservo1.attach(12);
  myservo2.attach(13);
}

//무한 반복하는 부분
void loop(){
  web();
  servo();
}

//웹 서버 함수
void web(){
  EthernetClient client = server.available();
  if(client){
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        if(readString.length()<100){
          readString += c;
        }

        if(c == 0x0D){
          client.println("HTTP/1.1 200 ok");
          client.println("Conntent - Type : text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<title>실험적인 웹서버 페이지 원</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>계란 부화기</h1>");
          client.println("<br>");
          client.println("<p>현재 온도 :");
//          client.println(dht_1(a)); //아직 구현 안함 온도 부분
          client.println("</p>");
          client.println("<h2><a href = \"/?LightON\"\">백열전구 ON</a><br></h2>");
          client.println("</body>");
          client.println("</html>");
          delay(10);
          client.stop();
          readString = "";
        }
      }
    }
  }
}

//서보 모터 구현
void servo(){
  for(angle = 0; angle<=180; angle+=1){
    myservo1.write(angle);
    myservo2.write(angle);
    delay(14400);
  }
}

//온도 습도 부분
void dht_1(){
  delay(200);
  float a;
  a = dht.readTemperature();
  return a;


}
