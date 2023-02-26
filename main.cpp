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
    std::cout << "Hello World!" << std::endl;
    std::cout << "DMTX Version" << DmtxVersion << std::endl;
    std::cout << "OPENCV Version" << CV_VERSION << std::endl;

    std::cout << "Test Numpy!" << std::endl;

    auto a = nc::random::randInt<int>({10, 10}, 0, 100);
    std::cout << a <<std::endl;

    std::cout << "PyTorch version: "
        << TORCH_VERSION_MAJOR << "."
        << TORCH_VERSION_MINOR << "."
        << TORCH_VERSION_PATCH << std::endl;

    auto v = json.View();
    Aws::SimpleStringStream ss;
    ss << "Good ";
    ss << v.GetString("time");

    JsonValue resp;
    resp.WithString("message", ss.str());

    return invocation_response::success(resp.View().WriteCompact(), "application/json");
}

int main()
{
    run_handler(my_handler);
    return 0;
}
