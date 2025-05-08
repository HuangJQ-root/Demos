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

#ifndef MVBS_CORE_QOS_H
#define MVBS_CORE_QOS_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/time.h>

enum {
	BEST_EFFORT = 1,
	RELIABLE = 2	/* Specification says 3 but eprosima sends 2 */
};

struct reliability_policy {
	duration_t max_blocking_time;
};

enum {
	VOLATILE = 0,
	TRANSIENT_LOCAL = 1,
	TRANSIENT = 2,
	PERSISTENT = 3
};

enum {
	KEEP_LAST,
	KEEP_ALL
};

struct history_policy {
	/* enum history_kind kind; */
	uint16_t depth;
};

struct resource_limit_policy {
	uint16_t max_samples;
	uint8_t max_instances;
	uint8_t max_samples_per_instance;
};

struct lifespan_policy {
	duration_t duration;
};

struct deadline_policy {
	duration_t duration;
};

enum {
	SHARED,
	EXCLUSIVE,
};

struct ownership_strength_policy {
	uint16_t value;
};

enum {
	QOS_LIVE_AUTOMATIC,
	QOS_LIVE_MANUAL_BY_PTCP,
	QOS_LIVE_MANUAL_BY_TOPIC
};

enum {
	/* ! Writer is matched but liveliness has not been asserted yet */
	NOT_ASSERTED = 0,
	/* ! Writer is alive */
	ALIVING = 1,
	/* ! Writer is not alive */
	NOT_ALIVE = 2
};

struct liveliness_policy {
	/*! Period within which liveliness should be asserted.
	 *  On a DataWriter it represents the period it commits to signal its liveliness.
	 *  On a DataReader it represents the period without assertion after which a DataWriter is
	 * considered inactive.
	 */
	duration_t lease_duration;
	/*! The period for automatic assertion of liveliness.
	 *  Only used for DataWriters with QOS_LIVE_AUTOMATIC liveliness.
	 *
	 * @warning When not infinite, must be < lease_duration, and it is advisable to be less than
	 * 0.7*lease_duration.
	 */
	duration_t announcement_period;
};

struct heartbeat_policy {
	uint8_t		heartbeats_per_max_samples;
	uint8_t		period_sec;
	uint16_t	period_msec;
};

struct e2e_policy {
	bool 		e2e_protection;

	duration_t 	e2e_liveliness_lease_duration;
	uint16_t 	e2e_liveliness_kind;

	uint16_t 	e2e_p04_min_data_length;
	uint16_t 	e2e_p04_max_data_length;
	uint16_t 	e2e_p04_max_delta_counter;

	uint16_t 	e2e_deadline_counter;
};

#endif
