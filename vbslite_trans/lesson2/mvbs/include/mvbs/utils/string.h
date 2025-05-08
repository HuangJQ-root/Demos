/*
 * Copyright (c) 2025 Li Auto Inc. and its affiliates
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MVBS_UTILS_STRING_H
#define MVBS_UTILS_STRING_H

#include <mvbs/base_type.h>

/**
 * Copy memory area between buffers.
 *
 * @param dest destination buffer
 * @param src source buffer
 * @param size number of bytes to copy
 */
void mvbs_memcpy(void *dest, const void *src, size_t size);

/**
 * Set the buffer to zero.
 *
 * @param mem buffer to set zero
 * @param size number of bytes to set zero
 */
void mvbs_memzero(void *mem, size_t size);

/**
 * Compare bytes in two buffers.
 *
 * @param left buffer to compare
 * @param right buffer to compare
 * @param size number of bytes to compare
 * @return negative number if left is less than right
 *         zero if left matches right
 *         positive number if left is greater than right
 */
int32_t mvbs_memcmp(const void *left, const void *right, size_t size);

/**
 * Move one buffer to another.
 *
 * @param dest destination buffer
 * @param src source buffer
 * @param size number of bytes to move
 */
void mvbs_memmove(void *dest, const void *src, size_t size);

/**
 * Find character in a buffer.
 *
 * @param s pointer to buffer
 * @param c character to look for
 * @param n number of bytes to check
 * @return a pointer to the matching character  if succeed, otherwise NULL
 */
void *mvbs_memchr(const void *s, int32_t c, size_t n);

/**
 * Get the length of a string.
 *
 * @param s pointer to the string
 * @return the number of bytes in the string
 */
 size_t mvbs_strlen(const char *s);

/**
 * Compare the two strings.
 *
 * @param left string to compare
 * @param right string to compare
 * @return negative number if left is less than right
 *         zero if left is identical to right
 *         positive number if left is greater than right
 */
int32_t mvbs_strcmp(const char *left, const char *right);

/**
 * Compare the first n bytes of two strings
 *
 * @param left string to compare
 * @param right string to compare
 * @param num number of bytes to compare.
 * @return negative number if left is less than right
 *         zero if left is identical to right
 *         positive number if left is greater than right
 */
int32_t mvbs_strncmp(const char *left, const char *right, size_t num);

/**
 * Copy a string.
 *
 * @param dest destination buffer
 * @param src source buffer
 * @return a pointer to the destination string
 */
char *mvbs_strcpy(char *dest, const char *src);

/**
 * Copy n bytes of a string.
 *
 * @param dest destination buffer
 * @param src source buffer
 * @param n number of bytes to copy
 * @return a pointer to the destination string
 */
char *mvbs_strncpy(char *dest, const char *src, size_t n);

char *mvbs_strcat(char *dest, const char *src);

#endif
