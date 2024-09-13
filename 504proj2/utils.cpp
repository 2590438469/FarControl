#include "utils.h"

bool isAddrByte(const QString &str, int &ret)
{
   ret = 0;
   bool is_addr;
   ret = str.toInt(&is_addr);
   return is_addr;
}

inline uchar hexCharToUchar(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<uchar>(c - '0');
    } else if (c >= 'A' && c <= 'F') {
        return static_cast<uchar>(c - 'A' + 10);
    } else if (c >= 'a' && c <= 'f') {
        return static_cast<uchar>(c - 'a' + 10);
    }
    return 0;
}

int hexQStringToUchar(const QString &str, uchar *&result)
{
    safeDelete(result);
    int result_size = (str.length() + 1) / 2;
    if (result_size == 0) {
        result = nullptr;
        return 0;
    }
    result = static_cast<uchar *>(malloc(static_cast<size_t>(result_size)));
    memset(result, 0, static_cast<size_t>(result_size));
    int pos = result_size - 1, reverse_i = 0;
    for (int i = str.length() - 1; i >= 0; --i) {
        result[pos] += hexCharToUchar(str.at(i).toLatin1()) * (reverse_i & 1 ? 16 : 1);
        if (reverse_i & 1) {
            --pos;
        }
        ++reverse_i;
    }
    return result_size;
}

void write2log(const QString &msg)
{
    FILE *log_file = fopen("log.txt", "a");
    fprintf(log_file, "%s\n", msg.toStdString().c_str());
    fclose(log_file);
}
