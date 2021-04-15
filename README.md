# soal-shift-sisop-modul-2-IT14-2021

Repository Sebagai Laporan Resmi Soal Shift Modul 2 Praktikum Sistem Operasi 2021
Disusun oleh :

- Romandhika (05311800000-)
- M. Shaladin Rangga (05311940000029)
- Moh. Ibadul Haqqi (05311940000037)

## Soal 3.a
**Deskripsi:**\
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

**Note:**
- Tidak boleh menggunakan system() dan mkdir()
- Program utama merupakan SEBUAH PROGRAM C
- Wajib memuat algoritma Caesar Cipher pada program utama yang dibuat
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
- Diatas merupakan ***library*** yang digunakan untuk menunjang dan menjalankan program.

```c
int main() {
    pid_t child_id,child2,child3,child4;
    int status;

    char str[50], url[100], file[100], save[100];
    int a;
```
- Fungsi diatas merupakan deklarasi dari sebuah variabel

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
* Variable `tm` dan `wm` digunakan untuk menyimpan timestamp yang sudah terstruktur sesuai dengan `localtime`
* kode `strftime` diatas digunakan untuk melakukan formatting dari waktu `tm` menjadi string sesuai dengan format yang diinginkan (**[YYYY-mm-dd_HH:ii:ss]**) kedalam buffer `now` sebesar `50`.
* Variable `now` akan digunakan sebagai buffer dari string hasil format variable `tm`

```c
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }
    ```
* Keluar pada saat fork gagal `pid < 0`

```c
   if (child_id == 0)
    {
        char *argv[] = {"mkdir", "-p", str, NULL};
	  	  execv("/bin/mkdir", argv);
    }
    ```
* Jika `pid == 0` akan melakukan process di `fork()` dan *child process* dan akan melakukan `execv()` terhadap perintah `mkdir` dengan *argument* `now`

```c
 else{
      wait(NULL);
      
      child2 = fork();

      if (child2 < 0){
          exit(EXIT_FAILURE);
      }

      if (child2 == 0){

          for (int i = 0; i < 10; i++) {

          child3 = fork();

          if (child3 < 0){
          exit(EXIT_FAILURE);
          }
 ```
 
 * jika tidak, maka `child_id` akan menunggu dan melakukan proses `child2`
 * pada bagian `for (int i = 0; i < 10; i++)` akan melakukan perulangan download gambar sebanyak 10 kali pada setiap folder
 
 ```c
           if (child3 == 0) {

            w = time(NULL);
            wm = localtime(&w);
            a = (w%1000)+50;
            sprintf (url, "https://picsum.photos/%d", a);
            strftime(file, 50, "%Y-%m-%d_%H:%M:%S", wm);
            sprintf (save, "%s/%s", str, file);
            char *args[] = {"wget","--no-check-certificate", "-q", "-O", save, url, NULL};

            execv("/usr/bin/wget", args);

          }
```

* Variabel `w` berfungsi untuk menyimpan *timestamp* dalam waktu saat ini dan formatnya juga perlu diubah ke format yang lebih standar
* Variabel `a` berfungsi untuk menyipan gambar dengan ukuran (n%1000) + 50 pixel dimana n adalah detik *Epoch Unix*
* Perintah `sprint (url, "https://picsum.photos/%d", a);` berfungsi untuk mendownload gambar pada URL tersebut
* Perintah `strftime(file, 50, "%Y-%m-%d_%H:%M:%S", wm);`adalah format penamaan file [YYYY-mm-dd_HH:ii:ss]
* Perintah `sprintf (save, "%s/%s", str, file);` adalah perintah save file
* Perintah `wget` berfungsi untuk mendowload otomatis


 # Dokumentasi no 3 
<img src="https://user-images.githubusercontent.com/61416036/114886765-04bd4b80-9e32-11eb-9239-65f6a3b0d356.png">

* pada window sebelah kiri adalah tampilan dari zip yang berisikan sebuah folder bernama tanggal dan waktu setempat dengan isi 10 foto dan status.txt yang berisi `Download Success` yang sudah di encrypt
