#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct user
{
	char name[20];
	struct user* down, * right;
};
struct user* head = NULL, *temp0 = NULL;

struct books
{
	char book_name[20], borrow_date[9], return_date[9];
	struct books* books_right;
};

void create_user()
{
	struct user* temp = NULL, * temp1 = NULL;
	temp = (struct user*)malloc(sizeof(struct user));
	temp->down = NULL;
	temp->right = NULL;
	printf("Enter your name\n");
	scanf("%s", temp->name);
	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		temp1 = head;
		while (temp1->down != NULL)
		{
			temp1 = temp1->down;
		}
		temp1->down = temp;
	}
}
void borrow_book()
{
	struct books* temp = NULL, * temp1 = NULL;
	temp = (struct books*)malloc(sizeof(struct books));
	temp->books_right = NULL;
	char name[20];
	printf("Enter the user name\n");
	scanf("%s", name);
	struct user* find = head;
	while (find != NULL)
	{
		if (strcmp(find->name, name) == 0)
		{
			break;
		}
		find = find->down;
	}
	printf("Enter the name of the book\n");
	scanf("%s", temp->book_name);
	printf("Enter the borrow date\n");
	scanf("%s", temp->borrow_date);
	printf("Enter the return date\n");
	scanf("%s", temp->return_date);
	if (find->right == NULL)
	{
		find->right = temp;
	}
	else
	{
		temp1 = find->right;
		while (temp1->books_right != NULL)
		{
			temp1 = temp1->books_right;
		}
		temp1->books_right = temp;
	}
}
void return_book()
{
	struct books* temp1_books = NULL, * temp2_books = NULL;
	struct user* find = head;
	int flag = 0;
	char search_user[20], search_books[20];
	printf("Enter the username\n");
	scanf("%s", search_user);
	printf("Enter the book name\n");
	scanf("%s", search_books);
	while (find != NULL)
	{
		if (strcmp(find->name, search_user) == 0 && flag == 0)
		{
			temp1_books = find->right;
			temp2_books = temp1_books->books_right;
			while (temp2_books != NULL)
			{
				if (strcmp(temp2_books->book_name, search_books) == 0)
				{
					temp1_books->books_right = temp2_books->books_right;
					free(temp2_books);
					flag = 1;
					break;
				}
				else
				{
					temp1_books = temp1_books->books_right;
					temp2_books = temp2_books->books_right;
				}
			}
		}
		find = find->down;
	}
}
void display_list()
{
	struct user* temp_user = head;
	struct books* temp_books = head;
	if (temp_user == NULL)
	{
		printf("There are no entries made\n");
	}
	else
	{
		while (temp_user != NULL)
		{
			printf("%s -> ", temp_user->name);
			temp_books = temp_user->right;
			while (temp_books != NULL)
			{
				printf("%s %s %s ->", temp_books->book_name, temp_books->borrow_date, temp_books->return_date);
				temp_books = temp_books->books_right;
			}
			printf("\n|");
			printf("\n");
			temp_user = temp_user->down;
		}
	}
}
void search_user()
{
	struct books* temp = NULL;
	struct user* find = head;
	char search[20];
	int flag = 0;
	printf("Enter the user name\n");
	scanf("%s", search);
	while (find != NULL)
	{
		if (strcmp(find->name, search) == 0)
		{
			printf("%s ->", find->name);
			temp = find->right;
			while (temp != NULL)
			{
				printf("%s %s %s ->", temp->book_name, temp->borrow_date, temp->return_date);
				temp = temp->books_right;
			}
			printf("\n");
			flag = 1;
		}
		find = find->down;
	}
	if (flag == 0)
	{
		printf("User not found\n\n");
	}
}

void read_from_file()
{
	struct user* user_init;
	struct books* books_init = NULL, *temp2 = NULL;
	FILE* fp;
	fp = fopen("data.txt", "r");
	rewind(fp);
	char temp_name[40];
	char ch = 'a';
	user_init = head = (struct user*)malloc(sizeof(struct user));
	user_init->right = NULL;
	user_init->down = NULL;
	fscanf(fp, "%s", user_init->name);
	while(ch != '\n')
	{
		books_init = (struct books*)malloc(sizeof(struct books));
		fscanf(fp, "%s %s %s", books_init->book_name, books_init->borrow_date, books_init->return_date);
		strcat(books_init->book_name, "\0");
		
		if (user_init->right == NULL)
		{
			user_init->right = books_init;
			temp2 = books_init;
		}
		else
		{
			temp2->books_right = books_init;
			temp2 = books_init;
		}
		ch = fgetc(fp);
		
	}
	temp2->books_right = NULL;
	books_init->books_right = NULL;
	books_init = NULL;
	temp2 = NULL;
	while (feof(fp) == 0)
	{
		
		if (ch == '\n')
		{
			
			temp0 = (struct user*)malloc(sizeof(struct user));
			temp0->down = NULL;
			temp0->right = NULL;
			fscanf(fp, "%s", temp0->name);
		//	printf("%s\n", temp->name);
		//	strcat(temp->name, "\0");
		//	printf("%s\n", temp->name);
			user_init->down = temp0;
			user_init = temp0;
			temp0->right = books_init = temp2;
			ch = fgetc(fp);
		}	
		while (ch != '\n' && feof(fp) == 0)
		{
			printf("Entered books while loop\n");
			books_init = (struct user*)malloc(sizeof(struct books));
			fscanf(fp, "%s %s %s", &books_init->book_name, &books_init->borrow_date, &books_init->return_date);
			if (temp0->right == NULL)
			{
				temp0->right = books_init;
				temp2 = books_init;
			}
			else
			{
				temp2->books_right = books_init;
				temp2 = books_init;
			}
			ch = fgetc(fp);
			//	printf("%s %s %s\n", books_init->book_name, books_init->borrow_date, books_init->return_date);	
		}
		
		temp2->books_right = NULL;
		books_init->books_right = NULL;
		books_init = NULL;
		temp2 = NULL;
	}
	fclose(fp);
}

void store_in_file()
{
	struct user* find = head;
	struct books* temp = head;
	FILE* fp;
	fp = fopen("data.txt", "w");
	while (find != NULL)
	{
		temp = find->right;
		fprintf(fp, "%s", find->name);
		while (temp != NULL)
		{
			fprintf(fp, " %s %s %s", temp->book_name, temp->borrow_date, temp->return_date);
			temp = temp->books_right;
		}
		fprintf(fp, "\n");
		find = find->down;
	}
	fflush;
	fclose(fp);
}


void main()
{
	int choice = 0;
	read_from_file();
	do
	{
		printf("\nEnter you choice\n");
		printf("1. create user 2. search user 3. borrow book 4. return book 5. place request 6. display inventory 7. exit\n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1: create_user();
			break;
		case 2: search_user();
			break;
		case 3: borrow_book();
			break;
		case 4: return_book();
			break;
		case 5:
			break;
		case 6: display_list();
			break;
		case 7: store_in_file();
			exit(0);
			break;
		default: printf("Invalid input\n");
		}
	} while (choice != -1);
}
