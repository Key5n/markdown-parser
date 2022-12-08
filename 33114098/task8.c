#include <string.h>
#include <regex.h>
#include <stdio.h>

int main(void)
{
    int i;
    char name[] = "**bold**, **aiueo**";
    const char pattern[] = "\\*\\*[a-z]+\\*\\*";
    regex_t regexBuffer;
    regmatch_t match[4];
    int size;
    char result[128];

    // 正規表現オブジェクトをコンパイル
    if ( regcomp(&regexBuffer, pattern, REG_EXTENDED | REG_NEWLINE ) != 0 )
    {
        printf("regcomp failed\n");
        return 1;
    }

    // 正規表現パターンとマッチする？
    size = sizeof(match) / sizeof(regmatch_t); // 4
    if ( regexec(&regexBuffer, name, size, match, 0) != 0 )
    {
        printf("no match\n");
        return 1;
    }

    // パターンマッチした場合の処理
    for ( i = 0; i < size; i++ )
    {
        // マッチした位置の開始・終了インデックス
        int startIndex = match[i].rm_so;    // 開始インデックス
        int endIndex = match[i].rm_eo;      // 終了インデックス
        if ( startIndex == -1 || endIndex == -1 )
        {
            printf("exit\n");
            continue;
        }
        strncpy(result, name+startIndex , endIndex - startIndex);
        printf("%s\n",result);
    }

    regfree(&regexBuffer);
    return 0;
}