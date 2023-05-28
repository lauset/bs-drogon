#include <drogon/drogon.h>
#include "CatFilter.h"

using namespace drogon;

void CatFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb) {

    if (1) {
        fccb();
        return;
    }

    // Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k500InternalServerError);
    fcb(res);
}
