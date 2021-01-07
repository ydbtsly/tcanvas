/**
 * @file: ToolFunction.h
 * @brief: 通用方法
 * @detail:
 */
#ifndef __SD_TOOLFUNCTION_H__
#define __SD_TOOLFUNCTION_H__

template<typename T>
void swap(T& l, T& r) {
    T t = l ;
    l = r ;
    r = t ;
}

#endif //DE_ANI_TOOLFUNCTION_H
