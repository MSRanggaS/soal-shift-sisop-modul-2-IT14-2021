# soal-shift-sisop-modul-2-IT14-2021

Repository Sebagai Laporan Resmi Soal Shift Modul 2 Praktikum Sistem Operasi 2021
Disusun oleh :

-Romandhika (05311800000-)
-M. Shaladin Rangga (05311940000029)
-Moh. Ibadul Haqqi (05311940000037)

## Soal 3.a
**Deskripsi:**\
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].
**Note:**\
-Tidak boleh menggunakan system() dan mkdir()
-Program utama merupakan SEBUAH PROGRAM C
-Wajib memuat algoritma Caesar Cipher pada program utama yang dibuat
**Pembahasan:**\
Pertama, kami akan melakukan `#include` library yang diperlukan
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>
```
-Diatas merupakan ***library*** yang digunakan untuk menunjang dan menjalankan program.

```c
int main() {
    pid_t child_id,child2,child3,child4;
    int status;

    char str[50], url[100], file[100], save[100];
    int a;
```
-Fungsi diatas merupakan deklarasi dari sebuah variabel

```c
 time_t t, w;
    t = time(NULL);
    struct tm *tm, *wm;
    tm = localtime(&t);
    strftime(str, 50, "%Y-%m-%d_%H:%M:%S", tm);
    char now[80];
    strftime(now, 80, "%Y-%m-%d_%H:%M:%S", tm);
```
* Variable `t` digunakan untuk menyimpan timestamp dalam format **epoch/unix timestamp**.
* Variable `tm` digunakan untuk menyimpan timestamp yang sudah terstruktur sesuai dengan `localtime`
* kode `strftime` diatas digunakan untuk melakukan formatting dari waktu `tm` menjadi string sesuai dengan format yang diinginkan (**[YYYY-mm-dd_HH:ii:ss]**) kedalam buffer `now` sebesar `50`.
* Variable `now` akan digunakan sebagai buffer dari string hasil format variable `tm`
* 
  
<img src="https://user-images.githubusercontent.com/61416036/114886765-04bd4b80-9e32-11eb-9239-65f6a3b0d356.png">
