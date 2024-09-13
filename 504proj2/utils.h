#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <cstdio>

#define safeDelete(x) {delete x; x = nullptr;}

bool isAddrByte(const QString &str, int &ret);
inline uchar hexCharToUchar(char c);
int hexQStringToUchar(const QString &str, uchar *&result);
void write2log(const QString &msg);
//template<class T>
//inline const T& max(const T &a, const T &b) {
//    return a > b ? a : b;
//}


#endif // UTILS_H
