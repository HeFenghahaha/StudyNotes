#define _CRT_SECURE_NO_WARNINGS

#include "textstruct.h"
#include "stdio.h"

//���ڽӱ�ת��������
void TableToArray(TextCompiler *text, seqstring *str)
{
	int count = 0; //�����±�
	for (int i = 0; i < text->count; i++)
	{
		int mn = 0; //�ڽӱ��ÿһ��������±�
		while (text->column[i].FirstWord->data[mn] != '\0')
		{
			char letter = text->column[i].FirstWord->data[mn];
			str->str[count] = letter;
			count++; //����������±��1
			mn++;	//�ڽӱ�������±��1
			str->length++;
		}
	}
	str->str[count] = '\0'; //�������һλ��ֵ'\0'
}

//�ڽӱ�д���ļ�
void TableToFile(TextCompiler *text, char *filename)
{
	char ch; //��ȡ���ַ�
	FILE *fp;
	int save = 0;			   //����д���ļ��ķ���ֵ
	fp = fopen(filename, "w"); //��д��ķ�ʽ���ļ�
	if (fp)
	{
		for (int i = 0; i < text->count; i++)
		{
			save = fprintf(fp, "%s", text->column[i].FirstWord->data);
			if (save == -1) //�������-1,�����ļ�д��ʧ��
			{
				printf("д���ļ�ʧ�ܣ�����\n");
				exit(0); //�˳�
			}
			fputc('\n', fp); //д��س��Ѵﵽ�����û��ķ�ʽ�洢�ı�
		}
		fputc('\n', fp);
	}
	else
		printf("�ļ���ʧ�ܣ���\n");
	fclose(fp); //�ر��ļ�
}

/*
�ַ����Ĳ���
@ Str ĸ��
@ Ttr ��Ҫƥ����Ӵ�
*/

void strinsert(Word *Str, int i, Word *Ttr)
{
	int k;
	if (i < 1 || i > Str->length + 1 || Str->length + Ttr->length > MAXSIZWE - 1) //�Ƿ�����Ĵ���
		printf("�ַ����������޷����в����������\n");
	else
	{
		for (k = Str->length - 1; k >= i - 1; k--) //Str�дӵ�i��Ԫ����������
			Str->data[Ttr->length + k] = Str->data[k];
		for (k = 0; k < Ttr->length; k++) //��д��S�еĵ�i���ַ���ʼ��λ��
			Str->data[i + k - 1] = Ttr->data[k];
		Str->length = Str->length + Ttr->length;
		Str->data[Str->length] = '\0'; //�����ַ���S�µĽ�����
	}
}

/*
�ַ�����ɾ��
@ Str ĸ��
@ i ��Ҫɾ����λ��
@ len ��Ҫɾ���ĳ���
*/

void strdelete(Word *Str, int i, int len)
{
	int k;
	if (i < 1 || i > Str->length || i + len - 1 > Str->length) //�Ƿ�����Ĵ���
	{
		printf("�޷�����ɾ����������\n");
		exit(0);
	}
	else
	{
		for (k = i + len - 1; k < Str->length; k++)
			Str->data[k - len] = Str->data[k]; //Str���±�Ϊi + len -1��ʼ��Ԫ��ǰ��
		Str->length = Str->length - len;
		Str->data[Str->length] = '\0'; //���ַ���Str�µĽ�����
	}
}

/*
�ַ���������
@ S1 ��һ���ַ���
@ S2 �ڶ����ַ���
*/

Word *strconcat(Word *S1, Word *S2)
{
	int i;
	Word *r;
	if (S1->length + S2->length > MAXSIZWE - 1) //�����ַ����ռ䲻������
	{
		printf("�޷��������ӣ�\n");
		return NULL;
	}
	else
	{
		r = (Word *)malloc(sizeof(Word));
		for (i = 0; i < S1->length; i++)
			r->data[i] = S1->data[i]; //��S1���Ƶ��ַ�����r��ǰ��
		for (i = 0; i < S2->length; i++)
			r->data[S1->length + i] = S2->data[i]; //��S2���Ƶ��ַ�����r�ĺ��
		r->data[r->length] = '\0';
	}
	return r;
}

//��S2�滻S1�е�iλ�õ��ַ���
void strreplace(Word *S1, int i, Word *S2)
{
	for (int j = 0; j < S2->length; j++)
		S1->data[i + j] = S2->data[j];
}

//���ÿһ���ı���next[]����
void getnext(Word *word, int next[])
{
	int index, jndex;				  //�����±�����ǰ��Ƚ�
	next[0] = -1;					  //��һ����-1
	index = 0, jndex = -1;			  //�ȸ�ֵ
	while (word->data[index] != '\0') //��û�ж�ȡ��ÿ�е����һ������
	{
		if (jndex == -1 || word->data[index] == word->data[jndex])
		{
			++index; //���Ƚ�
			++jndex;
			next[index] = jndex;
		}
		else
			jndex = next[jndex]; //next�����ٴ�Ƕ�ײ���
	}

	/*
	index = 0;
	while (word->data[index] != '\0')
	{
		printf("%d ", next[index]);
		index++;
	}
	*/

	printf("\n");
}

//kmp�ַ���ƥ��
int Kmp(Word *wordT, Word *wordP, int next[])
{
	int index = 0;
	int jndex = 0;
	while (index < wordT->length && jndex < wordP->length)
	{
		if (jndex == -1 || wordT->data[index] == wordP->data[jndex]) //����ڸ�λ�����
		{
			index++; //�����±�һ�������
			jndex++;
		}
		else
			jndex = next[jndex]; //����ƥ�䴮�����ģʽ�����
	}
	if (jndex == wordP->length)
		return index - wordP->length;
	else
		return -1;
}