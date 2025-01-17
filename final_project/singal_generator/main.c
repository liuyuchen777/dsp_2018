#include "lcd.h"
#include "ledkey.h"


#define IMR  *(volatile unsigned int *)0x0000
#define IFR  *(volatile unsigned int *)0x0001
#define PMST *(volatile unsigned int *)0x001D

ioport unsigned port0bfff;				//定义输出端口
#define IOSR port0bfff

unsigned char ch = 0 ;

unsigned char hint_str[] = {0x30,0x2c,0x25,0x21,0x33,0x25,0x00,0x23,0x28,0x2f,0x2f,0x33,0x25}; //please choose wave 
unsigned char sin_str[] = {0x10,0x11,0x00,0x33,0x29,0x2e,0x00,0x37,0x21,0x36,0x25}; //01 sine wave
unsigned char square_str[] = {0x10,0x12,0x00,0x33,0x31,0x35,0x21,0x32,0x25,0x00,0x37,0x21,0x36,0x25};//02 square wave
unsigned char tri_str[] = {0x10,0x13,0x00,0x34,0x32,0x29,0x00,0x37,0x21,0x36,0x25};// 03 tri wave
unsigned char nums[] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19};//number 0-9
unsigned char freq_str[] = {0x26,0x52,0x45,0x51};
unsigned char range_str[] = {0x32,0x41,0x4e,0x47,0x45};
unsigned char output[10];
#pragma DATA_SECTION(sin_value,"data_buf1")
float sin_value[] = {1037,1050,1063,1075,1088,1101,1114,1127,1140,1152,1165,1178,1191,1203,1216,1229,1241,1254,1266,1279,1291,1304,1316,1328,1340,1353,1365,1377,1389,1401,1413,1425,1437,1448,1460,1472,1483,1495,1506,1517,1529,1540,1551,1562,1573,1584,1594,1605,1615,1626,1636,1647,1657,1667,1677,1687,1696,1706,1716,1725,1734,1744,1753,1762,1770,1779,1788,1796,1805,1813,1821,1829,1837,1845,1852,1860,1867,1875,1882,1889,1895,1902,1909,1915,1921,1927,1933,1939,1945,1951,1956,1961,1966,1971,1976,1981,1985,1990,1994,1998,2002,2006,2009,2013,2016,2019,2022,2025,2027,2030,2032,2034,2036,2038,2040,2041,2043,2044,2045,2046,2047,2047,2048,2048,2048,2048,2048,2047,2047,2046,2045,2044,2043,2041,2040,2038,2036,2034,2032,2030,2027,2025,2022,2019,2016,2013,2009,2006,2002,1998,1994,1990,1985,1981,1976,1971,1966,1961,1956,1951,1945,1939,1933,1927,1921,1915,1909,1902,1895,1889,1882,1875,1867,1860,1852,1845,1837,1829,1821,1813,1805,1796,1788,1779,1770,1762,1753,1744,1734,1725,1716,1706,1696,1687,1677,1667,1657,1647,1636,1626,1615,1605,1594,1584,1573,1562,1551,1540,1529,1517,1506,1495,1483,1472,1460,1448,1437,1425,1413,1401,1389,1377,1365,1353,1340,1328,1316,1304,1291,1279,1266,1254,1241,1229,1216,1203,1191,1178,1165,1152,1140,1127,1114,1101,1088,1075,1063,1050,1037,1024,1011,998,985,973,960,947,934,921,908,896,883,870,857,845,832,819,807,794,782,769,757,744,732,720,708,695,683,671,659,647,635,623,611,600,588,576,565,553,542,531,519,508,497,486,475,464,454,443,433,422,412,401,391,381,371,361,352,342,332,323,314,304,295,286,278,269,260,252,243,235,227,219,211,203,196,188,181,173,166,159,153,146,139,133,127,121,115,109,103,97,92,87,82,77,72,67,63,58,54,50,46,42,39,35,32,29,26,23,21,18,16,14,12,10,8,7,5,4,3,2,1,1,0,0,0,0,0,1,1,2,3,4,5,7,8,10,12,14,16,18,21,23,26,29,32,35,39,42,46,50,54,58,63,67,72,77,82,87,92,97,103,109,115,121,127,133,139,146,153,159,166,173,181,188,196,203,211,219,227,235,243,252,260,269,278,286,295,304,314,323,332,342,352,361,371,381,391,401,412,422,433,443,454,464,475,486,497,508,519,531,542,553,565,576,588,600,611,623,635,647,659,671,683,695,708,720,732,744,757,769,782,794,807,819,832,845,857,870,883,896,908,921,934,947,960,973,985,998,1011,1024};
#pragma DATA_SECTION(tri_value,"data_buf2")
float tri_value[] = {8,16,25,33,41,49,57,66,74,82,90,98,106,115,123,131,139,147,156,164,172,180,188,197,205,213,221,229,238,246,254,262,270,279,287,295,303,311,319,328,336,344,352,360,369,377,385,393,401,410,418,426,434,442,451,459,467,475,483,492,500,508,516,524,532,541,549,557,565,573,582,590,598,606,614,623,631,639,647,655,664,672,680,688,696,705,713,721,729,737,745,754,762,770,778,786,795,803,811,819,827,836,844,852,860,868,877,885,893,901,909,918,926,934,942,950,958,967,975,983,991,999,1008,1016,1024,1032,1040,1049,1057,1065,1073,1081,1090,1098,1106,1114,1122,1130,1139,1147,1155,1163,1171,1180,1188,1196,1204,1212,1221,1229,1237,1245,1253,1262,1270,1278,1286,1294,1303,1311,1319,1327,1335,1343,1352,1360,1368,1376,1384,1393,1401,1409,1417,1425,1434,1442,1450,1458,1466,1475,1483,1491,1499,1507,1516,1524,1532,1540,1548,1556,1565,1573,1581,1589,1597,1606,1614,1622,1630,1638,1647,1655,1663,1671,1679,1688,1696,1704,1712,1720,1729,1737,1745,1753,1761,1769,1778,1786,1794,1802,1810,1819,1827,1835,1843,1851,1860,1868,1876,1884,1892,1901,1909,1917,1925,1933,1942,1950,1958,1966,1974,1982,1991,1999,2007,2015,2023,2032,2040,2048,2040,2032,2023,2015,2007,1999,1991,1982,1974,1966,1958,1950,1942,1933,1925,1917,1909,1901,1892,1884,1876,1868,1860,1851,1843,1835,1827,1819,1810,1802,1794,1786,1778,1769,1761,1753,1745,1737,1729,1720,1712,1704,1696,1688,1679,1671,1663,1655,1647,1638,1630,1622,1614,1606,1597,1589,1581,1573,1565,1556,1548,1540,1532,1524,1516,1507,1499,1491,1483,1475,1466,1458,1450,1442,1434,1425,1417,1409,1401,1393,1384,1376,1368,1360,1352,1343,1335,1327,1319,1311,1303,1294,1286,1278,1270,1262,1253,1245,1237,1229,1221,1212,1204,1196,1188,1180,1171,1163,1155,1147,1139,1130,1122,1114,1106,1098,1090,1081,1073,1065,1057,1049,1040,1032,1024,1016,1008,999,991,983,975,967,958,950,942,934,926,918,909,901,893,885,877,868,860,852,844,836,827,819,811,803,795,786,778,770,762,754,745,737,729,721,713,705,696,688,680,672,664,655,647,639,631,623,614,606,598,590,582,573,565,557,549,541,532,524,516,508,500,492,483,475,467,459,451,442,434,426,418,410,401,393,385,377,369,360,352,344,336,328,319,311,303,295,287,279,270,262,254,246,238,229,221,213,205,197,188,180,172,164,156,147,139,131,123,115,106,98,90,82,74,66,57,49,41,33,25,16,8,0};

unsigned int freq = 500;
unsigned int range = 1000;
#pragma DATA_SECTION(seq,"data_seq")
double seq = 0;
#pragma DATA_SECTION(gap,"data_gap")
double gap = 4.167;
int value=0;
unsigned int flag = 1;// 1=sine 2=square 3=tri
int temp = 0;
int count = 0;
int state = 1;

int main(){
	

	asm(" LDM PMST, A");
	asm(" OR #0x20, A");

	asm(" AND #0x007F, A");

	asm(" OR  #0x1C00, A ");
	asm(" STLM  A, PMST");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	initLcd();
	initLedkey();
	
	
	asm("	STM     #0010h,TCR");	
	asm("	NOP");
	asm("	NOP");
	asm("	STM		#0063h,PRD");	//60000hz	
	asm("	NOP");
	asm("	NOP");
	asm("	STM     #0029h,TCR");   
	asm("	NOP");
	asm("	NOP");
	asm("	STM		#000Ah,IMR");	
	asm("	NOP");
	asm("	NOP");

	delayLed(2);
	asm(" RSBX INTM");
 	delayLed(2);

	// 数码管依次显示"0-9"
    //ledDisplayNum();

	// 液晶屏显示main menue
	lcdDisplayStr(hint_str, sizeof(hint_str),0x22);
	lcdDisplayStr(sin_str, sizeof(sin_str),0x32);
	lcdDisplayStr(square_str, sizeof(square_str),0x42);
	lcdDisplayStr(tri_str, sizeof(tri_str),0x52);

	while(1){
	
	}

}

int calculate_len(unsigned int num){
	unsigned int length = 0;
	unsigned int temp = num;
	while (temp!=0){
		temp = temp/10;
		length++;
	}
	return length;
}

unsigned char* int2str(unsigned int num){
	int i;
	for (i=calculate_len(num)-1; i>=0; i--){
		int seq = num%10;
		num = num/10;
		output[i] = nums[seq];
	}
	return output; 
}

void second_menue(unsigned int flag){
	clc_lcd();
	switch(flag){
		case 1:lcdDisplayStr(sin_str, sizeof(sin_str),0x22);break;
		case 2:lcdDisplayStr(square_str, sizeof(square_str),0x22); break;
		case 3:lcdDisplayStr(tri_str, sizeof(tri_str),0x22);break;
	}
	lcdDisplayStr(freq_str, sizeof(freq_str),0x30);
	lcdDisplayStr(range_str, sizeof(range_str),0x40);

	lcdDisplayStr(int2str(freq), calculate_len(freq),0x3A);
	lcdDisplayStr(int2str(range), calculate_len(range),0x4A);
}

void sin_wave(){
	seq = seq + gap;
	if(seq >= 499)
		seq = 0;
	temp = seq;
	value = sin_value[temp]/2048*range;
	IOSR = value;
}

void square_wave(){
	int max = 60000/(freq*2);
	if(count >= max){
		count = 0;
		state = 1-state;
	}
	count = count+1;
	IOSR = state*range;
}

void tri_wave(){
	seq = seq + gap;
	if(seq >=499)
		seq = 0;
	temp = seq;
	value = tri_value[temp]/2048*range;
	IOSR = value;
}

interrupt void intrFn(){

	asm(" SSBX INTM");
	ledWrite(1, 0xdf);
	ledWrite(1, 0x50);
	ch = ledRead();
	ledWrite(1, 0x90);
	switch(ch){
		case 0x03: ledDisplayCh(0x00);break;	//0
		case 0x0B: ledDisplayCh(0x10); flag=1; second_menue(flag); break;	//1
		case 0x13: ledDisplayCh(0x20); flag=2; second_menue(flag); break;	//2
		case 0x1B: ledDisplayCh(0x30); flag=3; second_menue(flag); break;	//3
		case 0x02: ledDisplayCh(0x40); freq = freq+10;gap = (500*(freq*1.0))/60000; second_menue(flag); break;	//4
		case 0x0A: ledDisplayCh(0x50); range = range+50; second_menue(flag); break;	//5
		case 0x12: ledDisplayCh(0x60);break;	//6
		case 0x1A: ledDisplayCh(0x70);break;	//7
		case 0x01: ledDisplayCh(0x80); freq = freq-10;gap = (500*(freq*1.0))/60000; second_menue(flag); break;	//8
		case 0x09: ledDisplayCh(0x90); range = range-50; second_menue(flag); break;	//9
		default : break;		
	}

	ledWrite(1, 0xef);
	asm(" RSBX INTM");
}

interrupt void intrClock(){
	switch(flag){
		case 1:sin_wave();break;
		case 2:square_wave();break;
		case 3:tri_wave();break;
	}	
}

