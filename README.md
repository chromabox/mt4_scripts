mt4_scripts
==============================
自作したMetaTrader4用インジケータ、スクリプトなどをおいてます。



各インジケータの説明
==============================

cbx_spread.mq4
---------

現在のスプレッドをメインチャートに表示します。
MT4でのPoint単位ではなく、Pips単位で表示します。（調整可）
デフォルトではUSD/JPYに合うようになってます。

[設定項目]
* Pips_To_Point --- 1Pips辺りのポイント数を設定します。
* Label_Normal_Color --- 通常時のスプレッド表示色です。
* Label_High_Color --- HighSpreadを超えた時のスプレッド表示色です。
* Label_Corners --- スプレッド表示ラベルの初期位置の基準を設定します。0；右上端　１：左上端
* Label_XDistance --- スプレッド表示ラベルのX座標を指定します。Label_Cornersに依存します。
* Label_YDistance --- スプレッド表示ラベルのY座標を指定します。Label_Cornersに依存します。
* HighSpread --- スプレッドがこの値を超えた以降、表示ラベルのカラーをLabel_High_Colorに変更します。Pips単位で指定してください。


cbx_bband.mq4
---------

ただのボリンジャーバンドです。
MT4についているのは複数重ねないと駄目だったりするので一発で±３αまで表示できるようにしています。
あと、おまけで非表示にしたり2.3αなどの設定も可能です。

設定項目は日本語なのでそれを見てください。
デフォルトではSMA、Closeを使用、±１αは表示しません。

色の設定がちょっとわかりにくいのでここで説明します。
[色の設定]
* 0 --- ＋３αの線の色と種類です。 
* 1 --- ＋２αの線の色と種類です。 
* 2 --- ＋１αの線の色と種類です。 
* 3 --- 移動平均の線の色と種類です。 
* 4 --- －１αの線の色と種類です。 
* 5 --- －２αの線の色と種類です。 
* 6 --- －３αの線の色と種類です。 




注意事項
==============================
* 本スクリプト、およびデータについて、その情報源の確実性を保証したものではありません。本スクリプト類を利用することで被った被害について、配布元は一切の責任を負いません。万一、内容に誤りがあった場合でも、配布元は一切責任を負わないものとします。
* MITライセンスですが、商業利用、及びサイトに転載される場合はご連絡お願いします。


