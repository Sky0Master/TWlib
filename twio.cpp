#include "include/twio.hpp"
using namespace std;

string read_Textfile(const char * filename)             //返回全部文本
{
 
    FILE *fp;
    fopen_s(&fp,filename,"rt");
    if(fp==NULL) return "";
    char ch;
    string text="";
    while((ch=fgetc(fp)) != EOF) 
        text+=ch;
    fclose(fp);
    return text;
    

}

size_t write_Textfile(const char * filename , string text) //从文件开头位置写入 返回成功写入的字节数
{

        FILE * fp;
        fopen_s(&fp,filename,"wt");
        if(fp==NULL) return 0;
        for(size_t i=0;i<text.length();i++)
            fputc((char)text[i],fp);    
        fclose(fp);
        return text.length();
}

inline size_t append_Textfile(const char * filename, string text) //在文件末尾添加文本 返回成功写入的字节数
{
    FILE* fp;
    fopen_s(&fp,filename,"at");
    if(fp==NULL) return 0;
    for(size_t i=0;i<text.length();i++)
        fputc((char)text[i],fp);    
    fclose(fp);
    return text.length();
}

inline int create_Directory(const char * folderpath)       //创建目录
{
    if(!_mkdir(folderpath)) return 1;  //失败返回1
    else return 0;
}

inline int delete_Directory(const char * folderpath)       //删除目录
{
    if(!_rmdir(folderpath)) return 1;  //失败返回1
    else return 0;
}

inline size_t getFileSize(const char * filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL) return 0;  //空指针则返回0，文件打开失败
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);  //计算文件大小,单位:Byte
    fclose(fp);
    return size;
}

inline size_t readBinaryFile(const char * filename,unsigned char* & data) //unsigned char也可写作byte，BYTE
{
    FILE* fp;
    fopen_s(&fp,filename, "rb");
    if (fp == NULL) return 0;  //空指针则返回0，文件打开失败
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);  //计算文件大小,单位:Byte
    fseek(fp, 0, SEEK_SET);
    data = (unsigned char *)malloc(sizeof(unsigned char)*size);
    fread(data,size,1,fp);
    fclose(fp);
    return size;
}

inline size_t writeBinaryFile(const char* filename,const unsigned char* data, size_t size)  //size：要写入的数据大小(单位：字节)
{
    FILE* fp;
    fopen_s(&fp,filename, "wb");
    if (fp == NULL) return 0;
    size_t written_size= fwrite(data, size, 1 ,fp);
    fclose(fp);
    return written_size;
}

template<typename OB>
inline void saveObject(const char*filename, OB & object) //传入要保存的对象引用
{
    ofstream osm(filename, ios::out | ios::binary);
    osm.write((const char *)&object,sizeof(OB));
    osm.close();
}

template<typename OB>
inline void readObject(const char* filename, OB * object) //传入读取之后对象存储的指针
{
    ifstream ism(filename, ios::in | ios::binary);
    ism.read((char*)object, sizeof(OB));
    ism.close();
}

