/*--------------------------------------------------------------------------
 *
 * Copyright 2011-2018 SequoiaDB
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
 *
 *-------------------------------------------------------------------------
 */

#ifndef SDB_FDW_UTIL_H__
#define SDB_FDW_UTIL_H__

#include "client.h"
#include "fmgr.h"
#include "catalog/pg_foreign_server.h"
#include "catalog/pg_foreign_table.h"
#include "nodes/relation.h"
#include "sdb_fdw.h"


typedef enum
{
   SDB_VAR_VAR = 0,
   SDB_PARAM_VAR ,
   SDB_VAR_CONST ,
   SDB_UNSUPPORT_ARG_TYPE
} EnumSdbArgType;

typedef struct
{
   bool     nonempty;      /* True if lists are not all empty */
   /* Lists of RestrictInfos, one per index column */
   List     *indexclauses[INDEX_MAX_KEYS];
} sdbIndexClauseSet;

void sdbGetIndexEqclause( PlannerInfo *root, RelOptInfo *baserel, Oid tableID,
                          sdbIndexInfo *indexInfo,
                          sdbIndexClauseSet *clauseset ) ;

void sdbMatchJoinClausesToIndex( PlannerInfo *root, RelOptInfo *rel,
                                 Oid tableID, sdbIndexInfo *index,
                                 sdbIndexClauseSet *clauseset ) ;

void sdbMatchClauseToIndex( RelOptInfo *rel, Oid tableID, sdbIndexInfo *index,
                            RestrictInfo *rinfo,
                            sdbIndexClauseSet *clauseset ) ;

bool sdbMatchClauseToIndexcol( RelOptInfo *rel, Oid tableID,
                               sdbIndexInfo *index, int indexcol,
                               RestrictInfo *rinfo ) ;

//int sdbGetIndexInfo( SdbExecState *sdbState, sdbIndexInfo *indexInfo ) ;

int sdbGetIndexInfos( SdbExecState *sdbState, sdbIndexInfo *indexInfo,
                      int maxNum, int *indexNum ) ;


sdbConnectionHandle sdbGetConnectionHandle( const char **serverList,
                                            int serverNum,
                                            const char *usr,
                                            const char *passwd,
                                            const char *preference_instance,
                                            const char *transaction ) ;

sdbCollectionHandle sdbGetSdbCollection( sdbConnectionHandle connectionHandle,
      const char *sdbcs, const char *sdbcl ) ;


SdbConnectionPool *sdbGetConnectionPool() ;

int sdbSetConnectionPreference( sdbConnectionHandle hConnection,
                                const CHAR *preference_instance ) ;

BOOLEAN sdbIsInterrupt() ;

void sdbReleaseConnectionFromPool(int index) ;

IndexPath *sdb_build_index_paths(PlannerInfo *root, RelOptInfo *rel,
              sdbIndexInfo *sdbIndex, sdbIndexClauseSet *clauses,
              SdbExecState *fdw_state);

IndexPath *sdb_create_index_path(PlannerInfo *root, RelOptInfo *rel,
                                 IndexOptInfo *index, List *indexclauses,
                                 List *indexclausecols, List *indexorderbys,
                                 List *indexorderbycols, List *pathkeys,
                                 ScanDirection indexscandir, bool indexonly,
                                 Relids required_outer, double loop_count,
                                 SdbExecState *fdw_state);

EnumSdbArgType getArgumentType(List *arguments);

int sdbGenerateRescanCondition(SdbExecState *fdw_state, PlanState *planState,
                               bson *rescanCondition);

void sdbPrintBson( bson *bson, int log_level, const char *label ) ;

void debugClauseInfo( PlannerInfo *root, RelOptInfo *baserel, Oid tableID ) ;


/* record cache */
typedef struct
{
   bson *record ;
   BOOLEAN isUsed ;
} SdbRecordItem ;


#define SDB_MAX_RECORD_SIZE 100
#define FIELD_NAME_PREFERED_INSTANCE "PreferedInstance"
typedef struct
{
   INT32 size ;
   INT32 usedCount ;
   SdbRecordItem recordArray[ SDB_MAX_RECORD_SIZE ] ;
} SdbRecordCache ;

void SdbInitRecordCache() ;
void SdbFiniRecordCache() ;

SdbRecordCache *SdbGetRecordCache() ;
bson *SdbAllocRecord( SdbRecordCache *recordCache, UINT64 *recordID ) ;
bson *SdbGetRecord( SdbRecordCache *recordCache, UINT64 recordID ) ;
void SdbReleaseRecord( SdbRecordCache *recordCache, UINT64 recordID ) ;


#ifdef SDB_USE_OWN_POSTGRES
void sdbuseownpostgres() ;
#endif /* SDB_USE_OWN_POSTGRES */



#endif /*SDB_FDW_UTIL_H__*/


