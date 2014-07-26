#include "base64.h"


#include <string.h>

static const char Base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char Pad64 = '=';

/*******************************************************************************
base64编码知识
Base64要求把每三个8Bit的字节转换为四个6Bit的字节（3*8 = 4*6 = 24），
然后把6Bit再添两位高位0，组成四个8Bit的字节，也就是说，
转换后的字符串理论上将要比原来的长1/3。
原文的字节不够的地方可以用全0来补足，如果字节数不够,
转换时Base64编码用=号来代替
Base64编码会以一个或两个等号结束，但等号最多只有两个。因为：

余数 = 原文字节数 MOD 3

所以余数任何情况下都只可能是0，1，2这三个数中的一个。
如果余数是0的话，就表示原文字节数正好是3的倍数（最理想的情况啦）。
如果是1的话，为了让Base64编码是4的倍数，就要补2个等号；
同理，如果是2的话，就要补1个等号。

编码表如下:

      Value Encoding  	Value Encoding  Value Encoding  	Value Encoding
          0 A            		17 R            34 i            		51 z
          1 B            		18 S            35 j            		52 0
          2 C            		19 T            36 k            		53 1
          3 D            		20 U            37 l            		54 2
          4 E            		21 V            38 m            		55 3
          5 F            		22 W            39 n            		56 4
          6 G            		23 X            40 o            		57 5
          7 H            		24 Y            41 p            		58 6
          8 I            		25 Z            42 q            		59 7
          9 J            		26 a            43 r            		60 8
         10 K            		27 b            44 s            		61 9
         11 L            		28 c            45 t            		62 +
         12 M            		29 d            46 u            		63 /
         13 N            		30 e            47 v
         14 O            		31 f            48 w         			(pad) =
         15 P            		32 g            49 x
         16 Q            		33 h            50 y

算法:
第一个字符通过右移2位获得第一个目标字符的Base64表位置，
根据这个数值取到表上相应的字符，就是第一个目标字符。
然后将第一个字符左移4位加上第二个字符右移4位，
即获得第二个目标字符。
再将第二个字符左移2位加上第三个字符右移6位，
获得第三个目标字符。
最后取第三个字符的右6位即获得第四个目标字符。

在以上的每一个步骤之后，再把结果与 0x3F 进行 AND 位操作�
就可以得到编码后的字符了。*/

/*编码函数*/
int CBase64Encrypt::Encode(char const *src, size_t srclength, char *target, size_t targsize)
{
	size_t datalength = 0;
	u_char input[3];
	u_char output[4];
	u_int i;

	while (2 < srclength) {
		input[0] = *src++;
		input[1] = *src++;
		input[2] = *src++;
		srclength -= 3;

		output[0] = input[0] >> 2;
		output[1] = ((input[0] & 0x03) << 4) + (input[1] >> 4);
		output[2] = ((input[1] & 0x0f) << 2) + (input[2] >> 6);
		output[3] = input[2] & 0x3f;
		//assert(output[0] < 64);
		//assert(output[1] < 64);
		//assert(output[2] < 64);
		//assert(output[3] < 64);

		if (datalength + 4 > targsize)
			return (-1);
		target[datalength++] = Base64[output[0]];
		target[datalength++] = Base64[output[1]];
		target[datalength++] = Base64[output[2]];
		target[datalength++] = Base64[output[3]];
	}

	/* 开始考虑增加pad */
	if (0 != srclength) {
		/* 得到还有几个有效的字符串. */
		input[0] = input[1] = input[2] = '\0';
		for (i = 0; i < (u_int)srclength; i++)
			input[i] = *src++;

		output[0] = input[0] >> 2;
		output[1] = ((input[0] & 0x03) << 4) + (input[1] >> 4);
		output[2] = ((input[1] & 0x0f) << 2) + (input[2] >> 6);
		//assert(output[0] < 64);
		//assert(output[1] < 64);
		//assert(output[2] < 64);

		if (datalength + 4 > targsize)
			return (-1);
		target[datalength++] = Base64[output[0]];
		target[datalength++] = Base64[output[1]];
		/*根据情况决定补几个pad */
		if (srclength == 1)
			target[datalength++] = Pad64;
		else
			target[datalength++] = Base64[output[2]];
		target[datalength++] = Pad64;
	}
	if (datalength >= targsize)
		return (-1);
	target[datalength] = '\0';
	return (datalength);
}

/*
解码函数，忽略所有的空格
一次处理四个字符，得到三个字符
第一个目的字符通过把第一个源字符左移两位，
		与第二个源字符右移四位后相或。

第二个目的字符通过把第二个源字符与0x0f相与，左移四位，
		与第三个源字符右移两位后相或。

第三个目的字符通过把第三个源字符与0x03相与，左移六位，
		与第四个字符相或。

 */

int CBase64Encrypt::Decode(char const *src, char * target, size_t targsize)
{
	u_int tarindex, state;
	int ch;
	char *pos;

	state = 0;
	tarindex = 0;

	while ((ch = *src++) != '\0') {
		if (isspace(ch))	/* 忽略空格 */
			continue;
		/* 如果遇到pad跳出循环 */
		if (ch == Pad64)
			break;

		pos = (char *)strchr(Base64, ch);
		if (pos == 0)	/* 如果不是base64编码范围内的字符. */
			return (-1);

		switch (state) {
		case 0:
			if (target) {
				if (tarindex >= targsize)
					return (-1);
				target[tarindex] = (pos - Base64) << 2;
			}
			state = 1;
			break;
		case 1:
			if (target) {
				if (tarindex + 1 >= targsize)
					return (-1);
				target[tarindex] |= (pos - Base64) >> 4;
				target[tarindex + 1] = ((pos - Base64) & 0x0f)
				    << 4;
			}
			tarindex++;
			state = 2;
			break;
		case 2:
			if (target) {
				if (tarindex + 1 >= targsize)
					return (-1);
				target[tarindex] |= (pos - Base64) >> 2;
				target[tarindex + 1] = ((pos - Base64) & 0x03)
				    << 6;
			}
			tarindex++;
			state = 3;
			break;
		case 3:
			if (target) {
				if (tarindex >= targsize)
					return (-1);
				target[tarindex] |= (pos - Base64);
			}
			tarindex++;
			state = 0;
			break;
		}
	}

	/*
	 * 解码完毕.  查找是否是否只有少于两个的pad
	 ,并且源字符串是否是4的整数倍。
	 */

	if (ch == Pad64) {	/* We got a pad char. */
		ch = *src++;	/* Skip it, get next. */
		switch (state) {
		case 0:	/* Invalid = in first position */
		case 1:	/* Invalid = in second position */
			return (-1);

		case 2:	/* Valid, means one byte of info */
			/* Skip any number of spaces. */
			for (; ch != '\0'; ch = *src++)
				if (!isspace(ch))
					break;
			/* 确保还有另一个pad */
			if (ch != Pad64)
				return (-1);
			ch = *src++;	/* Skip the = */
			/* Fall through to "single trailing =" case. */
			/* FALLTHROUGH */

		case 3:	/* Valid, means two bytes of info */
			/*
			 * We know this char is an =.  Is there anything but
			 * whitespace after it?
			 */
			for (; ch != '\0'; ch = *src++)
				if (!isspace(ch))
					return (-1);

			/*
			 * Now make sure for cases 2 and 3 that the "extra"
			 * bits that slopped past the last full byte were
			 * zeros.  If we don't check them, they become a
			 * subliminal channel.
			 */
			if (target && target[tarindex] != 0)
				return (-1);
		}
	} else {
		/*
		 * We ended by seeing the end of the string.  Make sure we
		 * have no partial bytes lying around.
		 */
		if (state != 0)
			return (-1);
	}

	return (tarindex);
}
