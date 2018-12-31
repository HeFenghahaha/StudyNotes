#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "string.h"
#include "ArrayText.c"

void init(seqstack *st)
{
	st->top = 0;
}
void push(seqstack *st, int x)
{
	if (st->top == MAXSIZE)
	{
		printf("\nջ������!");
		exit(1);
	}
	st->a[st->top] = x;
	st->top++;
}

int pop(seqstack *st)
{
	if (st->top == 0)
	{
		printf("\nջ�ǿյ�!");
		exit(1);
	}
	st->top--;
	return st->a[st->top];
}

void ReadFromFile(TextCompiler *text, char *filename)
{
	Word *word; //�µĽ��
	FILE *file;
	Word *p = NULL;
	file = fopen(filename, "r");
	int i = 0;
	int j = -1;
	if (file)
	{
		word = (Word *)malloc(sizeof(Word));
		word->length = 0; //��ʼ��ֵ����Ϊ0
		while ((word->data[i] = fgetc(file)) != EOF)
		{
			if (word->data[i] == '\n') //�����ȡ�����
			{
				word->data[i] = '\0';
				j++;								 //������1�ٸ�ֵ
				text->column[j].FirstWord = word;	//����ȡ����һ�����ӵ�����ĺ���
				word = (Word *)malloc(sizeof(Word)); //�ٴο���һ���µ�word
				word->length = 0;					 //��ʼ��ֵ����Ϊ0
				i = 0;								 //�ٴδ�i=0��ʼѭ��
				text->count++;						 //����������1
			}
			else
			{
				i++;
				word->length++;
			}
		}
		printf("�ļ����ݶ�ȡ�ɹ�!!!\n");
	}
	else
		printf("�ļ���ʧ�ܣ�\n");
	fclose(file); //�ر��ļ�
}

//�������
void EasyOutput(TextCompiler *text)
{
	if (text == NULL)
	{
		printf("�����ı�Ϊ�գ������ԣ�\n");
		exit(0);
	}
	for (int i = 0; i < text->count; i++)
		printf("%s\n", text->column[i].FirstWord->data);
}

//ͳ�������ı���������ĸ�ĸ���
int TheLetterNumberOfText(TextCompiler *text)
{
	int count = 0; //������
	int j;		   //�����±��¼
	for (int i = 0; i < text->count; i++)
	{
		j = 0;
		while (text->column[i].FirstWord->data[j] != '\0')
		{
			j++;	 //�����±��ƶ�
			count++; //�������
		}
	}
	return count;
}
//ͳ�������ı������е��ʵĸ���
int TheWordNumberOfText(TextCompiler *text)
{
	int count = 0; //������
	int m;		   //�����±��¼
	int n;
	for (int i = 0; i < text->count; i++)
	{
		m = 0;
		n = 1;
		while (text->column[i].FirstWord->data[n] != '\0')
		{
			if (text->column[i].FirstWord->data[m] != ' ' &&
				(text->column[i].FirstWord->data[n] == ' ' ||
				 text->column[i].FirstWord->data[n] == '.' ||
				 text->column[i].FirstWord->data[n] == '!' ||
				 text->column[i].FirstWord->data[n] == '?' ||
				 text->column[i].FirstWord->data[n] == '"'))
				count++;
			n++; //�����±��ƶ�
			m++;
		}
	}
	return count;
}
//����ÿһ�е������ַ�
void RowNumber(TextCompiler *text)
{
	int row = 0;
	int input = 0;
	printf("\t1.ͳ��ָ���еĿո�ĸ���\n");
	printf("\t2.ͳ��ָ���е���ĸ�ĸ���\n");
	printf("\t3.ͳ��ָ���еı����ŵĸ���\n");
	printf("\t4.ͳ����ƪ���µ��ַ�����\n");
	printf("\t5.ͳ����ƪ���µĵ��ʸ���\n");
	printf("�����빦�ܱ�ţ�\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		printf("�������кţ�\n");
		scanf("%d", &row);
		int count = 0; //������
		int i = 0;	 //����±�
		while (text->column[row - 1].FirstWord->data[i] != '\0')
		{
			if (text->column[row - 1].FirstWord->data[i] == ' ')
				count++;
			i++;
		}
		printf("��%d���ı�����%d���ո�\n", row, count);
		break;
	}
	case 2:
	{
		printf("�������кţ�\n");
		scanf("%d", &row);
		int count = 0; //������
		int i = 0;	 //����±�
		char letter;
		while ((letter = text->column[row - 1].FirstWord->data[i]) != '\0')
		{
			if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
				count++;
			i++;
		}
		printf("��%d���ı�����%d����ĸ\n", row, count);
		break;
	}
	case 3:
	{
		printf("�������кţ�\n");
		scanf("%d", &row);
		int count = 0; //������
		int i = 0;	 //����±�
		while (text->column[row - 1].FirstWord->data[i] != '\0')
		{
			char data = text->column[row - 1].FirstWord->data[i];
			if (data == ',' || data == '.' || data == '?' || data == '"' || data == '\'')
				count++;
			i++;
		}
		printf("��%d���ı�����%d��������\n", row, count);
		break;
	}
	case 4:
	{
		printf("��ƪ�ı�����%d���ַ�\n", TheLetterNumberOfText(text));
		break;
	}
	case 5:
	{
		printf("��ƪ�ı�����%d������\n", TheWordNumberOfText(text));
		break;
	}
	default:
		printf("�������󣡣���\n");
		exit(0);
		break;
	}
}

//kmpģʽƥ��
void kmpmatch(TextCompiler *text)
{
	int i = 0, plength = 0;
	char p[20] = {0};
	printf("��������Ҫ���ҵĵ���:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++; //��ȡ�����ַ����ĳ���
		i++;	   //�ַ����±������ƶ�
	}
	p[plength] = '\0'; //���һλ����Ϊ'\0'
}

void chinesematch(TextCompiler *text, seqstack *st) //���Ĳ���
{
	int i = 0, j, k, m = 0, succ, q, plength = 0;
	char p[20] = {0};
	printf("��������Ҫ���ҵĺ���:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++;
		i++;
	}
	p[plength] = '\0';
	for (k = 0; k < text->count; k++)
	{
		i = 0;
		q = text->column[k].FirstWord->length;
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ)
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			i++;
			if (succ)
			{
				printf("ƥ��ɹ���λ���ڵ�%d�е�%d��\n", k + 1, i - 1);
				push(st, i - 1);
				push(st, k + 1);
				succ = 0;
			}
		}
	}
}
void englishmatch(TextCompiler *text, seqstack *st) //Ӣ�Ĳ���
{
	int i = 0, j, k, m = 0, succ, q, plength = 0;
	char p[20] = {0};
	printf("��������Ҫ���ҵĵ���:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++;
		i++;
	}
	p[plength] = '\0';
	for (k = 0; k < text->count; k++)
	{
		i = 0;
		q = text->column[k].FirstWord->length;
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ)
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			if (text->column[k].FirstWord->data[i + j] == ' ' && text->column[k].FirstWord->data[i - 1] == ' ')
				i++;
			else
			{
				succ = 0;
				i++;
			}
			if (succ)
			{
				printf("ƥ��ɹ���λ���ڵ�%d�е�%d��\n", k + 1, i - 1);
				push(st, i - 1); //д��ջ��������һ�ε���
				push(st, k + 1);
				succ = 0;
			}
		}
	}
}

//����ģʽƥ��
void nativematch(TextCompiler *text, seqstack *st)
{
	int input = 0;
	printf("��ѡ����Ҫ���ҵ���������:1.���� 2.Ӣ��\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
		chinesematch(text, st);
		break;
	case 2:
		englishmatch(text, st);
		break;
	default:
	{
		printf("�������󣡣�\n");
		exit(0);
		break;
	}
	}
}

//������д���ļ�
void PutInFile(char *filename, seqstring *array)
{
	int row; //ÿһ��������������
	printf("������һ����ռ��������\n");
	scanf("%d", &row);
	FILE *fp;
	int save = 0; //����д���ļ��ķ���ֵ
	int count = 0;
	fp = fopen(filename, "w"); //��д��ķ�ʽ���ļ�
	if (fp)
	{
		while (array->str[count] != '\0')
		{
			save = fputc(array->str[count], fp);
			if (save == -1) //�������-1,�����ļ�д��ʧ��
			{
				printf("д���ļ�ʧ�ܣ�����\n");
				exit(0); //�˳�
			}
			count++; //д���ַ���1
			if (count % row == 0)
				fputc('\n', fp); //д��س��Ѵﵽ�����û��ķ�ʽ�洢�ı�
		}
		fputc('\n', fp);
	}
	else
		printf("�ļ���ʧ�ܣ���\n");
	fclose(fp);
}

void IntoFile(TextCompiler *text, char *filename)
{
	printf("ɾ������ַ���:\n");
	EasyOutput(text);
	printf("ת�����������ĵ���\n");
	seqstring strtr;
	strtr.length = 0;
	TableToArray(text, &strtr);
	printf("%s\n", strtr.str);
	PutInFile(filename, &strtr);
}

//����ɾ������
void StrDelete(TextCompiler *text, char *filename)
{
	seqstring str;
	str.length = 0;
	int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
	char p[20] = {0};
	printf("��������Ҫɾ���ĵ���:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++; //��ȡ�����ַ����ĳ���
		i++;	   //�ַ����±������ƶ�
	}
	p[plength] = '\0';				  //���һλ����Ϊ'\0'
	for (k = 0; k < text->count; k++) //ѭ������ÿһ��
	{
		i = 0;
		q = text->column[k].FirstWord->length; //����һ�³���
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ) //û��ƥ������ұ�־λ��1
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			i++;
			if (succ)
			{
				strdelete(text->column[k].FirstWord, i, plength); //ɾ�����ַ���
				succ = 0;										  //��־λ�����趨Ϊ0
			}
		}
	}
	//TableToArray(text, &str);  //�Ƚ��ڽӱ�ת����һά����
	IntoFile(text, filename); //ת��������д���ļ�
}

//���ַ����滻
void StrReplace(TextCompiler *text)
{
	Word word;
	seqstring str;
	str.length = 0;
	int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
	char p[20] = {0};
	printf("��������Ҫ���滻���ַ���:\n");
	scanf("%s", p);
	printf("��������Ҫ�滻���ַ�����\n");
	scanf("%s", word.data);
	while (p[i])
	{
		plength++; //��ȡ�����ַ����ĳ���
		i++;	   //�ַ����±������ƶ�
	}
	p[plength] = '\0'; //���һλ����Ϊ'\0'
	word.length = plength;
	for (k = 0; k < text->count; k++) //ѭ������ÿһ��
	{
		i = 0;
		q = text->column[k].FirstWord->length; //����һ�³���
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ) //û��ƥ������ұ�־λ��1
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			i++;
			if (succ)
			{
				strreplace(text->column[k].FirstWord, i - 1, &word); //�滻���ַ���
				succ = 0;											 //��־λ�����趨Ϊ0
			}
		}
	}
	printf("�滻����ַ���:\n");
	EasyOutput(text);
}

//���ҡ��滻��ɾ��
void SearchReplaceDelete(TextCompiler *text, seqstack *st, char *filename)
{
	if (text == NULL)
	{
		printf("�����ı�Ϊ�գ������ļ�·���Ƿ�����\n");
		exit(0);
	}
	int input = 0;
	printf("\t1.�ַ�������\n");
	printf("\t2.�ַ����滻\n");
	printf("\t3.�ַ�������\n");
	printf("\t4.�ַ���ɾ��\n");
	printf("\t5.���ز���\n");
	printf("�����빦�ܱ�ţ�\n");
	scanf("%d", &input);
	int i;
	int next[50];
	switch (input)
	{
	case 1:
	{
		seqstack st;
		init(&st);
		nativematch(text, &st);
		break;
	}
	case 2:
	{
		StrReplace(text);
		break;
	}
	case 3:
	{
		int input = 0;
		printf("������Ҫ�в��뻹���в��룿\n");
		printf("\t1.�ַ������в���\n");
		printf("\t2.�ַ������в���\n");
		printf("\t3.�ַ����Ŀ����\n");
		printf("�����������ţ�\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			Word word;
			word.length = 0;
			int row = 0, column = 0; //�����и���
			printf("�������Ҫ�����λ�ã�(�и���)\n");
			printf("�кţ�");
			scanf("%d", &row);
			printf("�кţ�");
			scanf("%d", &column);
			printf("��������Ҫ������ַ�����\n");
			scanf("%s", word.data);
			while (word.data[word.length])
				word.length++;
			strinsert(text->column[row - 1].FirstWord, column, &word);
			EasyOutput(text);
			break;
		}
		case 2:
		{ //�еĲ���
			int dlength = 0;
			int col = 0;
			char data[100] = {0};
			int row = 0, column = 0; //�����и���
			printf("�������Ҫ�����λ�ã�(�и���)\n");
			printf("�кţ�");
			scanf("%d", &row);
			printf("�кţ�");
			scanf("%d", &column);
			printf("��������Ҫ������ַ�����\n");
			scanf("%s", data);
			while (data[dlength]) //ͳ�������ַ����ĳ���
				dlength++;
			for (int i = row - 1; i < row + dlength; i++) //ѭ�����������������������ַ����ĳ���
			{
				Word *word = text->column[i].FirstWord;
				for (int j = word->length - 1; j >= column; j--) //ѭ����ָ������
					word->data[j + 1] = word->data[j];
				if (data[col] != '\0')
					word->data[column] = data[col++];
				word->length++;
				word->data[word->length] = '\0';
			}
			EasyOutput(text);
			break;
		}
		case 3:
		{ //��Ĳ���
			int row = 0, column = 0;
			int width = 0, length = 0;
			Word word;
			word.length = 0;
			printf("��������Ҫ�������кš��кš���Ŀ�ȡ���ĳ��ȣ�\n");
			printf("�кţ�");
			scanf("%d", &row);
			printf("�кţ�");
			scanf("%d", &column);
			printf("���ȣ�");
			scanf("%d", &width);
			printf("��ȣ�");
			scanf("%d", &length);
			if (row + length > text->count || column + width > text->column[0].FirstWord->length)
			{
				printf("������λ�����������ԣ���\n");
				exit(0);
			}
			else
			{
				printf("��������Ҫ������ַ�����\n");
				scanf("%s", word.data);
				while (word.data[word.length]) //ͳ���ַ����ĳ���
					word.length++;
				int count; //�±���
				int j = 0;
				for (int i = row; i < row + length - 1; i++)
				{
					count = 0;								 //�±���
					Word wordT;								 //���ڲ����wordT
					Word *wordP = text->column[i].FirstWord; //����wordָ��ǰ����
					for (j = i * width; j < i * width + width; j++)
					{
						wordT.data[count++] = word.data[j];
						wordT.length = width; //���ȸ�ֵ
					}
					strinsert(wordP, column, &wordT); //���ֺ����
				}
				Word lastword;
				lastword.length = 0;
				while (word.data[j] != '\0')
					lastword.data[lastword.length++] = word.data[j++];					//�������һ��
				strinsert(text->column[row + length - 1].FirstWord, column, &lastword); //����
			}
			EasyOutput(text);
			break;
		}
		default:
			break;
		}
		break;
	}
	case 4:
	{
		int input = 0;
		printf("������Ҫ��ɾ��������ɾ����\n");
		printf("\t1.��ɾ��\n");
		printf("\t2.��ɾ��\n");
		printf("\t3.���ɾ��\n");
		printf("�����������ţ�\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{ //�ַ�����ɾ��
			StrDelete(text, filename);
			break;
		}
		case 2:
		{
			int column = 0;
			printf("��������Ҫɾ�����кţ�\n");
			scanf("%d", &column);
			for (int i = 0; i < text->count; i++)
				strdelete(text->column[i].FirstWord, column, 1);
			break;
		}
		case 3:
		{
			int row = 0, column = 0;
			int width = 0, length = 0;
			printf("��������Ҫɾ������кš��кš���ȡ����ȣ�\n");
			printf("�кţ�");
			scanf("%d", &row);
			printf("�кţ�");
			scanf("%d", &column);
			printf("���ȣ�");
			scanf("%d", &width);
			printf("��ȣ�");
			scanf("%d", &length);
			if (row + length > text->count || column + width > text->column[0].FirstWord->length)
			{
				printf("����������,�������������\n");
				exit(0);
			}
			for (int i = row - 1; i < row + length; i++)
				strdelete(text->column[i].FirstWord, column, length);
			IntoFile(text, filename);
			break;
		}
		default:
		{
			printf("�������󣡣�\n");
			exit(0);
			break;
		}
		}
		EasyOutput(text); //�����
		break;
	}
	case 5:
	{
		nativematch(text, st);
		break;
	}
	default:
		printf("��������\n");
		exit(0);
		break;
	}
}

void strRemove(TextCompiler *text, char *filename)
{
	int input = 0;
	printf("\t1.�ַ��������ƶ�\n");
	printf("\t2.�ַ��������ƶ�\n");
	printf("\t3.�ַ����Ŀ��ƶ�\n");
	printf("�����������ţ�\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		int row1 = 0; //�ƶ�ǰ����λ��
		int row2 = 0; //�ƶ�ǰ��
		printf("��������Ҫ�ƶ��е�λ�ã�\n");
		scanf("%d", &row1);
		printf("��������Ҫ�ƶ�����λ�ã�\n");
		scanf("%d", &row2);
		Word *word = text->column[row1 - 1].FirstWord; //����һ��
		text->column[row1 - 1].FirstWord = text->column[row2 - 1].FirstWord;
		text->column[row2 - 1].FirstWord = word;
		printf("���ƶ�����ı�:\n");
		EasyOutput(text);			 //�����
		TableToFile(text, filename); //д���ļ�
		break;
	}
	case 2:
	{
		int column1 = 0; //�ƶ�ǰ����λ��
		int column2 = 0; //�ƶ�ǰ��
		printf("��������Ҫ�ƶ��е�λ�ã�\n");
		scanf("%d", &column1);
		printf("��������Ҫ�ƶ��е�λ�ã�\n");
		scanf("%d", &column2);
		for (int i = 0; i < text->count; i++)
		{
			char temp; //�м佻����
			temp = text->column[i].FirstWord->data[column1 - 1];
			text->column[i].FirstWord->data[column1 - 1] = text->column[i].FirstWord->data[column2 - 1];
			text->column[i].FirstWord->data[column2 - 1] = temp;
		}
		printf("���ƶ�����ı�:\n");
		EasyOutput(text);			 //�����
		TableToFile(text, filename); //д���ļ�
		break;
	}
	case 3:
	{

		break;
	}
	default:
		break;
	}
}

void menu()
{
	puts("\n");
	printf("\t                        �����ı��༭��                 \n");
	printf("\t*\t                                                      *\n");
	printf("\t*\t 1.�����ı�����                                       *\n");
	printf("\t*\t 2.���ļ���ȡ����                                     *\n");
	printf("\t*\t 3.��������ı�                                       *\n");
	printf("\t*\t 4.ͳ���ı��е��ַ�����                               *\n");
	printf("\t*\t 5.ɾ���Ӵ�                                           *\n");
	printf("\t*\t 6.���ҡ��滻�������ַ���                             *\n");
	printf("\t*\t 7.�ַ������ƶ�                                       *\n");
	printf("\t*\t 8.����ĳ�����ʵ��кź��ڸ��г��ֵĴ����Լ�λ��       *\n");
	printf("\t*\t 9.���������                                         *\n");
	printf("\t*\t 10.�˳�                                              *\n");
}

//�û��ӽ��������ı�
void InputFromScreen(char *filename) //abcdefghiklmnopqrst
{
	int row; //ÿһ��������������
	printf("������һ����ռ��������\n");
	scanf("%d", &row);
	printf("����������Ҫ¼����ı���\n");
	char ch; //��ȡ���ַ�
	FILE *fp;
	int save = 0; //����д���ļ��ķ���ֵ
	int count = 0;
	fp = fopen(filename, "w"); //��д��ķ�ʽ���ļ�
	if (fp)
	{
		getchar();
		ch = getchar();
		while (ch != '\n')
		{
			save = fputc(ch, fp);
			count++;		//д���ַ���1
			if (save == -1) //�������-1,�����ļ�д��ʧ��
			{
				printf("д���ļ�ʧ�ܣ�����\n");
				exit(0); //�˳�
			}
			ch = getchar();
			if (count % row == 0)
				fputc('\n', fp); //д��س��Ѵﵽ�����û��ķ�ʽ�洢�ı�
		}
	}
	else
		printf("�ļ���ʧ�ܣ���\n");
	fclose(fp); //�ر��ļ�
}

int main()
{
	int input = 0;
	seqstack st;
	init(&st);
	menu();
	char filename[] = "D:\\Desktop\\Test.txt";
	char filename1[] = "D:\\Desktop\\Test2.txt";
	printf("��������ܱ�ţ�\n");
	scanf("%d", &input);
	TextCompiler text; //����Ľṹ��
	text.count = 0;	//һ��ʼ������Ϊ0
	while (input >= 0 && input <= 10)
	{
		switch (input)
		{
		case 1:
		{
			//������Ļ¼�������д���ļ�
			InputFromScreen(filename1);
			break;
		}
		case 2:
		{
			//printf("�������ļ�·����\n");  //D:\\Desktop\\test.txt
			//scanf("%s", filename);
			ReadFromFile(&text, filename1);
			break;
		}
		case 3:
		{
			EasyOutput(&text);
			break;
		}
		case 4:
		{
			RowNumber(&text);
			break;
		}
		case 5:
		{
			StrDelete(&text, filename1);
			break;
		}
		case 6:
		{
			SearchReplaceDelete(&text, &st, filename1);
			break;
		}
		case 7:
		{
			strRemove(&text, filename1);
			break;
		}
		case 8:
		{
			nativematch(&text, &st);
			break;
		}
		case 9:
		{
			printf("������Ϊ:%d\n", text.count);
		}
		case 10:
		{
			exit(0);
			break;
		}
		default:
			printf("�������󣡣���\n");
			exit(0);
			break;
		}
		//menu();
		printf("��������ܱ�ţ�\n");
		scanf("%d", &input);
	}
	system("pause");
	return 0;
}