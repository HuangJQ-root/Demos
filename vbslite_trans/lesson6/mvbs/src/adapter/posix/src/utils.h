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

#ifndef MVBS_ADAPTER_POSIX_UTILS
#define MVBS_ADAPTER_POSIX_UTILS

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE)
#define	MVBS_ADAPTER_EXTRA_UTILS
#endif

#ifdef MVBS_ADAPTER_EXTRA_UTILS

const struct udp_info *mvbs_get_udp_info_from_env(void);

#else

static inline const struct udp_info *mvbs_get_udp_info_from_env(void)
{
	return NULL;
}
#endif

#endif
