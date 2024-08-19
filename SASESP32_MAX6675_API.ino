#include "arduino_secrets.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <ArduinoJson.h>
#include "max6675.h"
#include "EspHtmlTemplateProcessor.h"

/* VariÃ¡veis globais */
const char* version = "1.3";
const char* deviceId = "637041df3dedebcd24bc424a";
bool enable_api_client = true;

/* Certificado CA do domÃ­nio https://smartmonitor-app.fly.dev */
const char* ca_cert =
  "-----BEGIN CERTIFICATE-----\n"
  "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\n"
  "-----END CERTIFICATE-----\n";

/* Wi-fi */
const char* host = "SASESP320001";
const char* ssid = "WIFI";
const char* password = "password";

/* Sensor MAX6675 */
unsigned long t_prev;
int thermoDO = 23;
int thermoCS = 5;
int thermoCLK = 18;
int toggle = 0;
int vccPin = 3;
int gndPin = 2;
float degC, degF;
unsigned long lastTime = 0;
unsigned long currentValue = 1;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

/* Webserver para se comunicar via browser com ESP32  */
WebServer server(8080);
EspHtmlTemplateProcessor templateProcessor(&server);

/*  Programa para ESP32 depois da atualizaÃ§Ã£o OTA */

/* CÃ³digos da pÃ¡gina que serÃ¡ aberta no browser 
   (quando comunicar via browser com o ESP32) 
   Esta pÃ¡gina exigirÃ¡ um login e senha, de modo que somente 
   quem tenha estas informaÃ§Ãµes consiga atualizar o firmware
   do ESP32 de forma OTA */
const char* loginIndex =
  "<form name='loginForm'>"
  "<table width='20%' bgcolor='A09F9F' align='center'>"
  "<tr>"
  "<td colspan=2>"
  "<center><font size=4><b>ESP32 - identifique-se</b></font></center>"
  "<br>"
  "</td>"
  "<br>"
  "<br>"
  "</tr>"
  "<td>Login:</td>"
  "<td><input type='text' size=25 name='userid'><br></td>"
  "</tr>"
  "<br>"
  "<br>"
  "<tr>"
  "<td>Senha:</td>"
  "<td><input type='Password' size=25 name='pwd'><br></td>"
  "<br>"
  "<br>"
  "</tr>"
  "<tr>"
  "<td><input type='submit' onclick='check(this.form)' value='Identificar'></td>"
  "</tr>"
  "</table>"
  "</form>"
  "<script>"
  "function check(form)"
  "{"
  "if(form.userid.value=='admin' && form.pwd.value=='admin')"
  "{"
  "window.open('/serverIndex')"
  "}"
  "else"
  "{"
  " alert('Login ou senha invÃ¡lidos')"
  "}"
  "}"
  "</script>";

const char* serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>"
  "<div id='prg'>Progresso: 0%</div>"
  "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('Progresso: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('Sucesso!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>";

void setup(void) {
  Serial.begin(115200);

  /* Conecta-se a rede wi-fi */
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a rede wi-fi ");
  Serial.println(ssid);
  Serial.print("IP obtido: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  /* Usa MDNS para resolver o DNS */
  if (!MDNS.begin(host)) {
    //http://esp32.local
    Serial.println("Erro ao configurar mDNS. O ESP32 vai reiniciar em 1s...");
    delay(1000);
    ESP.restart();
  }


  Serial.println("mDNS configurado e inicializado;");

  /* Configfura as pÃ¡ginas de login e upload de firmware OTA */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });

  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });

  /* Define tratamentos do update de firmware OTA */
  server.on(
    "/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    },
    []() {
      HTTPUpload& upload = server.upload();

      if (upload.status == UPLOAD_FILE_START) {
        /* Inicio do upload de firmware OTA */
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN))
          Update.printError(Serial);
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        /* Escrevendo firmware enviado na flash do ESP32 */
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
          Update.printError(Serial);
      } else if (upload.status == UPLOAD_FILE_END) {
        /* Final de upload */
        if (Update.end(true))
          Serial.printf("Sucesso no update de firmware: %u\nReiniciando ESP32...\n", upload.totalSize);
        else
          Update.printError(Serial);
      }
    });
  server.begin();

  /* Setup Sensor MAX6775 */
  Serial.println("Testando comunicaÃ§Ã£o com sensor MAX6675...");
  // wait for MAX chip to stabilize
  delay(1000);
  t_prev = millis();
}

void loop() {
  server.handleClient();
  delay(1);

  /* Coleta de dados do sensor MAX6675 */
  
  
  /*
  if (millis() - t_prev > 1000) { // Faz a leitura a cada segundo
      degC = thermocouple.readCelsius();
      degF = degC * 9.0 / 5.0 + 32;
      Serial.print("C = ");
      Serial.print(degC);
      Serial.print("    F = ");
      Serial.println(degF);
      toggle = !toggle;
      t_prev = millis();
    }
    /*
    
    


  /* ConexÃ£o com o Smart Monitor AtravÃ©s de API Rest */
  if (enable_api_client) {
    /* Coleta de dados do sensor MAX6675 */
    if (millis() - t_prev > 60000) {  // Faz a leitura a cada minuto
      Serial.println("Coletando dados do sensor MAX6675...");
      Serial.print("C = ");
      Serial.print(degC);
      Serial.print("    F = ");
      Serial.println(degF);
      degC = thermocouple.readCelsius();
      // degF = degC * 9.0 / 5.0 + 32;
      t_prev = millis();

      WiFiClientSecure client;
      HTTPClient https;

      client.setCACert(ca_cert);

      DynamicJsonDocument infoDoc(2048);
      DynamicJsonDocument sensorDoc(2048);

      infoDoc["deviceId"] = deviceId;
      infoDoc["chipModel"] = ESP.getChipModel();
      infoDoc["chipRevision"] = ESP.getChipRevision();
      infoDoc["firmware"] = version;
      infoDoc["ipv4"] = WiFi.localIP();
      infoDoc["mac"] = WiFi.macAddress();
      infoDoc["ssid"] = ssid;
      infoDoc["isOnline"] = true;

      sensorDoc["deviceId"] = "637041df3dedebcd24bc424a";
      sensorDoc["identifier"] = "degC";
      // sensorDoc["value"] = String(degC);
      sensorDoc["value"] = random(400, 600);

      String infoJson;
      serializeJson(infoDoc, infoJson);

      String sensorJson;
      serializeJson(sensorDoc, sensorJson);

      // Send request
      Serial.println("Enviando dados para o Smart Monitor...");

      // Envia dos dados do hardware
      https.begin(client, "https://smartmonitor-app.fly.dev/api/processing/device/status/637041df3dedebcd24bc424a");
      https.addHeader("Content-Type", "application/json");
      https.PATCH(infoJson);
      https.end();

      // Envia dos dados do sensor
      https.begin(client, "https://smartmonitor-app.fly.dev/api/processing/data");
      https.addHeader("Content-Type", "application/json");
      https.POST(sensorJson);
      https.end();
    }
  }
}