#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define LINE_INDEX 1000
#define Dict_SIZE 200000

#pragma warning(disable:4996)

int init_val = 0;

char *w[Dict_SIZE];
char *w_type[Dict_SIZE];
char *w_cont[Dict_SIZE];


void read();
int read_line(FILE *fp, char str[], int limit);
void cnt();
int find_index(char word[], int start, int end);
void find_word(char word[], int index);
void check_status();


int main(void) {

	check_status();

	getch();

	return 0;
}

void read() {
	char textname[LINE_INDEX];
	char str[LINE_INDEX];
	char bracket[] = "()";

	scanf("%s", textname);

	FILE *fp = fopen(textname, "r");


	while (1) {
		read_line(fp, str, LINE_INDEX);
		if (strcmp(str, "\0")) {
			char *token = strtok(str, bracket);
			w[init_val] = strdup(token);
			w[init_val][strlen(w[init_val]) - 1] = '\0';
			token = strtok(NULL, bracket);
			w_type[init_val] = strdup(token);
			token = strtok(NULL, bracket);
			w_cont[init_val] = strdup(token);
			init_val++;
		}
		if (feof(fp) != 0)

			break;

	}
	fclose(fp);
}

int read_line(FILE *fp, char str[], int limit) {

	int i = 0;
	int val = 0;

	while ((val = fgetc(fp)) != '\n' && val != EOF) {
		if (i < limit - 1)
			str[i++] = val;
	}

	str[i] = '\0';

	return i;
}

void cnt() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("%d\n\n", init_val);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int find_index(char word[], int start, int end) {
	int mid = (start + end) / 2;

	if (start > end) return start - 1;
	if (strcmp(word, w[mid]) == 0) return mid;
	else if (strcmp(word, w[mid]) < 0) return find_index(word, start, mid - 1);
	else return find_index(word, mid + 1, end);

}

void find_word(char word[], int index) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	if (index == -1) {
		printf("-1\n");
		printf("- - -\n");
		printf("%s (%s)\n", w[0], w_type[0]);
		printf("\n");
	}
	else if (strcmp(w[index], word) != 0) {
		printf("Not found.\n");
		printf("%s (%s)\n", w[index], w_type[index]);
		printf("- - -\n");
		if (index < init_val - 1) {
			printf("%s (%s)\n", w[index + 1], w_type[index + 1]);
			printf("\n");
		}
	}
	else {
		int upcnt = -1, downcnt = -1;
		int i = index, j = index;

		while (i >= 0 && strcmp(w[i--], word) == 0) {
			downcnt++;
		}
		while (j < init_val && strcmp(w[j++], word) == 0) {
			upcnt++;
		}
		printf("Found %d items.\n", upcnt + downcnt + 1);
		for (int i = index - downcnt; i < index; i++) {
			printf("%s (%s)%s\n", w[i], w_type[i], w_cont[i]);
		}
		printf("%s (%s)%s\n", w[index], w_type[index], w_cont[index]);
		for (int j = index + 1; j <= index + upcnt; j++) {
			printf("%s (%s)%s\n", w[j], w_type[j], w_cont[j]);
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void check_status() {
	char cmd[LINE_INDEX];
	while (1) {
		printf("$ "); scanf("%s", cmd);

		if (strcmp(cmd, "read") == 0) read();
		else if (strcmp(cmd, "size") == 0) cnt();
		else if (strcmp(cmd, "find") == 0) {
			char word[LINE_INDEX];
			scanf("%s", word);
			word[0] = word[0] - 32;
			int index = find_index(word, 0, init_val - 1);
			find_word(word, index);
		}
		else if (strcmp(cmd, "exit") == 0) exit(1);
		else printf("Error occured! Try again Plz.\n");
	}
}