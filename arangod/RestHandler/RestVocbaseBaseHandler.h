////////////////////////////////////////////////////////////////////////////////
/// @brief abstract base request handler
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2010-2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_REST_HANDLER_REST_VOCBASE_BASE_HANDLER_H
#define TRIAGENS_REST_HANDLER_REST_VOCBASE_BASE_HANDLER_H 1

#include "Admin/RestBaseHandler.h"

#include "BasicsC/json.h"
#include "BasicsC/json-utilities.h"

#include "Logger/Logger.h"
#include "Rest/HttpResponse.h"
#include "Utils/Collection.h"
#include "Utils/SelfContainedReadTransaction.h"
#include "Utils/SelfContainedWriteTransaction.h"

// -----------------------------------------------------------------------------
// --SECTION--                                              forward declarations
// -----------------------------------------------------------------------------

struct TRI_primary_collection_s;
struct TRI_result_set_s;
struct TRI_vocbase_col_s;
struct TRI_vocbase_s;
struct TRI_json_s;

// -----------------------------------------------------------------------------
// --SECTION--                                      class RestVocbaseBaseHandler
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

namespace triagens {
  namespace arango {

////////////////////////////////////////////////////////////////////////////////
/// @brief abstract base request handler
////////////////////////////////////////////////////////////////////////////////

    class RestVocbaseBaseHandler : public admin::RestBaseHandler {
      private:
        RestVocbaseBaseHandler (RestVocbaseBaseHandler const&);
        RestVocbaseBaseHandler& operator= (RestVocbaseBaseHandler const&);

// -----------------------------------------------------------------------------
// --SECTION--                                                  public constants
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief result RES-OK
////////////////////////////////////////////////////////////////////////////////

        static basics::LoggerData::Extra const RES_OK;

////////////////////////////////////////////////////////////////////////////////
/// @brief result RES-ERR
////////////////////////////////////////////////////////////////////////////////

        static basics::LoggerData::Extra const RES_ERR;

////////////////////////////////////////////////////////////////////////////////
/// @brief result RES-ERR
////////////////////////////////////////////////////////////////////////////////

        static basics::LoggerData::Extra const RES_FAIL;

////////////////////////////////////////////////////////////////////////////////
/// @brief document path
////////////////////////////////////////////////////////////////////////////////

        static string DOCUMENT_PATH;

////////////////////////////////////////////////////////////////////////////////
/// @brief edge path
////////////////////////////////////////////////////////////////////////////////

        static string EDGE_PATH;

////////////////////////////////////////////////////////////////////////////////
/// @brief collection path
////////////////////////////////////////////////////////////////////////////////

        static string COLLECTION_PATH;

////////////////////////////////////////////////////////////////////////////////
/// @brief document import path
////////////////////////////////////////////////////////////////////////////////

        static string DOCUMENT_IMPORT_PATH;

////////////////////////////////////////////////////////////////////////////////
/// @brief batch path
////////////////////////////////////////////////////////////////////////////////

        static string BATCH_PATH;

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

        RestVocbaseBaseHandler (rest::HttpRequest* request, struct TRI_vocbase_s* vocbase);

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////

        ~RestVocbaseBaseHandler ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 protected methods
// -----------------------------------------------------------------------------

      protected:

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief generates ok message without content
////////////////////////////////////////////////////////////////////////////////

        void generateOk ();

////////////////////////////////////////////////////////////////////////////////
/// @brief generates created message
////////////////////////////////////////////////////////////////////////////////

        void generateCreated (TRI_voc_cid_t, TRI_voc_key_t, TRI_voc_rid_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates accepted message
////////////////////////////////////////////////////////////////////////////////

        void generateAccepted (TRI_voc_cid_t, TRI_voc_key_t, TRI_voc_rid_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates deleted message
////////////////////////////////////////////////////////////////////////////////

        void generateDeleted (TRI_voc_cid_t, TRI_voc_key_t, TRI_voc_rid_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates updated message
////////////////////////////////////////////////////////////////////////////////

        void generateUpdated (TRI_voc_cid_t, TRI_voc_key_t, TRI_voc_rid_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates document not found error message
////////////////////////////////////////////////////////////////////////////////

        void generateDocumentNotFound (TRI_voc_cid_t, TRI_voc_key_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates conflict message
////////////////////////////////////////////////////////////////////////////////

        void generateConflict (TRI_voc_cid_t, TRI_voc_key_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates not implemented
////////////////////////////////////////////////////////////////////////////////

        void generateNotImplemented (string const& path);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates forbidden
////////////////////////////////////////////////////////////////////////////////

        void generateForbidden ();

////////////////////////////////////////////////////////////////////////////////
/// @brief generates precondition failed
////////////////////////////////////////////////////////////////////////////////

        void generatePreconditionFailed (TRI_voc_cid_t, TRI_voc_key_t, TRI_voc_rid_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates not modified
////////////////////////////////////////////////////////////////////////////////

        void generateNotModified (string const&);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates first entry from a result set
////////////////////////////////////////////////////////////////////////////////

        void generateDocument (TRI_doc_mptr_t const*,
                               const TRI_voc_cid_t,
                               TRI_shaper_t*,
                               const bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief generate an error message for a transaction error
////////////////////////////////////////////////////////////////////////////////

        void generateTransactionError (const string&, 
                                       const int,
                                       TRI_voc_cid_t = 0,
                                       TRI_voc_key_t = 0,
                                       TRI_voc_rid_t = 0);


////////////////////////////////////////////////////////////////////////////////
/// @brief extracts the revision
///
/// @note @FA{header} must be lowercase.
////////////////////////////////////////////////////////////////////////////////

        TRI_voc_rid_t extractRevision (char const* header, char const* parameter);

////////////////////////////////////////////////////////////////////////////////
/// @brief extracts the update policy
////////////////////////////////////////////////////////////////////////////////

        TRI_doc_update_policy_e extractUpdatePolicy () const;

////////////////////////////////////////////////////////////////////////////////
/// @brief extracts the waitForSync value
////////////////////////////////////////////////////////////////////////////////

        bool extractWaitForSync () const;

////////////////////////////////////////////////////////////////////////////////
/// @brief parses the body
////////////////////////////////////////////////////////////////////////////////

        struct TRI_json_s* parseJsonBody ();

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a document handle
////////////////////////////////////////////////////////////////////////////////

        int parseDocumentId (string const& handle,
                             TRI_voc_cid_t& cid,
                             TRI_voc_key_t& key);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                               protected variables
// -----------------------------------------------------------------------------

      protected:

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief the vocbase
////////////////////////////////////////////////////////////////////////////////

        struct TRI_vocbase_s* _vocbase;

////////////////////////////////////////////////////////////////////////////////
/// @brief timing data structure
////////////////////////////////////////////////////////////////////////////////

        triagens::basics::LoggerTiming _timing;

////////////////////////////////////////////////////////////////////////////////
/// @brief timing result
////////////////////////////////////////////////////////////////////////////////

        triagens::basics::LoggerData::Extra _timingResult;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   Handler methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        bool isDirect ();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:
