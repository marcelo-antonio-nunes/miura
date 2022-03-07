#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID "AMNET85_2672"
#define WIFI_PASSWORD ""
#define buzina 05
#define farol 0
#define farol_m 15
#define ligar 02
#define limpador 04
#define porta_mt 18
#define porta_ps 19
#define porta_ma 21
#define seta_d 22
#define seta_e 23

FirebaseData myFireBaseData;
FirebaseJson myJson;
FirebaseJsonData myJsonData;

unsigned long antes =0, agora =0; 
unsigned long antes2 =0, agora2 =0; 
int intervalo = 10000;
void setup(){
  pinMode(buzina, OUTPUT);
  pinMode(farol, OUTPUT);
  pinMode(farol_m, OUTPUT);
  pinMode(ligar, OUTPUT);
  pinMode(limpador, OUTPUT);
  pinMode(porta_mt, OUTPUT);
  pinMode(porta_ps, OUTPUT);
  pinMode(porta_ma, OUTPUT);
  pinMode(seta_d, OUTPUT);
  pinMode(seta_e, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a :");
  Serial.println(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado ao ip: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
String estados="",vbuzina="";
String vfarol,vfarol_m,vlimpa,vliga,vporta_mt,vporta_ps,vporta_ma,vseta_d,vseta_e;
void loop() {
   antes = millis();
   if (Firebase.ready() && (antes - agora >=500 || agora == 0)){
   agora = antes;

   Firebase.get(myFireBaseData, "/");
   estados = myFireBaseData.jsonString();
   myJson.setJsonData(estados);
   }
   antes2 = millis();
   if (Firebase.ready() && (antes2 - agora2 >=300 || agora2 == 0)){
   agora2 = antes2;
   myJson.get(myJsonData, "/Buzinar");
   vbuzina = myJsonData.stringValue;
   digitalWrite(buzina,vbuzina.toInt());
   Serial.println(vbuzina);
   
   myJson.get(myJsonData, "/Farol");
   vfarol = myJsonData.stringValue;
   digitalWrite(farol,vfarol.toInt());
   Serial.println(vfarol);
   
   myJson.get(myJsonData, "/Farol_m");
   vfarol_m = myJsonData.stringValue;
   digitalWrite(farol_m,vfarol_m.toInt());
   Serial.println(vfarol_m);
   
   myJson.get(myJsonData, "/Ligar");
   vliga = myJsonData.stringValue;
   digitalWrite(ligar,vliga.toInt());
   Serial.println(vliga);

   myJson.get(myJsonData, "/Limpa_p");
   vlimpa = myJsonData.stringValue;
   digitalWrite(limpador,vlimpa.toInt());
   Serial.println(vlimpa);

   myJson.get(myJsonData, "/Porta_m");
   vporta_mt = myJsonData.stringValue;
   digitalWrite(porta_mt,vporta_mt.toInt());
   Serial.println(vporta_mt);

   myJson.get(myJsonData, "/Porta_p");
   vporta_ps = myJsonData.stringValue;
   digitalWrite(porta_ps,vporta_mt.toInt());
   Serial.println(vporta_ps);

   myJson.get(myJsonData, "/Porta_malas");
   vporta_ma = myJsonData.stringValue;
   digitalWrite(porta_ma,vporta_ma.toInt());
   Serial.println(vporta_ma);

   myJson.get(myJsonData, "/Seta_d");
   vseta_d = myJsonData.stringValue;
   digitalWrite(seta_d,vseta_d.toInt());
   Serial.println(vseta_d);

   myJson.get(myJsonData, "/Seta_e");
   vseta_e = myJsonData.stringValue;
   digitalWrite(seta_e,vseta_e.toInt());
   Serial.println(vseta_e);

   
  
    
}
}
