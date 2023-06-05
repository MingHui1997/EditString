﻿/*
MIT License

Copyright (C) 2023 MingHui

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "EditString.h"

//--------------------------------------------------------------------
// String slice
//--------------------------------------------------------------------
void strslice(char *dest,char *sour,ind_t s,ind_t e)
{
    char *sour_e = sour + e;
    char *sour_c = sour + s;
    while(sour_c < sour_e)
    {
        *(dest) = *(sour_c);
        dest ++;
        sour_c ++;
    }
    *(dest) = 0x00;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// String clear
//--------------------------------------------------------------------
void strclear(char *dest)
{
    *(dest) = 0x00;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Char find
//--------------------------------------------------------------------
ind_t charindex(char *dest,char c)
{
    ind_t char_i = -1;
    char *dest_c = dest;
    while(*(dest_c) != 0x00)
    {
        if(*(dest_c) == c)
        {
            char_i = dest_c - dest;
            break;
        }
        dest_c ++;
    }
    return char_i;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Char find (From last to front)
//--------------------------------------------------------------------
ind_t charindex_last(char *dest,char c)
{
    ind_t str_i = -1;
    char *dest_c = dest + (strlen(dest) - 1);
    while(dest_c >= dest)
    {
        if(*(dest_c) == c)
        {
            str_i = dest_c - dest;
            break;
        }
        dest_c --;
    }
    return str_i;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// String find
//--------------------------------------------------------------------
ind_t strindex(char *dest,char *str)
{
    ind_t str_i = -1;
    size_t str_l = strlen(str);
    size_t dest_l = strlen(dest);
    char *dest_c = dest;
    char *dest_e = dest + (dest_l - str_l + 1);
    size_t equ_n = 0;
    ind_t i2;
    if(str_l > dest_l)
    {
        return -1;
    }
    while(dest_c < dest_e)
    {
        for(i2=0;i2<str_l;i2++)
        {
            if(*(dest_c+i2) == *(str+i2))
            {
                equ_n ++;
                if(equ_n == str_l)
                {
                    str_i = dest_c - dest;
                }
            }
        }
        equ_n = 0;
        if(str_i != -1)
        {
            break;
        }
        dest_c ++;
    }
    return str_i;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// String find (From last to front)
//--------------------------------------------------------------------
ind_t strindex_last(char *dest,char *str)
{
    ind_t str_i = -1;
    size_t str_l = strlen(str);
    size_t dest_l = strlen(dest);
    char *dest_c = dest + (dest_l - 1) - str_l + 1;
    size_t equ_n = 0;
    ind_t i2;
    if(str_l > dest_l)
    {
        return -1;
    }
    while(dest_c >= dest)
    {
        for(i2=0;i2<str_l;i2++)
        {
            if(*(dest_c+i2) == *(str+i2))
            {
                equ_n ++;
                if(equ_n == str_l)
                {
                    str_i = dest_c - dest;
                }
            }
        }
        equ_n = 0;
        if(str_i != -1)
        {
            break;
        }
        dest_c --;
    }
    return str_i;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// String replace
//--------------------------------------------------------------------
void strreplace(char *dest,char *repstr,char *str)
{
    size_t dest_l = strlen(dest);
    size_t reps_l = strlen(repstr);
    size_t str_l = strlen(str);
    ind_t reps_i = strindex(dest,repstr);
    size_t str_offset;
    ind_t offset_s;
    ind_t offset_e;
    ind_t str_i = 0;
    ind_t reps_e;
    char temp_c;
    ind_t i;
    if(reps_i != -1)
    {
        if(str[0] != 0x00)
        {
            if(str_l > reps_l)
            {
                str_offset = str_l - reps_l;
                offset_s = dest_l - 1 + str_offset;
                offset_e = reps_i + reps_l;
                reps_e = reps_i + str_l;
                for(i=offset_s;i>offset_e;i--)
                {
                    temp_c = *(dest+(i-str_offset));
                    *(dest+i) = temp_c;
                }
                for(i=reps_i;i<reps_e;i++)
                {
                    *(dest+i) = *(str+str_i);
                    str_i ++;
                }
            }
            if(str_l < reps_l)
            {
                str_offset = reps_l - str_l;
                offset_s = reps_i + reps_l - str_offset;
                offset_e = dest_l - str_offset + 1;
                reps_e = reps_i + str_l;
                for(i=offset_s;i<offset_e;i++)
                {
                    temp_c = *(dest+(i+str_offset));
                    *(dest+i) = temp_c;
                }
                for(i=reps_i;i<reps_e;i++)
                {
                    *(dest+i) = *(str+str_i);
                    str_i ++;
                }
            }
            if(str_l == reps_l)
            {
                reps_e = reps_i + str_l;
                for(i=reps_i;i<reps_e;i++)
                {
                    *(dest+i) = *(str+str_i);
                    str_i ++;
                }
            }
        }
        else
        {
            str_offset = reps_l;
            offset_s = reps_i;
            offset_e = dest_l - str_offset + 1;
            for(i=offset_s;i<offset_e;i++)
            {
                temp_c = *(dest+i+str_offset);
                *(dest+i) = temp_c;
            }
        }
    }
}
//--------------------------------------------------------------------