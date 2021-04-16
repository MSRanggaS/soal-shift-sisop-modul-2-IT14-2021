# soal-shift-sisop-modul-2-IT14-2021

Repository Sebagai Laporan Resmi Soal Shift Modul 2 Praktikum Sistem Operasi 2021
Disusun oleh :

- Romandhika (05311800000-)
- M. Shaladin Rangga (05311940000029)
- Moh. Ibadul Haqqi (05311940000037)

### Soal 3

a. Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].
b. Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.
c. Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.
d. Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.
e. Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

**Note:**
- Tidak boleh menggunakan system() dan mkdir()
- Program utama merupakan SEBUAH PROGRAM C
- Wajib memuat algoritma Caesar Cipher pada program utama yang dibuat

## Soal 3.a
**Deskripsi:**\
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

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
- Fungsi diatas merupakan deklarasi dari variabel yang akan digunakan

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
 
# Dokumentasi no 3a
<img src="https://user-images.githubusercontent.com/61416036/114983849-4e05ad80-9ebb-11eb-943f-c05d42f49cec.png">

* pada window sebelah kiri adalah tampilan dari zip yang berisikan sebuah folder bernama tanggal dan waktu setempat dengan isi 10 foto dan status.txt yang berisi `Download Success` yang sudah di encrypt


## Soal 3b
**Deskripsi:**
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

**Pembahasan**
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
          else{
            wait(NULL);
          }

          sleep(5);

        }
          }
```

* Variabel `w` berfungsi untuk menyimpan *timestamp* dalam waktu saat ini dan formatnya juga perlu diubah ke format yang lebih standar
* Variabel `a` berfungsi untuk menyipan gambar dengan ukuran (n%1000) + 50 pixel dimana n adalah detik *Epoch Unix*
* Perintah `sprint (url, "https://picsum.photos/%d", a);` berfungsi untuk mendownload gambar pada URL tersebut
* Perintah `strftime(file, 50, "%Y-%m-%d_%H:%M:%S", wm);`adalah format penamaan file [YYYY-mm-dd_HH:ii:ss]
* Perintah `sprintf (save, "%s/%s", str, file);` adalah perintah save file
* Perintah `wget` berfungsi untuk mendowload otomatis

## Dokumentasi 3b
<img src="https://user-images.githubusercontent.com/61416036/114983857-4fcf7100-9ebb-11eb-90ef-1ce6c77d49dc.png">

## Soal 3c
**Deskripsi:**\
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

**Pembahasan**\
```
 chdir(str);
        char message[100]="Download Success", ch;
        int i, key=5;
```

* perintah `chdir` untuk memindah direktori ke folder bernama `str`
* `char message[100]="Download Success", ch;` adalah message yang menyimpan array 100 yang bervariabel `char`yang isinya `"Dowmload Success"`
* `key=5` adalah pergeseran huruf sebanyak 5 kali

```
    for(i = 0; message[i] != '\0'; ++i){
          ch = message[i];
          
          if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            
            if(ch > 'z'){
              ch = ch - 'z' + 'a' - 1;
            }
            
            message[i] = ch;
          }
          else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            
            if(ch > 'Z'){
              ch = ch - 'Z' + 'A' - 1;
            }
            
            message[i] = ch;
          }
        }
```
* encrypt menggunakan perulangan `for loop`
* `ch` adalah isi pesan asli
* `for(ch >='a' && ch <= 'z')` jika `ch >= a && ch` <=z maka `ch` akan ditambah dengan `key` yang artinya di geser sebanyak 5
* jika `ch > z` maka akan `- 'z' + 'a' -1`
* begitu juga sama yang dialami pada 'A' dan 'Z'


## Dokumentasi 3c
<img src="https://user-images.githubusercontent.com/61973814/114990579-d9cf0800-9ec2-11eb-9d3a-344250f90603.png">
