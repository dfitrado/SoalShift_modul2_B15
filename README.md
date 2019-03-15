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
