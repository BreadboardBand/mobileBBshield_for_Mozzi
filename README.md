# mobileBB shield for Mozzi
## About
*MobileBB shield for Mozzi* is an Arduino shield for [Mozzi](http://sensorium.github.io/Mozzi/).
Mozzi is an Arduino library for tweaking audio signals.
The shield aims to use Mozzi easily, from the aspect of hardware.

![shield without any components](https://raw.github.com/BreadboardBand/mobileBBshield_for_Mozzi/gh-pages/mobileBBforMozzi01.jpg)
It consist of the very minimal parts necessary for using Mozzi:

- 3.5mm monaural jack with notch filter circuit for output
- 3.5mm monaural jack for input


Based on [Notch filter for STANDARD mode carrier frequency.](http://sensorium.github.io/Mozzi/learn/output/)
![cirtcuit diagram](https://raw.github.com/BreadboardBand/mobileBBshield_for_Mozzi/gh-pages/circuitDiagram.jpg)

Since it has many free spaces, you can put small breadboard on the shield.
![shield with BB and components](https://raw.github.com/BreadboardBand/mobileBBshield_for_Mozzi/gh-pages/mobileBBforMozzi02.jpg)

This work is a realization of [our](http://www.breadboardband.org) wish while creating new musical instruments and playing them at live performances.
Being made only from a small amount of components, is from our thought of wanting its users to create their own freely from this shield.

# Parts List
|Label                  |Part Type        |Properties|Quantities            |
|-----------------------|-----------------|----------|----------------------|
|C1,C2                  |Ceramic Capacitor|220nF     |2                     |
|C3                     |Ceramic Capacitor|1nF       |1                     |
|C4                     |Ceramic Capacitor|100nF     |1                     |
|R1,R2                  |Resistor         |680Ω      |2                     |
|R3                     |Resistor         |330Ω      |1                     |
|R4                     |Resistor         |270Ω      |1                     |
|Audio Jack             |Monaural, 3.5mm  |          |2 (*1)                |
|Pin Sockets For Arduino|N/A              |          |1 (*2)                |

*1 e.g. available at http://akizukidenshi.com/catalog/g/gC-02460/

*2 e.g. available at http://www.switch-science.com/catalog/246/

[Parts List(Fritzing exported original)](https://github.com/BreadboardBand/mobileBBshield_for_Mozzi/blob/master/parts_list_mobileBB_shield_for_mozzi.pdf?raw=true)

(in japanese)

mobileBB shield for Mozziは、Arduinoでオーディオ信号を扱うためのライブラリ 
[Mozzi](http://sensorium.github.io/Mozzi/)を、ハードウェアの面からも簡単に使うことができるようにしたArduino shieldです。
 
- Mozziからのオーディオ信号の高周波を取り除くフィルターと3.5mmモノジャック
- Mozziへの入力のための、3.5mmモノジャック

という、Mozziを使うために必要な最低限の部品で構成されています。
空いているスペースには小さいブレッドボードを入れることもできます。
[Notch filter for STANDARD mode carrier frequency](http://sensorium.github.io/Mozzi/learn/output/)を元に回路を設計しています。


mobileBB shield for Mozziは、[私たちBreadboard Band](http://www.breadboardband.org)がライブをしたり、新しい楽器を作る中で、
「こういうものがあったら便利なんじゃないか？考えていたことを実現したものです。

最低限の追加部品だけで作られているのは、ここから自由に発想をしてほしい、という思いからです。

# License
This work is licensed under a [Attribution 3.0 Unported (CC BY 3.0)](http://creativecommons.org/licenses/by/3.0/deed.en)
Copyright by The Breadboard Band 2013
