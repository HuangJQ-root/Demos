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

#ifndef MVBS_ERRNO_H
#define MVBS_ERRNO_H

/*
 * common
 */
#define ERR_INVALID		1
#define ERR_NOMEM		2
#define ERR_FAULT		3
#define ERR_NODATA		4
#define ERR_NOENT		5
#define ERR_TIMEOUT		6
#define ERR_BUSY		7
#define ERR_EXIST		8
#define ERR_USERS		9
#define ERR_NOBUFS		10
#define ERR_OVERFLOW		11
#define ERR_NOSYS		12
#define ERR_AGAIN		13

/*
 * For mutex
 */
#define ERR_LOCK		30
#define ERR_UNLOCK		31

/*
 * For netio
 */
#define ERR_SOCK		40
#define ERR_AFNOSUPPORT		41
#define ERR_ASSIGN		42
#define ERR_BIND		43
#define ERR_LISTEN		44
#define ERR_CONNECT		45
#define ERR_CLOSE		46
#define ERR_SEND		47
#define ERR_RECV		48
#define ERR_MSGSIZE		49
#define ERR_INPROGRESS		50

/*
 * For RPC
 */
#define ERR_SNFAIL		51
#define ERR_MCDR		52


#endif /* !MVBS_ERRNO_H */
