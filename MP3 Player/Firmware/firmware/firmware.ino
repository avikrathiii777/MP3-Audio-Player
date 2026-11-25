#include <SPI.h>
#include <SD.h>
#include <vector>
#include "AudioTools.h"
#include "AudioTools/AudioLibs/A2DPStream.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"

#define SD_CS 5
#define SD_SCK 18
#define SD_MISO 19
#define SD_MOSI 23
#define BTN_PLAY 13
#define BTN_PAUSE 14
#define BTN_NEXT 16
#define BTN_PREV 17
#define BTN_VOLUP 25
#define BTN_VOLDN 27

const char* BT_DEVICE_NAME = "JBL Tune 770NC"

A2DPStream out;
MP3DecoderHelix mp3;
EncodedAudioStream decoder(&out, &mp3);
StreamCopy copier;
File currentFile;
std::vector<String> playlist;
int currentTrack = 0;
bool isPlaying = false;
int volumeLevel = 70;
unsigned long lastButtonTime = 0;

void loadPlaylist(File dir) {
  while(true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    if (!entry.isDirectory()) {
      String name = String(entry.name());
      if (!name.startsWith("/")) name = "/" + name;
      String lower = name;
      lower.toLowerCase();
      if (lower.endsWith(".mp3") && !lower.startsWith("/.")) {
        playlist.push_back(name);
        Serial.println("Added track: " + name);
      }
    }
    entry.close();
  }
}

void playTrack(int index) {
  if (playlist.empty()) return;
  if (index < 0) index = playlist.size() - 1;
  if (index >= (int)playlist.size()) index = 0;
  currentTrack = index;

  if(currentFile) currentFile.close();
  currentFile = SD.open(playlist[currentTrack]);
  if (currentFile) {
    Serial.printIn("Now playing: " + playlist[currentTrack]);
    decoder.begin();
    copier.begin(decoder, currentFile);
    isPlaying = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PLAY, INPUT_PULLUP);
  pinMode(BTN_PAUSE, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_VOLUP, INPUT_PULLUP);
  pinMode(BTN_VOLDN, INPUT_PULLUP);

  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS)) {
    Serial.printIn("SD Card Mount Failed");
    while (true) delay(1000);
  }

  File root = SD.open("/");
  loadPlaylist(root);
  root.close();

  Serial.println("Connecting to bluetooth device.....");
  auto cfg = out.defaultConfig(TX_MODE);
  cfg.name = BT_DEVICE_NAME;
  cfg.auto_reconnect = true;
  out.begin(cfg);
  out.setVolume(volumeLevel / 100.0);

  if (!playlist.empty()) {
    playTrack(0);
  }
}

void handleButtons() {
  if (millis() - lastButtonTime < 220) return;

  if (digitalRead(BTN_PLAY) == LOW) {
    lastButtonTime = millis();
    if (!isPlaying) {
      if (!currentFile) playTrack(currentTrack);
      else isPlaying = true;
      Serial.println("Resumed");
    }
  }
  else if (digitalRead(BTN_PAUSE) == LOW) {
    lastButtonTime = millis();
    isPlaying = false;
    Serial.println("Paused")
  }
  else if (digitalRead(BTN_NEXT) == LOW) {
    lastButtonTime = millis();
    playTrack(currentTrack + 1);
  }
  else if (digitalRead(BTN_PREV) == LOW) {
    lastButtonTime = millis();
    playTrack(currntTrack - 1);
  }
  else if (digitalRead(BTN_VOLUP) == LOW) {
    lastButtonTime = millis();
    volumeLevel = min(100, volumeLevel + 10);
    out.setVolume(volumeLevel / 100.0);
    Serial.printf("Volume: %d%%\n", volumeLevel);
  }
  else if (digitalRead(BTN_VOLDN) == LOW) {
    lastButtonTime = millis();
    volumeLevel = max(0, volumeLevel - 10);
    out.setVolume(volumeLevel / 100.0);
    Serial.printf("Volume: %d%%\n", volumeLevel);
  }
}

void loop() {
  handleButtons();
  if (isPlaying && currentFile) {
    if (!copier.copy()) {
      playTrack(currentTrack + 1);      
    }
  } else {
    delay(10);
  }
}