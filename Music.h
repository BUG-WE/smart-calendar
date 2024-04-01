#ifndef  __YIFAN_MUSIC_H__
#define  __YIFAN_MUSIC_H__

/*
简谱是大众化的音乐记谱方式，比较容易理解和掌握。我们可以把一首乐谱（score）
看成是由若干个基本的音符（note）单元组成。一个音符由音名和时值组成。音名就是低音、
中音、高音的 1234567（唱作 do re mi fa sol la si） ，其本质是音符的发声频率。
用 L1～L7、M1～M7、H1～H7 定义了低音、中音、高音所对应的发声频率。
时值是音符的发声时间长短，有全音符、二分音符、四分音符……等等。
音符可以后缀一个“符点” ，表示时值增加 1/2，特殊地，二分音符加符点时用“－”代替
圆点。参见表 1110.726 的描述。
		表1110.726  常见简谱音符示例
音 符  			名 称  		   相 对 时 值
5―――  		全音符  		T
5－  			二分音符  		T/2
5  			四分音符  		T/4
5底部_  		八分音符  		T/8
5底部_ _  	        十六分音符  		T/16
5――  			符点二分音符 		T/2+T/4
5．  			符点四分音符  		T/4+T/8
5．底部__		符点八分音符  		T/8+T/16
*/
//  定义低音音名（数值单位：Hz）数字底部有点'.'
#define  L1     262     //  c
#define  L2     294     //  d
#define  L3     330     //  e
#define  L4     349     //  f
#define  L5     392     //  g
#define  L6     440     //  a1
#define  L7     494     //  b1
//  定义中音音名 数字底部无点'.'
#define  M0     0       //  c0
#define  M1     523     //  c1
#define  M2     587     //  d1
#define  M3     659     //  e1
#define  M4     698     //  f1
#define  M5     784     //  g1
#define  M6     880     //  a2
#define  M7     988     //  b2
//  定义高音音名 数字顶部有点'.'
#define  H1     1047    //  c2
#define  H2     1175    //  d2
#define  H3     1319    //  e2
#define  H4     1397    //  f2
#define  H5     1568    //  g2
#define  H6     1760    //  a3
#define  H7     1976    //  b3


//  定义时值单位，决定演奏速度（数值单位：ms）
#define  T      3600


//  定义音符结构
typedef struct
{
    short Music_Name;    //  音名：取值L1～L7、M1～M7、H1～H7分别表示低音、中音、高音的
                    //        1234567，取值0表示休止符
    short Music_Time;    //  时值：取值T、T/2、T/4、T/8、T/16、T/32分别表示全音符、
                    //        二分音符、四分音符、八分音符…，取值0表示演奏结束
}tMusic_hy;

//  定义乐曲：《看月亮爬上来》（张杰）
extern tMusic_hy my_music_kanyueliangpashanglai[];
//  定义乐曲：《化蝶》（梁祝）
extern tMusic_hy my_music_huadie[];


#endif  //  __YIFAN_MUSIC_H__

