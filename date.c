#include "types.h"
#include "user.h" 
#include "date.h" //struct rtcdate

//menampilkan nama-nama bulan terurut.
void nama_bulan(int ket)
{
	if(ket==1) printf(1,"Jan");
	if(ket==2) printf(1,"Feb");
	if(ket==3) printf(1,"Mar");
	if(ket==4) printf(1,"Apr");
	if(ket==5) printf(1,"May");
	if(ket==6) printf(1,"Jun");
	if(ket==7) printf(1,"Jul");
	if(ket==8) printf(1,"Aug");
	if(ket==9) printf(1,"Sep");
	if(ket==10) printf(1,"Oct");
	if(ket==11) printf(1,"Nov");
	if(ket==12) printf(1,"Dec");
}

//menampilkan nomor-nomor bulan 
void nomor_bulan(int ket)
{
	if(ket==1) printf(1,"01");
	if(ket==2) printf(1,"02");
	if(ket==3) printf(1,"03");
	if(ket==4) printf(1,"04");
	if(ket==5) printf(1,"05");
	if(ket==6) printf(1,"06");
	if(ket==7) printf(1,"07");
	if(ket==8) printf(1,"08");
	if(ket==9) printf(1,"09");
	if(ket==10) printf(1,"10");
	if(ket==11) printf(1,"11");
	if(ket==12) printf(1,"12");
}

//menampilkan nama hari sesuai urutannya.
void show_day(int nama_hari){
	
		if (nama_hari==0) printf(1,"Sun");
		if (nama_hari==1) printf(1,"Mon");
		if (nama_hari==2) printf(1,"Tue");
		if (nama_hari==3) printf(1,"Wed");
		if (nama_hari==4) printf(1,"Thur");
		if (nama_hari==5) printf(1,"Fri");
		if (nama_hari==6) printf(1,"Sat");
}

//sebagai checker
int langkah(int ket)
{
	int tandai = 0;
	
	if (ket%400==0 || ket%4==0)
		tandai = 1;
		else if(ket%100==0)
		tandai = 0;
	//else if(ket%4==0)
	//	tandai = 1;
	else tandai = 0;
	return(tandai);
}

//menghitung hari dan menyesuaikannya dengan bulan
void hari(int a,int b,int c)
{
	int hari1 = 4, hitung = 0;	
	if(a>1970)
	{
		for(int i=1970;i<a;i++)
		{
			if(langkah(i)) hitung = hitung + 366;
			else hitung = hitung + 365;
		}
	}
	for(int i=1;i<b;i++)
	{
		//februari
		
		if(i==2)
		{
			if(langkah(a)) hitung =hitung+ 29;
			else hitung =hitung+ 28;
		}
		
		//penyesuaian dengan bl yg ada
		else if((i>=8)&&(i%2==0)) hitung = hitung+ 31;
		else if((i<8)&&(i%2==1)) hitung = hitung+ 31;
		else if((i<8)&&(i%2==0)) hitung = hitung+30;
		else hitung =hitung+ 30;
	}
	int hit_hari = hari1+hitung+c-1;
	int nama_hari =  hit_hari%7;
	show_day(nama_hari);
}
//convert dari GMT menjadi waktu lokal setempat (WITA)
void local_time()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date gagal\n");
		exit();
	}
	//menghitung menit dan jam yang sesuai waktu lokal
	if(r.minute>59)
	{
		r.hour = r.hour+ 9;
		r.minute = r.minute-59;
	}
	//menghitung menit dan jam yang sesuai waktu lokal
	else if (r.minute<=59){ 
		r.hour = r.hour+8;}
	if(r.hour>=24)
		r.hour = r.hour - 24;
		//print jam menit detik dalam format %h:%m:%s
	printf(1," %d:", r.hour);
	printf(1,"%d:", r.minute);
	printf(1,"%d", r.second);
}
/* 
Keterangan penggunaan command:
date
date + “%d-%m-%y”
date -s “month/day/year HH:MM:SS”
date -r “nama_file” 
*/
int main(int arg1, char *arg2[])
{
	//untuk command date
	if(arg1==1){
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date gagal\n");
		exit();
	}
	hari(r.year,r.month,r.day);
	printf(1," ");
	nama_bulan(r.month);
	printf(1," %d",r.day);
	local_time();
   	//printf(1," %d:%d:%d",r.hour,r.minute,r.second);
	printf(1," WITA %d\n",r.year);
	//printf(1," %d\n",r.year); 
	}
	//untuk penggunaan command dengan arg lebih dari 1
	else if(arg1!=1)
	{
		//untuk command date+
		if((arg1==2)&&(strcmp("+",*(arg2+1))==0)){
		struct rtcdate r;
		if (date(&r)) 
		{
		printf(2, "date gagal\n");
		exit();
		}
		//int nobl = nomor_bulan(r.month);	
		//printf(1,"%d-%d-%d",r.day, nobl, r.year);
		printf(1,"%d-",r.day);
		nomor_bulan(r.month); 
		printf(1,"-%d\n",r.year);

		}
		//untuk command date-s
		else if((arg1==2)&&(strcmp("-s",*(arg2+1))==0)){
		//date_time();
		struct rtcdate r;
		if (date(&r)) 
		{
		printf(2, "date gagal\n");
		exit();
		}
		nama_bulan(r.month); 
		printf(1,"/%d/%d",r.day,r.year);
		//printf(1,"%d/%d/%d",nama_bulan(r.month), r.day,r.year);
		local_time();
		printf(1," WITA\n");
		
		}
		//untuk command date -r (belum selesai)
		else if((arg1==2)&&(strcmp("-r",*(arg2+1))==0)){
		//date_file();
		struct rtcdate r;
		
		if (date(&r)) 
		{
		printf(2, "date gagal\n");
		exit();
		}	
		//printf(1,"%d-%d-%d\n",r.day,nomor_bulan(r.month), r.year );
		printf(1,"%d-",r.day);
		nomor_bulan(r.month); 
		printf(1,"-%d\n",r.year);
		}

		//error handling jika command yang dimasukkan tidak sesuai
		else
		printf(1,"Command yang Anda masukkan salah, input command yang benar : '+'/'-s'/'-r'\n");
	}
exit();
}


