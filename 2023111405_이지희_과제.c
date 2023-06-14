#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct BOOK
{
	char b_name[100][30]; //책 배열 생성
	char au_name[100][30]; //저자 배열 생성
	char p_name[100][30]; //출판사 배열 생성
	int borrowed;
	
};

void register_book(struct BOOK* books, int *total_booknum) {
	FILE* fp;
	fp = fopen("books.txt", "a");
	if (fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}
	printf("도서의 이름:");
	scanf("%s", books[*total_booknum].b_name);

	printf("저자:");
	scanf("%s", books[*total_booknum].au_name);

	printf("출판사:");
	scanf("%s", books[*total_booknum].p_name);

	fprintf(fp, "%s %s %s\n", books[*total_booknum].b_name, books[*total_booknum].au_name, books[*total_booknum].p_name);

	books[*total_booknum].borrowed = 0;
	(*total_booknum)++; //total_booknum 증가

	fclose(fp);
}

int compare(char* str1, char* str2) {
	while (*str1) {
		if (*str1 != *str2) {
			return 0;
		}

		str1++;
		str2++;
	}
	if (*str2 == '\0') return 1;

	return 0;
}

void search_book(struct BOOK* books, int total_booknum) {
	int i;
	char user_search[30];
	int found = 0;

	printf("제목: ");
	scanf("%s", user_search);

	for (i = 0; i < total_booknum; i++ ) {
		//j가 0부터 total_booknum 까지 가면서 각각의 책 제목을 사용자가 입력한 검색어와 비교
		if (compare(books[i].b_name, user_search)) {
			printf("출판사는 %s\n", books[i].p_name);
			found = 1;
		}
	}
	if (!found) {
		printf("검색 결과를 찾을 수 없습니다.\n");
	}
}


int main(void) 
{
	int num; //사용자가 메뉴 중 선택한 번호
	int total_booknum = 0;
	int i;
	FILE* fp = NULL;

	struct BOOK* books;

	books = (struct BOOK*)malloc(100 * sizeof(struct BOOK)); //동적 메모리 할당


	while (1) {
		printf("====================\n");
		printf("1. 파일 읽기\n");
		printf("2. 추가\n"); //도서 목록 추가
		printf("3. 출력\n"); //도서 목록 출력
		printf("4. 검색\n"); //도서 목록 검색_제목으로
		printf("5. 파일 쓰기\n");
		printf("6. 종료\n");
		printf("====================\n");
		printf("정수값을 입력하시오 : ");
		scanf("%d", &num);

		
		//1번 입력한 경우
		if (num == 1) {
			if ((fp = fopen("books.txt", "r")) == NULL) {
				fprintf(stderr, "books.txt 파일을 열 수 없습니다.\n");
				exit(1);
			}
			else {
				printf("파일 오픈 성공!\n");
				total_booknum = 0;
				while (fscanf(fp, "제목 : %s\n저자 : %s\n출판사 : %s\n", books[total_booknum].b_name, books[total_booknum].au_name, books[total_booknum].p_name) == 3) {
					books[total_booknum].borrowed = 0;
					total_booknum++;
				}
			}
			fclose(fp);
		}
		
		//2를 입력한 경우
		else if (num == 2) {
			register_book(books, &total_booknum);
		}

		//3을 입력한 경우_도서 출력, 파일 읽기 후 출력
		else if (num == 3) {
			
			for (i = 0; i < total_booknum; i++) {
				printf("제목 : %s\n저자 : %s\n출판사 : %s\n", books[i].b_name, books[i].au_name, books[i].p_name);
			}
		}

		//4를 입력한 경우_제목으로 책 검색
		else if (num == 4) {
			search_book(books, total_booknum);
		}

		//5를 입력한 경우
		else if (num == 5) {
			if ((fp = fopen("books.txt", "w")) == NULL) {
				printf("books.txt를 열 수 없습니다.\n");
				exit(1);
			}
			else {
				printf("파일 오픈 성공!(2)\n");

				//책 정보를 파일에 쓰는 코드를 작성
				for (i = 0; i < total_booknum; i++) {
					fprintf(fp, "제목 : %s\n저자 : %s\n출판사 : %s\n", books[i].b_name, books[i].au_name, books[i].p_name);
				}
			}
			fclose(fp);
		}
		//6을 입력한 경우_종료
		else if (num == 6) {
			break;
		}
		//다른 숫자를 입력한 경우
		else {
			printf("올바른 숫자를 입력해주세요.\n");
		}


	}
	free(books);
	return 0;
}