#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include<string.h>
#include<cstdio>
using namespace std;
struct ch1 {
	int num;
	char word[3];
};
struct ch2 {
	int num;
	char word[5];
	bool valid;
};
struct ch3 {
	int num;
	char word[7];
	bool valid;
};
struct ch4 {
	int num;
	char word[9];
	bool valid;
};
void quickSort(ch3 s[], int l, int r) {
	if (l< r) {
		int i = l, j = r;
		ch3 x = s[l];
		while (i < j) {
			while (i < j && (s[j].num < x.num || (s[j].num == x.num && s[j].word[0] < x.word[0]))) // 从右向左找第一个小于x的数  
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && (s[i].num > x.num)) // 从左向右找第一个大于等于x的数  
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1); // 递归调用  
		quickSort(s, i + 1, r);
	}
}

void quickSort(ch4 s[], int l, int r) {
	if (l< r) {
		int i = l, j = r;
		ch4 x = s[l];
		while (i < j) {
			while (i < j && (s[j].num < x.num || (s[j].num == x.num && s[j].word[0] < x.word[0]))) // 从右向左找第一个小于x的数  
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && (s[i].num > x.num)) // 从左向右找第一个大于等于x的数  
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1); // 递归调用  
		quickSort(s, i + 1, r);
	}
}

int main() {
	clock_t start_time = clock();

	/*token.txt检测*/
	FILE *fp0 = fopen("d:\\token.txt", "r");
	if (fp0 == NULL) {
		cerr << "Unable to open token.txt" << endl;
		exit(-1);
	}

	const int ch1word_maxlen = 20000;
	ch1 ch1word[ch1word_maxlen];
	for (int i = 0; i < ch1word_maxlen; i++) 
		ch1word[i].num = 0;

	while (!feof(fp0)) {
		char line[20];
		fgets(line, 20, fp0);

		int a = (unsigned char)line[0];
		int b = (unsigned char)line[1];
		char word[3];
		word[0] = line[0];
		word[1] = line[1];
		word[2] = '\0';

		int key = a * a * 13 + b * b * 131;
		int i = (key) % ch1word_maxlen;
		while (ch1word[i].num != 0) {
			i = (i * 419 + b * a * 131) % ch1word_maxlen;
		}

		ch1word[i].word[0] = line[0];
		ch1word[i].word[1] = line[1];
		ch1word[i].word[2] = '\0';

		int num = 0;
		for (int i = 3; line[i] != '\n'; i++) 
			num = (int)(line[i] - '0') + num * 10;
		ch1word[i].num = num;

		if (ch1word[i].num <= 100) break;		//只取出现次数大于100的字
	}
	fclose(fp0);
	clock_t end_time1 = clock();
	cout << "token文件读取时间: " << static_cast<double>(end_time1 - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	/*word_2.txt检测*/
	FILE *fp1 = fopen("d:\\word_2.txt", "r");
	if (fp1 == NULL) {
		cerr << "Unable to open word_2.txt" << endl;
		exit(-1);
	}

	const int ch2words_maxlen = 1000000;
	ch2 ch2words[ch2words_maxlen];
	for (int i = 0; i < ch2words_maxlen; i++) 
		ch2words[i].num = 0;

	while (!feof(fp1)) {
		char line[20];
		fgets(line, 20, fp1);

		int num = 0;
		for (int i = 5; line[i] != '\n'; i++) 
			num = (int)(line[i] - '0') + num * 10;

		int n[2], a[4];
		int key, k;
		for (int j = 0; j < 4; j++) 
			a[j] = (unsigned char)line[j];

		for (int j = 0; j < 2; j++) {
			key = a[2 * j] * a[2 * j] * 13 + a[2 * j + 1] * a[2 * j + 1] * 131;
			k = (key) % ch1word_maxlen;
			while (ch1word[k].num != 0 && (ch1word[k].word[0] != line[2 * j] || ch1word[k].word[1] != line[2 * j + 1])) {
				k = (k * 419 + key * 191) % ch1word_maxlen;
			}
			if (ch1word[k].num != 0) 
				n[j] = ch1word[k].num;
		}
		char word[5];
		for (int j = 0; j < 4; j++) 
			word[j] = line[j];
		word[4] = '\0';

		unsigned int hash = 0;
		for (int k = 0; k < 4; k++) hash = hash * 131 + word[k] * 223;
		unsigned int i = (hash & 0x7fffffff) % ch2words_maxlen;

		while (ch2words[i].num != 0) {
			i = (i * 131 + hash) % ch2words_maxlen;
		}

		for (int j = 0; j < 4; j++) 
			ch2words[i].word[j] = line[j];
		ch2words[i].word[4] = '\0';
		ch2words[i].num = num;

		if (n[0] > 200000 || n[1] > 200000)
			ch2words[i].valid = false;
		else if ((n[0] / 10) * (n[1] / 10) > (num * 10000))
			ch2words[i].valid = false;
		else ch2words[i].valid = true;

		if (ch2words[i].num <= 19) break;		//只取出现次数大于19的双字词语
	}
	fclose(fp1);
	clock_t end_time2 = clock();
	cout << "word_2文件读取时间: " << static_cast<double>(end_time2 - end_time1) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	/*word_3.txt文件检测*/
	FILE *fp2 = fopen("d:\\word_3.txt", "r");
	if (fp2 == NULL) {
		cerr << "Unable to open word_3.txt" << endl;
		exit(-1);
	}

	const int ch3words_maxlen = 450000;
	ch3 ch3words[ch3words_maxlen];
	for (int i = 0; i < ch3words_maxlen; i++) {
		ch3words[i].valid = false;
		ch3words[i].num = 0;
	}
	while (!feof(fp2)) {
		char line[20];
		fgets(line, 20, fp2);

		int num = 0;
		for (int i = 7; line[i] != '\n'; i++) 
			num = (int)(line[i] - '0') + num * 10;

		int n[3], a[6];
		int key, k;
		for (int j = 0; j < 6; j++) 
			a[j] = (unsigned char)line[j];

		for (int j = 0; j < 3; j++) {
			key = a[2 * j] * a[2 * j] * 13 + a[2 * j + 1] * a[2 * j + 1] * 131;
			k = (key) % ch1word_maxlen;
			while (ch1word[k].num != 0 && (ch1word[k].word[0] != line[2 * j] || ch1word[k].word[1] != line[2 * j + 1])) {
				k = (k * 419 + key * 191) % ch1word_maxlen;
			}
			if (ch1word[k].num != 0) n[j] = ch1word[k].num;
		}

		char word[7];
		for (int j = 0; j < 6; j++)
			word[j] = line[j];
		word[6] = '\0';

		unsigned int hash = 0;
		for (int k = 0; k < 6; k++) hash = hash * 131 + word[k] * 223;
		unsigned int i = (hash & 0x7fffffff) % ch3words_maxlen;

		while (ch3words[i].num != 0) {
			i = (i * 131 + hash) % ch3words_maxlen;
		}

		for (int j = 0; j < 6; j++)
			ch3words[i].word[j] = line[j];
		ch3words[i].word[6] = '\0';
		ch3words[i].num = num;

		if (n[0] > 200000 || n[1] > 200000 || n[2] > 200000)
			ch3words[i].valid = false;
		else ch3words[i].valid = true;

		if (ch3words[i].num <= 19) break;		//只取出现次数大于5的san字词语
	}
	fclose(fp2);
	clock_t end_time3 = clock();
	cout << "word_3文件读取时间: " << static_cast<double>(end_time3 - end_time2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	/*word_4.txt检测*/
	FILE *fp3 = fopen("d:\\word_4.txt", "r");
	if (fp3 == NULL) {
		cerr << "Unable to open word_4.txt" << endl;
		exit(-1);
	}

	ch4 ch4words[1000000];
	int ch4words_len = 0;
	while (!feof(fp3)) {
		char line[30];
		fgets(line, 30, fp3);

		for (int j = 0; j < 8; j++)
			ch4words[ch4words_len].word[j] = line[j];
		ch4words[ch4words_len].word[8] = '\0';

		int num = 0;
		for (int i = 9; line[i] != '\n'; i++) 
			num = (int)(line[i] - '0') + num * 10;

		int n[4], a[8];
		int key, k;
		for (int j = 0; j < 8; j++)
			a[j] = (unsigned char)line[j];

		for (int j = 0; j < 4; j++) {
			key = a[2 * j] * a[2 * j] * 13 + a[2 * j + 1] * a[2 * j + 1] * 131;
			k = (key) % ch1word_maxlen;
			while (ch1word[k].num != 0 && (ch1word[k].word[0] != line[2 * j] || ch1word[k].word[1] != line[2 * j + 1])) {
				k = (k * 419 + key * 191) % ch1word_maxlen;
				//cout << ".";
			}
			if (ch1word[k].num != 0) n[j] = ch1word[k].num;
		}

		ch4words[ch4words_len].num = num;
		if (n[0] > 200000 || n[1] > 200000 || n[2] > 200000 || n[3] > 200000)
			ch4words[ch4words_len].valid = false;
		else ch4words[ch4words_len].valid = true;

		if (ch4words[ch4words_len].num <= 19) break;		//只取出现次数大于19的四字词语
		ch4words_len++;
	}
	fclose(fp3);
	clock_t end_time4 = clock();
	cout << "word_4文件读取时间: " << static_cast<double>(end_time4 - end_time3) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	/*词典生成*/
	ch4 dictionary[10000000];
	int dictionary_len = 0;
	int numOf2Words = 0;
	int numOf3Words = 0;
	int numOf4Words = 0;

	for (int i = 0; i < ch4words_len; i++) {
		if (ch4words[i].valid == false) continue;
		int flag = 0;
		for (int current = 0; current < 2; current++) {
			char word[7];
			for (int j = 0; j < 6; j++)
				word[j] = ch4words[i].word[current * 2 + j];
			word[6] = '\0';

			unsigned int hash = 0;
			for (int k = 0; k < 6; k++) hash = hash * 131 + word[k] * 223;
			unsigned int key = (hash & 0x7fffffff) % ch3words_maxlen;

			while (ch3words[key].num != 0 && strcmp(ch3words[key].word, word) != 0) {
				key = (key * 131 + hash) % ch3words_maxlen;
			}

			if (ch3words[key].num != 0 && ch3words[key].valid == true) {
				if (ch3words[key].num < ch4words[i].num * 2) {
					ch3words[key].valid = false;
				}
			}
		}
		for (int current = 0; current < 3; current++) {
			char word[5];
			for (int j = 0; j < 4; j++)
				word[j] = ch4words[i].word[current * 2 + j];
			word[4] = '\0';

			unsigned int hash = 0;
			for (int k = 0; k < 4; k++) hash = hash * 131 + word[k] * 223;
			unsigned int key = (hash & 0x7fffffff) % ch2words_maxlen;

			while (ch2words[key].num != 0 && strcmp(ch2words[key].word, word) != 0) {
				key = (key * 131 + hash) % ch2words_maxlen;
			}

			if (ch2words[key].num != 0 && ch2words[key].valid == true) {
				if (ch2words[key].num < ch4words[i].num * 2) {
					flag++;
					ch2words[key].valid = false;;
				}
			}
		}
		if (ch4words[i].valid == true && flag == 3) {
			dictionary[dictionary_len] = ch4words[i];
			dictionary_len++;
			numOf4Words++;
			ch4words[i].valid = false;
		}
	}

	quickSort(ch3words, 0, ch3words_maxlen);
	for (int i = 0; i < ch3words_maxlen; i++) {
		if (ch3words[i].num == 0) break;
		if (ch3words[i].valid == false) continue;
		int flag = 0;
		for (int current = 0; current < 2; current++) {
			char word[5];
			for (int j = 0; j < 4; j++)
				word[j] = ch3words[i].word[current * 2 + j];
			word[4] = '\0';

			unsigned int hash = 0;
			for (int k = 0; k < 4; k++) hash = hash * 131 + word[k] * 223;
			unsigned int key = (hash & 0x7fffffff) % ch2words_maxlen;

			while (ch2words[key].num != 0 && strcmp(ch2words[key].word, word) != 0) {
				key = (key * 131 + hash) % ch2words_maxlen;
			}

			if (ch2words[key].num != 0 && ch2words[key].valid == true) {
				if (ch2words[key].num < ch3words[i].num * 2) {
					flag++;
					ch2words[key].valid = false;
				}
				else if (ch2words[key].num > ch3words[i].num * 5) {
					dictionary[dictionary_len].num = ch2words[key].num;
					for (int j = 0; j < 4; j++)
						dictionary[dictionary_len].word[j] = ch2words[key].word[j];
					dictionary[dictionary_len].word[4] = '\0';
					dictionary_len++;
					numOf2Words++;
					ch2words[key].valid = false;
					ch3words[i].valid = false;
					break;
				}
			}
		}
		if (ch3words[i].valid == true && flag == 2) {
			dictionary[dictionary_len].num = ch3words[i].num;
			for (int j = 0; j < 6; j++)
				dictionary[dictionary_len].word[j] = ch3words[i].word[j];
			dictionary[dictionary_len].word[6] = '\0';
			dictionary_len++;
			numOf3Words++;
		}
	}
	quickSort(dictionary, 0, dictionary_len);
	clock_t end_time5 = clock();
	cout << "词典生成: " << static_cast<double>(end_time5 - end_time4) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "词典大小（词的个数）" << dictionary_len << endl;

	FILE *outfp = fopen("d:\\dictionary.txt", "w");
	if (outfp == NULL) {
		cerr << "Unable to open d:\\dictionary.txt" << endl;
		exit(-1);
	}

	for (int i = 0; i < dictionary_len; i++) {
		char outputInfo[30];
		char* blank = "\t";
		char* end = "\n";
		strcpy(outputInfo, dictionary[i].word);
		strcat(outputInfo, blank);
		int num = dictionary[i].num;
		char n1[10];
		int x = 0;
		for (; num != 0; x++){
			n1[x] = '0' + (char)(num % 10);
			num = num / 10;
		}
		char n2[10];
		int y = 0;
		for (; x>0; x--, y++) {
			n2[y] = n1[x - 1];
		}
		n2[y] = '\0';
		strcat(outputInfo, n2);

		strcat(outputInfo, end);
		fwrite(outputInfo, strlen(outputInfo) * sizeof(char), 1, outfp);
	}
	fclose(outfp);
	clock_t end_time6 = clock();
	cout << "词典输出: " << static_cast<double>(end_time6 - end_time5) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	cout << "二字词个数：" << numOf2Words << endl;
	cout << "三字词个数：" << numOf3Words << endl;
	cout << "四字词个数：" << numOf4Words << endl;
	return 0;
}