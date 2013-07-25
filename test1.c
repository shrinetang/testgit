//---------------------------------------------------------------------------

#include <alloc.h>
#include <string.h>
#include <stdio.h>
#include "JRegex.h"

//---------------------------------------------------------------------------
void WildcharTest(void)
{
   char *string;
   char *find_expression;    //查找用的通配符表达式
   char *regex_expression;   //正则表达式
   int start;                  //查找到的子串的起始位置
   int length;                 //子串的长度   

   string=malloc(256);
   strcpy(string,"hello.txt");
   find_expression="*.txt";

   //转换为regex的示例
   regex_expression=WildCharToRegex(find_expression);
   printf("\nWildchar Expression: %s \n",find_expression);
   printf("Regex Expression: %s \n",regex_expression);
   free(regex_expression); //由于WildCharToRegex时申请了内存，此处释放内存 

   //直接用通配符表达式查找/匹配
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
    char *find_regex_expr;      //查找用的正则表达式
    char *replace_regex_expr;   //替换用的正则表达式
    char *find_string;          //查找到的子串
    int start;                  //查找到的子串的起始位置
    int length;                 //子串的长度

    string=malloc(256);
    strcpy(string,"rat rot rpt");
    find_regex_expr="r[aou]t";     //意思是三个字符r?t, 第二个字符只能是a,o,u之一

    printf("\nRegexFind Example: string=%s, regex=%s\n",string,find_regex_expr);

    //Regex查找示例
    while (1==RegexFind(string,find_regex_expr,&start, &length))
      {
         //找到后，从string截取出子串
         find_string=ExtractString(string, start, length);
         if (find_string!=NULL)
           {
              printf("Found %s\n", find_string);
              free(find_string); //由于ExtractString时申请了内存，此处释放子串内存
           }
         string=string+length; //将指针指向下一个位置，以便继续查找
      }


    //Regex替换示例
    strcpy(string,"rat rot rpt");
    old_string=string;               //保存字串的起始位置
    find_regex_expr="r([aou])t";     //意思是三个字符r?t, 第二个字符只能是a,o,u之一
                                     // 其中 ( ) 的含义是把其中找到的字符编成一个组，在替换中可用 \1 来获得
    replace_regex_expr="r\\1\\1t";   //替换为 r??t, 把第二个字符重复一遍

    printf("\nRegexReplace Example: string=%s \n        find_regex=%s , replace_regex=%s\n",
            string,find_regex_expr,replace_regex_expr);

    while (1==RegexReplace(string,find_regex_expr,replace_regex_expr,&start, &length))
      {
         //找到后，从string截取出子串
         find_string=ExtractString(string, start, length);
         if (find_string!=NULL)
           {
              printf("Replace with %s\n", find_string);
              free(find_string); //由于ExtractString时申请了内存，此处释放子串内存
           }
         string=string+length; //将指针指向下一个位置，以便继续替换
      }

    printf("String after replace: %s \n",old_string); //显示完成替换后的字串

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
 