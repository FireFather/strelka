# strelka
Strelka (the Russian arrow), legendary chess engine from 2007...updated

![alt tag](https://raw.githubusercontent.com/FireFather/strelka/master/strelka-1.bmp)
![alt tag](https://raw.githubusercontent.com/FireFather/strelka/master/strelka-2.bmp)
![alt tag](https://raw.githubusercontent.com/FireFather/strelka/master/strelka-3.bmp)

- Strelka 2.1 (based on last open-source version 2.0b)
- now 64-bit
- code improvements and optimizations
- separation of terms into specific include files
- all warnings thru Level4 (/W4) resolved
- increase in strength (+80 elo in self-play)
- Visual Studio 2022 project files included

Games Completed = 16384 of 16384 (Avg game length = 9.645 sec)
Settings = Gauntlet/32MB/1000ms+100ms/M 500cp for 6 moves, D 120 moves/EPD:book.epd(31526)
Time = 13603 sec elapsed
 1.  Strelka-2.1  (10024.0/16384)
 2.  Strelka-2.0b (6360.0/16384)
 
   |			|      |   |       |                |        |       |    |        |
   | ---------- | ---- | - | ----- | -------------- | ------ | ----- | -- | ------ |
   |            |      | : | games |(   +,   =,   -)|   (%)  |   Diff|  SD| CFS (%)|
   |Strelka-2.1 |  2830| : | 16384 |(7262,5524,7262)|  61.2  |    +80|   2|  100.0 |
   |Strelka-2.0b|  2750| : | 16384 |(3598,5524,7262)|  38.8  |       |    |        |

