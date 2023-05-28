#include <drogon/drogon.h>

using namespace drogon;

class CatFilter : public drogon::HttpFilter<CatFilter> {
public:
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};