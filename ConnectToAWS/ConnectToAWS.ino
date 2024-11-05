#include <pgmspace.h>

 
#define SECRET
#define THINGNAME "esp3"  

//change this
 
const char WIFI_SSID[] = "Ragavan Devp";               //change this
const char WIFI_PASSWORD[] = "ragavan@200";           //change this
const char AWS_IOT_ENDPOINT[] = "a3ia39iuydga11-ats.iot.ap-southeast-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(s
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUZ6rfJM/p6TYE42NXhV0y8Wf7EiYwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MTAyODAxNTkx
NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAM6EKjRzxhmOpOoWS8O5
cy3yWy5tZ3EEvl/tdg41jUlKe+su0YFrG5vSylH2v9+vkSi6Sufd5p5QyhMx8HoC
YeNKMOHMfuJRYysV290GJnwuVeyIaS0LQ01e90F67Fn77PLErLJJXxPZCFts8gPt
sE7exhTqkt8uJvgr56GBg24R5w2GhkPUrEWyHO5UgCYY5mjdFnEVKsjbWc0jKjgq
jrBPoB8xPso5SXSofz/e0mLjw78S13BtCL+R3j//FbV7TPnZqpimGbHi8GWhhWC7
mLbtgVh+a+9Xx3cYI3S/BP2ue0TsPlCEvIR3LpiK8fNlefZy/9ndQyVwpg7Tl1Et
Ow0CAwEAAaNgMF4wHwYDVR0jBBgwFoAUIijc6egfFJ+jIA31Xs1rlxPYQMkwHQYD
VR0OBBYEFDgdWonn6/va+XCSuFb+rsKtuhwfMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBTRNLgtxopFUXup9kBwSXwMHnF
fev+B2/P1zgJyiFG1LyaULBnA1GSkYCMHq1mrYeFcOBbO8MgmhSLTpZlzEUCn3Xe
6KPgPZy+LOdXHol8lOxMAUrVTLFQYz6+W0CUvRu2g+0zLmQ8Tam4leJRikS0+OYI
4P+X7Cn3wDqQTZe5jxkhz34cLIY7jgZQg/ZU3vZ3+8GXJs8JyMvsew8Iq7tMd8MR
HVweTxqidxfO9EfGT7+TDmx8+eu7M+kgsR+86Y+iPeeX3qu9jocow4BCa6PmCE8L
cQ83VE74R+85ri/Ea3EueLRLzV5ckcmr3dqZML4/H8yFmkrA5mi6ewK7KV4n
-----END CERTIFICATE-----

)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAzoQqNHPGGY6k6hZLw7lzLfJbLm1ncQS+X+12DjWNSUp76y7R
gWsbm9LKUfa/36+RKLpK593mnlDKEzHwegJh40ow4cx+4lFjKxXb3QYmfC5V7Ihp
LQtDTV73QXrsWfvs8sSssklfE9kIW2zyA+2wTt7GFOqS3y4m+CvnoYGDbhHnDYaG
Q9SsRbIc7lSAJhjmaN0WcRUqyNtZzSMqOCqOsE+gHzE+yjlJdKh/P97SYuPDvxLX
cG0Iv5HeP/8VtXtM+dmqmKYZseLwZaGFYLuYtu2BWH5r71fHdxgjdL8E/a57ROw+
UIS8hHcumIrx82V59nL/2d1DJXCmDtOXUS07DQIDAQABAoIBAG8jNydVKsX0OxHy
/8EMG00dwS5CGEn9OIqdW0wYS7mmiPuvDXZtcsUv8kub0/SIIkFdyBPyGjsW1Tjx
Ri4S/CT6d0X87EfVbt3v/It81Nc9hGYvnxJrnkOUGNI3WdyvM/wOFbY4wB8JTHMP
NUsh7iDzyHvXJUVQLA6gah5DebyQlDrtgsnx3BoMV/HCJbl1gs/MVNl5xBgJu1yo
Gn092HPnPVPOao9KV+biYUOb3SeSkAIou5RnaGHdWyVSc7c569K/C2wEvWKFwdsK
hKPNdVjrFYxsS5DN577InVLuY1vj4xqDeTAhPZPPyc6XXutpcerTBI3faVHY7PpH
VWXrVEECgYEA7hnITcdh0rAxGyT341+427Up8jx4c3HCoXOsQLpFwb/7DAxX5MeJ
JBdg5ocryrdbh3ds7iKNO1riIqdtaee91Jq6O2z/mWhPPZctc6JsT3pV8hefDPeq
mK8laZFY73qsUsP6wwEMZrvW/BNRZ9YOU3uY+UZ7tNnWc3Tn3cJ6mB0CgYEA3gqL
O1QBv2c8KtyWv92HL1cySKqWXGDNbL/XnbIuef2QmsIkxaJnn/kpQUVrPsBqu5L+
QaV6JgoUnIC+BwubYG2edO7ss9BHda8hWLUZFBoLsw5Pm/W+CHGkWRtT3POWAbJk
KS7y6VdiHkB+JKRyjlb85mgmUzlJkHPA28WrG7ECgYEAovcSmem1krb1ZVbQM9f4
dqhwpVOuPZXHWSoK4+KajBoSghSQtA2+V+2IbUBnQMBu7TFYZUVQ1SdHT+C4ipwK
2dFtVe8sops6YTVv7o1lBKD+4kw4mG+LXCXEvZS2AnM8LwnkQEQfcNFwO+gc960S
8SDPew467XWLykphyO6raiECgYAyCaxAzXirWqdrfVSXnmOlnn/dclv6K3J/zGfZ
yNrCcQsSZSgGRcgWe/75D5zQgmpLJSAZSSJSyjjE4Bpy2gHE5E8uSN2c1BYWhkX8
iKtDJW93hYUZP3L40itYTVlD1Lz8WuhJg6QIQ8H/0UbcGRcbzqyle9kPLjzOydcv
b8dUsQKBgQDUKayIgp8xZOl1e1QQVZBt5o5OPRKYDbSwaq6R+zK0DVjtWkqzdvRe
hR3w7lxew6MDFyk7GvzegPBwsBB9h1lQskGUaSN5NlYAsXVG8PMsZ8pqMVthtcZY
95og0iRfaEf6eya6WeFIiTg7fUgYXkr/r+m5gqAPTguB6aAJ08aUXQ==
-----END RSA PRIVATE KEY-----

)KEY";


#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

 
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
 
float h = 0;
float t;
 

 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}
 
void setup()
{
  Serial.begin(115200);
  connectAWS();

}
 
void loop()
{
  h = 20;

  for(t = 0; t <= 10 ; t++){
      StaticJsonDocument<200> doc;
  doc["humidity"] = h;
  doc["temperature"] = t;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);

 
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Hack: "));
  Serial.print(t);
  Serial.println(F("°C "));
  client.loop();
  delay(3000);
  }

  delay(100);
}
