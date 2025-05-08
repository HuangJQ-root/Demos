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

#ifndef MVBS_RTE_DDS_ADAPTER_H
#define MVBS_RTE_DDS_ADAPTER_H

#include <mvbs/mvbs.h>

/* Part 1: The macros and return code used for rte interfaces. */

#define INVALID_SEQUENCE_NUMBER				{ -1, 0 }
#define TRANSFER_STATUS_INVALID				TRANS_CODE_INVALID

typedef uint8_t						Rte_Dds_ReturnType;

#define RTE_DDS_RETCODE_OK				(Rte_Dds_ReturnType)0
#define RTE_DDS_RETCODE_ERROR				(Rte_Dds_ReturnType)1
#define RTE_DDS_RETCODE_UNSUPPORTED			(Rte_Dds_ReturnType)2
#define RTE_DDS_RETCODE_BAD_PARAMETER			(Rte_Dds_ReturnType)3
#define RTE_DDS_RETCODE_PRECONDITION_NOT_MET		(Rte_Dds_ReturnType)4
#define RTE_DDS_RETCODE_OUT_OF_RESOURCES		(Rte_Dds_ReturnType)5
#define RTE_DDS_RETCODE_NOT_ENABLED			(Rte_Dds_ReturnType)6
#define RTE_DDS_RETCODE_IMMUTABLE_POLICY		(Rte_Dds_ReturnType)7
#define RTE_DDS_RETCODE_INCONSISTENT_POLICY		(Rte_Dds_ReturnType)8
#define RTE_DDS_RETCODE_ALREADY_DELETED			(Rte_Dds_ReturnType)9
#define RTE_DDS_RETCODE_TIMEOUT				(Rte_Dds_ReturnType)10
#define RTE_DDS_RETCODE_NO_DATA				(Rte_Dds_ReturnType)11
#define RTE_DDS_RETCODE_ILLEGAL_OPERATION		(Rte_Dds_ReturnType)12
#define RTE_DDS_RETCODE_NOT_ALLOWED_BY_SEC		(Rte_Dds_ReturnType)13


/* Part 2: The common parameter types for rte interfaces. */

typedef int8_t					Rte_Dds_Instance;

typedef struct Rte_Dds_TopicId {
	const char		*name;
	Rte_Dds_Instance	instance;
} Rte_Dds_TopicId;

typedef struct Rte_Dds_TopicData {
	void			*data;
} Rte_Dds_TopicData;

typedef struct participant *			Rte_Dds_Participant;
typedef struct reader *				Rte_Dds_Reader;
typedef struct writer *				Rte_Dds_Writer;
typedef struct sample_info 			Rte_Dds_SampleInfo;
typedef struct rtps_sn 				Rte_Dds_SequenceNumber;
typedef struct mvbs_endpoint_stat		Rte_Dds_TopicStats;
typedef struct mvbs_entity_info			Rte_Dds_Peers;
typedef TransferStatus 				Rte_Dds_TransferStatus;

/*! TODO: Remove the concepts of publication and subscription in mvbs */
typedef struct reader_matched_status		Rte_Dds_Reader_MatchStatus;
typedef struct writer_matched_status		Rte_Dds_Writer_MatchStatus;


/* Part 3: Interface list. */

#define DEF_RTE_DDS_TOPIC(topic, instance)				\
	{								\
		topic, instance						\
	}

#define Rte_Dds_PackData(_data, msg)					\
	do {								\
		(_data)->data = (void *)(msg);				\
	} while (0)

#define Rte_Dds_UnpackData(data, msg)

/**
 * \addtogroup RTE
 * @{
 */

/**
 * @brief	The rte adaptation layer initialization interface initializes the specified
 *		participant instance.\n
 *		Data transmission and reception operations can only be performed after the
 *		initialization is completed.
 * @param 	ptcp, where ptcp is the obtained participant entity.
 *		- The interface Rte_Dds_Participant Rte_Dds_GetParticipant(), which is generated
 *		by the XML tool, is used to obtain the specified participant.
 * @return 	Return type is Rte_Dds_ReturnType.
 * 		- RTE_DDS_RETCODE_OK: Initialization successful.
 * 		- RTE_DDS_RETCODE_ILLEGAL_OPERATION: Re-initialization attempted.
 * 		- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter passed.
 * 		- RTE_DDS_RETCODE_PRECONDITION_NOT_MET: Failed to read configuration information.
 * 		- RTE_DDS_RETCODE_ERROR: Failed to start participant.
 * @note
 *		- This function should be called only once during initialization to avoid
 *		repeated initialization.
 *		- If the return value is RTE_DDS_RETCODE_PRECONDITION_NOT_MET, it indicates
 *		that the underlying Ethernet is not ready. It is recommended that the user
 *		call this interface again to perform the initialization.
 * @see		**Example Code**
 * @code
 * 		extern Rte_Dds_Participant Rte_Dds_GetParticipant();
 *
 * 		// DDS initialization
 *		Rte_Dds_Participant ptcp = Rte_Dds_GetParticipant();
 * 		if (RTE_DDS_RETCODE_OK != Rte_Dds_Init(ptcp)) {
 * 			return NULL;
 * 		}
 *		pr_info("Rte_Dds_Init OK!");
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_Init(Rte_Dds_Participant ptcp);

/**
 * @brief	Following DDS initialization, you can acquire a read Topic object for
 *		the specified topic_name. This object serves as an interface for receiving DDS data.
 * @param[in]	topic_name Specify a topic_name.
 * @param[in]	ptcp the obtained participant entity
 * @return	The return type is a pointer to Rte_Dds_Reader (an incomplete type).
 * 		- NULL: Retrieval failed (either due to invalid parameters or the absence
 *			of an Rte_Dds_Reader object corresponding to the `topic_name`).
 * 		- Non-NULL: A valid Rte_Dds_Reader object.
 * @note	It is recommended to obtain the corresponding Reader object during
 *		initialization to avoid redundant searches.
 *
 * @see		**Example Code**
 * @code
 *		static Rte_Dds_Reader r;
 *
 *		w = Rte_Dds_GetReader(ptcp, topic_r.name);
 * @endcode
 */
Rte_Dds_Reader Rte_Dds_GetReader(Rte_Dds_Participant ptcp, const char *topic_name);

/**
 * @brief	After DDS initialization, you can obtain the write Topic object for the specified topic_name.
 *		This object can be used to send DDS data.
 * @param[in]	topic_name Specify a topic_name.
 * @param[in]	ptcp the obtained participant entity
 * @return	The return type is a pointer to Rte_Dds_Writer (an incomplete type).
 * 		- NULL: Retrieval failed (either due to invalid parameters or the absence
 *			of an Rte_Dds_Writer object corresponding to the `topic_name`).
 * 		- Non-NULL: A valid Rte_Dds_Writer object.
 * @note	It is recommended to obtain the corresponding Writer object during
 *		initialization to avoid redundant searches.
 *
 * @see		**Example Code**
 * @code
 *		static Rte_Dds_Writer w;
 *
 *		w = Rte_Dds_GetWriter(ptcp, topic_w.name);
 * @endcode
 */
Rte_Dds_Writer Rte_Dds_GetWriter(Rte_Dds_Participant ptcp, const char *topic_name);

/**
 * @brief	This interface allows a participant to receive data.
 *		Each time it is called, up to recv_max_pkg packets are fetched from the
 *		ring buffer and placed into the history of each reader.
 * @param[in]	ptcp The participant instance.
 * @param[in]	recv_max_pkg The maximum number of packets to be received during this call.
 * @return
 *		- RTE_DDS_RETCODE_BAD_PARAMETER: Parameter error.
 *		- RTE_DDS_RETCODE_OK: Success. 
 */
Rte_Dds_ReturnType Rte_Dds_Ptcp_Recv_Handler(Rte_Dds_Participant ptcp,
						uint32_t recv_max_pkg);

/**
 * @brief	Participant timer task handler interface.
 *		This interface executes periodic (timer) tasks registered in the participant.
 *		Each time it is called, the timer tasks within the participant are executed.
 * @param[in]	ptcp The participant instance.
 * @return
 *		- RTE_DDS_RETCODE_BAD_PARAMETER: Parameter error.
 *		- RTE_DDS_RETCODE_OK: Success.
 */
Rte_Dds_ReturnType Rte_Dds_Ptcp_Timer_Handler(Rte_Dds_Participant ptcp);

/**
 * @brief	Retrieve the status of an Rte_Dds_Reader object, including information
 *		such as the current number of online readers/writers, the number of offline
 *		readers/writers, received data, and lost data.
 * @param[in]	r Specify a Rte_Dds_Reader object.
 * @param[out]	stats Retrieve the status of the Reader object, which reflects all
 *		perceptible state changes of the topic, including:
 *		- instances: The number of currently registered instances.
 *		- remotes_online: The number of currently online remote writers.
 *		- total_remotes_online: The total number of writers that have ever matched.
 *		- total_remotes_offline: The total number of offline writers
 *		(calculated as total_remotes_online - remotes_online).
 *		- deadline_timeout: The cumulative number of samples not received within the deadline.
 *		- sample_lost: The number of samples lost.
 *		- sample_committed: The total number of received samples with non-empty data.
 *		- sample_rejected: The number of samples rejected.
 *		- event_bitmap: Unused.
 * @return	The return type is Rte_Dds_ReturnType.
		- RTE_DDS_RETCODE_OK: Successfully retrieved status.
		- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
		- RTE_DDS_RETCODE_ERROR: Failed to retrieve status.
 * @note	When reading status information, fields such as deadline_timeout, sample_lost,
 *		sample_committed, and sample_rejected may experience situations where the count
 *		is smaller than in previous instances. \n
 *		This occurs because DDS is continuously receiving data, and the overall count
 *		has exceeded the range that the status can normally handle, leading to an overflow.
 *
 * @see		**Example Code**
 * @code
 *		void show_info(Rte_Dds_Reader r)
 *		{
 *		        Rte_Dds_TopicStats stats;
 *		        Rte_Dds_ReturnType ret = Rte_Dds_GetReaderStats(r, &stats);
 *
 *		        if (RTE_DDS_RETCODE_OK != ret) {
 *		                return;
 *		        }
 *
 *		        pr_info("instances: %lu\n", stats.instances);
 *		        pr_info("remotes_online: %lu\n", stats.remotes_online);
 *		        pr_info("total_remotes_offline: %lu\n", stats.total_remotes_offline);
 *		        pr_info("deadline_timeout: %lu\n", stats.deadline_timeout);
 *		        pr_info("sample_lost: %lu\n", stats.sample_lost);
 *		        pr_info("sample_committed: %lu\n", stats.sample_committed);
 *		        pr_info("sample_rejected: %lu\n", stats.sample_rejected);
 *		}
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_GetReaderStats(Rte_Dds_Reader r,
					  Rte_Dds_TopicStats *stats);

/**
 * @brief	Retrieve the status of an Rte_Dds_Writer object.
 * @param[in]	topic_name Specify a Rte_Dds_Writer object.
 * @param[out]	stats Retrieve the status of the Writer object, which reflects all
 *		perceptible state changes of the topic, including:
 *		- instances: The number of currently registered instances.
 *		- remotes_online: The number of currently online remote writers.
 *		- total_remotes_online: The total number of writers that have ever matched.
 *		- total_remotes_offline: The total number of offline writers
 *		(calculated as total_remotes_online - remotes_online).
 *		- deadline_timeout: The cumulative number of samples not received within the deadline.
 *		- sample_lost: The number of samples lost.
 *		- sample_committed: The total number of received samples with non-empty data.
 *		- sample_rejected: The number of samples rejected.
 *		- event_bitmap: Unused.
 * @return	The return type is Rte_Dds_ReturnType.
		- RTE_DDS_RETCODE_OK: Successfully retrieved status.
		- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
		- RTE_DDS_RETCODE_ERROR: Failed to retrieve status.
 * @note	When reading status information, fields such as deadline_timeout, sample_lost,
 *		sample_committed, and sample_rejected may experience situations where the count
 *		is smaller than in previous instances. \n
 *		This occurs because DDS is continuously receiving data, and the overall count
 *		has exceeded the range that the status can normally handle, leading to an overflow.
 *
 * @see		**Example Code**
 * @code
 *		void show_info(Rte_Dds_Writer w)
 *		{
 *		        Rte_Dds_TopicStats stats;
 *		        Rte_Dds_ReturnType ret = Rte_Dds_GetWriterStats(w, &stats);
 *
 *		        if (RTE_DDS_RETCODE_OK != ret) {
 *		                return;
 *		        }
 *
 *		        pr_info("instances: %lu\n", stats.instances);
 *		        pr_info("remotes_online: %lu\n", stats.remotes_online);
 *		        pr_info("total_remotes_offline: %lu\n", stats.total_remotes_offline);
 *		        pr_info("deadline_timeout: %lu\n", stats.deadline_timeout);
 *		        pr_info("sample_lost: %lu\n", stats.sample_lost);
 *		        pr_info("sample_committed: %lu\n", stats.sample_committed);
 *		        pr_info("sample_rejected: %lu\n", stats.sample_rejected);
 *		}
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_GetWriterStats(Rte_Dds_Writer w,
					  Rte_Dds_TopicStats *stats);

/**
 * @brief		Queries the remote node status of the Reader,
 *			e.g., to check if the remote node is online before sending data.
 *
 * @param[in] 		r The specified Reader object.
 * @param[in] 		n The size of the peers array.
 * @param[out] 		peers An array of Rte_Dds_Peers that contains information about remote nodes.
 *
 * @return		A size_t type indicating the number of remote nodes:
 *			- If `peer == NULL` or `n = 0`,
 *			the function returns the number of already matched remote nodes.
 *			- If `peer != NULL` and `n != 0`,
 *			the function fills the specified peer array with matched remote node information:
 *			- If the actual number of matched nodes > n,
 *			only n remote node entries are filled, returning n.
 *			- If the actual number of matched nodes <= n,
 *			all matched node information is filled and returns the total count.
 *
 * @note
 *			- The return value represents the number of matched remote nodes,
 *			i.e., the count of valid entries in the peer array.
 *			- `remote_name` might be a null pointer.
 *			Be cautious when using this data after the remote node goes offline.
 *			- If `remote_name` is not NULL, it corresponds to the node's key + IP as
 *			configured in XML (MVBS), e.g., "node_1_127.0.0.1"; for participants sent
 *			from VBS,the output follows VBS configuration.
 * @see		**Example Code**
 * @code
 *		int peers_num = 5;
 *		struct Rte_Dds_Peers peers[5];
 *		Rte_Dds_Reader r = Rte_Dds_GetReader(topic_r.name);
 *
 *		size_t ret_num = Rte_Dds_GetReaderOnlinePeers(r, peers, peers_num);
 *
 *		// ret_num may not equal peers_num
 *		// The user might want to know about the current five online peers,
 *		// but only two are actually online, ret_num indicates the actual count.
 *		for (int i = 0; i < ret_num; i++) {
 *		    struct Rte_Dds_Peers *peer = &peers[i];
 *		    pr_info("guid_prefix: %d %d %d %d %d %d %d %d %d %d %d %d",
 *		                    peer->guid.prefix.id[0], peer->guid.prefix.id[1],
 *		                    peer->guid.prefix.id[2], peer->guid.prefix.id[3],
 *		                    peer->guid.prefix.id[4], peer->guid.prefix.id[5],
 *		                    peer->guid.prefix.id[6], peer->guid.prefix.id[7],
 *		                    peer->guid.prefix.id[8], peer->guid.prefix.id[9],
 *		                    peer->guid.prefix.id[10], peer->guid.prefix.id[11]);
 *		    pr_info("entity_kind: %d, entity_key: %d %d %d",
 *		                    peer->guid.eid.entity_kind, peer->guid.eid.entity_key[0],
 *		                    peer->guid.eid.entity_key[1], peer->guid.eid.entity_key[2]);
 *		    pr_info("remote_name: %s", (peer->remote_name == NULL)? "NULL": peer->remote_name);
 *		}
 *
 *		pr_info("topic(%s) online peers is %d@n", topic.name, ret_num);
 * @endcode
 */
size_t Rte_Dds_GetReaderOnlinePeers(Rte_Dds_Reader r, Rte_Dds_Peers *peer,
				    size_t n);

/**
 * @brief		Queries the remote node status of the Writer,
 *			e.g., to check if the remote node is online before sending data.
 *
 * @param[in] 		w The specified Writer object.
 * @param[in] 		n The size of the peers array.
 * @param[out] 		peers An array of Rte_Dds_Peers that contains information about remote nodes.
 *
 * @return		A size_t type indicating the number of remote nodes:
 *			- If `peer == NULL` or `n = 0`,
 *			the function returns the number of already matched remote nodes.
 *			- If `peer != NULL` and `n != 0`,
 *			the function fills the specified peer array with matched remote node information:
 *			- If the actual number of matched nodes > n,
 *			only n remote node entries are filled, returning n.
 *			- If the actual number of matched nodes <= n,
 *			all matched node information is filled and returns the total count.
 *
 * @note
 *			- The return value represents the number of matched remote nodes,
 *			i.e., the count of valid entries in the peer array.
 *			- `remote_name` might be a null pointer.
 *			Be cautious when using this data after the remote node goes offline.
 *			- If `remote_name` is not NULL, it corresponds to the node's key + IP as
 *			configured in XML (MVBS), e.g., "node_1_127.0.0.1"; for participants sent
 *			from VBS,the output follows VBS configuration.
 * @see			**Example Code**
 * @code
 *			int peers_num = 5;
 *			struct Rte_Dds_Peers peers[5];
 *			Rte_Dds_Writer w = Rte_Dds_GetWriter(topic_w.name);
 *
 *			size_t ret_num = Rte_Dds_GetWriterOnlinePeers(w, peers, peers_num);
 *			// ret_num may not equal peers_num
 *			// The user might want to know the current five online peers, but in reality,
 *			// there are only two; ret_num indicates the actual count
 *			for (int i = 0; i < ret_num; i++) {
 *			    struct Rte_Dds_Peers *peer = &peers[i];
 *			    pr_info("guid_prefix: %d %d %d %d %d %d %d %d %d %d %d %d",
 *			                    peer->guid.prefix.id[0], peer->guid.prefix.id[1],
 *			                    peer->guid.prefix.id[2], peer->guid.prefix.id[3],
 *			                    peer->guid.prefix.id[4], peer->guid.prefix.id[5],
 *			                    peer->guid.prefix.id[6], peer->guid.prefix.id[7],
 *			                    peer->guid.prefix.id[8], peer->guid.prefix.id[9],
 *			                    peer->guid.prefix.id[10], peer->guid.prefix.id[11]);
 *			    pr_info("entity_kind: %d, entity_key: %d %d %d",
 *			                    peer->guid.eid.entity_kind, peer->guid.eid.entity_key[0],
 *			                    peer->guid.eid.entity_key[1], peer->guid.eid.entity_key[2]);
 *			    pr_info("remote_name: %s", (peer->remote_name == NULL)? "NULL": peer->remote_name);
 *			}
 *
 *			pr_info("topic(%s) online peers is %d\n", topic.name, ret_num);
 * @endcode
 */
size_t Rte_Dds_GetWriterOnlinePeers(Rte_Dds_Writer w, Rte_Dds_Peers *peer,
				    size_t n);

/**
 * @brief		Reads a sample from the specified Reader object.
 *
 * @param[in]		r The specified Reader object.
 * @param[in]		take Specifies whether to delete the original sample from the history
 *			cache after reading a sample:
 *			- true: Delete the original sample from the history cache.
 *			- false: Do not delete the original sample from the history cache.
 *
 * @param[out] 		data The specified data, initialized in the same manner as the send
 *			interface, from which the user retrieves data.
 * @param[out] 		src_info Used to obtain information about the sample sender when multiple
 *			sample senders exist:
 *			- If NULL, sample information is not retrieved.
 *			- If not NULL, the source information of the sample will be returned.
 *
 *
 * @return		Return type is Rte_Dds_ReturnType.
 *			- RTE_DDS_RETCODE_OK: Successfully retrieved sample.
 *			- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
 *			- RTE_DDS_RETCODE_ERROR: Failed to retrieve sample.
 *
 * @note
 * 			- The `remote_name` in struct Rte_Dds_Peers may be a null pointer. \n
 *			Use with caution if retrieving data after the remote node goes offline.
 * 			- With a small history depth setting, the frequency of reading data using
 *			Rte_Dds_RxData should be greater than the frequency of sending data using Rte_Dds_TxData, \n
 *			i.e., read faster than write to avoid data loss. Recommended: freq(Rx) >= 2 * freq(Tx).
 *
 * @see			**Example Code** \n
 * 			Step 1 and 2 initialize once, then Step 3 can be repeated.
 * 			@code
 * 			// 1. Initialize topic
 * 			Rte_Dds_TopicId topic_r = DEF_RTE_DDS_TOPIC("hybrid2", {0});
 *
 * 			// 2. Data packaging
 * 			HybridMsg2 sample2;
 * 			HybridMsg2_init(&sample2);
 * 			Rte_Dds_TopicData data_r;
 * 			Rte_Dds_PackData(&data_r, &sample2);
 * 			struct sample_info info;
 * 			Rte_Dds_Reader r = Rte_Dds_GetReader(topic_r.name);
 *
 * 			// 3. Data reading:
 * 			if (Rte_Dds_RxData(r, true, &data_r, &info) == RTE_DDS_RETCODE_OK) {
 * 			    printf("--------rx msg : sample2.msg = %s\n", sample2.msg);
 * 			}
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_RxData(Rte_Dds_Reader r, bool take,
				  Rte_Dds_TopicData *data,
				  Rte_Dds_SampleInfo *src_info);

/**
 * @brief		Send DDS data by specifying a Writer operation object.
 *
 * @param[in]		w Rte_Dds_Writer type. The specified Writer operation object.
 * @param[in]		data Rte_Dds_TopicData type. The Data object to be sent, packaged using the
 *			macro Rte_Dds_PackData.
 *			@code
 *			// Allocate a message body corresponding to the topic
 *			HybridMsg1 sample1;
 *			HybridMsg1_init(&sample1)
 *			Rte_Dds_TopicData data_w;
 *			// Pack data_w
 *			Rte_Dds_PackData(&data_w, &sample1);
 *			@endcode
 * @param[out]		writesn Rte_Dds_SequenceNumber* type. Used to mark the sequence number corresponding
 *			to the sample.
 *			This can be used later to query the send status through Rte_Dds_Get_Sample_TxStatus.
 *			If tracking the sample's status is not required, the writesn parameter can be set to NULL.
 * @return		Rte_Dds_Return Type.
 *			- RTE_DDS_RETCODE_OK: Sample successfully placed into the Writer's CacheChange.
 *			- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
 *			- RTE_DDS_RETCODE_OUT_OF_RESOURCES: Failed to create cache change.
 * @note
 *			- The success or failure of sample transmission is not reflected in the return value.
 *			It can still only be queried through the interface Rte_Dds_Get_Sample_TxStatus.
 *			- If tracking the status of the data sample is not necessary, pass NULL for the
 *			writesn parameter.
 *			- If writesn is not NULL, the underlying system will return the sample's sequence number for
 *			tracking its send result.
 *			- The writesn is used globally and its status can be queried using the specific interface
 *			Rte_Dds_Get_Sample_TxStatus.
 * @see			**Example Code** \n
 *			Step 1 and Step 2 are initialized once, then Steps 3 and 4 can be repeated.
 * @code
 *			// 1. Initialize topic
 *			Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("hybrid1",{0});
 *
 *			// 2. Data packing
 *			HybridMsg1 sample1;
 *			HybridMsg1_init(&sample1);
 *			Rte_Dds_TopicData data_w;
 *			Rte_Dds_PackData(&data_w, &sample1);
 *			Rte_Dds_Writer w = Rte_Dds_GetWriter(topic_w.name);
 *			struct sequence_number writesn;
 *
 *			for (int i = 0; i < 10; i++) {
 *			    // 3. Modify data
 *			    sample1.id = 0x123;
 *
 *			    // 4. Send data: case 1: writesn used to query package status
 *			    ret = Rte_Dds_TxData(w, &data_w, &writesn);
 *			    if (ret != RTE_DDS_RETCODE_OK) {
 *			        printf("tx failed!\n");
 *			    }
 *
 *			    // 4. Send data: case 2: user does not monitor package status
 *			    ret = Rte_Dds_TxData(w, &data_w, NULL);
 *			    if (ret != RTE_DDS_RETCODE_OK) {
 *			        printf("tx failed!\n");
 *			    }
 *			}
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_TxData(Rte_Dds_Writer w, Rte_Dds_TopicData *data,
				  Rte_Dds_SequenceNumber *writesn);

/**
 * @brief		Retrieves the status of the data packet corresponding to the specified `writersn`.
 * @param[in] 		w Rte_Dds_Writer type.The specified Writer object.
 * @param[in] 		writersn Rte_Dds_SequenceNumber type.
 *			The sequence number of the sent sample, used to track the status of the sample.
 * @param[out] 		status Rte_Dds_TransStatus*: The valid values of status are:
 *			- TRANS_CODE_INVALID(0): Indicates invalid.
 *			- TRANS_CODE_ALL_SUCCESS(1): All data sent out and acknowledged.
 *			- TRANS_CODE_ALL_SUCCESS_ALL_OUT(2): All data sent out.
 *			- TRANS_CODE_PART_FAIL(100): Not used.
 *			- TRANS_CODE_PART_FAIL_PART_OUT(101): Part of cachechange not sent out.
 *			- TRANS_CODE_PART_FAIL_HAS_BEEN_RESENT(102): Part of cachechange not sent out, but retried.
 *			- TRANS_CODE_PART_FAIL_PART_ACK: Only part of the ACKs received, may need to wait a bit.
 *			- TRANS_CODE_ALL_FAIL(200): Not used.
 *			- TRANS_CODE_ALL_FAIL_NO_PROXY_HAS_MATCHED(201): None sent, topic matched, but no send proxy.
 *			- TRANS_CODE_ALL_FAIL_NO_PROXY_NO_MATCHED(202): None sent, topic not matched, no send proxy.
 *			- TRANS_CODE_ALL_FAIL_PROXY_INVALID(203): None sent, proxy exists but is invalid.
 *			- TRANS_CODE_ALL_FAIL_OTHERS(204): All failed to be sent for other reasons.
 *			- TRANS_CODE_ALL_FAIL_NONE_ACK(205): All sent out, but no ACK received.
 *			- TRANS_CODE_NO_STATUS_CC_DELETED(300): Cachechange deleted.
 *			- TRANS_CODE_UPPER_LIMIT: Used at the end for valid value checks.
 *
 * @return		Rte_Dds_Return type.
 *			- RTE_DDS_RETCODE_OK: Successfully retrieved sample status.
 *			- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
 *			- RTE_DDS_RETCODE_ERROR: Failed to retrieve sample status.
 *
 * @note
 * 			1. When Rte_Dds_SequenceNumber is invalid, the status is TRANS_CODE_NO_STATUS_CC_DELETED.
 *			When valid, the sample status can be: \n
 * 			   1) Successfully sent (received by all endpoints). \n
 * 			   2) Failed to send (not received by any endpoints). \n
 * 			   3) Partially failed (received by some endpoints). \n
 * 			In the event of a send failure, additional failure reasons such as Ethernet link faults
 *			may need to be obtained.
 * 			2. This is only applicable for the Reliability attribute and does not consider best-effort.
 * 			3. Limited by DDS's history, durability, etc. QoS settings, if too much data is sent,samples
 *			in the history cache may be deleted. \n
 *			If queried by writesn, it may return TRANS_CODE_NO_STATUS_CC_DELETED.
 * @see			**Example Code** \n
 * @code
 *			Rte_Dds_ReturnType ret;
 *			Rte_Dds_TopicData data;
 *			TransferStatus status;
 *			struct sequence_number writesn;
 *
 *			HelloWorld sample;
 *			HelloWorld_init(&sample);
 *			Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("topicA", {0});
 *			Rte_Dds_PackData(&data, &sample);
 *			Rte_Dds_Writer w = Rte_Dds_GetWriter(topic_w.name);
 *
 *			// Send a data sample, obtain the sequence number (sn)
 *			ret = Rte_Dds_TxData(w, &data, &writesn);
 *			if (ret != RTE_DDS_RETCODE_OK) {
 *			    pr_err("tx data failed!\n");
 *			    return ret;
 *			}
 *
 *			// Query status information using the sn number, stored in the status parameter
 *			ret = Rte_Dds_Get_Sample_TxStatus(w, writesn, &status);
 *			if (ret != RTE_DDS_RETCODE_OK) {
 *			    pr_err("Rte_Dds_Get_Sample_TxStatus failed!\n");
 *			    return ret;
 *			} else if (status == TRANS_CODE_ALL_SUCCESS) {
 *			    pr_info("status = %d means TRANS_CODE_ALL_SUCCESS", TRANS_CODE_ALL_SUCCESS);
 *			} else {
 *			    pr_warn("status = %d", status);
 *			}
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_Get_Sample_TxStatus(Rte_Dds_Writer w,
					       Rte_Dds_SequenceNumber writersn,
					       Rte_Dds_TransferStatus *status);

/**
 * @brief		Returns the Topic Name of the Reader.
 * @param[in]		r Rte_Dds_Reader type. The reader object.
 * @return		A pointer to the Topic Name.
 * @see			**Example Code** \n
 * @code
 *			Rte_Dds_Reader r;
 *			const char *ptr = Rte_Dds_Reader_Get_TopicName(r);
 *			printf("topic_name: %s\n", ptr);
 * @endcode
 */
const char *Rte_Dds_Reader_Get_TopicName(Rte_Dds_Reader r);

/**
 * @brief		Returns the Topic Name of the Writer.
 * @param[in]		w Rte_Dds_Writer type. The writer object.
 * @return 		const char* type. The Topic Name of the writer.
 * @see			**Example Code** \n
 * @code
 * 			Rte_Dds_Writer w;
 * 			const char *ptr = Rte_Dds_Writer_Get_TopicName(w);
 * 			printf("topic_name: %s\n", ptr);
 * @endcode
 */
const char *Rte_Dds_Writer_Get_TopicName(Rte_Dds_Writer w);

/**
 * @brief		Sets the Reader's private member variable.
 * @param[in]		r Rte_Dds_Reader type. The reader object.
 * @param[in]		private void* type. User-provided private data for the reader.
 * @return		Rte_Dds_Return type.
 *			- RTE_DDS_RETCODE_OK: Successfully set.
 *			- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
 *			- RTE_DDS_RETCODE_ERROR: Failed to set.
 * @see			**Example Code** \n
 * @code
 *			DataType data;
 *			Rte_Dds_ReturnType ret = RTE_DDS_RETCODE_OK;
 *			Rte_Dds_Reader r = Rte_Dds_GetReader("TopicA");
 *			void *private = &data;
 *
 *			ret = Rte_Dds_Reader_Set_Private(r, private);
 *			if (ret != RTE_DDS_RETCODE_OK) {
 *			    pr_err("set private error");
 *			}
 * @endcode
 */
Rte_Dds_ReturnType Rte_Dds_Reader_Set_Private(Rte_Dds_Reader r, void *priv_data);

/**
 * @brief		Sets the Writer's private member variable.
 * @param[in]		w Rte_Dds_Writer type. The writer object.
 * @param[in]		private void* type. User-provided private data for the writer.
 * @return		Rte_Dds_Return type.
 *			- RTE_DDS_RETCODE_OK: Successfully set.
 *			- RTE_DDS_RETCODE_BAD_PARAMETER: Invalid parameter.
 *			- RTE_DDS_RETCODE_ERROR: Failed to set.
 */
Rte_Dds_ReturnType Rte_Dds_Writer_Set_Private(Rte_Dds_Writer w, void *priv_data);

/**
 * @brief		Retrieves the Reader's private member variable.
 * @param[in]		r Rte_Dds_Reader type. The reader object.
 * @return		void* type. The private data of the reader object, or NULL on failure.
 * @see			**Example Code** \n
 * @code
 *			struct subscription_list {
 *				const char *topic_name;
 *				Rte_Dds_TopicData sample;
 *				Rte_Dds_Reader r;
 *			};
 *
 *			DataType1 sample1;
 *			DataType2 sample2;
 *			DataType3 sample3;
 *			DataType4 sample4;
 *
 *			#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
 *
 *			struct subscription_list table[] = {
 *				{
 *				    .topic_name = "Topic_1",
 *				    .sample = {
 *				        .data = &sample1,
 *				    },
 *				}, {
 *				    .topic_name = "Topic_2",
 *				    .sample = {
 *				        .data = &sample2,
 *				    },
 *				}, {
 *				    .topic_name = "Topic_3",
 *				    .sample = {
 *				        .data = &sample3,
 *				    },
 *				}, {
 *				    .topic_name = "Topic_4",
 *				    .sample = {
 *				        .data = &sample4,
 *				    },
 *				}
 *			};
 *
 *			void init(void)
 *			{
 *				int i;
 *
 *				for (i = 0; i < ARRAY_SIZE(table); i++) {
 *					table[i].r = Rte_Dds_GetReader(table[i].topic_name);
 *					Rte_Dds_Reader_Set_Private(table[i].r, &table[i].sample);
 *				}
 *			}
 *
 *			// User overrides the callback function
 *			void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
 *			{
 *				// Here, it's no longer necessary to use
 *				// Rte_Dds_Reader_Get_TopicName to get the topic name
 *				// and then find its data container location.
 *
 *				Rte_Dds_TopicData *sample;
 *
 *				sample = Rte_Dds_Reader_Get_Private(r);
 *
 *				Rte_Dds_RxData(r, true, sample, NULL);
 *
 *				// The private pointer can store not only data containers but also
 *				// function pointers, allowing each topic to have a dedicated processing
 *				// method:
 *				// struct info {
 *				// 	Rte_Dds_TopicData *sample;
 *				// 	void (*cb)(Rte_Dds_Reader r, Rte_Dds_TopicData *sample);
 *				// };
 *				// info = Rte_Dds_Reader_Get_Private(r);
 *				// Rte_Dds_RxData(r, true, info->sample, NULL);
 *				// info->cb(r, info->sample);
 *				//
 *				// The private field provides the potential for expanding
 *				// Rte_Dds_Reader and Rte_Dds_Writer functionalities.
 *			}
 * @endcode
 */
void *Rte_Dds_Reader_Get_Private(Rte_Dds_Reader r);

/**
 * @brief		Retrieves the Writer's private member variable.
 * @param[in]		w Rte_Dds_Writer type. The writer object.
 * @return		void* type. The private data of the writer object, or NULL on failure.
 * @see			**Example Code** \n
 * @code
 *			// User overrides the callback function
 *			void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
 *			    const struct publication_matched_status *status)
 *			{
 *			    void *ptr = Rte_Dds_Writer_Get_Private(w);
 *			}
 * @endcode
 */
void *Rte_Dds_Writer_Get_Private(Rte_Dds_Writer w);

/** @} */ // end of RTE

#ifdef __MVBS_CORE_SOURCE__
void Rte_Dds_Reader_On_Data(struct reader *r, instance_id instance);
void Rte_Dds_Reader_On_Matched(struct reader *r,
			       struct reader_matched_status *status);

void Rte_Dds_Reader_On_E2e_Exception(struct reader *r, int64_t sn,
				      uint32_t e2e_status);

void Rte_Dds_Writer_On_Matched(struct writer *w,
			       struct writer_matched_status *status);
#endif

#endif /* !MVBS_RTE_DDS_ADAPTER_H */
