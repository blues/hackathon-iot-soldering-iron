#include <Arduino.h>

////////////////////////////////////////////// Notecard

#include <Notecard.h>

#define productUID "com.blues.carl.hack.nashville"
Notecard notecard;

// Setup notecard
void setup_notecard()
{
  delay(2500);
  Serial.begin(115200);
  notecard.begin();
  J *req = notecard.newRequest("hub.set");
  JAddStringToObject(req, "product", productUID);
  JAddStringToObject(req, "mode", "continuous");
  notecard.sendRequest(req);
}

unsigned long last_note_time;

void found_iron(bool found)
{
  // convert bool to int
  int nfound = found ? 1 : 0;

  Serial.print(" found: ");
  Serial.print(found);
  Serial.print(" nfound: ");
  Serial.print(nfound);
  Serial.println();
  // send request to notehub
  J *req = notecard.newRequest("note.add");
  JAddStringToObject(req, "file", "data.qo");
  JAddBoolToObject(req, "sync", true);
  J *body = JCreateObject();
  JAddBoolToObject(body, "found", found);
  JAddNumberToObject(body, "nfound", nfound);
  JAddItemToObject(req, "body", body);
  notecard.sendRequest(req);
  last_note_time = millis();
  delay(5000);
}

////////////////////////////////////////////// BLE
#include <ArduinoBLE.h>

#define IRON_NAME "Pinecil"

void setup_ble()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // begin initialization
  if (!BLE.begin())
  {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1)
      ;
  }

  Serial.println("Bluetooth® Low Energy Central scan");

  // start scanning for peripheral
  BLE.scan();
}

void loop_ble()
{
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();
  if (!peripheral)
    return;

  // Bail if not the right local name
  if (!peripheral.hasLocalName())
    return;

  // discovered a peripheral
  // Serial.println("Discovered a peripheral");
  // Serial.println("-----------------------");

  // print the local name, if present
  String localName = peripheral.localName();
  // bail if IRON_NAME is not fonud in localName
  if (localName.indexOf(IRON_NAME) == -1)
    return;

  Serial.print("Name: ");
  Serial.println(localName);

  found_iron(true);

  // print the advertised service UUIDs, if present
  if (peripheral.hasAdvertisedServiceUuid())
  {
    Serial.print("Service UUIDs: ");
    for (int i = 0; i < peripheral.advertisedServiceUuidCount(); i++)
    {
      Serial.print(peripheral.advertisedServiceUuid(i));
      Serial.print(" ");
    }
    Serial.println();
  }
}

void setup()
{
  // put your setup code here, to run once:
  setup_notecard();
  setup_ble();
  Serial.begin(9600);
  Serial.println("Set up!");
}

// TIMEOUT in milliseconds, sets when to upload a note to notehub if no
// soldering iron is found.
#define TIMEOUT 10000

void loop()
{
  // put your main code here, to run repeatedly
  if (millis() - last_note_time > TIMEOUT)
  {
    found_iron(false);
    last_note_time = millis();
  }

  loop_ble();
}
