# soal-shift-sisop-modul-2-IT14-2021

Repository Sebagai Laporan Resmi Soal Shift Modul 2 Praktikum Sistem Operasi 2021
Disusun oleh :

- Romandhika Rijal I (0531180000048)
- M. Shaladin Rangga (05311940000029)
- Moh. Ibadul Haqqi (05311940000037)

---
# Daftar Isi

---
* [Soal 1]
  * [Soal 1a](#soal-1a)
  * [Soal 1b](#soal-1b)  
  * [Soal 1c](#soal-1c)
  * [Soal 1d](#soal-1d)
  * [Soal 1e](#soal-1e)
  * [Soal 1f](#soal-1f)
 
Source Code : [soal1.c](https://github.com/MSRanggaS/soal-shift-sisop-modul-2-T14-2021/blob/master/soal1/soal1.c)
* [Dokumentasi Soal 1a](#Dokumentasi-soal1)  

---
* [Soal 2]
  * [Soal 2a](#soal-2a)
  	* [Dokumentasi Soal 2](#Dokumentasi-soal2) 
  * [Soal 2b](#soal-2b)
  * [Soal 2c](#soal-2c)
  * [Soal 2d](#soal-2d)
  * [Soal 2e](#soal-2e)
  * [Dokumentasi Soal 2](#Dokumentasi-soal2)

Source Code : [soal2.c]

---
* [Soal 3]
  * [Soal 3a](#soal-3a)
  	* [Dokumentasi Soal3a](#Dokumentasi-3a) 
  * [Soal 3b](#soal-3b)
  	* [Dokumentasi Soal3b](#Dokumentasi-3b)
  * [Soal 3c](#soal-3c)
  	* [Dokumentasi Soal3c](#Dokumentasi-3c) 	
  * [Soal 3d](#soal-3d)
  	* [Dokumentasi Soal3d](#Dokumentasi-3d) 
  * [Soal 3e](#soal-3e)
  	* [Dokumentasi Soal3e](#Dokumentasi-3e)	 

Source Code : [soal3.c](https://github.com/MSRanggaS/soal-shift-sisop-modul-2-T14-2021/blob/master/soal3/soal3.c/)

---

## Soal 1a
**Deskripsi:**\
Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg (b) untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga 

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
int main(){
    pid_t pid, sid;     
    char file[100],fole[100]; 
    time_t w,t;
    struct tm *wm, *tm;
    pid_t child_id = fork();
    pid = fork();   
```
- Variable `t` dan `w` digunakan untuk menyimpan timestamp dalam format epoch/unix timestamp.
- Variable `wm` akan digunakan untuk menyimpan timestamp yang sudah terstruktur sesuai dengan `localtime` nantinya
- Lalu kami melakukan `fork()`. sehingga menghasilkan parent process dengan variable `pid` akan berisi `PID` dari child processnya dan child process dengan variable `pid` berisi nilai 0. 

```c
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
```
- kami akan melakukan `fork()`. sehingga menghasilkan parent process dengan variable `pid` berisi `PID` dari child processnya dan child process dengan variable pid berisi nilai 0. Lalu parent process akan di keluarkan menggunakan fungsi `exit()` dengan exit statusnya.

```c
 while (1) {

        w = time(NULL);
        wm = localtime(&w);
        strftime(file, 50, "%Y-%m-%d_%H:%M:%S", wm);
        if(strcmp(file,"2021-04-09 16:22:00") == 0){
```
- kami akan mengeset waktu saat ini pada variable `w` dengan fungsi `time(NULL)`. Karena format dari variable `w` masih dalam epoch/unix timestamp, sehingga perlu diubah ke bentuk format yang sudah terstandard. dan Disini kami menggunakan fungsi `localtime` dan memasukkannya kedalam variable `wm`.
- membuat variabel `file` yang berformat [YYYY-mm-dd_HH:ii:ss] pada linux

```c
    pid_t child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"mkdir", "-p", "Musyik", NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(NULL) != child_id);

    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"mkdir", "-p", "Fylm", NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(NULL) != child_id);

    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"mkdir", "-p", "Pyoto", NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(NULL) != child_id);
```
- intinya pada tiap child tersebut akan membuat masing-masing folder yang bernama: `Musyik`, `Fylm`, `Pyoto`
- `while(wait(NULL) != child_id);` dan variabel tersebut berfungsi agar menunggu selesai foldernya dahulu lalu dilanjutkan selanjutnya agar tidak bertabrakan outputnya

## Soal 1b
**Deskripsi:**\
 untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga
 
 **Pembahasan:**\
```c
 child_id = fork();
    if (child_id == 0) {
        char *args[] = {"wget","--no-check-certificate", "-q", 
        "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
        "-O", "Foto_for_Stevany.zip", NULL};
        execv("/usr/bin/wget", args);
    }
    while(wait(NULL) != child_id)
```
- Perintah tersebut akan mendownload dari google drive tersebut yang akan dinamai `Foto_for_Stevany.zip`

```c
    child_id = fork();
    if (child_id == 0) {
        char *args[] = {"wget","--no-check-certificate", "-q", 
        "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
        "-O", "Musik_for_Stevany.zip", NULL};
        execv("/usr/bin/wget", args);
    }
    while(wait(NULL) != child_id);
```
- Perintah tersebut akan mendownload dari google drive tersebut yang akan dinamai `Musik_for_Stevany.zip`

```c
    child_id = fork();
    if (child_id == 0) {
        char *args[] = {"wget","--no-check-certificate", "-q", 
        "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download",
        "-O", "Film_for_Stevany.zip", NULL};
        execv("/usr/bin/wget", args);
    }
    while(wait(NULL) != child_id);
```
- Perintah tersebut akan mendownload dari google drive tersebut yang akan dinamai `Film_for_Stevany.zip`

## Soal 1c
**Deskripsi:**\
Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload

**Pembahasan:**

```c
child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"unzip", "-q", "Foto_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while(wait(NULL) != child_id);
    
    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"unzip", "-q", "Musik_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while(wait(NULL) != child_id);
    
    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"unzip", "-q", "Film_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while(wait(NULL) != child_id);
```
- `unzip` adalah perintah untuk mengextract file yang ada di file tersebut secara otomatis. Masing-masing ada `Foto`, `Musik`, `Film`

## Soal 1d
**Deskripsi:**\
memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan)

**Pembahasan:**

```c
                child_id = fork();
                if (child_id == 0) {
                char *argv[] = {"find","FOTO","-type","f","-name","*",
                                "-exec","mv","-t","Pyoto/","{}","+",NULL};
                execv("/bin/find", argv);
                }
                while(wait(NULL) != child_id);

                child_id = fork();
                if (child_id == 0) {
                char *argv[] = {"find","MUSIK","-type","f","-name","*",
                                "-exec","mv","-t","Musyik/","{}","+",NULL};
                execv("/bin/find", argv);
                }
                while(wait(NULL) != child_id);

                child_id = fork();
                if (child_id == 0) {
                char *argv[] = {"find","FILM","-type","f","-name","*",
                                "-exec","mv","-t","Fylm/","{}","+",NULL};
                execv("/bin/find", argv);
                }
                while(wait(NULL) != child_id);

            }            

            break;
```
- intinya perintah tersebut untuk mencari sebuah file dalam folder `FOTO` dengan format `name`. Setelah menemukan foldernya, maka semua file yang ada di `FOTO` dipindah ke folder `Pyoto`. begitu juga yang dialami oleh `MUSIK`, `FILM`.
- lalu `break` berfungsi buat ketika fungsi `for` selesai maka akan keluar dari fungsi tersebut dan melanjutkan perintah selanjutnya 

## Soal 1e
**Deskripsi:**\
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany

**Pembahasan:**\
```c
        w = time(NULL);
        wm = localtime(&w);
        strftime(file, 50, "%Y-%m-%d %H:%M:%S", wm);
        if(strcmp(file,"2021-04-09 16:22:00") == 0){
```
- kami akan mengeset waktu saat ini pada variable `w` dengan fungsi `time(NULL)`. Karena format dari variable `w` masih dalam epoch/unix timestamp, sehingga perlu diubah ke bentuk format yang sudah terstandard. dan Disini kami menggunakan fungsi `localtime` dan memasukkannya kedalam variable `wm`.
- membuat variabel `file` yang berformat [YYYY-mm-dd_HH:ii:ss] pada linux

## Soal 1f
**Deskripsi:**\
Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip

**Pembahasan:**\

```c
   while (1) {

        w = time(NULL);
        wm = localtime(&w);
        strftime(file, 50, "%Y-%m-%d %H:%M:%S", wm);
        if(strcmp(file,"2021-04-09 22:22:00") == 0){

            child_id = fork();
            if (child_id == 0) {
                char *argv[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
                execv("/usr/bin/zip", argv);
            }
            else{

                child_id = fork();
                if (child_id == 0) {
                    char *argv[] = {"rm", "-r", "FILM", "FOTO", "MUSIK", "Pyoto", "Fylm", "Musyik", NULL};
                    execv("/bin/rm", argv);
                }
                while(wait(NULL) != child_id);

            }

            break;
```
- ` char *argv[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};` yang artinya membuat file `zip` yang berisikan file `Pyoto`, `Musyik`, `Fylm`
-  `char *argv[] = {"rm", "-r", "FILM", "FOTO", "MUSIK", "Pyoto", "Fylm", "Musyik", NULL};` selesai membuat `zip`, folder `FOTO`, `FILM`, `MUSIK`, `Pyoto`, `Fylm`, `Musyik` akan dihapus menggunakan perintah `rm`

## Soal 2.a
**Deskripsi:**\
Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

**Pembahasan:**

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
#include <wait.h>
#include <time.h>
#include <dirent.h>
```
- Diatas merupakan ***library*** yang digunakan untuk menunjang dan menjalankan program.

```c
int main(){
    pid_t child_id = fork();

    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"mkdir", "-p", "petshop", NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(NULL) != child_id);
```
- intinya perintah tersebut untuk membuat folder dengan nama `petshop`

```c
    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"unzip", "-q", "pets.zip", "-d", "petshop", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while(wait(NULL) != child_id);
```
- selanjutnya jika sudah membuat folder `petshop`, kita akan mengeluarkan semua file yang ada di `pets.zip` ke dalam folder `petshop`

```c
    child_id = fork();
    if (child_id == 0) {
    char *argv[] = {"find","petshop","-mindepth","1","-type","d","-name","*",
                    "-exec","rm","-r","{}","+",NULL};
    execv("/bin/find", argv);
    }
    while(wait(NULL) != child_id);
```
- di dalam folder `petshop` dan mencari file dengan kategori `folder`, dan kalau sudah menemukannya maka akan di remove

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
 
# Dokumentasi 3a
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
```c
 chdir(str);
        char message[100]="Download Success", ch;
        int i, key=5;
```

* perintah `chdir` untuk memindah direktori ke folder bernama `str`
* `char message[100]="Download Success", ch;` adalah message yang menyimpan array 100 yang bervariabel `char`yang isinya `"Dowmload Success"`
* `key=5` adalah pergeseran huruf sebanyak 5 kali

```c
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
