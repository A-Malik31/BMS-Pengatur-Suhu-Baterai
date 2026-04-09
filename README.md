# BMS-Pengatur-Suhu-Baterai

## Deskripsi

Battery Management System (BMS) dengan pengatur suhu baterai merupakan sistem yang dirancang untuk memonitor dan melindungi paket baterai sekaligus menjaga suhu operasional agar tetap optimal. Sistem ini menggunakan pendekatan modular dengan satu pengendali utama dan beberapa perangkat bawahan untuk meningkatkan fleksibilitas serta kemudahan pengembangan.

---

## 1. Fitur Utama

BMS dengan pengatur suhu baterai memiliki dua fitur utama, yaitu **monitoring** dan **proteksi**.

### Monitoring

Fitur monitoring digunakan untuk melakukan pengawasan terhadap kondisi utama baterai secara real-time, meliputi:

* Tegangan baterai
* Arus baterai
* Suhu baterai

Data monitoring ini digunakan sebagai dasar dalam pengambilan keputusan sistem kendali dan proteksi.

### Proteksi

Fitur proteksi bertujuan untuk menjaga baterai dari kondisi yang berpotensi merusak atau berbahaya, meliputi:

* Cut-off tegangan berlebih dan tegangan rendah
* Cell balancing untuk menjaga keseragaman tegangan antar sel
* Pengaturan suhu baterai menggunakan sistem kendali suhu

---

## 2. Parameter

Sel baterai yang digunakan diasumsikan berupa sel tipe 18650 yang disusun menjadi sebuah paket. Setiap paket terdiri dari puluhan atau ratusan sel yang dirangkai secara paralel.

Karakteristik sel:

* Tegangan minimum : 3,0 V (kosong)
* Tegangan maksimum : 4,2 V (penuh)

Konfigurasi paket baterai:

* Paket baterai 12V DC menggunakan 4 sel secara seri (4S)
* Tegangan total paket : 12V – 16,8V DC

Baterai diharapkan mampu menghasilkan daya minimum yang cukup untuk menjalankan sistem kendali suhu baterai.

Sistem kendali suhu menggunakan:

* Elemen Peltier sebagai aktuator pendingin/pemanas
* Metode kendali PID untuk menjaga suhu baterai tetap stabil

---

## 3. Desain BMS

Sistem BMS dirancang menggunakan konsep modular yang terdiri dari:

* Satu perangkat utama (master)
* Empat perangkat bawahan (slave)

### Mikrokontroler

* ESP8266 sebagai mikrokontroler utama
* ATTINY85 sebagai mikrokontroler bawahan
* Arduino Nano sebagai mikrokontroler bawahan tambahan

### Sensor

* Sensor arus menggunakan ACS712
* Sensor suhu menggunakan DS18B20

### Aktuator

* Elemen Peltier sebagai pengatur suhu baterai
* Driver L298N untuk mengendalikan elemen Peltier

Konsep modular ini memungkinkan sistem untuk dikembangkan lebih lanjut dengan menambah jumlah modul pengawasan baterai sesuai kebutuhan.
