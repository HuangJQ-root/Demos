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

#ifndef MVBS_BASE_TYPE_H
#define MVBS_BASE_TYPE_H

#if defined(__CTC__)
#include <stddef.h>		/* For size_t */
#include <stdint.h>
#include <stdbool.h>
#elif defined(__ghs__)
#include <stddef.h>		/* For size_t */
#include <stdint.h>
#include <stdbool.h>
#elif defined(__GNUC__)
#include <stddef.h>		/* For size_t */
#include <stdint.h>
#include <stdbool.h>
#endif

#define mvbs_false			(0 == 1)
#define mvbs_true			(1 == 1)


#endif /* !MVBS_BASE_TYPE_H */
