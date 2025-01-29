<div id="top"></div>

## 使用技術一覧

<p style="display: inline">
  <img src="https://img.shields.io/badge/-C-A8B9CC.svg?logo=c&style=for-the-badge">
</p>

## プロジェクトについて
 
フーリエ変換で画像のノイズを除去するプログラムを作成しました。

## ディレクトリ構成
.  
├── OutputBMP  
│   ├── imag.bmp  
│   ├── log_power.bmp  
│   ├── noiseaddimage.256.bmp  
│   ├── output.bmp  
│   ├── power.bmp  
│   ├── real.bmp  
│   ├── shifted_imag.bmp  
│   ├── shifted_power.bmp  
│   └── shifted_real.bmp  
├── OutputRaw  
│   ├── imag.raw  
│   ├── log_power.raw  
│   ├── output.raw  
│   ├── power.raw  
│   ├── real.raw  
│   ├── shifted_imag.raw  
│   ├── shifted_power.raw  
│   └── shifted_real.raw  
├── assignment1  
├── assignment1.c  
├── assignment2  
├── assignment2.c  
├── assignment3  
├── assignment3.c  
├── assignment4  
├── assignment4.c  
├── dft.c  
├── dft.h  
├── file_processing.c  
├── file_processing.h  
├── image_size.h  
└── noiseaddimage.256  

### 動作確認

1. assignment1.cと関連ファイルをコンパイルする。（実行ファイル名はassignment1としていますが、変更可能です。）
```
cc -Wall -Wextra -Werror assignment1.c file_processing.c dft.c -o assignment1
```
2. 1でできた実行ファイルを実行する。
```
./assignment1 noiseaddimage.256 real.raw imag.raw power.raw
```
これにより、noiseaddimage.256にフーリエ変換を適用した後の実部画像と虚部画像、パワースペクトル画像が作られます。
3. assignment2.cと関連ファイルをコンパイルする。（実行ファイル名はassignment2としていますが、変更可能です。）
```
cc -Wall -Wextra -Werror assignment2.c file_processing.c -o assignment2
```
4. 3でできた実行ファイルを実行する。
```
./assignment2 real.raw imag.raw power.raw shifted
```
これにより、2で作られた実部画像と虚部画像、パワースペクトル画像の中心が直流成分になるように並べ替えられます。
5. assignment3.cと関連ファイルをコンパイルする。（実行ファイル名はassignment3としていますが、変更可能です。）
```
cc -Wall -Wextra -Werror assignment3.c file_processing.c -lm -o assignment3
```
6. 5でできた実行ファイルを実行する。
```
./assignment3 shifted_power.raw log_power.raw
```
これにより、パワースペクトル画像の各画素の値に対して対数が取られ、見やすくなります。
7. assignment4.cと関連ファイルをコンパイルする。（実行ファイル名はassignment4としていますが、変更可能です。）
```
cc -Wall -Wextra -Werror assignment4.c file_processing.c dft.c -o assignment4
```
8. 7でできた実行ファイルを実行する。
```
./assignment4 shifted_real.raw shifted_imag.raw output.raw 1 16
```
これにより、フィルタリング処理後に逆離散フーリエ変換が行われ、原画像のノイズが除去されたoutput.rawが作成されます。

<p align="right">(<a href="#top">トップへ</a>)</p>
