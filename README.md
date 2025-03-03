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
* [Dokumentasi Soal 1](#Dokumentasi-soal1)  

---
* [Soal 2]
  * [Soal 2a](#soal-2a)

Source Code : [soal2.c]
* [Dokumentasi Soal 2](#Dokumentasi-soal2)  

---
* [Soal 3]
  * [Soal 3a](#soal-3a)
  * [Soal 3b](#soal-3b)
  * [Soal 3c](#soal-3c)	
  * [Soal 3d](#soal-3d)
  * [Soal 3e](#soal-3e) 

Source Code : [soal3.c](https://github.com/MSRanggaS/soal-shift-sisop-modul-2-T14-2021/blob/master/soal3/soal3.c/)
* [Dokumentasi Soal3](#Dokumentasi-soal3)  

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

# Dokumentasi Soal1
<img src="https://user-images.githubusercontent.com/61416036/115102885-0f81f880-9f78-11eb-94db-59c62e0c4b51.png">

- setelah daemon dijalankan, dan waktu diubah menjadi 2021-04-09 16:21:59 maka 1 detik berikutnya daemon akan melakukan pembuatan folder, pendownloadan zip, penextractan zip yang telah di download, dan memindahkan ke folder yang telah dibuat

<img src="https://user-images.githubusercontent.com/61416036/115102881-0db83500-9f78-11eb-8420-fe3a64d71f87.png">

- mengzip folder yang telah di download dan menghapus folder yang ada sehingga menyisakan zip

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

# Dokumentasi Soal2
<img src="https://user-images.githubusercontent.com/61416036/115104218-27aa4580-9f81-11eb-9f08-6819cfc2fb62.png">

- dari zip yang sudah di download, maka di extract ke dalam sebuah folder yang bernama `petshop`. dan kemudian folder-folder yang tidak dibutuhkan sudah dihapus menyisakan gambar hewan-hewan peliharaan
 
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

          sleep(5);

          }
```

* Variabel `w` berfungsi untuk menyimpan *timestamp* dalam waktu saat ini dan formatnya juga perlu diubah ke format yang lebih standar
* Variabel `a` berfungsi untuk menyipan gambar dengan ukuran (n%1000) + 50 pixel dimana n adalah detik *Epoch Unix*
* Perintah `sprint (url, "https://picsum.photos/%d", a);` berfungsi untuk mendownload gambar pada URL tersebut
* Perintah `strftime(file, 50, "%Y-%m-%d_%H:%M:%S", wm);`adalah format penamaan file [YYYY-mm-dd_HH:ii:ss]
* Perintah `sprintf (save, "%s/%s", str, file);` adalah perintah save file
* Perintah `wget` berfungsi untuk mendowload otomatis

## Soal 3c
**Deskripsi:**\
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

**Pembahasan**\
```c
 while(wait(NULL) >0);
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

## Soal 3d
**Deskripsi:**\
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

**Pembahasan:**\
Untuk men-generate sebuah program yang bisa menterminasi semua operasi program, kami pertama membuat file yang akan kami inputkan dengan kode C.
```c
 FILE *fileKiller;
    fileKiller = fopen("killer.sh", "w+");
```
- `fileKiller` akan digunakan sebagai pointer ke-file yang diinginkan
- `fopen`digunakan untuk membuka file yang diinginkan, karena mode yang kami gunakan adalah `w+` sehingga akan membuat file baru dan melakukan proses writing.
- Deklarasi diatas dilakukan sebelum bagian loop utama daemon dan setelah mendapatkan Session ID (`sid`).

```c
 char *contents = ""
    "#!/bin/bash\n"
    "/usr/bin/pkill -9 -s \"%d\"\n"
    "/bin/rm killer.sh";
    fprintf(fileKiller, contents, sid);
```
Lalu file `killer.sh` akan melakukan perintah pkill sesuai dengan Session ID (`sid`) dari program utama (Penggunaan Session ID agar seluruh child process juga ikut di kill melalui perintah pkill). Lalu program killer tersebut akan menghapus dirinya sendiri. Cara tersebut dapat dilakukan dengan melakukan `fork()` dimana child process akan melakukan `pkill` dan `parent` process akan menunggu `child` process dan melakukan `rm`. Lalu string tersebut diwrite kedalam `fileKiller` dengan fungsi `fprintf().`

```c
 fclose(fileKiller);
```
Lalu pointer file (`fileKiller`) akan ditutup koneksinya menggunakan fungsi `fclose()`.

```c
  pid = fork();
  if (pid == 0) {
    char *argt[] = {"chmod", "777", "killer.sh", NULL};
    execv("/bin/chmod", argt);
  }

  while(wait(NULL) != pid);
```
Lalu program utama akan membuat `child` process untuk melakukan compile terhadap file `killer.sh` menggunakan perintah chmod. Setelah itu program utama akan membuat child process kembali untuk melakukan remove terhadap file `killer.sh` menggunakan perintah `rm`.

## Soal 3e
**Deskripsi:**\
Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dsdengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

**Pembahasan:**\
```c
void killer(char argc[]){
  
}

int main(int argc, char **argv) {
    
  if(argc != 2){
    printf("Tidak terdefinisi, diharapkan ./new -z | ./new -x\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "-x") != 0 && strcmp(argv[1], "-z") != 0) {
    printf("Argumen kurang benar\n");
    return 1;
  }
```
banyaknya argument akan dicek dan `argv[]` akan dicek apakah sesuai dengan mode yang ada.

```c
  if(strcmp(argv[1],"-z") == 0){
    FILE *fileKiller;
    fileKiller = fopen("killer.sh", "w+");
    
    char *contents = ""
    "#!/bin/bash\n"
    "/usr/bin/pkill -9 -s \"%d\"\n"
    "/bin/rm killer.sh";
    fprintf(fileKiller, contents, sid);

    fclose(fileKiller);
  }
  if(strcmp(argv[1],"-x") == 0 ){
    FILE *fileKiller;
    fileKiller = fopen("killer.sh", "w+");

    char *contents = ""
    "#!/bin/bash\n"
    "/usr/bin/kill -9 \"%d\"\n"
    "/bin/rm killer.sh";
    fprintf(fileKiller, contents, getpid());
    
    fclose(fileKiller);
  }

```
Lalu, pada proses mendefinisian string untuk diinputkan pada [Soal 3d](#soal-3d)., akan dicek untuk masing masing arguments dan akan diberikan input yang berbeda. Untuk argument `-z` akan menggunakan input yang sama dengan Soal 2.d.. Untuk argument `-x` akan menggunakan perintah kill kepada Process ID yang dimiliki oleh process utama. Untuk mendapatkannya, kami menggunakan fungsi `getpid()`. Lalu pada masing-masing mode akan diwrite pada `fileKiller` dengan input yang sesuai dan Session ID atau Process ID yang sesuai. Setelah itu, program itu akan di-compile dan di-remove dengan metode yang sama seperti [Soal 3d](#soal-3d).

# Dokumentasi Soal3
<img src="https://user-images.githubusercontent.com/61416036/114886765-04bd4b80-9e32-11eb-9239-65f6a3b0d356.png">

- melakukan pembuatan folder bernama `waktu setempat` dan kemudian pendownloadan gambar pada link dan akan mendownload setiap 10 gambar yang ada

<img src="https://user-images.githubusercontent.com/61416036/114983857-4fcf7100-9ebb-11eb-90ef-1ce6c77d49dc.png">

- mendownload 10 gambar dari drive, dan menyimpannya dengan format folder [YYYY-mm-dd_HH:ii:ss]

<img src="https://user-images.githubusercontent.com/61416036/114983865-50680780-9ebb-11eb-8de7-43fd56d9ee1c.png">

- Membuat file `status.text` yang isi text nya adalah `Download Success`, setelah itu kita encrypt dan di masukkan ke dalam zip
  
<img src="https://user-images.githubusercontent.com/61416036/115736365-71e25b00-a3b5-11eb-8a44-788c79915d70.png">

-
