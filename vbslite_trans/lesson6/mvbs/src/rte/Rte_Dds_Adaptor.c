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

#include <mvbs/sections/start_sec_code.h>
#include <mvbs/sections/start_sec_bss.h>
#include <mvbs/sections/start_sec_const.h>
#include <mvbs/sections/start_sec_data.h>

/*
 * These interfaces defined in this file are for EE2.5.
 */
#include <core/core.h>
#include <mvbs/utils/mem_pool.h>
#include <mvbs/rte/Rte_Dds_Adaptor.h>

/* The following are weak functions */
void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst);
void Rte_Dds_Reader_OnMatch(Rte_Dds_Reader r,
			    const Rte_Dds_Reader_MatchStatus *status);
void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
			    const Rte_Dds_Writer_MatchStatus *status);
void Rte_Dds_Reader_OnE2eException(Rte_Dds_Reader r, uint16_t counter,
				   uint32_t e2e_status);

/**
 * \addtogroup RTE
 * @{
 */


/**
 * @brief	This interface is an event callback function, which is called automatically.
 *		When the MVBS protocol stack receives a sample and places it into the
 *		history cache,
 *		this event handling method for the Reader is triggered.
 *
 * @param[in]	r Rte_Dds_Reader type. The Reader whose history cache has a new sample,
 *		making it readable.
 * @param[in]	inst Rte_Dds_Instance type. If not using an instance, the inst parameter
 *		is set to INSTANCE_INVALID.
 * @return 	void
 * @note
 * 		- Users should override the void Rte_Dds_RxIndication(Rte_Dds_TopicId *topic),
 *		where the reader executes the user-defined Rte_Dds_RxIndication interface after
 *		receiving data related to the topic.
 * 		- It is recommended that users use flags or counters in this function to record
 *		data on a topic that needs to be read, rather than directly performing data reads. \n
 *		This helps avoid blocking the execution of DDS receive tasks. When the data volume
 *		is large, use the QoS of the history cache for sample overwrite or discard to prevent
 *		forced message loss due to delayed data reception.
 * @see		**Example Code**
 * @code
 *		bool flag = false;
 *
 *		// User override
 *		void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
 *		{
 *			const char * topic_name = Rte_Dds_Reader_Get_TopicName(r);
 *			if(strcmp(topic_name, "xxx") == 0){
 *				flag = true;
 *			}
 *		}
 *
 *		void Other_Control_Function()
 *		{
 *			Rte_Dds_TopicId topic_r = DEF_RTE_DDS_TOPIC("xxx", {0});
 *			HybridMsg1 sample1;
 *			HybridMsg1_init(&sample1);
 *			Rte_Dds_TopicData data_r;
 *			Rte_Dds_PackData(&data_r, &sample1);
 *
 *			if(flag){
 *				// Receive data
 *				if (Rte_Dds_RxData(&topic_r, TRUE, &data_r, NULL)
 *					== RTE_DDS_RETCODE_OK) {
 *					printf("--------rx msg : sample1.msg = %s\n", sample1.msg);
 *				}
 *				flag = false;
 *			 }
 *		}
 * @endcode
 */
#pragma weak Rte_Dds_RxIndication
void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
{
	(void)r;
	(void)inst;
#if 0
	char *topic;

	topic = string_or_null(Rte_Dds_Reader_Get_TopicName(r));

	pr_debug("topic :%s reader on Available!\n", topic);
#endif
}



/**
 * @brief	Provides DDS reader match/unmatch event notifications.
 * @param[in]	r Rte_Dds_Reader type. The Reader for the corresponding topic.
 * @param[out]	status Rte_Dds_Reader_MatchStatus* type. Holds the status information
 *		related to reader matches.
 * @code
 *		struct reader_matched_status
 *		{
 *			// The total number of writers that have matched.
 *			uint16_t total_count;
 *
 *			// The change in total_count since the last listener call.
 *			uint16_t total_count_change;
 *
 *			// The number of currently matched writers.
 *			uint16_t current_count;
 *
 *			// The change in current_count since the last listener call.
 *			int16_t current_count_change;
 *
 *			// The guid of the last writer that caused a status change.
 *			struct guid last_publication_handle;
 *		};
 *		typedef struct reader_matched_status			Rte_Dds_Reader_MatchStatus;
 * @endcode
 * @note
 * 		1. If `status->current_count_change > 0`, the reader is in the match phase,
 *		and `current_count_change` indicates the number of matched writers.
 * 		2. If `status->current_count_change < 0`, the reader is in the unmatch phase;
 *		the absolute value of `current_count_change` represents the number of offline writers.
 * 		3. Applications can customize this interface through strong symbols, enabling users
 *		to perform corresponding data processing during match and unmatch phases.
 * @see		**Example code**
 * @code
 *		// User override
 *		void Rte_Dds_Reader_OnMatch(
 *			Rte_Dds_Reader r,
 *			const Rte_Dds_Reader_MatchStatus *status)
 *		{
 *			const char * topic_name = Rte_Dds_Reader_Get_TopicName(r);
 *			if(strcmp(topic_name, "xxx") == 0){
 *			// Show status
 *			pr_info("reader(%s) %s! current count:%d, change count:%d\n",
 *			topic_name, status->current_count_change > 0 ? "match" : "unmatch",
 *			status->current_count, status->current_count_change);
 *
 *			if(status->current_count_change > 0){
 *					// match: do something
 *				}else{
 *					// unmatch: do something
 *				}
 *			}
 *			else if(strcmp(topic_name, "yyy") == 0){
 *				pr_info("reader(%s) %s! current count:%d, change count:%d\n",
 *				topic_name, status->current_count_change > 0 ? "match" : "unmatch",
 *				status->current_count, status->current_count_change);
 *			}
 *		}
 * @endcode
 */
#pragma weak Rte_Dds_Reader_OnMatch
void Rte_Dds_Reader_OnMatch(Rte_Dds_Reader r,
			    const Rte_Dds_Reader_MatchStatus *status)
{
	(void)r;
	(void)status;
}

/**
 * @brief	Provides DDS writer match/unmatch event notifications.
 * @param[in]	w Rte_Dds_Writer type. The writer for the corresponding topic.
 * @param[out]	status Rte_Dds_Writer_MatchStatus* type.
 *		Holds the status information related to writer matches.
 * @code
 *		struct writer_matched_status
 *		{
 *			//The total number of readers that have matched.
 *			uint16_t total_count;
 *
 *			//The change in total_count since the last listener call.
 *			uint16_t total_count_change;
 *
 *			//The number of currently matched readers.
 *			uint16_t current_count;
 *
 *			//The change in current_count since the last listener call.
 *			int16_t current_count_change;
 *
 *			//The guid of the last reader that caused a status change.
 *			struct guid last_subscription_handle;
 *		};
 *
 *		typedef struct writer_matched_status Rte_Dds_Writer_MatchStatus;
 * @endcode
 * @note
 *		1. If `status->current_count_change > 0`, the writer is in the match phase,
 *		and `current_count_change` indicates the number of matched readers.
 *		2. If `status->current_count_change < 0`, the writer is in the unmatch phase;
 *		the absolute value of `current_count_change` represents the number of offline readers.
 *		3. Applications can customize this interface through strong symbols, enabling users
 *		to perform corresponding data processing during match and unmatch phases.
 * @see		**Example code**
 * @code
 *		// User override
 *		void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
 *					    const Rte_Dds_Writer_MatchStatus *status)
 *		{
 *			const char * topic_name = Rte_Dds_Writer_Get_TopicName(w);
 *
 *			if (strcmp(topic_name, "xxx") == 0) {
 *				// Show status
 *				pr_info("writer(%s) %s! current count:%d, change count:%d\n",
 *				topic_name, status->current_count_change > 0 ? "match" : "unmatch",
 *				status->current_count, status->current_count_change);
 *
 *				if (status->current_count_change > 0) {
 *					// match: do something
 *				} else {
 *					// unmatch: do something
 *				}
 *			} else if(strcmp(topic_name, "yyy") == 0) {
 *				pr_info("writer(%s) %s! current count:%d, change count:%d\n",
 *				topic_name, status->current_count_change > 0 ? "match" : "unmatch",
 *				status->current_count, status->current_count_change);
 *			}
 *		}
 * @endcode
 */
#pragma weak Rte_Dds_Writer_OnMatch
void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
			    const Rte_Dds_Writer_MatchStatus *status)
{
	(void)w;
	(void)status;
}

/** @} */ // end of RTE

#pragma weak Rte_Dds_Reader_OnE2eException
void Rte_Dds_Reader_OnE2eException(Rte_Dds_Reader r, uint16_t counter,
				   uint32_t e2e_status)
{
	const char *topic_name = reader_get_topicname(r);

	pr_err(ERR_FAULT, "topic_name:%s, sn:%u, e2e status:%u\n", topic_name,
							 counter, e2e_status);
}

void Rte_Dds_Reader_On_Data(struct reader *r, instance_id instance)
{
	Rte_Dds_RxIndication(r, instance);
}

void Rte_Dds_Reader_On_Matched(struct reader *r,
			       struct reader_matched_status *status)
{
	Rte_Dds_Reader_OnMatch(r, status);
}

void Rte_Dds_Writer_On_Matched(struct writer *w,
			       struct writer_matched_status *status)
{
	Rte_Dds_Writer_OnMatch(w, status);
}

void Rte_Dds_Reader_On_E2e_Exception(struct reader *r, int64_t sn,
				      uint32_t e2e_status)
{
	Rte_Dds_Reader_OnE2eException(r, (uint16_t)sn, e2e_status);
}

Rte_Dds_ReturnType Rte_Dds_Init(Rte_Dds_Participant ptcp)
{
	int32_t ret = 0;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: ptcp is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	if (ptcp->started) {
		pr_warn("Repeat initialization.");
		return RTE_DDS_RETCODE_ILLEGAL_OPERATION;
	}

	ret = mvbs_participant_init(ptcp);
	if (ret < 0) {
		/* Failed to read configuration information. */
		return RTE_DDS_RETCODE_PRECONDITION_NOT_MET;
	}

	ret = ptcp_enable(ptcp);
	if (ret < 0) {
		mvbs_participant_deinit(ptcp);

		pr_err(ret, "Failed to start participant.");
		return RTE_DDS_RETCODE_ERROR;
	}

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_ReturnType Rte_Dds_Ptcp_Recv_Handler(Rte_Dds_Participant ptcp,
						uint32_t recv_max_pkg)
{
	if (ptcp == NULL) {
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	ptcp_recv_handler(ptcp, recv_max_pkg);

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_ReturnType Rte_Dds_Ptcp_Timer_Handler(Rte_Dds_Participant ptcp)
{
	if (ptcp == NULL) {
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	ptcp_timer_handler(ptcp);

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_Reader Rte_Dds_GetReader(Rte_Dds_Participant ptcp, const char *topic_name)
{
	Rte_Dds_Reader r;

	if ((ptcp == NULL) || (topic_name == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: ptcp or topic_name is null.");
		return NULL;
	}

	if (ptcp->started == 0) {
		pr_err(ERR_INVALID, "Bad parameter: ptcp hasn't been inited.");
		return NULL;
	}

	r = ptcp_get_reader_with_topic(ptcp, topic_name);
	if (r == NULL) {
		pr_err(ERR_INVALID, "Get reader(%s) fail.", topic_name);
		return NULL;
	}

	return r;
}

Rte_Dds_Writer Rte_Dds_GetWriter(Rte_Dds_Participant ptcp, const char *topic_name)
{
	Rte_Dds_Writer w;

	if ((ptcp == NULL) || (topic_name == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: ptcp or topic_name is null.");
		return NULL;
	}

	if (ptcp->started == 0) {
		pr_err(ERR_INVALID, "Bad parameter: ptcp hasn't been inited.");
		return NULL;
	}

	w = ptcp_get_writer_with_topic(ptcp, topic_name);
	if (w == NULL) {
		pr_err(ERR_INVALID, "Get writer(%s) fail.",topic_name);
		return NULL;
	}

	return w;
}

Rte_Dds_ReturnType Rte_Dds_GetReaderStats(Rte_Dds_Reader r,
					  Rte_Dds_TopicStats *stats)
{
	if ((r == NULL) || (stats == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: r or stats is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	mvbs_memzero(stats, sizeof(Rte_Dds_TopicStats));

	if (reader_get_status(r, stats) != 0) {
		return RTE_DDS_RETCODE_ERROR;
	}

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_ReturnType Rte_Dds_GetWriterStats(Rte_Dds_Writer w,
					  Rte_Dds_TopicStats *stats)
{
	if ((w == NULL) || (stats == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: w or stats is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	mvbs_memzero(stats, sizeof(Rte_Dds_TopicStats));

	if (writer_get_status(w, stats) != 0) {
		return RTE_DDS_RETCODE_ERROR;
	}

	return RTE_DDS_RETCODE_OK;
}

size_t Rte_Dds_GetReaderOnlinePeers(Rte_Dds_Reader r, Rte_Dds_Peers *peer,
				    size_t n)
{
	size_t ret = 0;

	if (r == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: r is null.");
		return ret;
	}

	if ((peer == NULL) || (n == 0U)) {
		pr_err(ERR_INVALID, "Bad parameter: peer is null or n == 0.");
	}

	ret = reader_get_onlinepeers(r, peer, n);

	return ret;
}

size_t Rte_Dds_GetWriterOnlinePeers(Rte_Dds_Writer w, Rte_Dds_Peers *peer,
				    size_t n)
{
	size_t ret = 0;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: w is null.");
		return ret;
	}

	if ((peer == NULL) || (n == 0U)) {
		pr_err(ERR_INVALID, "Bad parameter: peer is null or n == 0.");
	}

	ret = writer_get_onlinepeers(w, peer, n);

	return ret;
}

Rte_Dds_ReturnType Rte_Dds_RxData(Rte_Dds_Reader r, bool take,
				  Rte_Dds_TopicData *data,
				  Rte_Dds_SampleInfo *src_info)
{
	bool retcode = true;

	if ((r == NULL) || (data == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: r or data is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	retcode = reader_get_sample(r, data->data, 0U, src_info, take);
	if (!retcode) {
		return RTE_DDS_RETCODE_ERROR;
	}

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_ReturnType Rte_Dds_TxData(Rte_Dds_Writer w, Rte_Dds_TopicData *data,
				  Rte_Dds_SequenceNumber *writesn)
{
	struct rtps_sn sn;

	if ((w == NULL) || (data == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: w or data is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	sn = writer_submit_sample(w, (const uint8_t *)data->data, 0);
	if (rtps_sn_is_invalid(&sn)) {
		const char *topic_name = writer_get_topicname(w);
		pr_err(ERR_NOMEM, "Writer (%s) create cache change fail.",
		       (topic_name == NULL) ? "null" : topic_name);
		return RTE_DDS_RETCODE_OUT_OF_RESOURCES;
	}

	if (writesn != NULL) {
		*writesn = sn;
	}

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_ReturnType Rte_Dds_Get_Sample_TxStatus(Rte_Dds_Writer w,
					       Rte_Dds_SequenceNumber writersn,
					       Rte_Dds_TransferStatus *status)
{
	int32_t ret;

	if ((w == NULL) || (status == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: w or status is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	ret = writer_get_sample_status(w, writersn, status);

	return (ret == 0) ? RTE_DDS_RETCODE_OK : RTE_DDS_RETCODE_ERROR;
}

const char *Rte_Dds_Reader_Get_TopicName(Rte_Dds_Reader r)
{
	if (r == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: r is null.");
		return NULL;
	}

	return reader_get_topicname(r);
}

const char *Rte_Dds_Writer_Get_TopicName(Rte_Dds_Writer w)
{
	if (w == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: w is null.");
		return NULL;
	}

	return writer_get_topicname(w);
}

Rte_Dds_ReturnType Rte_Dds_Reader_Set_Private(Rte_Dds_Reader r, void *priv_data)
{
	if ((r == NULL) || (priv_data == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: r or private is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	reader_set_private(r, priv_data);

	return RTE_DDS_RETCODE_OK;
}

Rte_Dds_ReturnType Rte_Dds_Writer_Set_Private(Rte_Dds_Writer w, void *priv_data)
{
	if ((w == NULL) || (priv_data == NULL)) {
		pr_err(ERR_INVALID, "Bad parameter: w or private is null.");
		return RTE_DDS_RETCODE_BAD_PARAMETER;
	}

	writer_set_private(w, priv_data);

	return RTE_DDS_RETCODE_OK;
}

void *Rte_Dds_Reader_Get_Private(Rte_Dds_Reader r)
{
	if (r == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: r is null.");
		return NULL;
	}

	return reader_get_private(r);
}

void *Rte_Dds_Writer_Get_Private(Rte_Dds_Writer w)
{
	if (w == NULL) {
		pr_err(ERR_INVALID, "Bad parameter: w is null.");
		return NULL;
	}

	return writer_get_private(w);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
