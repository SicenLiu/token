//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<time.h>
//#include<cstdio>
//using namespace std;
//
//struct chinese_ch {
//	int num;
//	char word[3];
//};
//
//void quickSort(chinese_ch s[], int l, int r) {
//	if (l< r) {
//		int i = l, j = r;
//		chinese_ch x = s[l];
//		while (i < j) {
//			while (i < j && (s[j].num < x.num || (s[j].num == x.num && s[j].word[0] < x.word[0]))) // ���������ҵ�һ��С��x����  
//				j--;
//			if (i < j)
//				s[i++] = s[j];
//			while (i < j && s[i].num > x.num) // ���������ҵ�һ�����ڵ���x����  
//				i++;
//			if (i < j)
//				s[j--] = s[i];
//		}
//		s[i] = x;
//		quickSort(s, l, i - 1); // �ݹ����  
//		quickSort(s, i + 1, r);
//	}
//}
//
//int main() {
//	clock_t start_time = clock();
//
//	FILE *fp=fopen("data_51_100.txt","r");
//	if (fp == NULL) {
//		cerr << "Unable to open data_51_100.txt" << endl;
//		exit(-1);
//	}
//
//	chinese_ch words[35000];
//
//	const int bottom = 0x8140;
//	const int top0 = 0xa0fe-bottom;
//	const int bottom1 = 0xAA40-bottom;
//	const int top1 = 0xfefe-bottom;
//
//	//���ڴ�ź���ʹ�ø��������飬���ں��ֱ��뷶Χ��8041-FEFE�������±�+0xB0A1����ʾ���ֱ���
//	for (int i = 0; i < 35000; i++) words[i].num = 0;
//
//	while (!feof(fp)) {
//		char line[150];
//		fgets(line, 150, fp);
//
//		int p = 0;
//		int strlen = 0;
//		int len = 0;
//
//		while (line[len] != '\n') len++;
//		while (p <= len) {
//			/*
//			 * �жϸ�λ�ǲ���1����1��ʾΪ�����ַ���ȫ�Ƿ��ŵ���λ��
//			 * ԭ����ȡ���ո��м���ַ�������ȡ��ԭ��Ϊ�ı��д��ں��ֺ���Ӱ�Ƿ��ŵ����
//			 *		-- ������û �� �� �� �� �� �� ; �� �� �� �� �� �� �� �� �� �� �� �� �� ��-r . b . �� �� �� ����
//			 */
//			if (line[p]<0) {
//				int a = (unsigned char)line[p];
//				int b = (unsigned char)line[p + 1];
//				int index = (a << 8) + b - bottom;
//
//				if (((index >= 0 && index <= top0) || (index >= bottom1 && index <= top1))) {
//					words[index].num++;
//					words[index].word[0] = line[p];
//					words[index].word[1] = line[p + 1];
//					words[index].word[2] = '\0';
//				}
//				p++;
//			}
//			p++;
//		}
//	}
//	clock_t end_time1 = clock();
//	cout << "�ļ���ȡʱ��: " << static_cast<double>(end_time1 - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//	fclose(fp);
//
//	quickSort(words, 0, 34999);
//	clock_t end_time2 = clock();
//	cout << "����ʱ��: " << static_cast<double>(end_time2 - end_time1) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//
//	FILE *outfp = fopen("d:\\token.txt", "w");
//	if (outfp == NULL) {
//		cerr << "Unable to open d:\\token.txt" << endl;
//		exit(-1);
//	}
//
//	int count = 0;
//	for (int j = 0; j < 35000; j++) {
//		if (words[j].num > 0) {
//			char outputInfo[20];
//			char* blank = " ";
//			char* end = "\n";
//			strcpy(outputInfo, words[j].word);
//			strcat(outputInfo, blank);
//			int num = words[j].num;
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
//			strcat(outputInfo, end);
//			fwrite(outputInfo, strlen(outputInfo) * sizeof(char), 1, outfp);
//			count++;
//		}
//	}
//	cout << "���ָ�����" << count << endl;
//	fclose(outfp);
//
//	clock_t end_time3 = clock();
//	cout << "���ʱ��: " << static_cast<double>(end_time3 - end_time2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//
//	return 0;
//}