#include<ESP8266WiFi.h>

WiFiServer server(80);

const char* ssid = "Ap";
const char* password = "234567890";
int ledpin5=D8;
int ledpin6=D9;
int ledpin7=D12;
int ledpin8=D13;
int l = D11;
int r = D10;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 delay(10);
 Serial.println();
 WiFi.begin(ssid,password);
pinMode(ledpin5,OUTPUT);
pinMode(ledpin6,OUTPUT);
pinMode(ledpin7,OUTPUT);
pinMode(ledpin8,OUTPUT);
    digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
while(WiFi.status() !=WL_CONNECTED){
  delay(500);
  Serial.println(".");
  pinMode(l,OUTPUT);
  analogWrite(l,340);
    pinMode(r,OUTPUT);
  analogWrite(r,300);
  }

  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client  = server.available();
  if(!client){
    return;
    }
  while(!client.available()){
    delay(200);
    }
  String s = "HII!!";
String request = client.readStringUntil('\r');
    client.flush();
 
 
  if (request.indexOf("/dir=b/dir=lt") != -1 || request.indexOf("/dir=f/dir=lt") != -1||request.indexOf("/dir=l/dir=lt") != -1||request.indexOf("/dir=r/dir=lt") != -1
  ||request.indexOf("/dir=s/dir=lt") !=-1||request.indexOf("/dir=lt") != -1) {
    digitalWrite(ledpin7, HIGH);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
  delay(37);
    digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
    s = "TURNING LEFT";
    
  } 
  else if (request.indexOf("/dir=r/dir=rt") != -1 || request.indexOf("/dir=l/dir=rt") != -1 ||request.indexOf("/dir=f/dir=rt") != -1||request.indexOf("/dir=b/dir=rt") != -1
    ||request.indexOf("/dir=s/dir=rt") !=-1||request.indexOf("/dir=rt") != -1) {
     digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,HIGH);
    digitalWrite(ledpin6,LOW);
    s = "TURNING RIGHT";
    delay(37);
     digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
  
  }
  
  else if (request.indexOf("/dir=r/") != -1){
     digitalWrite(ledpin7, LOW);
    digitalWrite(ledpin8,HIGH);
    digitalWrite(ledpin5,HIGH);
    digitalWrite(ledpin6,LOW);
    s = " MOVED RIGHT";
    delay(350);
    digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
  }
  else if (request.indexOf("/dir=l/") != -1){
     digitalWrite(ledpin7, HIGH);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,HIGH);
    s = "MOVED LEFT";
  delay(280);
    digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
  }
  else if (request.indexOf("/dir=b/") != -1){
     digitalWrite(ledpin7,LOW);
    digitalWrite(ledpin8,HIGH);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,HIGH);
    s = "MOVING BACK";
     }
   else if (request.indexOf("/dir=f/") != -1){
     digitalWrite(ledpin7, HIGH);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,HIGH);
    digitalWrite(ledpin6,LOW);
    s  ="MOVING FRONT";
     } 
      else if (request.indexOf("/dir=s/") != -1){
     digitalWrite(ledpin7, LOW);
    digitalWrite(ledpin8,LOW);
    digitalWrite(ledpin5,LOW);
    digitalWrite(ledpin6,LOW);
    s  ="STOP";
     } 
   
    client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
    client.println("<html><body bgcolor = aqua>\n");
    client.print("<h2>BOT IS NOW :  <h2>"+ s );
client.print("<center>\n"
"<a href = \"/dir=f\\\"><button id = front  style=\"float :absolute; font-size:25px; margin:5px ; padding : 10px; height: 50px; width: 160px; border-radius:20%\"> FRONT </button></a></center>\n"
"<br><br>");
client.println("<center>\n"
"<a href = \"/dir=l\\\"><button id = left style=\"float :absolute; margin:5px ;leftmargin:40px; font-size:25px; padding : 10px; height: 50px; width: 140px; border-radius:20%\"> LEFT </button></a> ");
client.println("<a href = \"/dir=s\\\"><button  id = right style=\"float :absolute; margin:5px ; font-size:25px; padding : 10px; background:#c4545f; height: 50px; width: 100px; border-radius:40%\">STOP</button></a>");

client.println("<a href = \"/dir=r\\\"><button  id = right style=\"float :absolute; margin:5px ;font-size:25px; padding : 10px; height: 50px; width: 140px; border-radius:20%\"> RIGHT </button></a></center>");
client.println("<br><br>\n"
"<center>\n"
"<a href = \"/dir=b\\\"><button id = back  style=\"float :absolute; margin:5px ; padding : 10px;font-size:25px; height: 50px; width: 160px; border-radius:20%\"> BACK </button></a></center>");
client.println("<p>\n"
" <div id=\"LR\"></div>\n"
" <div id=\"FB\"></div>\n"
" <div id=\"DIR\"></div>\n"
" <script type=\"text/javascript\">\n"
"if (window.DeviceOrientationEvent) {\n"
"\n"
" console.log(\"DeviceOrientation is supported\");\n"
" window.addEventListener('deviceorientation', function(eventData) {\n"
"// gamme is for left/right inclinaison\n"
"var LR = eventData.gamma;\n"
" if(LR>15){\n"
"   window.location.replace('dir=rt\');\n"
"  }\n"
"  else if(LR<-15){\n"
    " window.location.replace('dir=lt\');\n"
    " }\n"
" deviceOrientationHandler(LR, FB, DIR);\n"
"}, false);\n"
"\n"
"} else {\n"
"\n"
"alert(\"Device orientation not supported on your device or browser.Sorry.\");\n"
"}\n"
"function deviceOrientationHandler(LR, FB, DIR) {\n"
"  }\n"
"</script>\n"
"\n"
"</body></html>");
delay(1);
Serial.println("client disconnected");
Serial.println("");
    
}
