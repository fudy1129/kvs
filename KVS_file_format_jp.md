# 7. ファイルフォーマット #
KVSでは、可視化の対象となるデータをハードディスク上に保存、または、ハードディスクから読み込むために、XML形式で記述された独自のファイルフォーマット（KVSML）を定義しています。ここでは、KVSML形式に加え、KVSが対応している他のファイルフォーマットについて説明します。以下に現在対応しているファイルフォーマットを示します。

| **フォーマット名** | **拡張子** | **読み込み** | **書き込み** | **備考** |
|:--------------------------|:--------------|:-----------------|:-----------------|:-----------|
| KVSMLフォーマット | kvsml | ○ | ○ |  |
| AVS Filed フォーマット | fld | ○ | ○ | 1ファイルバイナリ形式にのみ対応 |
| AVS UCD フォーマット | inp | ○ | ○ | 時系列データには未対応 |
| Bitmap画像フォーマット | bmp | ○ | ○ |  |
| CSVフォーマット | csv | ○ | ○ |  |
| DICOMフォーマット | dcm | ○ | × |  |
| FrontFlowフォーマット | --- | ○ | × |  |
| FrontSTRフォーマット | --- | ○ | × |  |
| GrADSフォーマット | --- | ○ | × |  |
| PLYフォーマット | ply | ○ | ○ |  |
| PNM画像フォーマット | ppm,pgm,pbm | ○ | ○ |  |
| STLフォーマット | stl | ○ | ○ |  |
| Tiff画像フォーマット | tiff, tif | ○ | ○ |  |

ここでは、各データの読み込みまたは書き込み方法について説明する。

  * 7.1 KVSMLフォーマット
  * 7.2 AVS Fieldフォーマット
  * 7.3 AVS UCDフォーマット
  * 7.4 Bitmap画像フォーマット
  * 7.5 CSVフォーマット
  * 7.6 DICOMフォーマット
  * 7.7 FrontFlowフォーマット
  * 7.8 FrontSTRフォーマット
  * 7.9 GrADSフォーマット
  * 7.10 PLYフォーマット
  * 7.11 PNM画像フォーマット
  * 7.12 STLフォーマット
  * 7.13 Tiff画像フォーマット