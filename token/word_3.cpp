//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<time.h>
//#include<string.h>
//#include<cstdio>
//using namespace std;
//
//struct chinese_ch {
//	int num;
//	char word[7];
//};
//
//void quickSort(chinese_ch s[], int l, int r) {
//	if (l< r) {
//		int i = l, j = r;
//		chinese_ch x = s[l];
//		while (i < j) {
//			while (i < j && (s[j].num < x.num || (s[j].num == x.num && s[j].word[0] < x.word[0]))) // 从右向左找第一个小于x的数  
//				j--;
//			if (i < j)
//				s[i++] = s[j];
//			while (i < j && (s[i].num > x.num)) // 从左向右找第一个大于等于x的数  
//				i++;
//			if (i < j)
//				s[j--] = s[i];
//		}
//		s[i] = x;
//		quickSort(s, l, i - 1); // 递归调用  
//		quickSort(s, i + 1, r);
//	}
//}
//
//int main() {
//	clock_t start_time = clock();
//	FILE *fp = fopen("data_51_100.txt", "r");
//	if (fp == NULL) {
//		cerr << "Unable to open data_51_100.txt" << endl;
//		exit(-1);
//	}
//
//	const int n = 10000000;
//	chinese_ch doubleWords[n];
//
//	const int bottom = 0x8140;
//	const int top0 = 0xa0fe;
//	const int bottom1 = 0xAA40;
//	const int top1 = 0xfefe;
//
//	const unsigned int seed = 131;
//
//	//用于存放汉字使用个数的数组，由于汉字编码范围是8041-FEFE，数组下标+0xB0A1，表示汉字编码
//	for (int i = 0; i < n; i++) doubleWords[i].num = 0;
//
//	while (!feof(fp)) {
//
//		char line[150];
//		fgets(line, 150, fp);
//
//		int p = 0;
//		int len = 0;
//		int wordNum = 0;
//		char doubleWord[7];
//		doubleWord[6] = '\0';
//
//		while (line[len] != '\n') len++;
//		while (p <= len) {
//			if (line[p]<0) {
//				int a = (unsigned char)line[p];
//				int b = (unsigned char)line[p + 1];
//				int index = (a << 8) + b;
//
//				if ((index >= bottom && index <= top0) || (index >= bottom1 && index <= top1)) {	//是汉字
//					doubleWord[wordNum * 2] = line[p];
//					doubleWord[wordNum * 2 + 1] = line[p + 1];
//					
//					if (wordNum == 2) { //三字
//
//						unsigned int hash = 0;
//						for (int k = 0; k < 6; k++) hash = hash * seed + doubleWord[k];
//						unsigned int i = (hash & 0x7fffffff) % n;
//						while (doubleWords[i].num != 0 && strcmp(doubleWords[i].word, doubleWord) != 0) {
//							i = (i * 1313 + hash) % n;
//						}
//
//						if (doubleWords[i].num == 0) {
//							doubleWords[i].num = 1;
//							for (int j = 0; j < 6; j++)
//								doubleWords[i].word[j] = doubleWord[j];
//							doubleWords[i].word[6] = '\0';
//						}
//						else {
//							doubleWords[i].num++;
//						}
//						for (int j = 0; j < 4; j++)
//							doubleWord[j] = doubleWord[j + 2];
//					}
//					else wordNum++;
//					p++;
//				}
//				else wordNum = 0;
//				p++;
//			}
//			else wordNum = 0;
//			p++;
//		}
//	}
//	clock_t end_time1 = clock();
//	cout << "读取文件: " << static_cast<double>(end_time1 - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//	fclose(fp);
//
//	chinese_ch outputWords[10000000];
//	int j = 0;
//	for (int i = 0; i < n && j < 10000000; i++) {
//		if (doubleWords[i].num > 1) {
//			outputWords[j].num = doubleWords[i].num;
//			for (int k = 0; k < 7; k++)
//			outputWords[j].word[k] = doubleWords[i].word[k];
//			j++;
//		}
//	}
//	if (j == 10000000) {
//		cout << "overflow" << endl;
//		return -1;
//	}
//	cout << "三字词个数：" << j << endl;
//
//	quickSort(outputWords, 0, j);
//
//	clock_t end_time2 = clock();
//	cout << "排序时间: " << static_cast<double>(end_time2 - end_time1) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//
//	FILE *outfp = fopen("d:\\word_3.txt", "w");
//	if (outfp == NULL) {
//		cerr << "Unable to open d:\\word_3.txt" << endl;
//		exit(-1);
//	}
//
//	for (int i = 0; i < j; i++) {
//		if (outputWords[i].num > 1) {
//			char outputInfo[30];
//			char* blank = " ";
//			char* end = "\n";
//			strcpy(outputInfo, outputWords[i].word);
//			strcat(outputInfo, blank);
//			int num = outputWords[i].num;
//			char n1[10];
//			int i = 0;
//			for (; num != 0; i++){
//				n1[i] = '0' + (char)(num % 10);
//				num = num / 10;
//			}
//			char n2[10];
//			int j = 0;
//			for (; i>0; i--, j++) {
//				n2[j] = n1[i - 1];
//			}
//			n2[j] = '\0';
//			strcat(outputInfo, n2);
//
//			strcat(outputInfo, end);
//			fwrite(outputInfo, strlen(outputInfo) * sizeof(char), 1, outfp);
//		}
//	}
//	fclose(outfp);
//	clock_t end_time3 = clock();
//	cout << "输出时间: " << static_cast<double>(end_time3 - end_time2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//
//	return 0;
//}