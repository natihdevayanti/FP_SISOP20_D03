#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
//error handling
//untuk cek command
void usage(){
    printf(2, "Masukkan 2 file\n");
    printf(2, "Usage: cmp [file1] [file2]\n");
    exit();
}

void error(){
    printf(1, "Gagal read\n");
    exit();
 }
//untuk buffer
void errorw(){
    printf(1, "Gagal write\n");
    exit();
 }
//Command cmp :
//Membandingkan 2 file byte per byte
//Contoh: cmp file1.c file2.c -> outputnya menunjukkan kedua file tersebut 
//tidak sama pertama kali di byte ke-berapa dan line ke-berapa

int main(int arg1, char *arg2[])
{
    int x = 0, y = 0, jumlah_byte = 0, size, size1, ulang, count_byte=-1, lines=0;
    struct stat st;
	int cmpr1, cmpr2;
    
    //jika sudah memasukkan 3 argumen
    if (arg1 >= 3)
    {
       // int cmpr1, cmpr2;
     
       // if ((cmpr1 = open(arg2[1], 0)) < 0)
        // Error jika tidak bisa membaca file 1
       if ((cmpr1 = open(arg2[1], 0)) ==-1)
        {
            printf(1, "cmp: Gagal membaca file %s\n", arg2[1]);
            exit();
        }
      //  if ((cmpr2 = open(arg2[2], 0)) < 0)
      //error jika tidak bisa membaca file 2
        if ((cmpr2 = open(arg2[2], 0)) == -1)
        {
            printf(1, "cmp: Gagal membaca file %s\n", arg2[2]);
            exit();
        }
/*
        if ((cmpr2 = open(arg2[2], 0)==-1 && (cmpr1 = open(arg2[1], 0) == -1)
        {
            printf(1, "cmp: Gagal membaca file %s dan %s\n", arg2[1], arg2[2]);
            exit();
        }
*/
//error jika ternyata file yang dibandingkan benar-benar sama
	   if (strcmp(arg2[1], arg2[2] ) == 0){
            printf(1, "File tersebut adalah file yang sudah pasti sama\n");
            exit();
        }
    
	//cmpr1 merupakan file 1 yang akan dicompare
    fstat(cmpr1,&st);
    size = st.size;
    char buf1[st.size];
    //cmpr2 merupakan file 2 yang akan dicompare
    fstat(cmpr2,&st);
    size1 = st.size; 
    char buf2[st.size];
	//menghitung ukuran-ukurannya
    if(size > size1) jumlah_byte = size;
    else if (size <= size1) jumlah_byte = size1;
	//looping untuk melakukan cek posisi
    //finding byte position
    while (((x = read(cmpr1, buf1, sizeof(buf1))) > 0) && ((y = read(cmpr2, buf2, sizeof(buf2))) > 0))
    {
        if (write(1, buf1, x) != x)  errorw();
        if (write(1, buf2, y) != y) errorw();
       
    }
	//print jumlah bytes dari masing-masing file (sebagai referensi dan patokan perbandingan)
    printf(2,"Bytes of %s = %d\n", arg2[1], size);
    printf(2,"Bytes of %s = %d\n", arg2[2], size1);
	    //file kosong-> error
    if (x == -1) error();
    if (y == -1) error();
  //  ulang = 0;
    for (ulang =0; ulang < jumlah_byte; ulang++)
    {
        count_byte = 0; //penanda
        if(buf1[ulang] != buf2[ulang])
        {
            count_byte = ulang;
            break;
        }
        if(buf1[ulang] == '\n') lines++; //akan membaca line demi line
       // ulang++;
    }
    //jika ternyata file tersebut memiliki size yang sama 
    if(count_byte == -1){
        printf(2,"%s and %s are matched/same files\n", arg2[1], arg2[2]);
        exit();
    }
    //jika berbeda, maka print letak perbedaannya
    else if (count_byte !=-1) printf(2,"%s %s differ: byte %d, lines %d\n",arg2[1], arg2[2],count_byte+1,lines+1);
	//closing file
        close(cmpr1);
        close(cmpr2);
        exit();
    }
    //jika memasukkan argumen kurang dari 3
    else if(arg1 < 3) usage();
}

