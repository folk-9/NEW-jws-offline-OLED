#include <Wire.h>
#include <RTClib.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/Org_01.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

RTC_DS3231 rtc;

// =========================
// KOORDINAT MASJID
// =========================

const double LATITUDE  = -8.545277432685705;
const double LONGITUDE = 118.43718929520696;

const int TIMEZONE = 8; // WITA

// =========================
// SHOLAT
// =========================

char sholatName[16];
char countdownText[16];
char tanggalText[32];

char waktuSubuh[6];
char waktuDzuhur[6];
char waktuAshar[6];
char waktuMaghrib[6];
char waktuIsya[6];

static const unsigned char PROGMEM image_LOGO_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x15,0x55,0x55,0x50,0x54,0x14,0x15,0x55,0x55,0x54,0x55,0x00,0x00,0x00,0x2a,0xaa,0xaa,0xa8,0xaa,0x2a,0x2a,0xaa,0xaa,0xa8,0xaa,0x00,0x00,0x00,0x55,0x55,0x55,0x51,0x54,0x54,0x55,0x55,0x55,0x54,0x55,0x00,0x00,0x00,0xaa,0xaa,0xaa,0xa2,0xa8,0xa0,0xaa,0xaa,0xaa,0xa8,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x41,0x41,0x50,0x00,0x00,0x00,0x05,0x08,0x00,0x00,0x00,0x00,0x00,0x0a,0x82,0x82,0xa0,0x00,0x00,0x00,0x02,0x15,0x55,0x55,0x55,0x55,0x55,0x45,0x05,0x05,0x41,0x55,0x55,0x54,0x55,0x2a,0xaa,0xaa,0xaa,0xaa,0xaa,0xa2,0x0a,0x22,0x88,0xaa,0xaa,0xa8,0xaa,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x44,0x51,0x14,0x55,0x55,0x54,0x55,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xa8,0xa0,0xa8,0x2a,0x2a,0xaa,0xa8,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x50,0x54,0x15,0x00,0x00,0x14,0x05,0x00,0x00,0x00,0x00,0x00,0x02,0x28,0x28,0x2a,0x0a,0x80,0x00,0x08,0x02,0x55,0x55,0x55,0x55,0x55,0x55,0x11,0x14,0x15,0x05,0x55,0x55,0x54,0x55,0x2a,0xaa,0xaa,0xaa,0xaa,0xaa,0x82,0x88,0x8a,0x22,0xaa,0xaa,0xa8,0xaa,0x15,0x55,0x55,0x55,0x55,0x55,0x05,0x41,0x44,0x51,0x55,0x55,0x54,0x55,0x0a,0xaa,0xaa,0xaa,0xaa,0xaa,0x0a,0x82,0xa0,0xa0,0xaa,0xaa,0xa8,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x05,0x41,0x40,0x00,0x00,0x14,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x2a,0x2a,0x82,0x88,0x00,0x00,0x08,0x02,0x00,0x00,0x01,0x55,0x55,0x55,0x54,0x55,0x15,0x15,0x55,0x55,0x54,0x55,0x00,0x00,0x00,0xaa,0xaa,0xaa,0xa8,0xaa,0x2a,0x2a,0xaa,0xaa,0xa8,0xaa,0x00,0x00,0x00,0x55,0x55,0x55,0x50,0x54,0x14,0x15,0x55,0x55,0x54,0x55,0x00,0x00,0x00,0x2a,0xaa,0xaa,0xa0,0x28,0x08,0x0a,0xaa,0xaa,0xa8,0xaa,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x14,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x88,0xa2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x54,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xa8,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x54,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02};

bool modeAlarmSholat = false;

unsigned long alarmStartMillis = 0;

char namaAlarmSholat[16] = "";

void drawTAMPILAN_ALARM(void) {

    display.clearDisplay();

    // ALARM
    display.setTextColor(1);
    display.setTextWrap(false);

    display.setCursor(41, 10);
    display.print("WAKTUNYA");

    // NAMA SHOLAT MISALNYA WAKTUNYA SUBUH. VARIABEL

    display.setTextSize(2);

    display.setCursor(35, 25);
    display.print(namaAlarmSholat);

    // rect 3

    display.drawRect(
        20,
        20,
        88,
        25,
        1
    );

    display.display();
}
void drawopening_boot_awal_dinyalakan(void) {
    display.clearDisplay();

    // LOGO
    display.drawBitmap(8, 9, image_LOGO_bits, 112, 46, 1);

    display.display();
}


// =========================
// ICON
// =========================

static const unsigned char PROGMEM image_COUNTDOWN_icon_bits[] = {
  0x80,0xc0,0xe0,0xf0,0xe0,0xc0,0x80
};

// =========================
// DAY NAME
// =========================

const char* namaHari[] = {
  "Ahad",
  "Senin",
  "Selasa",
  "Rabu",
  "Kamis",
  "Jumat",
  "Sabtu"
};

// =========================
// PRAYER CALCULATION
// =========================

double degToRad(double degree) {
  return ((3.1415926 / 180) * degree);
}

double radToDeg(double radian) {
  return (radian * (180 / 3.1415926));
}

double moreLess360(double value) {
  while (value > 360 || value < 0) {
    if (value > 360)
      value -= 360;
    else if (value < 0)
      value += 360;
  }
  return value;
}

double moreLess24(double value) {
  while (value > 24 || value < 0) {
    if (value > 24)
      value -= 24;
    else if (value < 0)
      value += 24;
  }
  return value;
}

void doubleToHrMin(double number, int &hours, int &minutes) {
  hours = floor(moreLess24(number));
  minutes = floor(moreLess24(number - hours) * 60);
}

void calcPrayerTimes(
  int year,
  int month,
  int day,
  double longitude,
  double latitude,
  int timeZone,
  double fajrTwilight,
  double ishaTwilight,
  double &fajrTime,
  double &sunRiseTime,
  double &zuhrTime,
  double &asrTime,
  double &maghribTime,
  double &ishaTime)
{
  double D =
    (367 * year)
    - ((year + (int)((month + 9) / 12)) * 7 / 4)
    + (((int)(275 * month / 9)) + day - 730531.5);

  double L = 280.461 + 0.9856474 * D;
  L = moreLess360(L);

  double M = 357.528 + (0.9856003) * D;
  M = moreLess360(M);

  double Lambda =
    L + 1.915 * sin(degToRad(M))
    + 0.02 * sin(degToRad(2 * M));

  Lambda = moreLess360(Lambda);

  double Obliquity = 23.439 - 0.0000004 * D;

  double Alpha =
    radToDeg(
      atan(
        (cos(degToRad(Obliquity))
         * tan(degToRad(Lambda)))
      )
    );

  Alpha = moreLess360(Alpha);

  Alpha = Alpha - (360 * (int)(Alpha / 360));
  Alpha = Alpha + 90 * (floor(Lambda / 90) - floor(Alpha / 90));

  double ST = 100.46 + 0.985647352 * D;

  double Dec =
    radToDeg(
      asin(
        sin(degToRad(Obliquity))
        * sin(degToRad(Lambda))
      )
    );

  double Durinal_Arc =
    radToDeg(
      acos(
        (sin(degToRad(-0.8333))
         - sin(degToRad(Dec))
         * sin(degToRad(latitude)))
        /
        (cos(degToRad(Dec))
         * cos(degToRad(latitude)))
      )
    );

  double Noon = Alpha - ST;
  Noon = moreLess360(Noon);

  double UT_Noon = Noon - longitude;

  zuhrTime = UT_Noon / 15 + timeZone;

  double Asr_Alt =
    radToDeg(
      atan(1 + tan(degToRad(abs(latitude - Dec))))
    );

  double Asr_Arc =
    radToDeg(
      acos(
        (sin(degToRad(90 - Asr_Alt))
         - sin(degToRad(Dec))
         * sin(degToRad(latitude)))
        /
        (cos(degToRad(Dec))
         * cos(degToRad(latitude)))
      )
    );

  Asr_Arc = Asr_Arc / 15;

  asrTime = zuhrTime + Asr_Arc;

  sunRiseTime = zuhrTime - (Durinal_Arc / 15);

  maghribTime = zuhrTime + (Durinal_Arc / 15);

  double Esha_Arc =
    radToDeg(
      acos(
        (sin(degToRad(ishaTwilight))
         - sin(degToRad(Dec))
         * sin(degToRad(latitude)))
        /
        (cos(degToRad(Dec))
         * cos(degToRad(latitude)))
      )
    );

  ishaTime = zuhrTime + (Esha_Arc / 15);

  double Fajr_Arc =
    radToDeg(
      acos(
        (sin(degToRad(fajrTwilight))
         - sin(degToRad(Dec))
         * sin(degToRad(latitude)))
        /
        (cos(degToRad(Dec))
         * cos(degToRad(latitude)))
      )
    );

  fajrTime = zuhrTime - (Fajr_Arc / 15);
}

// =========================

void formatTime(double t, char* buf) {

    int h, m;

    doubleToHrMin(t, h, m);

    bool isPM = false;

    // =====================
    // KONVERSI 12 JAM
    // =====================

    if (h >= 12)
        isPM = true;

    if (h == 0)
        h = 12;

    else if (h > 12)
        h -= 12;

    sprintf(
        buf,
        "%02d:%02d",
        h,
        m
    );
}

// =========================

void hitungJadwalSholat(DateTime now) {

  double fajr, sunrise, zuhr, asr, maghrib, isha;

  calcPrayerTimes(
    now.year(),
    now.month(),
    now.day(),
    LONGITUDE,
    LATITUDE,
    TIMEZONE,
    -20,
    -18,
    fajr,
    sunrise,
    zuhr,
    asr,
    maghrib,
    isha
  );

  formatTime(fajr, waktuSubuh);
  formatTime(zuhr, waktuDzuhur);
  formatTime(asr, waktuAshar);
  formatTime(maghrib, waktuMaghrib);
  formatTime(isha, waktuIsya);

  int currentMinute = now.hour() * 60 + now.minute();

  int prayerMinutes[5];

  int h, m;

  doubleToHrMin(fajr, h, m);
  prayerMinutes[0] = h * 60 + m;

  doubleToHrMin(zuhr, h, m);
  prayerMinutes[1] = h * 60 + m;

  doubleToHrMin(asr, h, m);
  prayerMinutes[2] = h * 60 + m;

  doubleToHrMin(maghrib, h, m);
  prayerMinutes[3] = h * 60 + m;

  doubleToHrMin(isha, h, m);
  prayerMinutes[4] = h * 60 + m;

  const char* prayerNames[5] = {
    "SUBUH",
    "DZUHR",
    "ASHAR",
    "MAGRIB",
    "I`SYA"
  };

  int nextPrayer = 0;

  for (int i = 0; i < 5; i++) {
    if (currentMinute < prayerMinutes[i]) {
      nextPrayer = i;
      break;
    }
  }

  strcpy(sholatName, prayerNames[nextPrayer]);

  int diff = prayerMinutes[nextPrayer] - currentMinute;

  if (diff < 0)
    diff += 1440;

  int jam = diff / 60;
  int menit = diff % 60;

  sprintf(
    countdownText,
    "%02dJ  %02dM",
    jam,
    menit
  );

  sprintf(
    tanggalText,
    "%s %02d/%02d/%04d",
    namaHari[now.dayOfTheWeek()],
    now.day(),
    now.month(),
    now.year()
  );
}

// =========================

void drawScreen_UTAMA(DateTime now) {

  display.clearDisplay();

  char jamText[16];

  bool isPM = now.hour() >= 12;

  int displayHour = now.hour();

  if (displayHour == 0)
    displayHour = 12;

  if (displayHour > 12)
    displayHour -= 12;

  sprintf(
    jamText,
    "%02d:%02d:%02d",
    displayHour,
    now.minute(),
    now.second()
  );

  display.setTextColor(1);
  display.setTextSize(2);
  display.setTextWrap(false);

  display.setFont(&Org_01);

  display.setCursor(35, 12);
  display.print(jamText);

  display.setTextSize(1);

  display.setCursor(115, 11);

  if (isPM)
    display.print("PM");
  else
    display.print("AM");

  display.setFont();

  display.setCursor(0, 0);
  display.print("I`SYA");

  display.setCursor(0, 10);
  display.print(waktuIsya);

  display.setCursor(0, 21);
  display.print("SUBUH");

  display.setCursor(0, 31);
  display.print(waktuSubuh);

  display.setTextColor(1, 0);

  display.setCursor(33, 21);
  display.print("DZUHR");

  display.setTextColor(1);

  display.setCursor(33, 31);
  display.print(waktuDzuhur);

  display.setCursor(66, 21);
  display.print("ASHAR");

  display.setCursor(66, 31);
  display.print(waktuAshar);

  display.setCursor(99, 21);
  display.print("MAGRB");

  display.setCursor(99, 31);
  display.print(waktuMaghrib);

  display.setCursor(45, 48);
  display.print(tanggalText);

  display.setCursor(81, 57);
  display.print(countdownText);

  display.setCursor(39, 57);
  display.print(sholatName);

  display.drawBitmap(
    73,
    57,
    image_COUNTDOWN_icon_bits,
    4,
    7,
    1
  );

  display.display();
}

// =========================

void setup() {

  Wire.begin(D2, D1);

  rtc.begin();

  // SET SEKALI SAJA
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  display.begin(
    SSD1306_SWITCHCAPVCC,
    0x3C
  );
drawopening_boot_awal_dinyalakan();

delay(3000);

  display.clearDisplay();
  display.display();
}

// =========================

void loop() {

    static uint32_t lastUpdate = 0;

    if (millis() - lastUpdate >= 1000) {

        lastUpdate = millis();

        DateTime now = rtc.now();

        hitungJadwalSholat(now);

        cekAlarmSholat(now);

        // =========================
        // MODE ALARM SHOLAT
        // =========================

        if (modeAlarmSholat) {

            drawTAMPILAN_ALARM();

            // 1 MENIT
            if (millis() - alarmStartMillis >= 60000) {

                modeAlarmSholat = false;
            }
        }

        // =========================
        // SCREEN NORMAL
        // =========================

        else {

            drawScreen_UTAMA(now);
        }
    }
}

void cekAlarmSholat(DateTime now) {

    static int lastMinute = -1;

    if (lastMinute == now.minute())
        return;

    lastMinute = now.minute();

    char waktuSekarang[6];

    sprintf(
        waktuSekarang,
        "%02d:%02d",
        now.hour(),
        now.minute()
    );

    if (strcmp(waktuSekarang, waktuSubuh) == 0) {

        strcpy(namaAlarmSholat, "SUBUH");

        modeAlarmSholat = true;

        alarmStartMillis = millis();
    }

    else if (strcmp(waktuSekarang, waktuDzuhur) == 0) {

        strcpy(namaAlarmSholat, "DZUHR");

        modeAlarmSholat = true;

        alarmStartMillis = millis();
    }

    else if (strcmp(waktuSekarang, waktuAshar) == 0) {

        strcpy(namaAlarmSholat, "ASHAR");

        modeAlarmSholat = true;

        alarmStartMillis = millis();
    }

    else if (strcmp(waktuSekarang, waktuMaghrib) == 0) {

        strcpy(namaAlarmSholat, "MAGRIB");

        modeAlarmSholat = true;

        alarmStartMillis = millis();
    }

    else if (strcmp(waktuSekarang, waktuIsya) == 0) {

        strcpy(namaAlarmSholat, "I`SYA");

        modeAlarmSholat = true;

        alarmStartMillis = millis();
    }
}
