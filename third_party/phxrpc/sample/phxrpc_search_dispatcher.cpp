/* phxrpc_search_dispatcher.h

 Generated by phxrpc_pb2service from search.proto

 Please DO NOT edit unless you know exactly what you are doing.

*/

#include "phxrpc_search_dispatcher.h"

#include <errno.h>

#include "phxrpc/http.h"
#include "phxrpc/file.h"

#include "search.pb.h"
#include "phxrpc_search_service.h"


SearchDispatcher::SearchDispatcher(SearchService &service, phxrpc::DispatcherArgs_t *dispatcher_args)
        : service_(service), dispatcher_args_(dispatcher_args) {
}

SearchDispatcher::~SearchDispatcher() {
}

const phxrpc::BaseDispatcher<SearchDispatcher>::URIFuncMap &SearchDispatcher::GetURIFuncMap() {
    static phxrpc::BaseDispatcher<SearchDispatcher>::URIFuncMap uri_func_map = {
        {"/search/PHXEcho", &SearchDispatcher::PHXEcho},
        {"/search/Search", &SearchDispatcher::Search},
        {"/search/Notify", &SearchDispatcher::Notify}};
    return uri_func_map;
}

int SearchDispatcher::PHXEcho(const phxrpc::BaseRequest &req, phxrpc::BaseResponse *const resp) {
    dispatcher_args_->server_monitor->SvrCall(-1, "PHXEcho", 1);

    int ret{-1};

    google::protobuf::StringValue req_pb;
    google::protobuf::StringValue resp_pb;

    // unpack request
    {
        ret = req.ToPb(&req_pb);
        if (0 != ret) {
            phxrpc::log(LOG_ERR, "ToPb err %d", ret);

            return -EINVAL;
        }
    }

    // logic process
    {
        if (0 == ret) {
            ret = service_.PHXEcho(req_pb, &resp_pb);
        }
    }

    // pack response
    {
        if (0 != resp->FromPb(resp_pb)) {
            phxrpc::log(LOG_ERR, "FromPb err %d", ret);

            return -ENOMEM;
        }
    }

    phxrpc::log(LOG_DEBUG, "RETN: PHXEcho = %d", ret);

    return ret;
}

int SearchDispatcher::Search(const phxrpc::BaseRequest &req, phxrpc::BaseResponse *const resp) {
    dispatcher_args_->server_monitor->SvrCall(1, "Search", 1);

    int ret{-1};

    search::SearchRequest req_pb;
    search::SearchResult resp_pb;

    // unpack request
    {
        ret = req.ToPb(&req_pb);
        if (0 != ret) {
            phxrpc::log(LOG_ERR, "ToPb err %d", ret);

            return -EINVAL;
        }
    }

    // logic process
    {
        if (0 == ret) {
            ret = service_.Search(req_pb, &resp_pb);
        }
    }

    // pack response
    {
        if (0 != resp->FromPb(resp_pb)) {
            phxrpc::log(LOG_ERR, "FromPb err %d", ret);

            return -ENOMEM;
        }
    }

    phxrpc::log(LOG_DEBUG, "RETN: Search = %d", ret);

    return ret;
}

int SearchDispatcher::Notify(const phxrpc::BaseRequest &req, phxrpc::BaseResponse *const resp) {
    dispatcher_args_->server_monitor->SvrCall(2, "Notify", 1);

    int ret{-1};

    google::protobuf::StringValue req_pb;
    google::protobuf::Empty resp_pb;

    // unpack request
    {
        ret = req.ToPb(&req_pb);
        if (0 != ret) {
            phxrpc::log(LOG_ERR, "ToPb err %d", ret);

            return -EINVAL;
        }
    }

    // logic process
    {
        if (0 == ret) {
            ret = service_.Notify(req_pb, &resp_pb);
        }
    }

    phxrpc::log(LOG_DEBUG, "RETN: Notify = %d", ret);

    return ret;
}

