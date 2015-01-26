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





注意事項
==============================
* 本スクリプト、およびデータについて、その情報源の確実性を保証したものではありません。本スクリプト類を利用することで被った被害について、配布元は一切の責任を負いません。万一、内容に誤りがあった場合でも、配布元は一切責任を負わないものとします。
* MITライセンスですが、商業利用、及びサイトに転載される場合はご連絡お願いします。


