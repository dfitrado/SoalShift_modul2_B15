# Laporan Soal Shift Modul 2
<br />

Daftar Isi
1. [NO1](#NO1)
2. [NO2](#NO2)
3. [NO3](#NO3)
4. [NO4](#NO4)
5. [NO5](#NO5)

## NO1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

### JAWAB:

### PENJELASAN:


## NO2
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

### JAWAB:

### PENJELASAN:


## NO3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
- Gunakan fork dan exec.
- Gunakan minimal 3 proses yang diakhiri dengan exec.
- Gunakan pipe
- Pastikan file daftar.txt dapat diakses dari text editor

### JAWAB:

### PENJELASAN:


## NO4
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan:
- dilarang menggunakan crontab
- Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

### JAWAB:

### PENJELASAN:
1. Pertama, kita akan menginisialisasi direktori sebagai berikut:
```
int main(){
  pid_t child;
  int status;
  char dir[55];
  char *uname;
  uname = getlogin();
  sprintf(dir, "/home/hp/Documents/makanan", uname);
  ```
  Kita menggunakan fungsi ``getlogin`` untuk mendapatkan ``uname``, lalu menggunakan fungssi ``sprintf`` untuk insialisasi alamat ke dalam variabel ``dir``
  
  2. Kedua, dengan bantuan ``dir`` yang telah dibuat, kita akan menginisialisasi file ``makan_enak.txt``
  ```
  int main(){
      ...
      char file[100];
      sprintf(file, "hp/makan_enak.txt", dir);
  ```
  
  3. Dikarenakan program yang akan terus berjalan dan memiliki jeda 5 detik, maka kita membuat program utamanya ke dalam ``while(1)`` dan dengan fungsi ``sleep(5)``
  ```
  int main(){
      ...
      while(1){
      sleep(5);
 ```
 
 4. Keempat, dengan menggunakan fungsi ``stat()`` pada library ``sys/stat.h`` dan ``time.h``, kita akan memeriksa kapan file ``makan_enak.txt`` terakhir diakses.
  ```
  int main(){
      ...
      while(1){
      sleep(5);
      struct stat filestat;
      stat(file, &filestat);
      time_t fileAccessed = filestat.st_atime;
 ```
 
 5. Kemudian apabila perbandingan selisih waktu terakhir diakses dengan waktu saat ini kurang dari sama dengan 30 detik, maka akan membuat file ``makan_sehat%d.txt`` dengan ``%d`` yang merupakan bilangan bulat.
   ```
  int main(){
      ...
      int ct = 1;
      while(1){
              ...
              if(difftime(time(NULL), fileAccessed) <= 30){
                 char newfile[100];
                 sprintf(newfile, "hp/makan_sehat%d.txt", dir, ct);
 ```
 6. Membuat alamat file baru yang akan digunakan untuk penomoran file baru yang akan dibuat, dengan bantuan fungsi ``sprintf`` dan variabel ``ct``
 ```
  int main(){
      ...
      int ct = 1;
      while(1){
              ...
              if(difftime(time(NULL), fileAccessed) <= 30){
                 char newfile[100];
                 sprintf(newfile, "hp/makan_sehat%d.txt", dir, ct);
                 child = fork();
                  if(child == 0){
                  char *argv[] = {"cp", file, newfile, NULL};
                  execv("/bin/cp", argv);
                } 
                while ((wait(&status)) > 0); 
	              kill(child, SIGKILL);
                ct++;
 ```
7. Setelah program utama selesai, maka kita akan menambahkan fungsi agar ``daemon`` terbuat.
```
  void crDaemon();
  
  int main(){
    ...
    crDaemon();
    
    while(1){
    ...
    }
    
    exit(EXIT_SUCCESS);
  }
  void crDaemon(){
    pid_t pid, sid;
    pid = fork();
    if (pid < 0){
      exit(EXIT_FAILURE);
  }
  if (pid > 0){
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0){
    exit(EXIT_FAILURE);
  }
  if ((chdir("/")) < 0){
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
}
```


## NO5
Kerjakan poin a dan b di bawah:<br />
a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
- Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
- Per menit memasukkan log#.log ke dalam folder tersebut
- ‘#’ : increment per menit. Mulai dari 1 <br />
b. Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

### JAWAB:

### PENJELASAN:
### 5a
1. Pertama, kia akan membuat function ``getDate()`` yang akan me-return sebuah string tanggal dengan format yang ada di soal, yaitu ``dd:MM:yyyy-hh:mm``
```
char* getDate(){
    time_t raw;
    struct tm *timeinfo;
    
    char *re = (char *)calloc(20, sizeof(char));

    time(&raw);                                     
    timeinfo = localtime(&raw);                     

    strftime(re, 20, "%d:%m:%Y-%R", timeinfo);    

    return re;
}
```
Array ``re`` ada sehingga nantinya akan membuat nilai dikembalikan ke dalam fungsi ``main()``. Kemudian, ``time_t`` akan disimpan ke dalam variabel raw ketika ada jam yang dipanggil dengan ``time``. Variabel ``raw`` ini akan dipass ke dalam fungsi ``localtime`` yang akan mengembalikan struct yang berisi local time. ``strftime`` berfungsi untuk mengambil data tanggal, waktu, bulan dan tahun dalam format ``dd:MM:yyyy-hh:mm``. Kita dapat menggunakan format specifier, sebagai berikut:
- ``%d`` sebagai pengganti tanggal
- ``%m`` sebagai pengganti bulan
- ``%Y`` sebagai pengganti tahun
- ``%R`` yang setara dengan jam dan menit dengan format hh:mm

2. Kedua, kita dapat membuat sebuah fungsi untuk menyalin isi file /var/log/syslog ke dalam file log#.log di direktori yang telah kita buat.
```
void copyToDirectory(char* directory){
    FILE *source, *out;
    int i = 1;
    char    ch,
            newname[28],
            src[]={"/var/log/syslog"};

    while(i<=30){
      ...
    }
}
```
File log ini akan dibuat sebanyak 1 kali setiap menitnya dan diulang sebanyak 30 kali.

3. Menginisialisasi variabel yang dibutuhkan:
```
 while(i<=30){
    source = fopen(src, "r");
    snprintf(newname, 28, "%s/log%d.log", directory, i);

    out = fopen(newname, "w");

    if(source != NULL && out != NULL){
        while ((ch = fgetc(source)) != EOF)
              fputc(ch, out);

         fclose(out);
    }

    i++;

    fclose(source);
    sleep(60);  
}
```
- Array ``newname`` sebagai nama file output
- ``ch`` sebagai menyimpan karakter yang akan disalin
- ``i`` sebagai counter
- Pointer ke file log di ``/var/log/syslog`` dan file output

4. Kita panggil fungsi getDate() untuk mendapatkan nama direktori yang harus dibuat
```
if(!mkdir(date, S_IRWXU | S_IRWXO | S_IRWXG))
    copyToDirectory(date);
 ```

5. Kemudian, kita dapat membuat direktori sesuai nama yang telah didapat dengan permission mode 777 dengan cara menggunakan bitwise OR operation terhadap:
- ``S_IRWXG`` untuk read, write dan execute permission bagi group
- ``S_IRWXU`` untuk read, write dan execute permission bagi owner
- ``S_IRWXO`` untuk read, write dan execute permission bagi other atau user lain

6. Apabila kita telah berhasil membuat direktori, kita bisa menjalankan fungsi ``copyToDirectory`` untuk membuat file-file log yang diambil dari ``/var/log/syslog`` ke dalam folder tersebut
```
free(date);
```

### 5b
1. Menggunakan command ``pidof`` untuk mendapatkan pid dari sebuah proses:
```
FILE *cmd = popen("pidof /home/hp/Documents/sisop2/soal5a", "r");
fgets(out, 7, cmd);
```
Shell command ``pidof`` akan mencari pid dari input string nama proses yang berjalan. Dalam kasus ini, adalah absolute path dari file soal sebelumnya, yaitu soal 5a.

2. Isi dari array out akan dikonversi menjadi unsigned long integer dan disimpan di variabel pid dengan ``tipe pid_t``.
```
pid_t pid = strtoul(out, NULL, 10);
pclose(cmd);

if(!kill(pid, SIGKILL))
    printf("Process with pid of %d is successfully killed!\n", pid);
```
``SIGKILL`` akan menggunakan command ``kill`` ke pid.
