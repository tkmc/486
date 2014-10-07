# 本プロジェクトについて

 書籍[『はじめて読む486』](http://ascii.asciimw.jp/books/books/detail/4-7561-0213-1.shtml)のサンプルプログラム集です。
『はじめて読む486』(以下本書)はIntel x86のIA32アーキテクチャを解説した書籍で、特にプロテクトモード周りのOSサポート機能を中心に紹介しています。IA32アーキテクチャは当初から完成度が高く、現在のCPUにおいても完全な互換性を保っています。したがって本書のサンプルプログラムも基本部分はそのまま実行して試すことができます。
 しかし、CPUは互換性を保っているものの、動作環境であるOSやツール、そして周辺ハードウェアは当時より大きく進化しており、サンプルプログラムをそのままの形で実行できる状況にはありません。

 本書は1994年に発刊されましたが、電子版としても発刊されることとなりました。そこで本サイトでは、現在の環境でサンプルプログラムを実行させるための情報を提供していきます。

# 必要なツール
 サンプルプログラムを動作させるには以下のものが必要です。

* MS-DOS互換OS
* x86用アセンブラ
* x86-16ビット対応Cコンパイラ

## MS-DOS互換OS

サンプルプログラムはx86のリアルモードの状態で起動されることを前提に記述されています。このためリアルモードで動作するMS-DOS、もしくは互換OSが必要です。

例えば下記のOSが利用できます。

* [freedos](http://www.freedos.org/)

## x86用アセンブラ

サンプルプログラムをアセンブルするには、MASM、もしくは互換のアセンブラが必要です。MASMは下記で入手できるようです。

* [MASM 8.0](http://www.microsoft.com/ja-jp/download/details.aspx?id=12654)


## x86-16ビット対応Cコンパイラ

 サンプルプログラムはC言語のプログラムからアセンブラのプログラムを呼び出す形で記述されています。このためリアルモードで実行できる16ビット対応のCコンパイラが必要です。
 MicrosoftのVisualC++の入手可能な版では16ビットをサポートしていませんので、他のコンパイラが必要です。現在入手可能なものでは、例えば下記のコンパイラがあるようです。

* [LSC-C86試食版](http://www.lsi-j.co.jp/freesoft/)

# ソースコードの修正

 本サイト開始時点(2014年10月)では、本書のサンプルプログラムとして掲載されているソースコードをそのまま公開します。今後修正があれば本サイトのソースコードに修正内容を反映させて紹介していきます。

 サンプルプログラムの記述のうち、本書のテーマである486のプロテクトモードやその操作手順に関しては現在のCPUでも互換性を保っていますので、そのまま実行することが可能です。しかし、一部の処理は本書が発刊された当時のPCハードウェアを前提に記述されています。このため現在主流のPCハードウェアでは動作しない部分があり、修正が必要です。

# 協力依頼

 このサイトでは『はじめて読む486』のサンプルプログラムに関する情報を提供するとともに、読者の皆さんからの情報を募りたいと思います。上記のOSや開発ツールを用いて現在の環境でも実行させることができると思われますが、著者多忙にて十分な検証ができていません。皆さんの中でツールの利用が確認できた方や、プログラムの修正に成功した方は、ぜひご連絡ください。このサイトで掲載したいと思います。プルリクエストも歓迎いたします。ご協力をよろしくお願いします。

github: [tkmc](https://github.com/tkmc/486)
twitter: [@tkmc](https://twitter.com/tkmc)
**蒲地輝尚**

