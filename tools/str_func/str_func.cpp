#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "../../include/osDefine.h"
#ifdef OS_WINDOWS
#include <stdlib.h>
#elif defined(OS_LINUX)
#include <errno.h>
#endif

//ԭ  ��: char *strcpy(char* dest, const char *src);
//��  ��: �Ѵ�src��ַ��ʼ�Һ���NULL���������ַ������Ƶ���dest��ʼ�ĵ�ַ�ռ�
//˵  ��:
void test_strcpy()
{
    char string[10];
    char *str1 = "abcdefghi";
    strcpy(string, str1);
    printf("%s\n", string);
}

//ԭ  ��: char *stpcpy(char *destin, char *source);
//��  ��: ��src��ָ��NULL�������ַ������Ƶ�dest��ָ��������
//˵  ��:
//�����ԣ�linux������
void test_stpcpy()
{
    char *str1 = "abcdefghi";
#ifdef OS_WINDOWS
    printf("There is no ==strcpy== in windows platform\n");
#elif defined(OS_LINUX)
    char string[10];
    stpcpy(string, str1);
    printf("%s\n", string);
#endif
}

//ԭ  ��: char* strncpy(char* dest,char* src,size_t num);
//��  ��: ����src�е����ݵ�dest�����ƶ�����num��ֵ����������ָ��dest��ָ��
//˵  ��: �������null�ַ���'\0'�����һ�û�е�num���ַ�ʱ�����ã�num - n����n������null�ַ�ǰ�Ѿ��еķ�null�ַ���������null�ַ����ӵ�destination
//        ע�⣺��������ӵ�destination����󣬶��ǽ�������source�и��ƶ������ַ�����
void test_strncpy()
{
    char string[10];
    char *str1 = "abcdefghi";
    strncpy(string, str1, 3);
    string[3] = '\0';
    printf("%s\n", string);
    char chardes[] = "Hello,iam!";
    char charsource[] = "abc\0def";
    strncpy(chardes, charsource, 5);
    printf("%s\n", chardes);
}

//ԭ  ��: char *strcat(char *dest,char *src);
//��  ��: ��src��ָ�ַ�����ӵ�dest��β��(����dest��β����'\0')�����'\0'
//˵  ��: src��dest��ָ�ڴ����򲻿����ص���dest�������㹻�Ŀռ�������src���ַ���
void test_strcat()
{
    char destination[25];
    char *blank = " ", *c = "C++", *Borland = "Borland";
    strcpy(destination, Borland);
    strcat(destination, blank);
    strcat(destination, c);
    printf("%s\n", destination);
}

//ԭ  ��: int strcmp(const char *s1,const char * s2);
//��  ��: �Ƚ��ַ���s1��s2
//˵  ��: ��ASCIIֵ��С��Ƚ�
void test_strcmp()
{
    char *buf1 = "aaa", *buf2 = "bbb", *buf3 = "ccc";
    int ptr;
    ptr = strcmp(buf2, buf1);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 1\n");
    else
        printf("buffer 2 is less than buffer 1\n");
    ptr = strcmp(buf2, buf3);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 3\n");
    else
        printf("buffer 2 is less than buffer 3\n");
}

//ԭ  ��: int stricmp(char *str1, char *str2);
//��  ��: �Ƚ�������,��Сд������
//˵  ��:
//�����ԣ�Windows���У�����Щlinuxϵͳ��û�иú����Ķ���
void test_stricmp()
{
#ifdef OS_WINDOWS
    char *buf1 = "BBB", *buf2 = "bbb";
    int ptr = stricmp(buf2, buf1);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 1\n");
    else if (ptr < 0)
        printf("buffer 2 is less than buffer 1\n");
    else if (ptr == 0)
        printf("buffer 2 equals buffer 1\n");
#elif defined(OS_LINUX)
    printf("There is no ==stricmp== in windows platform\n");
#endif
}

//ԭ  ��: int strnicmp(char *str1, char *str2, unsigned maxlen);
//��  ��: ��һ���ַ����е�һ��������һ���ַ����Ƚ�, ��Сд������
//˵  ��:
//�����ԣ�Windows���У�����Щlinuxϵͳ��û�иú����Ķ���
void test_strncmpi()
{
#ifdef OS_WINDOWS
    char *buf1 = "BBB", *buf2 = "bbb";
    int ptr = strnicmp(buf2, buf1, strlen(buf1));
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 1\n");
    else if (ptr < 0)
        printf("buffer 2 is less than buffer 1\n");
    else if (ptr == 0)
        printf("buffer 2 equals buffer 1\n");
#elif defined(OS_LINUX)
    printf("There is no ==stricmp== in windows platform\n");
#endif
}

//ԭ  ��: int stricmp(char *s1,char * s2);
//��  ��: �Ƚ�������,��Сд������
//˵  ��:
//�����ԣ�Windows���У�����Щlinuxϵͳ��û�иú����Ķ���
void test_strcmpi()
{
#ifdef OS_WINDOWS
    char *buf1 = "BBB", *buf2 = "bbb";
    int ptr = strcmpi(buf2, buf1);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 1\n");
    else if (ptr < 0)
        printf("buffer 2 is less than buffer 1\n");
    else if (ptr == 0)
        printf("buffer 2 equals buffer 1\n");
#elif defined(OS_LINUX)
    printf("There is no ==strcmpi== in windows platform\n");
#endif
}

//ԭ  ��: int strncmp(char *str1, char *str2, int maxlen);
//��  ��: �Ƚ�s1��s2�ַ�����ǰmaxlen���ַ�����Сд����
//˵  ��:
//�����ԣ�Windows���У�����Щlinuxϵͳ��û�иú����Ķ���
void test_strncmp()
{
    char *buf1 = "aaabbb", *buf2 = "bbbccc", *buf3 = "ccc";
    int ptr;
#ifdef OS_WINDOWS
    ptr = strncmp(buf2, buf1, 3);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 1\n");
    else
        printf("buffer 2 is less than buffer 1\n");
    ptr = strncmp(buf2, buf3, 3);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 3\n");
    else
        printf("buffer 2 is less than buffer 3\n");
    printf("There is no ==strcpy== in windows platform\n");
#elif defined(OS_LINUX)
    printf("There is no ==strncmp== in linux platform\n");
#endif
}

//ԭ  ��:  int strnicmp(char *str1, char *str2, unsigned maxlen);
//��  ��: �Ƚ��������� ��Сд������
//˵  ��:
//�����ԣ�Windows���У�����Щlinuxϵͳ��û�иú����Ķ���
void test_strnicmp()
{
#ifdef OS_WINDOWS
    char *buf1 = "BBBccc", *buf2 = "bbbccc";
    int ptr = strnicmp(buf2, buf1, 3);
    if (ptr > 0)
        printf("buffer 2 is greater than buffer 1\n");
    else if (ptr < 0)
        printf("buffer 2 is less than buffer 1\n");
    else if (ptr == 0)
        printf("buffer 2 equals buffer 1\n");
#elif defined(OS_LINUX)
    printf("There is no ==strnicmp== in windows platform\n");
#endif
}

//ԭ  ��: int strcasecmp(const char *s1, const char *s2);
//��  ��: �Ƚ��ַ�������Сд������
//˵  ��:
//�����ԣ�Linuxƽ̨���У��൱��windowsƽ̨��stricmp
void test_strcasecmp()
{
#ifdef OS_WINDOWS
    printf("There is no ==strcasecmp== in windows platform\n");
#elif defined(OS_LINUX)
    char *a = "aBcDeF";
    char *b = "AbCdEf";
    if(!strcasecmp(a, b))
        printf("%s=%s\n", a, b);
#endif
}

//ԭ  ��: int strncasecmp(const char *s1, const char *s2, size_t n)
//��  ��: �����Ƚϲ���s1��s2�ַ���ǰn���ַ�����Сд������
//˵  ��:
//�����ԣ�Linuxƽ̨���У�
void test_strncasecmp()
{
#ifdef OS_WINDOWS
    printf("There is no ==strncasecmp== in windows platform\n");
#elif defined(OS_LINUX)
    char *a = "aBcddfefekr";
    char *b = "AbCddfefekr";
    printf("%d\n", strncasecmp(a, b, strlen(a)));
#endif
}

//ԭ  ��: char *strchr(const char *s,char c);
//��  ��: �����ַ���s���״γ����ַ�c��λ��
//˵  ��: �ɹ��򷵻�Ҫ�����ַ���һ�γ��ֵ�λ�ã�ʧ�ܷ���NULL
void test_strchr()
{
    char string[15];
    char *ptr, c = 'r';
    strcpy(string, "This is a string");
    ptr = strchr(string, c);
    if (ptr)
        printf("The character %c is at position: %d\n", c, ptr - string);
    else
        printf("The character was not found\n");
}

//ԭ  ��: char *strstr(const char *str1, const char *str2);
//��  ��: �ڴ��в���ָ���ַ����ĵ�һ�γ���
//˵  ��: �ú�������str2��һ����str1�е�λ�ã����û���ҵ�������NULL
void test_strstr()
{
    char *str1 = "Borland International", *str2 = "nation", *ptr;
    ptr = strstr(str1, str2);
    printf("The substring is: %s\n", ptr);
}

//ԭ  ��: size_t strspn (const char *s,const char * accept);
//��  ��: �����ַ����е�һ������ָ���ַ����г��ֵ��ַ��±�
//˵  ��: �����ַ���s��ͷ���������ַ���accept�ڵ��ַ���Ŀ
void test_strspn()
{
    char *string1 = "1234567890";
    char *string2 = "123DC8";
    int length = strspn(string1, string2);
    printf("Character where strings differ is at position %d\n", length);
}

//ԭ  ��: size_t strcspn(const char *s1,const char *s2);
//��  ��: ˳�����ַ���s1����Ѱ��s2���ַ��ĵ�һ����ͬ�ַ�������������NULL
//˵  ��: ��������ַ���S1�е�һ�γ��ֵ�λ��
void test_strcspn()
{
    char *string1 = "1234567890";
    char *string2 = "747DC8";
    int length = strcspn(string1, string2);
    printf("Character where strings intersect is at position %d\n", length);
}

//ԭ  ��: char *strpbrk(const char *s1, const char *s2);
//��  ��: ���μ����ַ���s1�е��ַ������������ַ����ַ���s2��Ҳ����ʱ����ֹͣ���飬�����ظ��ַ�λ��
//˵  ��: ���ַ�NULL�����������ڴ��в��Ҹ����ַ����е��ַ�
void test_strpbrk()
{
    char *string1 = "abcdefghijklmnopqrstuvwxyz";
    char *string2 = "onm";
    char *ptr = strpbrk(string1, string2);
    if (ptr)
        printf("strpbrk found first character: %c\n", *ptr);
    else
        printf("strpbrk didn't find character in set\n");
}

//ԭ  ��: char *strrchr(const char *str, char c);
//��  ��: ����һ���ַ�c����һ���ַ���str��ĩ�γ��ֵ�λ��
//˵  ��: ���ش��ַ����е����λ����һֱ���ַ��������������ַ�
void test_strrchr()
{
    char string[15];
    char *ptr, c = 'r';
    strcpy(string, "This is a string");
    ptr = strrchr(string, c);
    if (ptr)
        printf("The character %c is at position: %d\n", c, ptr - string);
    else
        printf("The character was not found\n");
}

//ԭ  ��: char *strdup(char *s);
//��  ��: �����������½���λ�ô�
//˵  ��: strdup()���ڲ�������malloc()Ϊ���������ڴ棬����Ҫʹ�÷��ص��ַ���ʱ����Ҫ��free()�ͷ���Ӧ���ڴ�ռ�
void test_strdup()
{
    char *dup_str, *string = "abcde";
    dup_str = strdup(string);
    printf("%s\n", dup_str);
    free(dup_str);
}

//ԭ  ��: char *strrev(char *s);
//��  ��: ���ַ���s�������ַ���˳��ߵ����������������ַ�NULL��
//˵  ��: ����ָ��ߵ�˳�����ַ���ָ��
void test_strrev()
{
#ifdef OS_WINDOWS
    char *forward = "string";
    printf("Before strrev(): %s\n", forward);
    strrev(forward);
    printf("After strrev():  %s\n", forward);
#elif defined(OS_LINUX)
    printf("There is no ==strcpy== in linux platform\n");
#endif
}

//ԭ  ��: char *strset(char *str, char c);
//��  ��: ��һ�����е������ַ�����Ϊָ���ַ�c
//˵  ��:
void test_strset()
{
#ifdef OS_WINDOWS
    char string[10] = "123456789";
    char symbol = 'c';
    printf("Before strset(): %s\n", string);
    strset(string, symbol);
    printf("After strset():  %s\n", string);
#elif defined(OS_LINUX)
    printf("There is no ==strset== in linux platform\n");
#endif
}

//ԭ  ��: char *strnset(char *str, char ch, unsigned n);
//��  ��: ��һ�����е�ǰn���ַ�����Ϊָ���ַ�ch
//˵  ��:
void test_strnset()
{
#ifdef OS_WINDOWS
    char *string = "abcdefghijklmnopqrstuvwxyz";
    char letter = 'x';
    printf("string before strnset: %s\n", string);
    strnset(string, letter, 13);
    printf("string after  strnset: %s\n", string);
#elif defined(OS_LINUX)
    printf("There is no ==strnset== in linux platform\n");
#endif
}

//ԭ  ��: double strtod(const char *nptr,char **endptr);
//��  ��: ���ַ���ת��Ϊdouble��ֵ
//˵  ��: ɨ���ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת���������ַ����ֻ��ַ�������ʱ('\0')�Ž���ת��
void test_strtod()
{
    char input[80], *endptr;
    printf("Enter a floating point number:");
    gets(input);
    double value = strtod(input, &endptr);
    printf("The string is %s the number is %lf\n", input, value);
}

//ԭ  ��: long int strtol(const char *nptr,char **endptr,int base);
//��  ��: ������nptr�ַ������ݲ���base��ת���ɳ�������
//˵  ��:
void test_strtol()
{
    char *string = "87654321", *endptr;
    long lnumber;
    /* strtol converts string to long integer  */
    lnumber = strtol(string, &endptr, 10);
    printf("string = %s  long = %ld\n", string, lnumber);
}

//ԭ  ��: unsigned long strtoul(const char *nptr,char **endptr,int base);
//��  ��: ���ַ������ݲ���baseת�����޷��ų�������
//˵  ��: ����base������õĽ��Ʒ�ʽ����baseֵΪ16�����16�������ȵ�baseֵΪ0ʱ��������ѡ�������ֽ���:
//        �����һ���ַ���'0'�����жϵڶ��ַ�����ǡ�x������16���ƣ�������8���ƣ���һ���ַ����ǡ�0��������10����
void test_strtoul()
{
    char pNum[] = "0xFF";
    int a = strtoul(pNum, 0, 16);
    printf("%d\n", a);
}

//ԭ  ��: char *strtok(char s[], const char *delim);
//��  ��: �ֽ��ַ���Ϊһ���ַ���sΪҪ�ֽ���ַ�����delimΪ�ָ����ַ���
//˵  ��:
void test_strtok()
{
    char input[16] = "abc,d";
    char *p;
    /* strtok places a NULL terminator
    in front of the token, if found */
    p = strtok(input, ",");
    if (p)   printf("%s\n", p);
    /* A second call to strtok using a NULL
    as the first parameter returns a pointer
    to the character following the token  */
    p = strtok(NULL, ",");
    if (p)   printf("%s\n", p);
}

//ԭ  ��: char *strupr(char *str);
//��  ��: �����е�Сд��ĸת��Ϊ��д��ĸ
//˵  ��:
//�����ԣ�Windowsƽ̨VC�º���
void test_strupr()
{
#ifdef OS_WINDOWS
    char *string = "abcdefghijklmnopqrstuvwxyz", *ptr;
    /* converts string to upper case characters */
    ptr = strupr(string);
    printf("%s\n", ptr);
#elif defined(OS_LINUX)
    printf("There is no ==strupr== in windows platform\n");
#endif
}

//ԭ  ��: void swab (char *from, char *to, int nbytes);
//��  ��: �������ٵ������ֽ�
//˵  ��:
void test_swab()
{
    char source[15] = "lizheng";//"rFna koBlrna d";
    char target[15] = {'\0'};
    swab(source, target, strlen(source));
    printf("This is target: %s\n", target);
}

//ԭ  ��: char *strerror(int errnum);
//��  ��: ����ָ�������Ϣ�ַ�����ָ��
//˵  ��:
void test_strerror()
{
    char *buffer = strerror(errno);
    printf("Error: %s\n", buffer);
}

int main(int argc, char *argv[])
{
    test_swab();
    system("pause");
    return 0;
}