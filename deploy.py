import boto3

client = boto3.client("lambda")

image_uri = "131791614471.dkr.ecr.ap-southeast-1.amazonaws.com/test:test-v0"

lambda_functions = {
    "test": {"timeout": 60, "memory_size": 10240,},
}


def update_lambda_functions_image_uri():
    for function_name in lambda_functions:
        response = client.update_function_code(
            FunctionName=function_name, ImageUri=image_uri,
        )
        print(response)



if __name__ == "__main__":
    update_lambda_functions_image_uri()
