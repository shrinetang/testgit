//---------------------------------------------------------------------------

#include <alloc.h>
#include <string.h>
#include <stdio.h>
#include "JRegex.h"

//---------------------------------------------------------------------------
void WildcharTest(void)
{
   char *string;
   char *find_expression;    //�����õ�ͨ������ʽ
   char *regex_expression;   //������ʽ
   int start;                  //���ҵ����Ӵ�����ʼλ��
   int length;                 //�Ӵ��ĳ���   

   string=malloc(256);
   strcpy(string,"hello.txt");
   find_expression="*.txt";

   //ת��Ϊregex��ʾ��
   regex_expression=WildCharToRegex(find_expression);
   printf("\nWildchar Expression: %s \n",find_expression);
   printf("Regex Expression: %s \n",regex_expression);
   free(regex_expression); //����WildCharToRegexʱ�������ڴ棬�˴��ͷ��ڴ� 

   //ֱ����ͨ������ʽ����/ƥ��
   printf("String %s \n",string);
   if (1==WildCharFind(string, find_expression, &start, &length))
     {
       printf("Found %s at %d  \n",find_expression,start);
     }
   else
     {
        printf("Not find  %s \n",find_expression); 
     }

   free(string);  

}
/*---------------------------------------------------------------------------*/
void RegexTest(void)
{
    char *string;
    char *old_string;
    char *find_regex_expr;      //�����õ�������ʽ
    char *replace_regex_expr;   //�滻�õ�������ʽ
    char *find_string;          //���ҵ����Ӵ�
    int start;                  //���ҵ����Ӵ�����ʼλ��
    int length;                 //�Ӵ��ĳ���

    string=malloc(256);
    strcpy(string,"rat rot rpt");
    find_regex_expr="r[aou]t";     //��˼�������ַ�r?t, �ڶ����ַ�ֻ����a,o,u֮һ

    printf("\nRegexFind Example: string=%s, regex=%s\n",string,find_regex_expr);

    //Regex����ʾ��
    while (1==RegexFind(string,find_regex_expr,&start, &length))
      {
         //�ҵ��󣬴�string��ȡ���Ӵ�
         find_string=ExtractString(string, start, length);
         if (find_string!=NULL)
           {
              printf("Found %s\n", find_string);
              free(find_string); //����ExtractStringʱ�������ڴ棬�˴��ͷ��Ӵ��ڴ�
           }
         string=string+length; //��ָ��ָ����һ��λ�ã��Ա��������
      }


    //Regex�滻ʾ��
    strcpy(string,"rat rot rpt");
    old_string=string;               //�����ִ�����ʼλ��
    find_regex_expr="r([aou])t";     //��˼�������ַ�r?t, �ڶ����ַ�ֻ����a,o,u֮һ
                                     // ���� ( ) �ĺ����ǰ������ҵ����ַ����һ���飬���滻�п��� \1 �����
    replace_regex_expr="r\\1\\1t";   //�滻Ϊ r??t, �ѵڶ����ַ��ظ�һ��

    printf("\nRegexReplace Example: string=%s \n        find_regex=%s , replace_regex=%s\n",
            string,find_regex_expr,replace_regex_expr);

    while (1==RegexReplace(string,find_regex_expr,replace_regex_expr,&start, &length))
      {
         //�ҵ��󣬴�string��ȡ���Ӵ�
         find_string=ExtractString(string, start, length);
         if (find_string!=NULL)
           {
              printf("Replace with %s\n", find_string);
              free(find_string); //����ExtractStringʱ�������ڴ棬�˴��ͷ��Ӵ��ڴ�
           }
         string=string+length; //��ָ��ָ����һ��λ�ã��Ա�����滻
      }

    printf("String after replace: %s \n",old_string); //��ʾ����滻����ִ�

    free(string);
}
/*---------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
    RegexTest();

    WildcharTest();
    
    return 0;
}
//---------------------------------------------------------------------------
 