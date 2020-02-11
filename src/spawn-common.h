#ifndef __STRING_HASH_H__
#define __STRING_HASH_H__

#define MSG_TEXT_SIZE (64 - sizeof(long))
struct MyMsgStruct
{
    long msg_type;
    char msg_text[MSG_TEXT_SIZE];
};
#define MSG_CMD_TYPE 1
#define MSG_END_TYPE 2
#define MSG_CONTINUE_TYPE 3

/* ELF Hash Function */
static unsigned int elf_hash( char const * str, int size )
{
    unsigned int hash = 0;
    unsigned int x = 0;

    for ( int i = 0; i < size; ++i )
    {
        hash = ( hash << 4 ) + str[i]; /* hash左移4位，把当前字符ASCII存入hash低四位。 */
        if ( ( x = hash & 0xF0000000L ) != 0 )
        {
            /* 如果最高的四位不为0，则说明字符多余7个，现在正在存第7个字符，如果不处理，再加下一个字符时，第一个字符会被移出，因此要有如下处理。
               该处理，如果最高位为0，就会仅仅影响5-8位，否则会影响5-31位，因为C语言使用的算数移位
               因为1-4位刚刚存储了新加入到字符，所以不能>>28 */
            hash ^= (x >> 24);
            /* 上面这行代码并不会对X有影响，本身X和hash的高4位相同，下面这行代码&~即对28-31(高4位)位清零。 */
            hash &= ~x;
        }
    }
    /* 返回一个符号位为0的数，即丢弃最高位，以免函数外产生影响。(我们可以考虑，如果只有字符，符号位不可能为负) */
    return (hash & 0x7FFFFFFF);
}

#endif // __STRING_HASH_H__
