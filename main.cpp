#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include <torch/torch.h>
#include <dmtx.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <NumCpp.hpp>


using namespace aws::lambda_runtime;

invocation_response my_handler(invocation_request const& request)
{

    using namespace Aws::Utils::Json;

    JsonValue json(request.payload);
    if (!json.WasParseSuccessful()) {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }
    auto event_message = json.View().GetString("message");
    std::cout << event_message << std::endl;

    auto v = json.View();
    Aws::SimpleStringStream message;
    message << event_message;

    Aws::SimpleStringStream dmtxVersion;
    dmtxVersion << DmtxVersion;

    Aws::SimpleStringStream cvVersion;
    cvVersion << CV_VERSION;

    Aws::SimpleStringStream torchVersion;
    torchVersion << TORCH_VERSION_MAJOR << "." << TORCH_VERSION_MINOR << "." << TORCH_VERSION_PATCH;

    Aws::SimpleStringStream currentDate;
    currentDate << nc::DateTime::now().toStr();

    JsonValue resp;
    resp.WithString("message", message.str());
    resp.WithString("dmtx_version", dmtxVersion.str());
    resp.WithString("cv_version", cvVersion.str());
    resp.WithString("torch_version", torchVersion.str());
    resp.WithString("current_date", currentDate.str());

    return invocation_response::success(resp.View().WriteCompact(), "application/json");
}

int main()
{
    run_handler(my_handler);
    return 0;
}
