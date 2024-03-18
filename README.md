# Algoritma Titik Tengah
> Membangun Kurva Bézier dengan Algoritma Titik Tengah berbasis Divide and Conquer

## Table of Contents
* [Deskripsi Singkat](#deskripsi-singkat)
* [Preview](#preview)
* [Deskripsi Program](#deskripsi-program)
* [Dependencies](#dependencies)
* [Cara Pemakaian](#cara-pemakaian)
* [Kompilasi](#kompilasi)
* [Important Notes](#important-notes)
* [Credits](#credits)

## Deskripsi Singkat
Kurva Bézier adalah kurva yang dibangun dengan menghubungkan beberapa titik kontrol yang menentukan bentuk dan arah kurva. Kurva Bézier terkenal penggunaannya dalam desain grafis, animasi, dan manufaktur. Pada proyek ini, dibuat program pembentukan Kurva Bézier dengan strategi Divide and Conquer, yaitu dengan Algoritma Titik Tengah. Diimplementasikan juga Algoritma Brute Force sebagai pembanding.

## Preview
![BezierCurveApp](./test/BezierCurveAppGIF.gif)

## Deskripsi Program
Program interaktif berbasis GUI yang memvisualisasikan pembentukan kurva Bézier dengan metode divide and conquer dan brute force. Pengguna dapat menambah titik kontrol, mengubah jumlah iterasi, serta mengubah posisi titik.

Direktori tugas kecil ini memiliki struktur file sebagai berikut:
```shell
.
│   README.md
├───bin                                 # Hasil compile file java (.class)
│       BezierCurveApp.exe
│       Qt6Core.dll
│       ...  
├───doc                                 # Laporan tugas kecil (dokumentasi)
├───src                                 # Source code tugas kecil
│       main.cpp
│       ImageView.cpp
│       ControlPanel.cpp
│       widget.cpp
│       widget.ui
│       ...
└───test                                # Screenshot data uji
        BF 1.png
        DNC 1.png
        ...
```

## Dependencies
* Qt 6 ke atas (hanya untuk kompilasi)

## Cara Pemakaian
1. Download atau clone repository
2. Klik folder repository dan klik folder `\bin`
3. Klik `BezierCurveApp.exe`

## Kompilasi
1. Download atau clone repository
2. Download [Qt](https://www.qt.io/download) sesuai sistem operasi
3. Jalankan Qt Creator
4. Pilih "Open Project" dan kemudian pilih semua file yang ada pada folder `\src`
5. Build and Run project

## Important Notes
File executable pada `\bin` hanya dapat dijalankan pada sistem operasi Windows

## Credits
- Ariel Herfrison (NIM 13522002)
- Kristo Anugrah (NIM 13522024)
